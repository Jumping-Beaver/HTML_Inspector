#include <php.h>
#include "html_inspector.c"

static zend_class_entry *class_entry_html_inspector;

struct html_inspector_object {
    struct HtmlInspector *hi;
    zend_object std;
};

#define HTML_INSPECTOR(this) \
    ((struct html_inspector_object *) ((char *) Z_OBJ_P(this) - offsetof(struct html_inspector_object, std)))->hi

ZEND_METHOD(HtmlInspector, resolve_iri_to_uri)
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

ZEND_METHOD(HtmlInspector, entities_to_utf8)
{
    zend_string *html;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(html)
    ZEND_PARSE_PARAMETERS_END();

    struct String string = {ZSTR_VAL(html), ZSTR_LEN(html), false};
    HtmlInspector_entities_to_utf8(&string, false);
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_entities_to_utf8, IS_STRING, false)
    ZEND_ARG_TYPE_INFO(0, html, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, normalize_space)
{
    zend_string *html;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(html)
    ZEND_PARSE_PARAMETERS_END();

    struct String string = {ZSTR_VAL(html), ZSTR_LEN(html), false};
    HtmlInspector_normalize_space(&string);
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_normalize_space, IS_STRING, true)
    ZEND_ARG_TYPE_INFO(0, html, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, extract_charset)
{
    zend_string *html;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(html)
    ZEND_PARSE_PARAMETERS_END();

    struct String charset = HtmlInspector_extract_charset(ZSTR_VAL(html));
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

ZEND_METHOD(HtmlInspector, __construct)
{
    zend_string *html;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(html)
    ZEND_PARSE_PARAMETERS_END();
    HTML_INSPECTOR(ZEND_THIS) = HtmlInspector(ZSTR_VAL(html));
    if (HTML_INSPECTOR(ZEND_THIS) == NULL) {
        zend_throw_error(NULL, "malloc failed", 0);
    }
}
ZEND_BEGIN_ARG_INFO(arginfo___construct, 0)
    ZEND_ARG_TYPE_INFO(0, html, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, __destruct)
{
    ZEND_PARSE_PARAMETERS_NONE();
    //HtmlInspector_free(HTML_INSPECTOR(ZEND_THIS));
}
ZEND_BEGIN_ARG_INFO(arginfo___destruct, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, fork)
{
    /*ZEND_PARSE_PARAMETERS_NONE();
    struct HtmlInspector *hi = HtmlInspector("HTML_INSPECTOR(ZEND_THIS)");
    if (hi == NULL) {
        zend_throw_error(NULL, "malloc failed", 0);
        return;
    }
	struct html_inspector_object *intern = ecalloc(1, sizeof(struct html_inspector_object) + zend_object_properties_size(class_entry_html_inspector));
	intern->hi = hi;

	zend_object_std_init(&intern->std, class_entry_html_inspector);
	object_properties_init(&intern->std, class_entry_html_inspector);

    ZVAL_OBJ(return_value, &intern->std);
    */

    ZEND_PARSE_PARAMETERS_NONE();
    struct HtmlInspector *hi = HtmlInspector_fork(HTML_INSPECTOR(ZEND_THIS));
    if (hi == NULL) {
        zend_throw_error(NULL, "malloc failed", 0);
        return;
    }
    ZVAL_OBJ_COPY(return_value, zend_objects_new(class_entry_html_inspector));
    HTML_INSPECTOR(return_value) = hi;
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_fork, HtmlInspector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, reset)
{
    ZEND_PARSE_PARAMETERS_NONE();
    HtmlInspector_reset(HTML_INSPECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_reset, HtmlInspector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, iterate)
{
    ZEND_PARSE_PARAMETERS_NONE();
    ZVAL_BOOL(return_value, HtmlInspector_iterate(HTML_INSPECTOR(ZEND_THIS)));
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_iterate, _IS_BOOL, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, rewind)
{
    ZEND_PARSE_PARAMETERS_NONE();
    HtmlInspector_rewind(HTML_INSPECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_rewind, HtmlInspector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, nth)
{
    zend_long n;
    ZEND_PARSE_PARAMETERS_START(1, 1);
        Z_PARAM_LONG(n)
    ZEND_PARSE_PARAMETERS_END();
    HtmlInspector_nth(HTML_INSPECTOR(ZEND_THIS), n);
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_nth, HtmlInspector, false)
    ZEND_ARG_TYPE_INFO(0, n, IS_LONG, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, child)
{
    ZEND_PARSE_PARAMETERS_NONE();
    HtmlInspector_child(HTML_INSPECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_child, HtmlInspector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, descendant)
{
    ZEND_PARSE_PARAMETERS_NONE();
    HtmlInspector_descendant(HTML_INSPECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_descendant, HtmlInspector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, ancestor)
{
    ZEND_PARSE_PARAMETERS_NONE();
    HtmlInspector_ancestor(HTML_INSPECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_ancestor, HtmlInspector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, preceding_sibling)
{
    ZEND_PARSE_PARAMETERS_NONE();
    HtmlInspector_preceding_sibling(HTML_INSPECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_preceding_sibling, HtmlInspector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, following_sibling)
{
    ZEND_PARSE_PARAMETERS_NONE();
    HtmlInspector_following_sibling(HTML_INSPECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_following_sibling, HtmlInspector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, name)
{
    zend_string *name;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(name)
    ZEND_PARSE_PARAMETERS_END();
    HtmlInspector_name(HTML_INSPECTOR(ZEND_THIS), ZSTR_VAL(name));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_name, HtmlInspector, false)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, attribute_exists)
{
    zend_string *name;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(name)
    ZEND_PARSE_PARAMETERS_END();
    HtmlInspector_attribute_exists(HTML_INSPECTOR(ZEND_THIS), ZSTR_VAL(name));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_attribute_exists, HtmlInspector, false)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, attribute_equals)
{
    zend_string *name;
    zend_string *value;
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(name)
        Z_PARAM_STR(value)
    ZEND_PARSE_PARAMETERS_END();
    HtmlInspector_attribute_equals(HTML_INSPECTOR(ZEND_THIS), ZSTR_VAL(name), ZSTR_VAL(value));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_attribute_equals, HtmlInspector, false)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, false)
    ZEND_ARG_TYPE_INFO(0, value, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, attribute_contains)
{
    zend_string *name;
    zend_string *value;
    ZEND_PARSE_PARAMETERS_START(2, 2);
        Z_PARAM_STR(name)
        Z_PARAM_STR(value)
    ZEND_PARSE_PARAMETERS_END();
    HtmlInspector_attribute_contains(HTML_INSPECTOR(ZEND_THIS), ZSTR_VAL(name), ZSTR_VAL(value));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_attribute_contains, HtmlInspector, false)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, false)
    ZEND_ARG_TYPE_INFO(0, value, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, attribute_starts_with)
{
    zend_string *name;
    zend_string *value;
    ZEND_PARSE_PARAMETERS_START(2, 2);
        Z_PARAM_STR(name)
        Z_PARAM_STR(value)
    ZEND_PARSE_PARAMETERS_END();
    HtmlInspector_attribute_starts_with(HTML_INSPECTOR(ZEND_THIS), ZSTR_VAL(name), ZSTR_VAL(value));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_attribute_starts_with, HtmlInspector, false)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, false)
    ZEND_ARG_TYPE_INFO(0, value, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, or)
{
    ZEND_PARSE_PARAMETERS_NONE();
    HtmlInspector_or(HTML_INSPECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_or, HtmlInspector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, and)
{
    ZEND_PARSE_PARAMETERS_NONE();
    HtmlInspector_and(HTML_INSPECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_and, HtmlInspector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, not)
{
    ZEND_PARSE_PARAMETERS_NONE();
    HtmlInspector_not(HTML_INSPECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_not, HtmlInspector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, case_i)
{
    ZEND_PARSE_PARAMETERS_NONE();
    HtmlInspector_case_i(HTML_INSPECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_case_i, HtmlInspector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, get_name)
{
    ZEND_PARSE_PARAMETERS_NONE();
    struct HtmlInspector *hi = HTML_INSPECTOR(ZEND_THIS);
    struct String string = HtmlInspector_get_name(hi);
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_name, IS_STRING, true)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, get_value)
{
    ZEND_PARSE_PARAMETERS_NONE();
    struct String string = HtmlInspector_get_value(HTML_INSPECTOR(ZEND_THIS));
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_value, IS_STRING, true)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, get_inner_html)
{
    ZEND_PARSE_PARAMETERS_NONE();
    struct String string = HtmlInspector_get_inner_html(HTML_INSPECTOR(ZEND_THIS));
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_inner_html, IS_STRING, true)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, get_outer_html)
{
    ZEND_PARSE_PARAMETERS_NONE();
    struct String string = HtmlInspector_get_outer_html(HTML_INSPECTOR(ZEND_THIS));
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_outer_html, IS_STRING, true)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, get_attribute)
{
    zend_string *attribute;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(attribute)
    ZEND_PARSE_PARAMETERS_END();
    struct String string = HtmlInspector_get_attribute(HTML_INSPECTOR(ZEND_THIS), ZSTR_VAL(attribute));
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    string_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_attribute, IS_STRING, true)
    ZEND_ARG_TYPE_INFO(0, attribute, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, get_offset)
{
    ZEND_PARSE_PARAMETERS_NONE();
    ZVAL_LONG(return_value, HtmlInspector_get_offset(HTML_INSPECTOR(ZEND_THIS)));
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_offset, IS_LONG, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, get_index)
{
    ZEND_PARSE_PARAMETERS_NONE();
    ZVAL_LONG(return_value, HtmlInspector_get_index(HTML_INSPECTOR(ZEND_THIS)));
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_index, IS_LONG, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlInspector, set_index)
{
    zend_long index;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(index)
    ZEND_PARSE_PARAMETERS_END();
    HtmlInspector_set_index(HTML_INSPECTOR(ZEND_THIS), index);
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_set_index, IS_VOID, false)
    ZEND_ARG_TYPE_INFO(0, attribute, IS_LONG, false)
ZEND_END_ARG_INFO()

/******************************************************************************/

zend_object_handlers object_handlers;

static zend_object *
create_object_html_inspector(zend_class_entry *ce)
{
    struct html_inspector_object *this = zend_object_alloc(sizeof (struct html_inspector_object), ce);
    zend_object_std_init(&this->std, ce);
    this->std.handlers = &object_handlers;
    return &this->std;
}

zend_function_entry functions_HtmlInspector[] = {
    ZEND_ME(HtmlInspector, resolve_iri_to_uri, arginfo_resolve_iri_to_uri, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    ZEND_ME(HtmlInspector, entities_to_utf8, arginfo_entities_to_utf8, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    ZEND_ME(HtmlInspector, extract_charset, arginfo_extract_charset, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    ZEND_ME(HtmlInspector, normalize_space, arginfo_normalize_space, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    ZEND_ME(HtmlInspector, __construct, arginfo___construct, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, __destruct, arginfo___destruct, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, fork, arginfo_fork, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, reset, arginfo_reset, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, iterate, arginfo_iterate, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, rewind, arginfo_rewind, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, nth, arginfo_nth, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, child, arginfo_child, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, ancestor, arginfo_ancestor, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, descendant, arginfo_descendant, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, preceding_sibling, arginfo_preceding_sibling, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, following_sibling, arginfo_following_sibling, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, name, arginfo_name, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, attribute_exists, arginfo_attribute_exists, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, attribute_equals, arginfo_attribute_equals, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, attribute_contains, arginfo_attribute_contains, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, attribute_starts_with, arginfo_attribute_starts_with, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, or, arginfo_or, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, and, arginfo_and, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, not, arginfo_not, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, case_i, arginfo_case_i, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, get_inner_html, arginfo_get_inner_html, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, get_outer_html, arginfo_get_outer_html, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, get_name, arginfo_get_name, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, get_value, arginfo_get_value, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, get_attribute, arginfo_get_attribute, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, get_offset, arginfo_get_offset, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, get_index, arginfo_get_index, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlInspector, set_index, arginfo_set_index, ZEND_ACC_PUBLIC)
    ZEND_FE_END
};

PHP_MINIT_FUNCTION(html_inspector_minit)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "HtmlInspector", functions_HtmlInspector);
    class_entry_html_inspector = zend_register_internal_class(&ce);
    class_entry_html_inspector->create_object = create_object_html_inspector;

    memcpy(&object_handlers, &std_object_handlers, sizeof (zend_object_handlers));
    object_handlers.offset = offsetof(struct html_inspector_object, std);

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
