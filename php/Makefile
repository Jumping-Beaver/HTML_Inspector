.PHONY: all
all:
	mkdir -p phpize build && cd phpize && \
	ln -sf ../html_inspector.c html_inspector.c && \
	ln -sf ../html_inspector_php.c html_inspector_php.c && \
	ln -sf ../config.m4 config.m4 && \
	phpize && ./configure && make && cp modules/html_inspector.so ../build

.PHONY: test
test:
	php -dextension=build/html_inspector.so test.php

.PHONY: clean
clean:
	rm -rf phpize build

