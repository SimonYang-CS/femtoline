#-fno-stack-protector
O=-fvisibility=hidden -flax-vector-conversions -fno-common -fno-asynchronous-unwind-tables
WL=-Werror -pedantic -Wno-empty-body -Wno-variadic-macros -Wno-gnu-statement-expression \
	-Wno-gnu-zero-variadic-macro-arguments -Wno-unused-value -Wno-language-extension-token \
	-Wno-pointer-sign -Wno-int-conversion -Wno-gnu-empty-initializer
WG=-Werror -pedantic -Wno-variadic-macros -Wno-unused-value -Wno-builtin-declaration-mismatch -Wno-int-conversion
A=-m64

#-Wno-empty-body -Wno-unused-value

pf: c
	@tcc -DFPF -std=c11 -pedantic -fno-common -funsigned-char -opf $A src/p.c -Os
	@strip -s pf
	@ls -la pf
	@./pf

t: c
	@#tcc -std=c11 -DNOLIBC=1 -Werror -pedantic -dynamic $A -c src/p.c  -O0
	@#tcc -DAW=0 -DNOLIBC=1 -std=c11 -nostdlib -Werror -pedantic $A -ot src/[lms].c src/s.S p.o -O0
	@#tcc -DAW=0 -DNOLIBC=1 -std=c11 -nostdlib -Werror -pedantic $A -c src/[lms].c src/s.S -Os
	@#tcc -DAW=0 -DNOLIBC=1 -std=c11 -Werror -pedantic $A -ot ?.o -Os
	@#tcc -DAW=0 -DNOLIBC=1 -nostdlib -std=c11 $A -ot src/?.[cS] -O0 -g -w
	@tcc -DAW=0 -DNOLIBC=1 -std=c11 $A -ot src/?.c -O0 -g -w
	@ls -la t
	@./t

tc: c
	@tcc -DAW=0 -DNOLIBC=1 -std=c11 -Werror -pedantic -otc $A src/?.c -Os
	@strip -s tc
	@ls -la tc
	@./tc


l: c
	@clang -DAW=0 -DNOLIBC=1 src/?.[c] -ol $O $(WL) $A -O2 -Wno-format -Wno-format-pedantic
	@strip l
	@ls -la l
	@./l

g: c
	@gcc -DNOLIBC=1 -no-pie -DAW=0 src/?.c -og $O $(WG) $A -O0 -g -Wno-pedantic
	@#strip g
	@ls -la g
	@lldb ./g

gg: c
	@gcc -DNOLIBC=1 -nostdlib -no-pie -DAW=0 src/?.[cS] -og $O $(WG) $A -Os -Wno-pedantic
	@strip g
	@ls -la g
	#s

k:
	@clang -w -okk -DAW=1 ../[^lt].c src/?.c -rdynamic -lm -ldl $A $O -g -O0

c:
	@rm -f t l g k r k kk tc

#/:~
