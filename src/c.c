//! nolibc
#include"c.h"

#if NOLIBC

//! core comms (tx)byte (txn)bytes (txN)times
I tx(G c){R write(1,&c,1);}G RX(){G c;R read(0,&c,1),c;}
I txn(S x,I n){P(!n,n)N(n,tx(x[i]));R n;}I txN(G c,I n){N(n,tx(c))R n;}
I sln(S s)               {I r=0;W(*s++)r++;R r;}
S sch(S s,I c)           {W(*s-c)P(!*s++,(S)0)R s;}
S mcp(S d,S s,I n)       {W(n--)*d++=*s++;R d;}//{S x=(S)d,y=(S)s;W(n--)*x++=*y++;R d;}
S memmove(S d,S s,I n)   {P(s<d&&d<s+n,d+=n,s+=n;W(n--)*--d=*--s;d)R mcp(d,s,n);}
_*memcpy(_*d, const _*s, size_t n)  {S x=(S)d,y=(S)s;W(n--)*x++=*y++;R d;}
S memset(S x,I c,I n)    {N(n,x[i]=c);R x;}//{S s=(S)d;W(n--)*s++=c;R d;}

#else

#include<stdarg.h>
I tx(G c){R write(1,&c,1);}I txn(S x,I n){P(!n,n)N(n,tx(x[i]));R n;}I txN(G c,I n){N(n,tx(c))R n;}
I pf(S f,...) {I r;va_list p;va_start(p,f);r=printf(f,&p);fflush(0);va_end(p);R r;}

#endif

//! mmap|munmap
extern I txfatal(S s);
#include<sys/mman.h>     //!< mmap|unmap
#include<sys/stat.h>     //!< stat|fstat
#include<fcntl.h>        //!< open|close

//! mmap(w/o)ffset (m)ap(f)ile(t)ail (m)m(a)p (m)ap(f)ile
ZS mao(I d,szt n,szt o){ZJ p=BASE;p+=d?0:n;_*r=mmap((_*)(d?0:p-n),n,PROT_READ|PROT_WRITE|PROT_EXEC,d?MAP_PRIVATE:(MAP_ANON|MAP_PRIVATE|MAP_FIXED),d-!d,0);P(r==MAP_FAILED,txfatal((S)"mmap"),(S)0)R r;}
K mft(S s,J*n,J l){struct stat b;I d=open((_*)s,0);P(0>d,txfatal(s))R(K)(fstat(d,&b),s=(*n=l?MN(l,b.st_size):b.st_size)?mao(d,*n,b.st_size-*n):s,close(d),s);} //!< mmap l trailing bytes or entire file
S ma(I d,szt n){R mao(d,n,0);}ZK mf(S s,J*n){R mft(s,n,0);}


//:~
