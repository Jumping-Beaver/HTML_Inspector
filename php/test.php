#!/usr/bin/env -S php -dextension=build/html_inspector.so
<?php

function benchmark_HtmlInspector()
{
    $html = file_get_contents('../test-html.html');

    $time = microtime(true);
    $num = 0;
    for ($i = 0; $i < 100; ++$i) {
        $hi = new HtmlDocument($html);
        $selector = $hi->select(0)->descendant()->name('a');
        while (($node = $selector->iterate()) != -1) {
            $href = $hi->get_attribute($node, 'href');
            $num += strlen($href);
        }
    }
    print($i / (microtime(true) - $time) . " / second");
    print(" (" . $num / $i . ")\n");
}

function benchmark_libxml2()
{
    $html = file_get_contents('../test-html.html');

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
