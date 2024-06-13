PHP_ARG_ENABLE(html_inspector, HtmlInspector, [--enable-html-inspector Enable HtmlInspector])
if test $PHP_HTML_INSPECTOR != "no"; then
	PHP_NEW_EXTENSION(html_inspector, html_inspector_php.c, $ext_shared)
fi
