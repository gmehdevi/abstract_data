#!/bin/bash

containers="unordered_set.cpp unordered_map.cpp unordered_multimap.cpp unordered_multiset.cpp matrix.cpp"

T_PATH="$(pwd)/src/bonus"
FT_CONT="./../include"

RED='\033[0;31m'
WHITE='\033[0m'

if [[ -z $1 ]]; then
    TO_COMPILE=(${containers})
else
    if [[ " ${containers} " =~ " $1.cpp " || -f "${FT_CONT}/$1.cpp" ]]; then
        TO_COMPILE=("$1.cpp")
    else
        echo -e "${RED}The specified file '$1.cpp' is not recognized or does not exist in the directory${WHITE}\n"
        exit 1
    fi
fi

for t in "${TO_COMPILE[@]}"; do
    echo -e "${RED}Compiling: ${T_PATH}/${t}${WHITE}"
    clang++ -std=c++98 -Wall -Wextra -Werror -I. -I${FT_CONT} -O0 ${T_PATH}/${t}  -o ./test_ft
    ./test_ft
    rm -f ./test_ft
done

exit 0
