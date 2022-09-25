#!/bin/sh

# assuming we have clang format in PATH
CLANG_FORMAT="clang-format"

function format {
    directory="$1"
    echo "Formatting code under $directory/"
    find "$directory" \( -name '*.h' -or -name '*.cpp' \) -print0 | xargs -0 "$CLANG_FORMAT" -i
}

format $(pwd)/src

