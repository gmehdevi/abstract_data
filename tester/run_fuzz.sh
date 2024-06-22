#!/bin/bash
#usage ./run_fuzz.sh <container> [iterations] [seed]

#Set the path to the include directory of your project and the fuzzer test headers
INCLUDES="-I./../include -I./src/fuzzing/headers"
CXXFLAGS="-std=c++98 -Wall -Wextra -Werror"


mandatory=(vector stack map list queue deque set multiset multimap priority_queue)
all=${mandatory[@]}

if [ $# -lt 1 ]; then
    echo "Usage: ./run_fuzz.sh <container> [iterations] [seed]"
    exit 1
fi

if [ $1 == "mandatory" ] || [ $1 == "all" ]; then
    containers=${all[@]}
else
    containers=$1
fi

for container in $containers; do
    if [[ ! " ${all[@]} " =~ " ${container} " ]]; then
        echo "Error: $container is not a valid container"
        exit 1
    fi
done

if [ $# -gt 1 ]; then
    iterations=$2
else
    iterations=100
fi

if [ $# -gt 2 ]; then
    Seed=$3
else
    Seed=$RANDOM
fi

for container in $containers; do

    g++ $CXXFLAGS $INCLUDES               ./src/fuzzing/tests/${container}.cpp  -o ./src/fuzzing/${container}_std
    g++ $CXXFLAGS $INCLUDES -D TEST_FT    ./src/fuzzing/tests/${container}.cpp  -o ./src/fuzzing/${container}_ft 

    ./src/fuzzing/${container}_std $iterations $Seed > ./res/${container}_std.txt
    ./src/fuzzing/${container}_ft $iterations $Seed > ./res/${container}_ft.txt

    diff ./res/${container}_std.txt ./res/${container}_ft.txt > ./res/${container}_diff.txt

    if [ $? -ne 0 ]; then
        echo "Error: $container failed"
    else
        echo "Success: $container passed"
    fi

done


