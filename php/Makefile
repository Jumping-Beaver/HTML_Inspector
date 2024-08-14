build/html_inspector.so: phpize html_inspector.c html_inspector_php.c
	mkdir -p build && cd phpize && \
	make && cp modules/html_inspector.so ../build && strip "../$@"

phpize:
	mkdir -p phpize && cd phpize && \
	ln -s ../html_inspector.c . && \
	ln -s ../html_inspector_php.c . && \
	ln -s ../config.m4 . && \
	phpize && ./configure

html_inspector.c: ../html_inspector.c
	ln -s ../html_inspector.c html_inspector.c

.PHONY: test
test:
	php -dextension=build/html_inspector.so test.php

.PHONY: clean
clean:
	rm -rf phpize build

