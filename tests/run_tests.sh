#!/usr/bin/env bash

files=(
    "linked_list"
)

for file in "${files[@]}"; do
    clang "${file}_test.c" "../${file}.c" -o a.out
    ./a.out
    rm ./a.out
done
