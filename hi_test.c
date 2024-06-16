#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "html_inspector.c"

void HtmlInspector_dump(struct HtmlInspector *hi)
{
    struct Node *node = &hi->doc->nodes[0];
    while (node < &hi->doc->nodes[hi->doc->node_count]) {
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
            node->name_length, node->name_start
        );
        struct Attribute *attribute = &hi->doc->attributes[node->attributes_start];
        while (attribute < &hi->doc->attributes[node->attributes_start + node->attributes_count]) {
            printf(
                ", %.*s=%.*s",
                attribute->name_length, attribute->name_start,
                attribute->value_length, attribute->value_start
            );
            attribute += 1;
        }
        putc('\n', stdout);
        node += 1;
    }
}
void HtmlInspector_print_stats(struct HtmlInspector *hi)
{
    int attributes_count = 0;
    int max_nesting_level = 0;
    for (int i = 0; i < hi->doc->node_count; ++i) {
        attributes_count += hi->doc->nodes[i].attributes_count;
        if (hi->doc->nodes[i].nesting_level > max_nesting_level) {
            max_nesting_level = hi->doc->nodes[i].nesting_level;
        }
    }
    int memory = hi->doc->node_count * sizeof (struct Node) + attributes_count * sizeof (struct Attribute);
    printf("Maximum nesting level: %d\n", max_nesting_level);
    printf("Number of nodes: %d\n", hi->doc->node_count);
    printf("Number of attributes: %d\n", attributes_count);
    printf("Number of attributes / number of nodes: %.2f\n", (float) attributes_count / hi->doc->node_count);
    printf("Input length: %zu bytes\n", strlen(hi->doc->html));
    printf("Input length / number of nodes: %.2f\n", (float) strlen(hi->doc->html) / hi->doc->node_count);
    printf("Size of data structures: %d bytes\n", memory);
}

char *
read_test_file()
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

void test_dump()
{
    unsigned char html[] = "text <ul><li>eins<li>zwei<li>drei</ul>";
    struct HtmlInspector *hi = HtmlInspector(html);
    if (hi == NULL) {
        return;
    }
    HtmlInspector_dump(hi);
    return;
}

void test_charset()
{
    unsigned char html[] = "<meta content = 'text/html; charset=&quot;iso-8859-1\"' http-equiv='CONtent-typ&#69;'>";
    struct String charset = HtmlInspector_extract_charset(html);
    if (charset.data == NULL) {
        printf("The document has no meta charset\n");
        return;
    }
    printf("Charset: %.*s\n", charset.length, charset.data);
}

void benchmark_loading()
{
    char *html = read_test_file();
    int i;
    struct timespec start, end;
    struct HtmlInspector *hi;
    hi = HtmlInspector(html);
    HtmlInspector_print_stats(hi);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for (i = 0; i < 200; ++i) {
        hi = HtmlInspector(html);
        if (hi == NULL) {
            continue;
        }
        HtmlInspector_free(hi);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    long elapsed_nsec = (end.tv_sec - start.tv_sec) * 1e+9 + (end.tv_nsec - start.tv_nsec);
    printf("Time: %f per second\n", 1e+9 * i / elapsed_nsec);
}

void benchmark_resolve_url()
{
    struct String base = STRING("https://www.example.org:443/b/c/d;p?q");
    struct String reference = STRING("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    struct timespec start, end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    int i;
    for (i = 0; i < 500000; ++i) {
        struct String target = HtmlInspector_resolve_iri_to_uri(reference, base);
        string_free(target);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    long elapsed_nsec = (end.tv_sec - start.tv_sec) * 1e+9 + (end.tv_nsec - start.tv_nsec);
    printf("Time: %f per second\n", 1e+9 * i / elapsed_nsec);
}

void test_url_join()
{
    // TODO: Rename string to charseq?
    struct String base = STRING("http://a/b/c/d;p?q");
    struct {
        struct String base;
        struct String relative;
        struct String target;
    } test_cases[] = {
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

        // Subseqent test cases are from here: https://www.rfc-editor.org/rfc/rfc3986#section-5.4.1

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
        struct String target = HtmlInspector_resolve_iri_to_uri(test_cases[i].relative, test_cases[i].base);
        if (target.length != test_cases[i].target.length ||
            strncmp(target.data, test_cases[i].target.data, target.length))
        {
            printf("%.*s != %.*s\n", target.length, target.data,
                    test_cases[i].target.length, test_cases[i].target.data);
        }
        string_free(target);
    }
}

void test_entities_to_utf8()
{
    char cstring[] =
        "&auml;sdluifaiuocvbfgqoiwcuhfqnoifueoiuhnqoiefquhefo &quot; &alpha; "
        "&beta; &gamma; &delta; [&#x3a9;]</stray>u&invalid;entity";
    for (int i = 0; i < 100000; ++i) {
        struct String string = STRING(cstring);
        HtmlInspector_entities_to_utf8(&string, true);
        string_free(string);
    }
    struct String string = STRING(cstring);
    HtmlInspector_entities_to_utf8(&string, true);
    printf("%.*s", string.length, string.data);
    string_free(string);
}

void test_normalize_space()
{
    struct String string = STRING("    asldkfas\n\nl  \r  dk→ø↓ſ€¶fjöasldfjö a         ");
    HtmlInspector_normalize_space(&string);
    printf("%.*s", string.length, string.data);
    string_free(string);
}

void test_get_hrefs()
{
    char *html = read_test_file();
    struct HtmlInspector *hi = HtmlInspector(html);
    HtmlInspector_descendant(hi);
    HtmlInspector_name(hi, "a");
    HtmlInspector_attribute_equals(hi, "href", "#");
    HtmlInspector_not(hi);
    HtmlInspector_attribute_starts_with(hi, "href", "javascript:");
    HtmlInspector_not(hi);
    int count = 0;
    while (HtmlInspector_iterate(hi)) {
        struct String href = HtmlInspector_get_attribute(hi, "href");
        struct String uri = href;// HtmlInspector_resolve_iri_to_uri(href, STRING("http://example.org"));
        //struct String href = HtmlInspector_get_name(hi);
        printf("%.*s\n", uri.length, uri.data);
        string_free(href);
        count += 1;
        //string_free(uri);
    }
    printf("Extracted %d links\n", count);
    HtmlInspector_free(hi);
    free(html);
}

void test_outer_html()
{
    // TODO: Insert empty head or not?
    struct {
        const char *input;
        const char *outer_html;
    } test_cases[] = {
        {"<p>p<div>div</div></p>", "<html><head></head><body><p>p</p><div>div</div></body></html>"},
        {"<head>a</head>", "<html><head></head><body>a</body></html>"},
        {"<head><meta><body>", "<html><head><meta></head><body></body></html>"},
        {"<HTML LANG=en><META></HTML>", "<html lang=\"en\"><head><meta></head></html>"},
        {"<table><tr><td>a", "<html><head></head><body><table><tbody><tr><td>a</td></tr></tbody></table></body></html>"},
        {"<body a='<>&quot;'>&auml;&gt;&lt;&quot;&z", "<html><head></head><body a=\"<>&quot;\">ä&gt;&lt;\"&amp;z</body></html>"},
        {"b</stray>c", "<html><body>bc</body></html>"},
        {" <!--a-->b", "<!--a--><html><body>b</body></html>"},
        {"<script><a>&auml;", "<html><head><script><a>&auml;</script></head></html>"},
        {"<title>a", "<html><head><title>a</title></head></html>"},
        {"<head>a<body>b", "<html><head></head><body>ab</body></html>"}, // TODO We get 2 text nodes here
    };
    for (int i = 0; i < sizeof test_cases / sizeof *test_cases; ++i) {
        struct HtmlInspector *hi = HtmlInspector(test_cases[i].input);
        if (hi == NULL) {
            printf("OOM\n");
            continue;
        }
        struct String outer_html = HtmlInspector_get_outer_html(hi);
        if (strncmp(test_cases[i].outer_html, outer_html.data, outer_html.length)) {
            printf("Input: %s\nExpected output:\n%s\nActual output:\n%.*s\n\n",
                   test_cases[i].input, test_cases[i].outer_html, outer_html.length, outer_html.data);
            HtmlInspector_dump(hi);
        }
        HtmlInspector_free(hi);
    }
}

int main()
{
    /*struct HtmlInspector *hi = HtmlInspector("<html><body><b>a</b></body></html>");
    HtmlInspector_child(hi);
    HtmlInspector_nth(hi, 1);
    HtmlInspector_child(hi);
    HtmlInspector_nth(hi, 2);
    while (HtmlInspector_iterate(hi)) {
        struct String name = HtmlInspector_get_name(hi);
        printf("%.*s\n", name.length, name.data);
        string_free(name);
    }
    */
    //test_outer_html();
    benchmark_loading();
    //benchmark_resolve_url();
    //test_url_join();
    //test_entities_to_utf8();
    //test_attribute();
    //test_get_hrefs();
    //test_normalize_space();
    return 0;
}
