//! better c, public domain

typedef void _;typedef unsigned char*S,G;typedef int I;typedef unsigned long long UJ;typedef long long J;typedef unsigned int UI;
typedef struct k{UI m;G t;UI n;S x;}k;typedef k*K;

#define R             return
#define  W(a...)      while(({a;}))
#define  N(n,a...)    {I _n=(n),i=-1;W(++i<_n){a;}}
#define Nj(n,a...)    {I _n=(n),j=-1;W(++j<_n){a;}}
#define _N(n,a...)    {I i=(n);W(i--){a;}}
#define  P(b,a...)    if(b)R({a;});
#define  Z(b,a...)    if(b){a;}else
#define  C(i,a...)    case i:{a;}break;
#define SW(i,c,a...)  switch(i){c default:a;}
#define MN(x,y)       ((y)>(x)?(x):(y))
#define MX(x,y)       ((y)>(x)?(y):(x))
#define IN(l,x,r)     ((l)<=(x)&&(x)<=(r))

//! statics
#define Z_            static _
#define ZI            static I
#define ZS            static S
#define ZG            static G
#define ZJ            static J
#define ZK            static K

//! malloc
ZI ws=0;
#include<stdlib.h>    //!< malloc calloc realloc free
#define m1(n)         (ws+=n,malloc(n))
#define m2(t,n)       (ws+=sizeof(t)*n,calloc(sizeof(t),n))
#define m3(a,n)       realloc(a,n)
#define m0            free

//! rxy accessors
#define xG            ((G*)x->x)
#define yG            ((G*)y->x)
#define rG            ((G*)r->x)
#define xK            ((K*)x->x)
#define yK            ((K*)y->x)
#define rK            ((K*)r->x)
#define Xg            xG[i]
#define Yg            yG[i]
#define Rg            rG[i]
#define Xk            xK[i]
#define Rk            rK[i]
#define xn            (x->n)
#define yn            (y->n)
#define rn            (r->n)

#define xm            x->m
#define xt            x->t
#define xx            x->x
#define xnt           (xn*xt)
#define SZk           sizeof(k)
#define SZK           sizeof(K)

#if NOLIBC
 ZI sln(S s)              {I r=0;W(*s++)r++;R r;}
 ZS sch(S s,I c)          {W(*s-c)P(!*s++,(S)0)R s;}
 ZS mcp(S d,S s,I n)      {W(n--)*d++=*s++;R d;}
 ZS mmv(S d,S s,I n)      {P(s<d&&d<s+n,d+=n,s+=n;W(n--)*--d=*--s;d)R mcp(d,s,n);}
#else
 #include<string.h>
 #define sln(s)           ((UI)strlen((char*)s))
 #define sch(s,c)         ((S)strchr((char*)s,c))
 #define mcp(d,s,n)       ((S)memcpy((char*)d,(char*)s,n))
 #define mmv(d,s,n)       ((S)memmove((char*)d,(char*)s,n))
#endif//NOLIBC


//:~
