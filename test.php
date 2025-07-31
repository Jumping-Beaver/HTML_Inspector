#!/usr/bin/env -S php -dextension=build/html_inspector_php.so
<?php

function benchmark_HtmlInspector()
{
    $html = file_get_contents('test-html.html');

    $time = microtime(true);
    $num = 0;
    for ($i = 0; $i < 200; ++$i) {
        $doc = new HtmlInspector\HtmlDocument($html);
        $selector = $doc->select(0)->descendant()->name('a')->attribute_contains('href', 'abc');
        while (($node = $selector->iterate()) != -1) {
            //$doc->get_outer_html($node);
            $href = $doc->get_attribute($node, 'href');
            $num += strlen($href);
        }
    }
    print($i / (microtime(true) - $time) . " / second");
    print(" (" . $num / $i . ")\n");
}

function benchmark_libxml2()
{
    $html = file_get_contents('./test-html.html');

    $time = microtime(true);
    $num = 0;
    for ($i = 0; $i < 100; ++$i) {
        $doc = new DOMDocument;
        $doc->loadHTML($html, LIBXML_NOERROR | LIBXML_NOWARNING);
        $xpath = new DOMXPath($doc);
        foreach ($xpath->query('//a') as $a) {
            $num += strlen($a->getAttribute('href'));
        }
    }
    print($i / (microtime(true) - $time) . "/ second");
    print(" (" . $num / $i . ")\n");
}

function main()
{
    benchmark_HtmlInspector();
    benchmark_libxml2();
}

main();
