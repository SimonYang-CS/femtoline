O=-fvisibility=hidden -flax-vector-conversions -fno-common -fno-stack-protector -fno-asynchronous-unwind-tables
W=-Werror -Wno-empty-body -Wno-unused-value
A=-m64

t: c
	@tcc -Werror -ot $A src/?.c -O0
	@strip t
	@ls -la t
	@./t

r: c
	@clang src/?.c -or $O $W $A -Os
	@strip r
	@ls -la r
	@./r

#k:
#	@tcc -Werror -ok -DAW=1 ../[^lt].c src/?.c -rdynamic -lm -ldl $A
#	./k

c:
	@rm -f t r k

#/:~
