# HTML Inspector

This is a readonly error-tolerant HTML parser and URI resolver with focus on fast
performance. Data queries are supported by iterating over node axes while applying boolean filters,
similar to CSS or XPath selectors. The use case is very large scale web crawling. The parser is implemented
in C with bindings to PHP.

Reasonably fast alternatives are Gumbo, Lexbor, and LibXML2. These alternatives are slower by a
factor of 10. LibXML2 does not parse script tags correctly, does not support case insensitive
attribute names, and handles the input encoding in a way that is hard to control. Gumbo is not
really maintained. Lexbor is a recommendable alternative; it has more features, has a wider scope
than just web scraping, is better tested, has slower performance and might be less maintainable due to
its larger code base.

See also: `https://wiki.php.net/rfc/domdocument_html5_parser`

## Usage

### General

Selectors are implemented using a stack of operations, which fall into two categories: iterators
along axes of the node tree, and filters. Boolean operations (and, or, not) on filters are
implemented using postfix notation. “and” operations are appended implicitly to chained filters.

Nodes are represented by integers. Node `0` is the always present `#document` node. A node value
of `-1` is returned by `iterate()` if the iterator is exhausted. Passing `-1` or other non-existent
node references to the `get_*` methods returns null.

### C

In C you can `#include "html_inspector.c"` to statically compile the library into your project.

The HTML input must remain allocated and immutable as along as the `HtmlInspector` instance is
used.

### PHP bindings

Example code:

```
<?php

function extract_anchors(string $html_utf8, string $document_uri)
{
    $doc = new HtmlInspector\HtmlDocument($html_utf8);
    $base_node = $doc->select(0)->child()->name('html')->child()->name('head')->child()
        ->name('base')->iterate();
    $base = HtmlInspector\resolve_iri($doc->get_attribute($base_node, 'href'), $document_uri);
    $selector = $doc->select(0)->descendant()->name('a')->attribute_starts_with('#')->not();
    while (($node_a = $selector->iterate()) !== -1) {
        $href = $doc->get_attribute($node_a, 'href');
        $uri = HtmlInspector\resolve_iri($href, $base);
        print("$uri\n");
    }
}
```

## Scope

Objectives:

- Provide very fast read-only analysis of HTML documents

- Enable queries on HTML similar to XPath or CSS selectors

- Parse real-world markup correctly and in a lenient way

- Have bindings for scripting languages, especially PHP

- Method to resolve URLs

- Minimise redundancy or syntactic sugar in the API

  Example: A parent selector is not required because we can use `ancestor()->nth(1)`

Out of scope:

- Implementation of a pure XML parser (besides XHTML)

  There are more good-quality XML parsers than HTML parsers.

  An XML parser included in this library would not have a strong unique selling proposition.
  For the best possible performance and handling of big data files it is advisable to use a streaming
  approach, which is not compatible with the data structures optimized for HTML parsing.

  In the context of web scraping, commercial crawlers accept `sitemap.xml` of up to 50 MB size, a
  size for which one should use a streaming parser. RSS feeds can also be parsed conveniently enough
  with a streaming parser because they have a data schema. This means there is no use case for a
  non-streaming XML parser in a web scraper.

  When it comes to parsing XHTML, the HTML parser should recognize and support this format without
  requiring an extra hint.

- Support for encodings other than UTF-8

  You need to convert the input to UTF-8. For this there is plenty of good tooling available.
  To determine the input encoding you need to inspect the HTTP headers and use the
  `HtmlInspector_extract_charset(…)` function.

- LibXML2 interoperability

  The slow part of LibXML2 is not looping through the input string, but building the DOM tree.
  Building the DOM using LibXML2's native functions (like `xmlAddNode(…)`) is therefore not an
  option. LibXML2 expects that every string of the data be allocated using malloc. To get around
  that, we could modify the memory allocator using `xmlMemSetup(…)`. It's a pretty ugly solution
  and the effort of creating CSS-like selectors, which I generally consider as superior to XPath
  due to their simplicity, is not that big.

- XPath support

  XPath is a whole programming language and overly complex for its purpose. The XPath
  implementation of LibXML2 is as long as 15k lines. Simpler kinds of selectors can be implemented
  in a few hundred lines of code and are powerful enough.

- Decoding Punycode to UTF-8 in internationalised domain names

  When displaying crawled URLs to users, it is user-friendly to decode the percent-encoding to
  Unicode, and this library may include a corresponding decoding function. But Punycode in
  internationalised domain names (IDN) will not be decoded.

  IDN are a failed concept because of the security risk of homographic attacks. I like the approach of
  decoding URL paths and other components to Unicode, but domain names should be ASCII-only. It's
  an inconvenience for users of some languages but the security risk is not acceptable.
  One illustrative example is `xn--80ak6aa92e.com`.

  Chrome does by default not (always) show decoded domain names in the address bar, and in Firefox
  I recommend to set `network.IDN_show_punycode` to `true`.

## Technical details

### How is the fast performance achieved?

- Conceptually: Only two contiguous memory blocks store the parsed document: a list
  of nodes and a list of attributes. Other parsers make thousands of memory allocations to
  build a tree data structure.

- Conceptually: Data queries use lazy evaluation for the iteration over nodes and for the decoding of HTML
  entities to UTF-8.

- Most essential implementation detail: The parser maintains a stack of unclosed tags to match them
  quickly. Looping backwards through the whole node list to find them is very slow.

- The named HTML entities are indexed by their first character.

### About PHP iterators

I have thought back and forth whether to implement PHP iterators to loop through nodes. How PHP
implements iterators is awkward. Firstly, two redundant implementations are needed to support
looping with `foreach` and to implement the `Iterator` interface. Moreover, it needs the two
methods `next` (with no return value) and `current` instead of just one, we have to implement a
caching of both the current value and of the validity state of the iterator, and in `current` we
conditionally have to make one implicit iteration. Python is an example where iteration is
implemented more elegantly using a single `__next__` method that both iterates and then returns the
current value. Another complication is how to encode the non-existence of a node. With PHP iterators,
we need to use the value `false` and implement union type hints and a respective check for the `get_*`
methods to enable a concise syntax. Without iterators, we can use the value `-1` and pass it to the
C functions without further checks.

## What makes HTML difficult to parse?

A large amount of complexity stems from the error tolerance that browsers implement, which results
in the quality degradation of real-world HTML markup. Admittedly, there may be some need of error
tolerance for historical reasons but generally strictness is a better practice.

One drawback is the large list of named entities. In the age of Unicode, most are unneeded.

Having to support both decimal and hexadecimal entities is an unneeded complexity.

Another bummer is optional starting and closing tags. They require a large amount of code to
handle.

## Exploration to optimize the memory allocator of LibXML2

My original idea to was write a fast parser that creates LibXML2-compatible data structure.
However, not the parser but these data structures are the main reason why LibXML2 is slow, because
they require many memory allocations.

To investigate this issue I have set up a custom memory allocations using `xmlMemSetup(...)`.

I found that parsing a 1.3 MB big test document needs 400k mallocs and 44k reallocs. Especially
concerning are the reallocs because they are hard to optimize.

Then I have pre-allocated a big pool of memory and let each modified-malloc return a chunk at the
end of the used area in pool. I assumed for testing that the data is always null-terminated
strings, which is not a safe assumption but suitable for testing. Without this assumption we would
have to register the size of every allocation in an efficient search tree. Although the custom
allocator enhances the performance significantly, it is not satisfactory: from 15 parsings / second
to 20 parsings / seconds.

### Defects in Python's `lxml` module

`lxml` is a Python binding for LibXML2. It cannot be used to parse HTML correctly. Examples of
incorrect behavior follow.

Here is omits the script content and generally it incorrectly creates self-closing tags:
```
>>> lxml.etree.tostring(lxml.etree.HTML('<script></</script>'))
b'<html><head><script/></head></html>'
```

None of the `<a>` strings must be modified here:
```
lxml.etree.tostring(lxml.etree.HTML('<title><a></title><textarea><a></textarea><script><a></script>'))
b'<html><head><title><a/></title><textarea><a/></textarea><script>&lt;a&gt;</script></head></html>'
```

Inserting a `<p>` node is incorrect:
```
>>> lxml.etree.tostring(lxml.etree.HTML('fragment'))
b'<html><body><p>fragment</p></body></html>'
````

`&` must not be escaped in script tags:
```
>>> lxml.etree.tostring(lxml.etree.HTML('<script>&uuml;</script>'))
b'<html><head><script>&amp;uuml;</script></head></html>'
```

### What is `phpize`?

In the context of PHP extensions, `phpize` is a command that creates dozens of files with thousands
of lines of code to set up a complex and slow C compilation toolchain. It is supposed to provide a
compatibility layer for MacOS and other systems. It may be overengineered in the age of
containerization and I don't use it.
