CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17 -g
TEST_SOURCES=Model/parser.cc Model/affine.cc Model/model.cc Tests/*.cc
GCOV_FLAGS=
LDFLAGS=-lgtest -lgtest_main -lpthread

all: install

test:
	$(CC) $(CFLAGS) $(TEST_SOURCES) $(LDFLAGS) $(GCOV_FLAGS) -o test

gcov_report: GCOV_FLAGS += -fprofile-arcs -ftest-coverage
gcov_report: test
	./test > /dev/null
	lcov --no-external -t "report" -o report.info -c -d .
	genhtml -o "html_report" report.info
	open html_report/index.html

install:
	rm -rf s21_3d_viewer
	mkdir s21_3d_viewer
	qmake CPP_3DViewer.pro -o s21_3d_viewer
	cd s21_3d_viewer && make && cd ../
	chmod +x s21_3d_viewer/CPP_3DViewer.app
	ln -s ${PWD}/s21_3d_viewer/CPP_3DViewer.app ${HOME}/Desktop/3DViewer_2.0

uninstall:
	rm -rf s21_3d_viewer
	rm ${HOME}/Desktop/3DViewer_2.0

dvi:
	open html/index.html
#	doxygen -g Doxyfile
#	doxygen Doxyfile

dist: install
	tar -czf s21_3d_viewer.tar.gz --directory=s21_3d_viewer/ .

style:
	clang-format -style=google -i Model/*.cc Model/*.h View/*.cc View/*.h Controller/*.cc Controller/*.h Tests/*.cc *.cc
	clang-format -style=google -n Model/*.cc Model/*.h View/*.cc View/*.h Controller/*.cc Controller/*.h Tests/*.cc *.cc

clean:
	rm -rf obj *.a test html_report report.info program *.o *.gch calc_functions/*.gch *.gcno *.gcda s21_3d_viewer.tar.gz *.dSYM

.PHONY: all test clean gcov_report
