//! femtoline copyright (c) 2020 regents of kparc, bsd-2-clause

#include"c.h"

//! simple line buffer
#define kK(n)             ma(n,SZK)
#define S0                r1(s0)
#define tak(i,x)          x=tk(x,i)
#define drp(i,x)          x=ct(x,0,i)
#define cut(i,n)          r=ct(r,i,n)
#define ins(i,x)          r=xy(r,i,x)
#define XY(x,y)           sw(x,y)
#define rleql             eq
#define WS                ws

#define PAD               8
#define rr(f)             P(!x,(K)0)Z(SZK==xt,N(xn,f(Xk)));
#define ss(s)             Sn((S)s,sln((S)s))
#define X(i,n)            e1(r0,x,i,n)
#define R0                R(K)0;
#define Rx                R x;
#define MV(a,b,c)         mmv(xx+a+b*xt,xx+c,xnt-c)

ZK s0;
ZK ma(I n,I t){K x=m1(SZk);xt=t,xr=0,xm=n*t,xn=n,xx=m1(xm);ws+=SZk+xm;Rx}                              //!< (ma)lloc K[n*t]
ZK fr(K x){rr(fr)ws-=SZk+xm,m0(xx),m0(x);R0}                                                           //!< (fr)ee memory
ZK r1(K x){P(!x,(K)0)R xr++,x;}ZK r0(K x){P(s0==x,xr=0,x)R--xr?x:fr(x);}                                             //!< (r)efcount +-
ZK e1(K(*f)(),K x,I j,I n){Z(SZK==xt,N(n,f(xK[j+i])));Rx}                                              //!< (e)ach
ZK Sn(S s,I n){K x=ma(n,1);mcp(xx,s,n);Rx}                                                             //!< new string of len n
ZS xp(K x,I n){I t=n*xt;Z(xnt+t>xm,t=t+xt*PAD,ws+=t,xx=m2(xx,xm+=t));R xx+xnt;}                        //!< (expand)alloc
ZS bl(K x,I i,I n){i*=xt;Z(i>xnt,i=xnt);Z(0<n,xp(x,n),MV(i,n,i),xn+=n);R xx+i;}                        //!< insert (bl)anks
ZK xy(K x,I i,_*y){S s=bl(x,i,1);SW(xt,C(1,*((S)s)=*(S)y)C(SZK,*((K*)s)=(K)y));Rx}                     //!< (ins)ert y at x[i]
ZK ct(K x,I i,I n){P(i>=xn,x)I t=xn;Z(i+n>=xn,X(xn-i,xn),xn=i)X(i,n),t=(i+n)*xt,MV(0,i,t),xn-=n;Rx}    //!< (cut)out chars x[i..i+n]
ZK tk(K x,I n){P(n>xn,drp(xn,x))X(n,xn-n),xn=n;Rx}                                                     //!< take|drop
ZK va(K x,K y){*((K*)xp(x,1))=y,++xn;Rx}                                                               //!< append y to a
ZK gc(K x){rr(gc)I d=xm-xnt;Z(d,xx=m2(xx,xm=xnt),ws-=d);Rx}                                            //!< compact unused ram
ZG eq(K x,K y){P(xn-yn,0)N(xn,P(Xg-Yg,0))R 1;}                                                         //!< compare
ZK sw(K*k,K y){R r0(*k),*k=y;}                                                                         //!< free x and replace with y
ZK go(){R s0=r1(ss(""));}ZK ex(){printf("sigint *** ws=%d s0->r=%d\n",ws,s0->r);R0;}

//! roll your own
// #define go()         //!< optional early init
// #define ex()         //!< optional teardown
// #define tak(i,x)     //!< drop x[i..xn]
// #define drp(i,x)     //!< drop x[0..i]
// #define ins(i,c)     //!< insert c at r[i]
// #define cut(i,n)     //!< cut r[i..i+n]
// #define r0(x)        //!< release x
// ZG rleql(K x,K y)    //!< equality test
// #define S0           //!< empty string
// #define ss           //!< K from string
// #define WS           //!< current heap size
// ZK Sn(S s,I n)       //!< new line of len n

//:~
