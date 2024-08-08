#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "html_inspector.c"

static void HtmlDocument_dump(struct HtmlDocument *doc)
{
    struct Node *node = doc->nodes;
    while (node < &doc->nodes[doc->node_count]) {
        for (int k = 0; k < node->nesting_level; ++k) {
            putc(' ', stdout);
        }
        printf(
            "type: %s, name: %.*s",
            node->type == NODE_TYPE_DOCUMENT ? "document" :
            node->type == NODE_TYPE_UNCLOSED_ELEMENT ? "unclosed_element" :
            node->type == NODE_TYPE_VOID_ELEMENT ? "void_element" :
            node->type == NODE_TYPE_NONVOID_ELEMENT ? "non-void_element" :
            node->type == NODE_TYPE_DOCTYPE ? "doctype" :
            node->type == NODE_TYPE_COMMENT ? "comment" :
            node->type == NODE_TYPE_CDATA ? "cdata" :
            node->type == NODE_TYPE_TEXT ? "text" : "?",
            (int) node->content_length, node->content
        );
        struct Attribute *attribute = &doc->attributes[node->attributes];
        while (attribute < &doc->attributes[node->attributes + node->attributes_count]) {
            printf(
                ", %.*s=%.*s",
                (int) attribute->name_length, attribute->name,
                (int) attribute->value_length, attribute->value
            );
            attribute += 1;
        }
        putc('\n', stdout);
        node += 1;
    }
}

static void HtmlDocument_print_stats(struct HtmlDocument *doc)
{
    int attributes_count = 0;
    int max_nesting_level = 0;
    for (int i = 0; i < doc->node_count; ++i) {
        attributes_count += doc->nodes[i].attributes_count;
        if (doc->nodes[i].nesting_level > max_nesting_level) {
            max_nesting_level = doc->nodes[i].nesting_level;
        }
    }
    int memory = doc->node_count * sizeof (struct Node) + attributes_count * sizeof (struct Attribute);
    printf("Maximum nesting level: %d\n", max_nesting_level);
    printf("Number of nodes: %zu\n", doc->node_count);
    printf("Number of attributes: %d\n", attributes_count);
    printf("Number of attributes / number of nodes: %.2f\n", (float) attributes_count / doc->node_count);
    printf("Input length: %zu bytes\n", strlen(doc->html));
    printf("Input length / number of nodes: %.2f\n", (float) strlen(doc->html) / doc->node_count);
    printf("Size of data structures: %d bytes\n", memory);
}

static char * read_test_file()
{
    FILE *file = fopen("test-html.html", "r");
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    char *html = malloc(file_size);
    fread(html, sizeof (char), file_size, file);
    fclose(file);
    return html;
}

static void test_extract_charset()
{
    char html[] = "<meta content = 'text/html; charset=&quot;iso-8859-1\"' http-equiv='CONtent-typ&#69;'>";
    struct String charset = HtmlDocument_extract_charset(html);
    if (charset.data == NULL) {
        printf("The document has no meta charset\n");
        return;
    }
    printf("Charset: %.*s\n", (int) charset.length, charset.data);
}

static void benchmark()
{
    const char *html = read_test_file();
    struct timespec start, end;
    struct HtmlDocument *doc;
    doc = HtmlDocument(html, strlen(html));
    HtmlDocument_print_stats(doc);
    //HtmlDocument_dump(doc); return;
    //puts(HtmlDocument_get_outer_html(doc, 0, false).data);
    //return;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    int_fast8_t i;
    for (i = 0; i < 20; ++i) {
        String_free(HtmlDocument_get_outer_html(doc, 0));
    }
    HtmlDocument_free(doc);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    long elapsed_nsec = (end.tv_sec - start.tv_sec) * 1e+9 + (end.tv_nsec - start.tv_nsec);
    printf("Time: %f per second\n", 1e+9 * i / elapsed_nsec);
}

static void test_resolve_iri()
{
    struct String base = STRING("http://a/b/c/d;p?q");
    struct {
        struct String base;
        struct String relative;
        struct String target;
    } test_cases[] = {
        {STRING("http://host:"), STRING(""), STRING("http://host/")},
        {STRING("http://datenbörse.net"), STRING(""), STRING("http://xn--datenbrse-57a.net/")},
        {STRING("/%p%p"), STRING(""), STRING("/%p%p")},
        {base, base, base}, // Asserting that there is no endless loop if `reference == base`
        {NULL_STRING, STRING("http://a/b"), STRING("http://a/b")},
        {STRING(""), STRING("http://a/→"), STRING("http://a/%E2%86%92")},
        {STRING("http://a?f"), STRING("p"), STRING("http://a/p")},
        {STRING("http://a/?b?c#b#c"), STRING("?e?f#e#f"), STRING("http://a/?e?f#e#f")},
        {STRING(""), STRING("HTTP://A/%61%62%63/%25"), STRING("http://a/abc/%25")},

        {STRING(""), STRING("HTTP://A"), STRING("http://a/")},
        {STRING(""), STRING("HTTP://A:080"), STRING("http://a/")},
        {STRING(""), STRING("HTTP://A:081"), STRING("http://a:81/")},
        {STRING(""), STRING("HTTPS://A:0443"), STRING("https://a/")},
        {STRING(""), STRING("HTTPS://A:0444"), STRING("https://a:444/")},

        //{STRING(""), STRING("hTTp://uSEr:pASSWOrd@aAJDOIJsde/ooob/1c2/u/u/..?abcdef#1234"), STRING("http://a/")},

        // Subsequent test cases are from here: https://www.rfc-editor.org/rfc/rfc3986#section-5.4.1

        {base, STRING("g:h"), STRING("g:h")},
        {base, STRING("g"), STRING("http://a/b/c/g")},
        {base, STRING("./g"), STRING("http://a/b/c/g")},
        {base, STRING("g/"), STRING("http://a/b/c/g/")},
        {base, STRING("/g"), STRING("http://a/g")},
        {base, STRING("//g"), STRING("http://g/")},  // I appended `/` compared to the RFC
        {base, STRING("?y"), STRING("http://a/b/c/d;p?y")},
        {base, STRING("g?y"), STRING("http://a/b/c/g?y")},
        {base, STRING("#s"), STRING("http://a/b/c/d;p?q#s")},
        {base, STRING("g#s"), STRING("http://a/b/c/g#s")},
        {base, STRING("g?y#s"), STRING("http://a/b/c/g?y#s")},
        {base, STRING(";x"), STRING("http://a/b/c/;x")},
        {base, STRING("g;x"), STRING("http://a/b/c/g;x")},
        {base, STRING("g;x?y#s"), STRING("http://a/b/c/g;x?y#s")},
        {base, STRING(""), STRING("http://a/b/c/d;p?q")},
        {base, STRING("."), STRING("http://a/b/c/")},
        {base, STRING("./"), STRING("http://a/b/c/")},
        {base, STRING(".."), STRING("http://a/b/")},
        {base, STRING("../"), STRING("http://a/b/")},
        {base, STRING("../g"), STRING("http://a/b/g")},
        {base, STRING("../.."), STRING("http://a/")},
        {base, STRING("../../"), STRING("http://a/")},
        {base, STRING("../../g"), STRING("http://a/g")},
        {base, STRING("../../../g"), STRING("http://a/g")},
        {base, STRING("../../../../g"), STRING("http://a/g")},
        {base, STRING("/./g"), STRING("http://a/g")},
        {base, STRING("/../g"), STRING("http://a/g")},
        {base, STRING("g."), STRING("http://a/b/c/g.")},
        {base, STRING(".g"), STRING("http://a/b/c/.g")},
        {base, STRING("g.."), STRING("http://a/b/c/g..")},
        {base, STRING("..g"), STRING("http://a/b/c/..g")},
        {base, STRING("./../g"), STRING("http://a/b/g")},
        {base, STRING("./g/."), STRING("http://a/b/c/g/")},
        {base, STRING("g/./h"), STRING("http://a/b/c/g/h")},
        {base, STRING("g/../h"), STRING("http://a/b/c/h")},
        {base, STRING("g;x=1/./y"), STRING("http://a/b/c/g;x=1/y")},
        {base, STRING("g;x=1/../y"), STRING("http://a/b/c/y")},
        {base, STRING("g?y/./x"), STRING("http://a/b/c/g?y/./x")},
        {base, STRING("g?y/../x"), STRING("http://a/b/c/g?y/../x")},
        {base, STRING("g#s/./x"), STRING("http://a/b/c/g#s/./x")},
        {base, STRING("g#s/../x"), STRING("http://a/b/c/g#s/../x")},
    };
    for (int i = 0; i < sizeof test_cases / sizeof *test_cases; ++i) {
        struct String target = resolve_iri(test_cases[i].relative, test_cases[i].base);
        if (target.length != test_cases[i].target.length ||
            strncmp(target.data, test_cases[i].target.data, target.length))
        {
            printf("%.*s != %.*s\n", (int) target.length, target.data,
                   (int) test_cases[i].target.length, test_cases[i].target.data);
        }
        String_free(target);
    }
}

static void test_outer_html()
{
    struct {
        const char *input;
        const char *outer_html;
    } test_cases[] = {
        {"<<b>", "<html><head></head><body>&lt;<b></b></body></html>"},
        {"<!comment>text-->", "<!--comment--><html><head></head><body>text--&gt;</body></html>"},
        {"<42></42>", "<html><head></head><body>&lt;42&gt;<!--42--></body></html>"},
        {"<body id=>", "<html><head></head><body id=\"\"></body></html>"},
        {"<ul><li>1<li><ul><li>2</ul></ul>", "<html><head></head><body><ul><li>1</li><li><ul><li>2</li></ul></li></ul></body></html>"},
        {"<body a='<>&quot;'>&auml;&gt;&lt;&quot;&z", "<html><head></head><body a=\"<>&quot;\">ä&gt;&lt;\"&amp;z</body></html>"},
        {"<HTML LANG=en><META></HTML>", "<html lang=\"en\"><head><meta></head></html>"},
        {"<!----><title>t", "<!----><html><head><title>t</title></head></html>"},
        {"<html><!--&uuml;--></html>", "<html><!--&uuml;--></html>"},
        {"<html><head>a</head><body></body></html>", "<html><head></head><body>a</body></html>"},
        {"<head>a</head><body></body>", "<html><head></head><body>a</body></html>"},
        {"<head>a<body>b", "<html><head></head><body>ab</body></html>"},
        {"<body>a<body b=c>", "<html><head></head><body b=\"c\">a</body></html>"},
        {"<head>a</head>", "<html><head></head><body>a</body></html>"},
        {"<head><meta><body>", "<html><head><meta></head><body></body></html>"},
        {"<p>p<div>div</div></p>", "<html><head></head><body><p>p</p><div>div</div></body></html>"},
        {"<table><tr><td>a", "<html><head></head><body><table><tbody><tr><td>a</td></tr></tbody></table></body></html>"},
        {"b</stray>c", "<html><head></head><body>bc</body></html>"},
        {" <!--a-->b", "<!--a--><html><head></head><body>b</body></html>"},
        {"<script><a>&auml;", "<html><head><script><a>&auml;</script></head></html>"},
        {"<title>a", "<html><head><title>a</title></head></html>"},
    };
    for (size_t i = 0; i < sizeof test_cases / sizeof *test_cases; ++i) {
        struct HtmlDocument *doc = HtmlDocument(test_cases[i].input, strlen(test_cases[i].input));
        if (doc == NULL) {
            printf("OOM\n");
            continue;
        }
        struct String outer_html = HtmlDocument_get_outer_html(doc, 0);
        if (strncmp(test_cases[i].outer_html, outer_html.data, outer_html.length)) {
            printf("Input: %s\nExpected output:\n%s\nActual output:\n%.*s\n\n",
                   test_cases[i].input, test_cases[i].outer_html, (int) outer_html.length, outer_html.data);
            HtmlDocument_dump(doc);
        }
        HtmlDocument_free(doc);
    }
}

int main()
{
    test_outer_html();
    test_resolve_iri();
    //benchmark();
    //test_extract_charset();
    return 0;
}
