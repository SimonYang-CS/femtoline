//! kparc femtolib        public domain

#include"_.h"             //!< core macros and types

//! type system
#define KC 1ULL           //!< char
#define KH 2ULL           //!< short
#define KI 3ULL           //!< int
#define KJ 4ULL           //!< long
#define KE 5ULL           //!< float
#define KF 6ULL           //!< double
#define KS 7ULL           //!< symbol

#define ptr(x) (*(S*)&x)  //!< cast x to an S lvalue

//! x y z f r             ..are classic locals:
#define xi I(x)           //!< cast x to int32 atom
#define xj (J)(x)         //!< cast x to int64 atom
#define xf *(F*)&x        //!< retrieve double atom
//! vector preamble is mturnnnn:
#define xm xG[-8]         //!< (m)alloc bucket id
#define xt xG[-5]         //!< (t)ype id
#define xu xG[-6]         //!< list attrib(u)tes
#define xr xG[-7]         //!< (r)eference count
#define xn xI[-1]         //!< vector le(n)gth
//! vector accessors and casts:
#define xI ((I*)x)        //!< cast to list of ints
#define xJ ((J*)x)        //!<           ..of longs
#define xF ((F*)x)        //!<         ..of doubles
#define xK ((K*)x)        //!<        ..of sublists
#define Xg ((S)x)[i]      //!<          ..to string
#define Xi xI[i]          //!<      i'th int32 of x
#define Xj xJ[i]          //!<      i'th int64 of x
#define Xk xK[i]          //!<    i'th sublist of x
#define Xx xK[i]          //!<  i'th subvector of x
#define xx xK[0]          //!<     1st element of x
#define xy xK[1]          //!<                ..2nd
#define xz xK[2]          //!<                ..3rd
#define xxu ptr(xx)[-6]   //!< attrs of 1st element
#define xyu ptr(xy)[-6]   //!< attrs of 2st element
#define xG  ptr(x)        //!< cast x to byte list

#define yi I(y)           //!< cast y to int32 atom
#define yj (J)(y)         //!< cast y to int64 atom
#define yf *(F*)&y        //!< retrieve double atom
#define ym yG[-8]         //!< (m)alloc bucket id
#define yt yG[-5]         //!< (t)ype id
#define yu yG[-6]         //!< list attrib(u)tes
#define yr yG[-7]         //!< (r)eference count
#define yn yI[-1]         //!< vector le(n)gth
#define yI ((I*)y)        //!< cast to list of ints
#define yF ((F*)y)        //!<         ..of doubles
#define yK ((K*)y)        //!<        ..of sublists
#define Yg ((S)y)[i]      //!<          ..to string
#define Yi yI[i]          //!<      i'th int32 of y
#define Yj yJ[i]          //!<      i'th int64 of y
#define Yk yK[i]          //!<  i'th subvector of y
#define yx yK[0]          //!<     1st element of y
#define yy yK[1]          //!<                ..2nd
#define yz yK[2]          //!<                ..3rd
#define yxu ptr(yx)[-6]   //!< attrs of 1st element
#define yyu ptr(yy)[-6]   //!< attrs of 2st element
#define yG  ptr(y)

#define ri I(r)           //!< cast r to int32 atom
#define rj (J)(r)         //!< cast r to int64 atom
#define rf *(F*)&r        //!< retrieve double atom
#define rm rG[-8]         //!< (m)alloc bucket id
#define rt rG[-5]         //!< (t)ype id
#define ru rG[-6]         //!< list attrib(u)tes
#define rr rG[-7]         //!< (r)eference count
#define rn rI[-1]         //!< vector le(n)gth
#define rI ((I*)r)        //!< cast to list of ints
#define rF ((F*)r)        //!<         ..of doubles
#define rK ((K*)r)        //!<        ..of sublists
#define Rg ((S)r)[i]      //!<          ..to string
#define Ri rI[i]          //!<      i'th int32 of r
#define Rj rJ[i]          //!<      i'th int64 of r
#define Rk rK[i]          //!<  i'th subvector of r
#define rx rK[0]          //!<     1st element of r
#define ry rK[1]          //!<                ..2nd
#define rz rK[2]          //!<                ..3rd
#define rxu ptr(rx)[-6]   //!< attrs of 1st element
#define ryu ptr(ry)[-6]   //!< attrs of 2st element
#define rG ptr(r)

#define zG ptr(z)
#define fG ptr(f)

#define A(x) ({J _j=(J)(x);!_j||_j>>52?KF:15&_j>>48;})
#define Ax A(x)           //!< is x atom or vector?
#define Ay A(y)           //!< is y atom or vector?
#define Az A(z)           //!< is z atom or vector?
#define Ar A(r)           //!< is r atom or vector?

//! attempt to release x upon execution of e:
#define X0(e)   ({typeof(e)_e=(e);r0(x);_e;})
#define Y0(e)   ({typeof(e)_e=(e);r0(x);_e;})

//! mmap|munmap
extern I txfatal(S s);
#include <sys/mman.h>     //!< mmap|unmap
#include <sys/stat.h>     //!< stat|fstat
#include <fcntl.h>        //!< open|close
#define BASE              0x70000000L     //!< sbrk (2)
#define                   USE_AW_MALLOC   //!< enable aw_malloc posix shims
ZS mao(I d,szt n,szt o){ZJ p=BASE;p+=d?0:n;_*r=mmap((_*)(d?0:p-n),n,PROT_READ|PROT_WRITE|PROT_EXEC,d?MAP_PRIVATE:(MAP_ANON|MAP_PRIVATE|MAP_FIXED),d-!d,0);P(r==MAP_FAILED,txfatal((S)"mmap"),(S)0)R r;}
ZK mft(S s,J*n,J l){struct stat b;I d=open((_*)s,0);P(0>d,txfatal(s))R(K)(fstat(d,&b),s=(*n=l?MN(l,b.st_size):b.st_size)?mao(d,*n,b.st_size-*n):s,close(d),s);} //!< mmap l trailing bytes or entire file
ZS ma(I d,szt n){R mao(d,n,0);}ZK mf(S s,J*n){R mft(s,n,0);}

#if NOLIBC                //!< unix|linux
#include <unistd.h>       //!< write|read
#define Sn(s,n)           pn(s,n)         //!< string vector from first n bytes of s
//K m1(J n);V1(r0);V1(l0);K3(l1);K1(l2);K tn(I t,I n),r1(K),xiy(K x,I i,K y);K2(j2);J ws();K mf(S s,J*n);
_ aw_malloc_init(),*aw_malloc(szt n),*aw_realloc(_*p,szt n),aw_free(_*p);//!< *aw_calloc(size_t n,size_t sz);
K kK(I n),kC(I n),r1(K x),j2(K x,K y);_ r0(K x);K sr1(),pn(S s,I n);
ZI wb(G c){R write(1,&c,1);}ZG rb(){G c;R read(0,&c,1),c;}_ exit(I);//S mmap();I open(),close(I d),fstat(),munmap();
//K dmp(S s,S x,J n){I d=open((V*)s,O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);Qs(0>d,(S)s)write(d,x,n);R close(d),0;}

ZI sln(S s)               {I r=0;W(*s++)r++;R r;}
ZS sch(S s,I c)           {W(*s-c)P(!*s++,(S)0)R s;}
ZS mcp(S d,S s,I n)       {W(n--)*d++=*s++;R d;}
ZS memmove(S d,S s,I n)   {P(s<d&&d<s+n,d+=n,s+=n;W(n--)*--d=*--s;d)R mcp(d,s,n);}
//void *memset(void *s, int c, size_t n);
ZS memset(S s,I c,I n)    {N(n,s[n]=c);R s;}
#define mmv memmove
#define mset memset
#define ABS(e)            ((0>(e))?(-(e)):(e))
#define strerror(e)       txsi("strerror: ",e)

//! math
#if (__x86_64__||i386)&&(!__TINYC__)
#define clz(n)            (__builtin_clz((UI)n))    //!< count leading zeros
#define clzl(n)           (__builtin_clzl((UJ)n))
#else
#define __(n)             i|=i>>n;
#define npw2(n)         __(1)__(2)__(4)__(8)__(16)  //!< round n up to the next power of 2
ZI dbj[32] =              {0,9,1,10,13,21,2,29,11,14,16,18,22,25,3,30,8,12,20,28,15,17,24,7,19,27,23,6,26,5,4,31};
static inline             I __lg2(UI i){npw2(i);R dbj[i*0x07C4ACDDU>>27];}
#define clz(i)            (31-__lg2((UI)i))
#define clzl(i)           (63-__lg2((UI)i))
#endif
static UI p10[] =         {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
static inline             I lg10(UI i){I t=(32-clz(i)+1)*1233>>12;R t-(i<p10[t]);}
#define ABS(e)            ((0>(e))?(-(e)):(e))


#else                     //!< use local stdlib

#include<string.h>        //!< str* mem*
#include<stdlib.h>        //!< *alloc free

#define sln(s)            ((UI)strlen((char*)s))
#define sch(s,c)          ((S)strchr((char*)s,c))
#define mcp(d,s,n)        ((S)memcpy((char*)d,(char*)s,n))
#define mmv(d,s,n)        ((S)memmove((char*)d,(char*)s,n))

#define ABS(e)            abs(e)

#endif                    //NOLIBC

//:~
