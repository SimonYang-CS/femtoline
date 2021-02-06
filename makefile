O=-fvisibility=hidden -flax-vector-conversions -fno-common -fno-stack-protector -fno-asynchronous-unwind-tables
W=-Werror -pedantic -Wno-variadic-macros -Wno-gnu-statement-expression -Wno-gnu-zero-variadic-macro-arguments -Wno-unused-value
A=-m64

#-Wno-empty-body -Wno-unused-value

t: c
	@tcc -Werror -pedantic -ot $A src/?.c -O0
	@strip t
	@ls -la t
	@./t

r: c
	@clang -DAW=0 -DNOLIBC=1 src/?.c -orl $O $W $A -Os
	@strip rl
	@ls -la rl
	@./rl

#k:
#	@tcc -Werror -ok -DAW=1 ../[^lt].c src/?.c -rdynamic -lm -ldl $A
#	./k

c:
	@rm -f a w rl

#/:~
