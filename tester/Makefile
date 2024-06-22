.PHONY: 
	clean fclean

all:
	./run_fuzz.sh mandatory
	./run_basic.sh
	./run_basic.sh speed

fuzz:
	./run_fuzz.sh mandatory

basic:
	./run_basic.sh

bonus:
	./run_new.sh

fclean: clean
# for run_fuzz.sh
	rm -f ./src/fuzzing/*ft
	rm -f ./src/fuzzing/*std
# for run_basic.sh
	rm -f ./src/basic/*ft
	rm -f ./src/basic/*std
# for run_new.sh
	rm -f ./test_ft

clean:
	rm -f ./res/*

