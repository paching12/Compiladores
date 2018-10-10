Gram=y.tab.c y.tab.h 

all: $(Gram) lex.yy.c math.c symbol.c init.c racional.c
	@gcc -o racio y.tab.c lex.yy.c math.c symbol.c init.c  racional.c -lm
	@echo Compiled

init.c:
	@echo "Si esta"

$(Gram): hoc3.y
	@yacc -d hoc3.y

lex.yy.c: racional_cal.l
	@flex racional_cal.l

clean:
	@rm -f *.out lex.yy.c *.tab.* racio
	@echo Clean
