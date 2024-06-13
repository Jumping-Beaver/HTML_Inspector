#!/usr/bin/env bash

# Missing semicolons for codepoints < 256 used to be valid historically but are reported as invalid
# by validator.w3.org. Here We filter out entities with missing semicolons.

if [ ! -f entities.json ]; then
    curl https://html.spec.whatwg.org/entities.json > entities.json
fi

outfile=entities.h
cat > "$outfile" <<EOF
struct {
    const char *decoding;
    const char *entity;
} entities[] = {
EOF
cat entities.json | jq -r \
    '. | to_entries[] | "    {\"" + .value.characters + "\", \"" + .key[1:] + "\"}," |
    sub("\n"; "\\n") | sub("\\\\"; "\\\\\\\\") | sub("\"\"\""; "\"\\\"\"")' | \
    grep ';' >> "$outfile"
echo '};' >> "$outfile"
