//! femtoline copyright (c) 2020 regents of kparc, bsd-2-clause

#include"c.h"

//! simple line buffer
#define kK(n)             $buf(n,SZK)
#define S0                $buf(0,1)
#define tak(i,x)          x=$tak(x,i)
#define drp(i,x)          x=$cut(x,0,i)
#define cut(i,n)          r=$cut(r,i,n)
#define ins(i,x)          r=$ins(r,i,x)
#define va                $app
#define Sn                $str
#define rleql             $cmp
#define r0(x)             (x)
#define r1(x)             (x)
#define WS                (ws)
#define go()

#define PAD               8
#define rr(f)             P(!x,(K)0)Z(SZK==xt,N(xn,f(Xk)));
#define $sn(s)            $str((S)s,sln((S)s))
#define X(i,n)            e1($del,x,i,n)
#define R0                R(K)0;
#define Rx                R x;
#define MV(a,b,c)         mmv(xx+a+b*xt,xx+c,xnt-c)

ZK e1(K(*f)(),K x,I j,I n){Z(SZK==xt,N(n,f(xK[j+i])));R x;}                                             //!< (e)ach
ZK $buf(I n,I t){K x=m2(k,1);xt=t,xm=n*t,xn=n,xx=m1(xm);Rx}                                             //!< (new)buffer
ZK $str(S s,I n){K x=$buf(n,1);mcp(xx,s,n);Rx}                                                          //!< new ascii(str)
ZK $del(K x){rr($del)ws-=xm+SZk,m0(xx),m0(x);R0}                                                        //!< (del)etestr
ZS $inc(K x,I n){I t=n*xt;Z(xnt+t>xm,t=t+xt*PAD,ws+=t,xx=m3(xx,xm+=t));R xx+xnt;}                       //!< (increase)alloc
ZS $inj(K x,I i,I n){i*=xt;Z(i>xnt,i=xnt);Z(0<n,$inc(x,n),MV(i,n,i),xn+=n);R xx+i;}                     //!< (inj)ectblanks
ZK $ins(K x,I i,_*y){S s=$inj(x,i,1);SW(xt,C(1,*((S)s)=*(S)y)C(SZK,*((K*)s)=(K)y));Rx}                  //!< (ins)ert
ZK $cut(K x,I i,I n){P(i>=xn,x)I t=xn;Z(i+n>=xn,X(xn-i,xn),xn=i)X(i,n),t=(i+n)*xt,MV(0,i,t),xn-=n;Rx}   //!< (cut)outchars
ZK $tak(K x,I n){P(n>xn,drp(xn,x))X(n,xn-n),xn=n;Rx}                                                    //!< drop|take
ZK $app(K x,K y){*((K*)$inc(x,1))=y,++xn;Rx}                                                            //!< append y to a
ZK $zip(K x){rr($zip)I d=xm-xnt;Z(d,xx=m3(xx,xm=xnt),ws-=d);Rx}                                         //!< compact mem
ZG $cmp(K x,K y){P(xn-yn,0)N(xn,P(Xg-Yg,0))R 1;}                                                        //!< compare

/*
roll your own

#define tak(i,x)
#define drp(i,x)
#define ins(i,c)
#define cut(i,n)
#define go()
ZG rleql(K x,K y)
ZK Sn(S s,I n)
ZI WS()
ZI
*/

//:~
