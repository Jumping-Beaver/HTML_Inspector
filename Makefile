CFLAGS := -g -O2 -Wall -Werror -Wno-unused-function -Wno-parentheses

build/test: test.c html_inspector.c
	gcc $(CFLAGS) test.c -o "$@"

entities:
	./entities_download.sh
	gcc -Os entities_print_table.c -o build/entities_print_table
	./build/entities_print_table

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction \
	    --check-level=exhaustive html_inspector.c

clean:
	rm -f build/*

build/html_inspector_php.so: html_inspector_php.c
	gcc -I/usr/include/php -I/usr/include/php/main -I/usr/include/php/TSRM -I/usr/include/php/Zend \
	    $(CFLAGS) \
	    -fPIC -shared "$<" -o "$@"
