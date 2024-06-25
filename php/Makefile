build/html_inspector.so: html_inspector.c html_inspector_php.c phpize
	mkdir -p phpize build && cd phpize && \
	make && cp modules/html_inspector.so ../build # && strip "../$@"

phpsize:
	phpize && ./configure

html_inspector.c: ../html_inspector.c
	ln -s ../html_inspector.c html_inspector.c

.PHONY: test
test:
	php -dextension=build/html_inspector.so test.php

.PHONY: clean
clean:
	rm -rf phpize build

