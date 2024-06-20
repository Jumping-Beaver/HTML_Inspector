#include <php.h>
#include "html_inspector.c"

static zend_class_entry *class_entry_html_inspector;
static zend_class_entry *class_entry_selector;

struct html_inspector_object {
    struct HtmlDocument *hi;
    zend_object std;
};

struct selector_object {
    struct Selector *s;
    zend_object std;
};

#define HTML_INSPECTOR(this) \
    ((struct html_inspector_object *) ((char *) Z_OBJ_P(this) - offsetof(struct html_inspector_object, std)))->hi

#define SELECTOR(this) \
    ((struct selector_object *) ((char *) Z_OBJ_P(this) - offsetof(struct selector_object, std)))->s

ZEND_METHOD(HtmlDocument, resolve_iri_to_uri)
{
    zend_string *reference;
    zend_string *base;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(reference)
        Z_PARAM_STR(base)
    ZEND_PARSE_PARAMETERS_END();

    struct String _base = {ZSTR_VAL(base), ZSTR_LEN(reference), false};
    struct String _reference = {ZSTR_VAL(base), ZSTR_LEN(reference), false};
    struct String uri = HtmlInspector_resolve_iri_to_uri(_reference, _base);
    ZVAL_STRINGL(return_value, uri.data, uri.length);
    string_free(uri);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_resolve_iri_to_uri, IS_STRING, false)
    ZEND_ARG_TYPE_INFO(0, reference, IS_STRING, false)
    ZEND_ARG_TYPE_INFO(0, base, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, entities_to_utf8)
{
    zend_string *html;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(html)
    ZEND_PARSE_PARAMETERS_END();

    struct String string = {ZSTR_VAL(html), ZSTR_LEN(html), false};
    HtmlDocument_entities_to_utf8(&string, false);
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_entities_to_utf8, IS_STRING, false)
    ZEND_ARG_TYPE_INFO(0, html, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, normalize_space)
{
    zend_string *html;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(html)
    ZEND_PARSE_PARAMETERS_END();

    struct String string = {ZSTR_VAL(html), ZSTR_LEN(html), false};
    HtmlDocument_normalize_space(&string);
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_normalize_space, IS_STRING, true)
    ZEND_ARG_TYPE_INFO(0, html, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, extract_charset)
{
    zend_string *html;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(html)
    ZEND_PARSE_PARAMETERS_END();

    struct String charset = HtmlDocument_extract_charset(ZSTR_VAL(html));
    if (charset.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, charset.data, charset.length);
    string_free(charset);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_extract_charset, IS_STRING, true)
    ZEND_ARG_TYPE_INFO(0, html, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, __construct)
{
    zend_string *html;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(html)
    ZEND_PARSE_PARAMETERS_END();
    HTML_INSPECTOR(ZEND_THIS) = HtmlDocument(ZSTR_VAL(html));
    if (HTML_INSPECTOR(ZEND_THIS) == NULL) {
        zend_throw_error(NULL, "malloc failed", 0);
    }
}
ZEND_BEGIN_ARG_INFO(arginfo___construct, 0)
    ZEND_ARG_TYPE_INFO(0, html, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, __destruct)
{
    ZEND_PARSE_PARAMETERS_NONE();
    HtmlDocument_free(HTML_INSPECTOR(ZEND_THIS));
}
ZEND_BEGIN_ARG_INFO(arginfo___destruct, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, iterate)
{
    ZEND_PARSE_PARAMETERS_NONE();
    ZVAL_LONG(return_value, Selector_iterate(SELECTOR(ZEND_THIS)));
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_iterate, IS_LONG, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, rewind)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_rewind(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_rewind, HtmlDocument, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, __destruct)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_free(SELECTOR(ZEND_THIS));
}
ZEND_BEGIN_ARG_INFO(arginfo_selector__destruct, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, nth)
{
    zend_long n;
    ZEND_PARSE_PARAMETERS_START(1, 1);
        Z_PARAM_LONG(n)
    ZEND_PARSE_PARAMETERS_END();
    Selector_nth(SELECTOR(ZEND_THIS), n);
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_nth, HtmlDocument, false)
    ZEND_ARG_TYPE_INFO(0, n, IS_LONG, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, name)
{
    zend_string *name;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(name)
    ZEND_PARSE_PARAMETERS_END();
    Selector_name(SELECTOR(ZEND_THIS), ZSTR_VAL(name));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_name, HtmlDocument, false)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, child)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_child(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_child, HtmlDocument, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, descendant)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_descendant(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_descendant, HtmlDocument, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, ancestor)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_ancestor(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_ancestor, HtmlDocument, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, preceding_sibling)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_preceding_sibling(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_preceding_sibling, HtmlDocument, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, following_sibling)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_following_sibling(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_following_sibling, HtmlDocument, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, attribute_exists)
{
    zend_string *name;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(name)
    ZEND_PARSE_PARAMETERS_END();
    Selector_attribute_exists(SELECTOR(ZEND_THIS), ZSTR_VAL(name));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_attribute_exists, HtmlDocument, false)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, attribute_equals)
{
    zend_string *name;
    zend_string *value;
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(name)
        Z_PARAM_STR(value)
    ZEND_PARSE_PARAMETERS_END();
    Selector_attribute_equals(SELECTOR(ZEND_THIS), ZSTR_VAL(name), ZSTR_VAL(value));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_attribute_equals, HtmlDocument, false)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, false)
    ZEND_ARG_TYPE_INFO(0, value, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, attribute_contains)
{
    zend_string *name;
    zend_string *value;
    ZEND_PARSE_PARAMETERS_START(2, 2);
        Z_PARAM_STR(name)
        Z_PARAM_STR(value)
    ZEND_PARSE_PARAMETERS_END();
    Selector_attribute_contains(SELECTOR(ZEND_THIS), ZSTR_VAL(name), ZSTR_VAL(value));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_attribute_contains, HtmlDocument, false)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, false)
    ZEND_ARG_TYPE_INFO(0, value, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, attribute_starts_with)
{
    zend_string *name;
    zend_string *value;
    ZEND_PARSE_PARAMETERS_START(2, 2);
        Z_PARAM_STR(name)
        Z_PARAM_STR(value)
    ZEND_PARSE_PARAMETERS_END();
    Selector_attribute_starts_with(SELECTOR(ZEND_THIS), ZSTR_VAL(name), ZSTR_VAL(value));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_attribute_starts_with, HtmlDocument, false)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, false)
    ZEND_ARG_TYPE_INFO(0, value, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, or)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_or(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_or, HtmlDocument, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, and)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_and(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_and, HtmlDocument, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, not)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_not(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_not, HtmlDocument, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, case_i)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_case_i(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_case_i, HtmlDocument, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, get_name)
{
    zend_long node;
    ZEND_PARSE_PARAMETERS_START(1, 1);
        Z_PARAM_LONG(node)
    ZEND_PARSE_PARAMETERS_END();
    struct String string = HtmlDocument_get_name(HTML_INSPECTOR(ZEND_THIS), node);
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_name, IS_STRING, true)
    ZEND_ARG_TYPE_INFO(0, node, IS_LONG, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, get_value)
{
    zend_long node;
    ZEND_PARSE_PARAMETERS_START(1, 1);
        Z_PARAM_LONG(node)
    ZEND_PARSE_PARAMETERS_END();
    struct String string = HtmlDocument_get_value(HTML_INSPECTOR(ZEND_THIS), node);
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_value, IS_STRING, true)
    ZEND_ARG_TYPE_INFO(0, node, IS_LONG, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, get_inner_html)
{
    zend_long node;
    ZEND_PARSE_PARAMETERS_START(1, 1);
        Z_PARAM_LONG(node)
    ZEND_PARSE_PARAMETERS_END();
    struct String string = HtmlDocument_get_inner_html(HTML_INSPECTOR(ZEND_THIS), node);
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_inner_html, IS_STRING, true)
    ZEND_ARG_TYPE_INFO(0, node, IS_LONG, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, get_outer_html)
{
    zend_long node;
    ZEND_PARSE_PARAMETERS_START(1, 1);
        Z_PARAM_LONG(node)
    ZEND_PARSE_PARAMETERS_END();
    struct String string = HtmlDocument_get_outer_html(HTML_INSPECTOR(ZEND_THIS), node);
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_outer_html, IS_STRING, true)
    ZEND_ARG_TYPE_INFO(0, node, IS_LONG, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, get_attribute)
{
    zend_long node;
    zend_string *attribute;
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(node)
        Z_PARAM_STR(attribute)
    ZEND_PARSE_PARAMETERS_END();
    struct String string = HtmlDocument_get_attribute(HTML_INSPECTOR(ZEND_THIS), node, ZSTR_VAL(attribute));
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_attribute, IS_STRING, true)
    ZEND_ARG_TYPE_INFO(0, node, IS_LONG, false)
    ZEND_ARG_TYPE_INFO(0, attribute, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, select)
{
    zend_long node;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(node)
    ZEND_PARSE_PARAMETERS_END();
    struct Selector *s = HtmlDocument_select(HTML_INSPECTOR(ZEND_THIS), node);
    if (s == NULL) {
        zend_throw_error(NULL, "malloc failed", 0);
        return;
    }
    ZVAL_OBJ(return_value, zend_objects_new(class_entry_selector));
    SELECTOR(return_value) = s;
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_select, Selector, false)
    ZEND_ARG_TYPE_INFO(0, node, IS_LONG, false)
ZEND_END_ARG_INFO()

/******************************************************************************/

zend_object_handlers object_handlers_html_inspector, object_handlers_selector;

static zend_object * create_object_html_inspector(zend_class_entry *ce)
{
    struct html_inspector_object *this = zend_object_alloc(sizeof (struct html_inspector_object), ce);
    zend_object_std_init(&this->std, ce);
    this->std.handlers = &object_handlers_html_inspector;
    return &this->std;
}

static zend_object * create_object_selector(zend_class_entry *ce)
{
    struct selector_object *this = zend_object_alloc(sizeof (struct selector_object), ce);
    zend_object_std_init(&this->std, ce);
    this->std.handlers = &object_handlers_selector;
    return &this->std;
}

zend_function_entry functions_HtmlDocument[] = {
    ZEND_ME(HtmlDocument, resolve_iri_to_uri, arginfo_resolve_iri_to_uri, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    ZEND_ME(HtmlDocument, entities_to_utf8, arginfo_entities_to_utf8, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    ZEND_ME(HtmlDocument, extract_charset, arginfo_extract_charset, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    ZEND_ME(HtmlDocument, normalize_space, arginfo_normalize_space, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    ZEND_ME(HtmlDocument, __construct, arginfo___construct, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, __destruct, arginfo___destruct, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, get_inner_html, arginfo_get_inner_html, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, get_outer_html, arginfo_get_outer_html, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, get_name, arginfo_get_name, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, get_value, arginfo_get_value, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, get_attribute, arginfo_get_attribute, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, select, arginfo_select, ZEND_ACC_PUBLIC)
    ZEND_FE_END
};

zend_function_entry functions_Selector[] = {
    ZEND_ME(Selector, __destruct, arginfo_selector__destruct, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, nth, arginfo_nth, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, name, arginfo_name, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, child, arginfo_child, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, rewind, arginfo_rewind, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, iterate, arginfo_iterate, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, ancestor, arginfo_ancestor, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, descendant, arginfo_descendant, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, preceding_sibling, arginfo_preceding_sibling, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, following_sibling, arginfo_following_sibling, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, attribute_exists, arginfo_attribute_exists, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, attribute_equals, arginfo_attribute_equals, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, attribute_contains, arginfo_attribute_contains, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, attribute_starts_with, arginfo_attribute_starts_with, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, or, arginfo_or, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, and, arginfo_and, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, not, arginfo_not, ZEND_ACC_PUBLIC)
    ZEND_ME(Selector, case_i, arginfo_case_i, ZEND_ACC_PUBLIC)
    ZEND_FE_END
};

PHP_MINIT_FUNCTION(html_inspector_minit)
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "HtmlDocument", functions_HtmlDocument);
    class_entry_html_inspector = zend_register_internal_class(&ce);
    class_entry_html_inspector->create_object = create_object_html_inspector;
    memcpy(&object_handlers_html_inspector, &std_object_handlers, sizeof (zend_object_handlers));
    object_handlers_html_inspector.offset = offsetof(struct html_inspector_object, std);

    INIT_CLASS_ENTRY(ce, "Selector", functions_Selector);
    class_entry_selector = zend_register_internal_class(&ce);
    class_entry_selector->create_object = create_object_selector;
    memcpy(&object_handlers_selector, &std_object_handlers, sizeof (zend_object_handlers));
    object_handlers_selector.offset = offsetof(struct selector_object, std);

    return SUCCESS;
}

zend_module_entry html_inspector_module_entry = {
    STANDARD_MODULE_HEADER,
    "html-inspector",
    NULL,
    PHP_MINIT(html_inspector_minit),
    NULL,
    NULL,
    NULL,
    NULL,
    "1.0.0",
    STANDARD_MODULE_PROPERTIES
};

// This macro appends `_module_entry` to its argument. This is obscure & bad design.
ZEND_GET_MODULE(html_inspector)
