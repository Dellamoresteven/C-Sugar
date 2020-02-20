makem: extensions/main.cpp extensions/parser.cpp extensions/replacer.cpp extensions/largerFuncs/print.cpp 
	g++ --std=c++2a -O3 -Wall -o run \
				extensions/main.cpp \
				extensions/parser.cpp \
				extensions/replacer.cpp \
				extensions/configReader.cpp \
				extensions/largerFuncs/print.cpp \
				extensions/largerFuncs/println.cpp \
				extensions/largerFuncs/printv.cpp \
				extensions/largerFuncs/replaceIncludes.cpp \
				extensions/largerFuncs/replaceVar.cpp \
				extensions/largerFuncs/vector.cpp \
				extensions/largerFuncs/pushv.cpp \
				extensions/largerFuncs/comments.cpp \
				extensions/largerFuncs/functions/functionDef.cpp

testRunner: test/testRunner.cpp test/unit/tests.cpp
	g++ --std=c++2a -O3 -Wall -o tests \
				test/testRunner.cpp \
				test/unit/tests.cpp \
				extensions/parser.cpp \
				extensions/replacer.cpp \
				extensions/configReader.cpp \
				extensions/largerFuncs/print.cpp \
				extensions/largerFuncs/println.cpp \
				extensions/largerFuncs/printv.cpp \
				extensions/largerFuncs/replaceIncludes.cpp \
				extensions/largerFuncs/replaceVar.cpp \
				extensions/largerFuncs/vector.cpp \
				extensions/largerFuncs/pushv.cpp \
				extensions/largerFuncs/comments.cpp \
				extensions/largerFuncs/functions/functionDef.cpp

clean:
	rm -f run
	rm -f tests