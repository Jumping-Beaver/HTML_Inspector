#include <php.h>
#include <zend_interfaces.h>
#include "html_inspector.c"

static zend_class_entry *class_entry_html_document, *class_entry_selector;
static zend_object_handlers object_handlers_html_document, object_handlers_selector;

struct HtmlDocumentObject {
    struct HtmlDocument *doc;
    zend_object std;
};

struct SelectorObject {
    struct Selector *sel;
    zend_object std;
};

static zend_object * create_object_html_document(zend_class_entry *ce)
{
    struct HtmlDocumentObject *this = zend_object_alloc(sizeof (struct HtmlDocumentObject), ce);
    zend_object_std_init(&this->std, ce);
    this->std.handlers = &object_handlers_html_document;
    return &this->std;
}

static zend_object * create_object_selector(zend_class_entry *ce)
{
    struct SelectorObject *this = zend_object_alloc(sizeof (struct SelectorObject), ce);
    zend_object_std_init(&this->std, ce);
    this->std.handlers = &object_handlers_selector;
    return &this->std;
}

#define HTML_DOCUMENT(this) \
    ((struct HtmlDocumentObject *) ((char *) Z_OBJ_P(this) - offsetof(struct HtmlDocumentObject, std)))->doc

#define SELECTOR(this) \
    ((struct SelectorObject *) ((char *) Z_OBJ_P(this) - offsetof(struct SelectorObject, std)))->sel

ZEND_FUNCTION(resolve_iri)
{
    zend_string *reference;
    zend_string *base;
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(reference)
        Z_PARAM_STR(base)
    ZEND_PARSE_PARAMETERS_END();

    struct String _base = {base->val, base->len, false};
    struct String _reference = {reference->val, reference->len, false};
    struct String uri = resolve_iri(_reference, _base);
    if (uri.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, uri.data, uri.length);
    String_free(uri);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_resolve_iri, IS_STRING, true)
    ZEND_ARG_TYPE_INFO(0, reference, IS_STRING, false)
    ZEND_ARG_TYPE_INFO(0, base, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, extract_charset)
{
    zend_string *html;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(html)
    ZEND_PARSE_PARAMETERS_END();

    struct String charset = HtmlDocument_extract_charset(html->val);
    if (charset.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, charset.data, charset.length);
    String_free(charset);
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
    HTML_DOCUMENT(ZEND_THIS) = HtmlDocument(html->val, html->len);
    if (HTML_DOCUMENT(ZEND_THIS) == NULL) {
        zend_throw_error(NULL, "malloc failed", 0);
    }
}
ZEND_BEGIN_ARG_INFO(arginfo___construct, 0)
    ZEND_ARG_TYPE_INFO(0, html, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, __destruct)
{
    ZEND_PARSE_PARAMETERS_NONE();
    HtmlDocument_free(HTML_DOCUMENT(ZEND_THIS));
}
ZEND_BEGIN_ARG_INFO(arginfo___destruct, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, get_name)
{
    zend_long node;
    ZEND_PARSE_PARAMETERS_START(1, 1);
        Z_PARAM_LONG(node)
    ZEND_PARSE_PARAMETERS_END();
    struct String string = HtmlDocument_get_name(HTML_DOCUMENT(ZEND_THIS), node);
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    String_free(string);
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
    struct String string = HtmlDocument_get_value(HTML_DOCUMENT(ZEND_THIS), node);
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    String_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_value, IS_STRING, true)
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
    struct String string = HtmlDocument_get_attribute(HTML_DOCUMENT(ZEND_THIS), node,
            attribute->val);
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    String_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_attribute, IS_STRING, true)
    ZEND_ARG_TYPE_INFO(0, node, IS_LONG, false)
    ZEND_ARG_TYPE_INFO(0, attribute, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, get_inner_html)
{
    zend_long node;
    ZEND_PARSE_PARAMETERS_START(1, 1);
        Z_PARAM_LONG(node)
    ZEND_PARSE_PARAMETERS_END();
    struct String string = HtmlDocument_get_inner_html(HTML_DOCUMENT(ZEND_THIS), node);
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    String_free(string);
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
    struct String string = HtmlDocument_get_outer_html(HTML_DOCUMENT(ZEND_THIS), node);
    if (string.data == NULL) {
        ZVAL_NULL(return_value);
        return;
    }
    ZVAL_STRINGL(return_value, string.data, string.length);
    String_free(string);
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_get_outer_html, IS_STRING, true)
    ZEND_ARG_TYPE_INFO(0, node, IS_LONG, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(HtmlDocument, select)
{
    zend_long node;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(node)
    ZEND_PARSE_PARAMETERS_END();
    struct Selector *sel = HtmlDocument_select(HTML_DOCUMENT(ZEND_THIS), node);
    if (sel == NULL) {
        zend_throw_error(NULL, "malloc failed", 0);
        return;
    }
    zend_object *object = create_object_selector(class_entry_selector);
    ZVAL_OBJ(return_value, object);
    SELECTOR(return_value) = sel;
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_select, HtmlInspector\\Selector, false)
    ZEND_ARG_TYPE_INFO(0, node, IS_LONG, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, __destruct)
{
    ZEND_PARSE_PARAMETERS_NONE();
    free(SELECTOR(ZEND_THIS));
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
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_nth, HtmlInspector\\Selector, false)
    ZEND_ARG_TYPE_INFO(0, n, IS_LONG, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, child)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_child(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_child, HtmlInspector\\Selector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, name)
{
    zend_string *name;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(name)
    ZEND_PARSE_PARAMETERS_END();
    Selector_name(SELECTOR(ZEND_THIS), name->val);
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_name, HtmlInspector\\Selector, false)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, rewind)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_rewind(SELECTOR(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_rewind, IS_VOID, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, iterate)
{
    ZEND_PARSE_PARAMETERS_NONE();
    ZVAL_LONG(return_value, Selector_iterate(SELECTOR(ZEND_THIS)));
}
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_iterate, IS_LONG, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, ancestor)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_ancestor(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_ancestor, HtmlInspector\\Selector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, descendant)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_descendant(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_descendant, HtmlInspector\\Selector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, preceding_sibling)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_preceding_sibling(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_preceding_sibling, HtmlInspector\\Selector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, following_sibling)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_following_sibling(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_following_sibling, HtmlInspector\\Selector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, attribute_exists)
{
    zend_string *name;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(name)
    ZEND_PARSE_PARAMETERS_END();
    Selector_attribute_exists(SELECTOR(ZEND_THIS), name->val);
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_attribute_exists, HtmlInspector\\Selector, false)
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
    Selector_attribute_equals(SELECTOR(ZEND_THIS), name->val, value->val);
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_attribute_equals, HtmlInspector\\Selector, false)
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
    Selector_attribute_contains(SELECTOR(ZEND_THIS), name->val, value->val);
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_attribute_contains, HtmlInspector\\Selector, false)
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
    Selector_attribute_starts_with(SELECTOR(ZEND_THIS), name->val, value->val);
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_attribute_starts_with, HtmlInspector\\Selector, false)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, false)
    ZEND_ARG_TYPE_INFO(0, value, IS_STRING, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, or)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_or(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_or, HtmlInspector\\Selector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, and)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_and(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_and, HtmlInspector\\Selector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, not)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_not(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_not, HtmlInspector\\Selector, false)
ZEND_END_ARG_INFO()

ZEND_METHOD(Selector, case_i)
{
    ZEND_PARSE_PARAMETERS_NONE();
    Selector_case_i(SELECTOR(ZEND_THIS));
    ZVAL_OBJ_COPY(return_value, Z_OBJ_P(ZEND_THIS));
}
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_case_i, HtmlInspector\\Selector, false)
ZEND_END_ARG_INFO()

static zend_function_entry functions[] = {
    ZEND_NS_FE("HtmlInspector", resolve_iri, arginfo_resolve_iri)
    ZEND_FE_END
};

static zend_function_entry functions_HtmlDocument[] = {
    ZEND_ME(HtmlDocument, extract_charset, arginfo_extract_charset, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    ZEND_ME(HtmlDocument, __construct, arginfo___construct, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, __destruct, arginfo___destruct, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, get_name, arginfo_get_name, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, get_value, arginfo_get_value, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, get_attribute, arginfo_get_attribute, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, get_inner_html, arginfo_get_inner_html, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, get_outer_html, arginfo_get_outer_html, ZEND_ACC_PUBLIC)
    ZEND_ME(HtmlDocument, select, arginfo_select, ZEND_ACC_PUBLIC)
    ZEND_FE_END
};

static zend_function_entry functions_Selector[] = {
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

    INIT_CLASS_ENTRY(ce, "HtmlInspector\\HtmlDocument", functions_HtmlDocument);
    class_entry_html_document = zend_register_internal_class(&ce);
    class_entry_html_document->create_object = create_object_html_document;
    memcpy(&object_handlers_html_document, &std_object_handlers, sizeof (zend_object_handlers));
    object_handlers_html_document.offset = offsetof(struct HtmlDocumentObject, std);

    INIT_CLASS_ENTRY(ce, "HtmlInspector\\Selector", functions_Selector);
    class_entry_selector = zend_register_internal_class(&ce);
    class_entry_selector->create_object = create_object_selector;
    memcpy(&object_handlers_selector, &std_object_handlers, sizeof (zend_object_handlers));
    object_handlers_selector.offset = offsetof(struct SelectorObject, std);

    return SUCCESS;
}

static zend_module_entry html_inspector_module_entry = {
    STANDARD_MODULE_HEADER,
    "html_inspector",
    functions,
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
