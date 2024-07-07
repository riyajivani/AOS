.DEFAULT_GOAL := all
all : header object compile run remove

header : 
	@echo "exicuting sqrt and cbrt"
object : sqrt.c cbrt.c
	@cc -c sqrt.c
	@cc -c cbrt.c
compile : object
	@cc sqrt.o -o sqrt.out -lm
	@cc cbrt.o -o cbrt.out -lm
run : compile
	@./sqrt.out
	@./cbrt.out
remove :
	@rm sqrt.o
	@rm cbrt.o
	@rm sqrt.out
	@rm cbrt.out
	@echo "All files deleted." 

