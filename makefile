obj = main.o WordAnalyze.o Global.o ProdAnlzFather.o\
	  ProgameAnalyze.o FuncAnaly.o Expression.o Table.o Interpret.o \
	  Errors.o
main : $(obj)
	g++ -o main $(obj) 
	g++ -g *.cpp
	rm $(obj)
WordAnalyze.o : WordAnalyze.cpp WordAnalyze.h
	g++ -c WordAnalyze.cpp
main.o : main.cpp WordAnalyze.h
	g++ -c main.cpp
Global.o : Global.cpp Global.h
	g++ -c Global.cpp
ProdAnlzFather.o : ProdAnlzFather.cpp ProdAnlzFather.h
	g++ -c ProdAnlzFather.cpp
ProgameAnalyze.o : ProgameAnalyze.cpp ProgameAnalyze.h
	g++ -c ProgameAnalyze.cpp
FuncAnaly.o : FuncAnaly.cpp FuncAnaly.h
	g++ -c FuncAnaly.cpp
Expression.o : Expression.cpp  Expression.h
	g++ -c Expression.cpp
Table.o : Table.cpp Table.h
	g++ -c Table.cpp
Interpret.o : Interpret.cpp Interpret.h
	g++ -c Interpret.cpp
Errors.o : Errors.cpp Errors.h
	g++ -c Errors.cpp
clean : 
	rm main $(obj)
