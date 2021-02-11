#include<unistd.h>  //!< size_t
typedef void _;typedef unsigned char*S,G;typedef unsigned short H;typedef int I;typedef double F;typedef unsigned long long UJ,K;typedef long long J;typedef unsigned int UI;typedef size_t szt;

static UI ws=0;

#define  R                return                                 //!< usually K.
#define  W(a...)          while(({a;}))                          //!< while is fine.
#define  N(n,a...)        {I _n=(n),i=-1;W(++i<_n){a;}}          //!< no stinking loops.
#define Nj(n,a...)        {I _n=(n),j=-1;W(++j<_n){a;}}          //!< staple inner loop i,j
#define _N(n,a...)        {I i=(n);W(i--){a;}}                   //!< walk something backwards.
#define N1(n,a...)        {I i=0,_n=(n);do{a;}while(++i<_n);}    //!< do at least one iteration.
#define  P(b,a...)        if(b)R({a;});                          //!< "bail early" predicate aka panic.
#define  Z(b,a...)        if(b){a;}else                          //!< be sure to terminate dangling else.
#define  C(i,a...)        case i:{a;}break;                      //!< case statement without a forgotten break.
#define SW(i,c,a...)      switch(i){c default:a;}                //!< default case is separated by a single comma.

//! avoid explicit ops as much as possible:
#define MN(x,y)           ((y)>(x)?(x):(y))
#define MX(x,y)           ((y)>(x)?(y):(x))
#define IN(l,x,r)         ((l)<=(x)&&(x)<=(r))

//! limit scope as much as you can:
#define ZG                static G
#define ZH                static G
#define ZI                static I
#define ZS                static S
#define ZJ                static J
#define ZK                static K
#define Z_                static _

//:~
