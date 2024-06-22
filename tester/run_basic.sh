#!/usr/bin/bash

FT_CONT="./../include/"
seed=$RANDOM
containers="multiset.cpp multimap.cpp stack.cpp queue.cpp \
vector.cpp list.cpp set.cpp map.cpp stack.cpp deque.cpp \
priority_queue.cpp 42.cpp"

speed="speed/map.cpp speed/vector.cpp speed/list.cpp speed/queue.cpp"

T_PATH="$(pwd)/src/basic"

GREEN="\033[1;32m"
BLUE="\033[1;34m"
PURPLE="\033[1;35m"
WHITE="\033[0;37m"
RED="\033[1;31m"

if [[ $# -gt 2 ]]; then
    echo -e "${RED}Require one, two, or no arguments${WHITE}\n"
    exit 1
fi

if [[ -z $1 ]]; then
    TO_COMPILE="${containers}"
elif [ $1 == "speed" ]; then
    TO_COMPILE="${speed}"
elif [[ ! " ${containers} " =~ " $1.cpp " && ! -f "$FT_CONT/$1.cpp" ]]; then
    echo -e "${RED}The specified file '$1.cpp' is not recognized or does not exist in the directory${WHITE}\n"
    exit 1
else
    TO_COMPILE="$1.cpp"
fi

echo -e "${RED}Compiling: $TO_COMPILE${WHITE}";


if [ "$1" = "speed" ]
	then
	for t in ${TO_COMPILE[@]}; do
	clang++ -Wall -Wextra -Werror -I. -I${FT_CONT} -std=c++98 ${T_PATH}/${t} -D TEST_FT -O2 -o ${T_PATH}/test_ft
	printf "ft ${t} took "
	${T_PATH}/test_ft ${seed}
	clang++ -Wall -Wextra -Werror -I. -I${FT_CONT} -std=c++98 ${T_PATH}/${t} -o ${T_PATH}/test_std
	printf "std ${t} took "
	${T_PATH}/test_std ${seed}
	rm -f ${T_PATH}/test_std  ${T_PATH}time_f ${T_PATH}time_std ${T_PATH}/test_ft
	done
	exit
fi

for t in ${TO_COMPILE[@]}; do
	g++ -Wall -Wextra -Werror -I. -I${FT_CONT} -std=c++98 ${T_PATH}/${t}  -D TEST_FT -o test_ft

	start=`date +%s.%N`
	./test_ft ${seed} > $(pwd)/res/log_ft.txt 
	end=`date +%s.%N`
	ft=$(awk -v start="$start" -v end="$end" 'BEGIN { print end - start }')

	g++ -Wall -Wextra -Werror -I. -I${FT_CONT} -std=c++98 ${T_PATH}/${t} -o test_std

	start=`date +%s.%N`
	./test_std ${seed} > $(pwd)/res/log_std.txt
	end=`date +%s.%N`
	std=$(awk -v start="$start" -v end="$end" 'BEGIN { print end - start }')

	diff $(pwd)/res/log_std.txt $(pwd)/res/log_ft.txt > $(pwd)/res//diff

	if [ $? -eq 0 ]
		then
		printf "${PURPLE}${t} ${GREEN}OK ٩{˘◡˘}۶${WHITE}\n"
		if [ "$2" = "time" ]
		then
			e=$(awk -v ft="$ft" -v std="$std" 'BEGIN { print ft/std }')
			printf "times : ft : ${ft}, std : ${std} => ft is ${e} times slower than std\n"
		fi
	else
		printf "${PURPLE}${t} ${BLUE}KO ಥ_ಥ${WHITE}\n"
	fi
	rm -f test_std  test_ft

done