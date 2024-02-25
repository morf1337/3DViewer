# all install uninstall clean dvi dist tests
FLAGS = -Wall -Werror -Wextra -std=c++17 -lgtest -lgtest_main --coverage
OS := $(shell uname -s)

all: install

install: clean
	mkdir build
	cd ./build/ && qmake ../view && make
	mkdir -p app
ifeq ($(OS), Darwin)
	mv build/3DViewer2.app ./app/3DViewer2.app
else
	mv build/3DViewer2 ./app/3DViewer2
endif
	rm -rf build

uninstall:
	rm -rf app

clean:
	rm -rf ./build* ./dist ./app ./report ./test.dSYM
	rm -rf *.gc* test test.exe ./view/*.pro.user .DS_Store rep.info 

dvi: 
	open ./view/dvi.html

dist:
	mkdir -p dist
	tar -cvzf dist/3DViewer2.tar.gz .

tests:
ifeq ($(OS), Darwin)
	g++ tests.cpp model/objtransform.cc model/objdata.cc model/fileparcer.cc -g -fprofile-arcs -ftest-coverage $(FLAGS) -o test
	./test
else
	g++ tests.cpp model/objtransform.cc model/objdata.cc model/fileparcer.cc -g $(FLAGS) -pthread -o test
	./test
endif

leaks:
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test
else
	valgrind --leak-check=yes ./test
endif
