//! malloc/free: list join (k[cifs] k[CIFS])

#if NOLIBC                //!< unix|linux

#define                   USE_AW_MALLOC   //!< enable aw_malloc posix shims

_ aw_malloc_init(),*aw_malloc(szt n),*aw_realloc(_*p,size_t n),aw_free(_*p),*aw_calloc(size_t n,size_t sz);

K K0(),kK(I n);_ r0(K x);J wss();

//,kC(I n),r1(K x),sr1(),j2(K x,K y),pn(S s,I n);
//#define Sn(s,n)           pn(s,n)         //!< string vector from first n bytes of s
//K m1(J n);V1(r0);V1(l0);K3(l1);K1(l2);K tn(I t,I n),r1(K),xiy(K x,I i,K y);K2(j2);J ws();K mf(S s,J*n);

//! evaluate e and attempt to release xyz:
#define X0(e)   ({typeof(e)_e=(e);r0(x);_e;})
#define Y0(e)   ({typeof(e)_e=(e);r0(y);_e;})
#define Z0(e)   ({typeof(e)_e=(e);r0(z);_e;})

#define M1                aw_malloc
#define M2                aw_realloc
#define M0                aw_free

#else                     //!< use local stdlib

#include<stdio.h>
#include<string.h>        //!< str* mem*
#include<stdlib.h>        //!< *alloc free

#define M1                malloc
#define M2                realloc
#define M0                free
#define tx                putchar
#define RX                getchar
#define pf                printf

J wss();

#endif//NOLIBC


//:~
