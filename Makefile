CFLAGS := -g -fshort-enums -Werror

build/hi_test: hi_test.c html_inspector.c
	gcc $(CFLAGS) hi_test.c -o "$@"

entities:
	./entities_download.sh
	gcc -Os entities_print_table.c -o build/entities_print_table
	./build/entities_print_table

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction \
		--check-level=exhaustive html_inspector.c

clean:
	rm -f build/*
