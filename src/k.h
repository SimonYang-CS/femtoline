//! femtoline copyright (c) 2020 regents of kparc, bsd-2-clause

#include"c.h"

#define WS                ws
#define va                j2
#define R0                R(K)0;
ZK go()                   {R0;}
ZK ext()                  {R0;}
#define S0                sr1()
#define cmp(x,y)          eq(x,y)
ZG eq(K x,K y){P(xn-yn,0)N(xn,P(Xg-Yg,0))R 1;}                                                         //!< compare

typedef struct gb{S buf;I total;I front;I gap;}gb;typedef gb*V;
#define Vb b->buf
#define Vt b->total
#define Vf b->front
#define Vg b->gap
#define Vfg (Vf+Vg)
#define Vfb (Vf+Vb)
#define Vfbg (Vfb+Vg)

_ vini(V b,I n){Vt=Vg=n;Vf=0;Vb=M1(n);}
_ vinC(V b,I c){
	Z(!Vg,
		I bk=Vt-Vf;Vg=Vt;Vt*=2;
		Vb=M2(Vb,Vt);mmv(Vfbg,Vfb,bk)
	);
	Vb[Vf]=c;++Vf,--Vg;}

_ vinS(V b,S s){
	I n=sln(s);W(Vg<n)Vg=0,vinC(b,0),--Vf;
	mcp(Vfb,s,n),Vf+=n,Vb-=n;}

_ vmov(V b,I a){I l;S d,s;
	Z(0>a,l=-a;Z(Vf<l,l=Vf);d=Vfbg-l;s=Vfb-l;Vf-=l)
     {I bk=Vt-Vfg;l=a;Z(bk<l)l=bk;d=Vfb;s=Vfbg;Vf+=l;}
    mmv(d,s,l);}

_ vbkw(V b){Z(0<Vf,Vb[Vf+Vg-1]=Vb[Vf-1];--Vf);}
_ vfwd(V b){I bk=Vt-Vf+Vg;Z(0<bk,	Vb[Vf]=Vb[Vfg]);}
_ vdel(V b){Z(Vt>Vfg)++Vg;}_ vbkp(V b){Z(Vf,Vf--,++Vg);}

/*
_ vout(V b,FILE*o){
    fwrite(Vb,1,Vf,o);
    S back_start=Vfbg;
    I back_len=Vt-Vfg;
    fwrite(back_start,1,back_len,o);}

_ vfre(V b){M0(Vb),Vb=0;}
*/

/*

//! simple line buffer
#define kK(n)             ma(n,SZK)
#define S0                r1(s0)
#define tak(i,x)          x=tk(x,i)
#define drp(i,x)          x=ct(x,0,i)
#define cut(i,n)          r=ct(r,i,n)
#define ins(i,x)          r=xy(r,i,x)
#define cmp(x,y)          eq(x,y)
#define YX(x,y)           sw(x,y)

#define PAD               8
#define rr(f)             P(!x,(K)0)Z(SZK==xt,N(xn,f(Xk)));
#define ss(s)             Sn((S)s,sln((S)s))
#define X(i,n)            e1(r0,x,i,n)
#define R0                R(K)0;
#define Rx                R x;
#define MV(a,b,c)         mmv(xx+a+b*xt,xx+c,xnt-c)

ZK s0;
ZK ma(I n,I t){K x=M1(SZk);xt=t,xr=0,xm=n*t,xn=n,xx=M1(xm);ws+=SZk+xm;Rx}                              //!< (ma)lloc K[n*t]
ZK fr(K x){rr(fr)ws-=0+xm,M0(xx),M0(x);R0}                                                             //!< (fr)ee memory
ZK e1(K(*f)(),K x,I j,I n){Z(SZK==xt,N(n,f(xK[j+i])));Rx}                                              //!< (e)ach
ZK Sn(S s,I n){K x=ma(n,1);mcp(xx,s,n);Rx}                                                             //!< new string of len n
ZS xp(K x,I n){I t=n*xt;Z(xnt+t>xm,t=t+xt*PAD,ws+=t,xx=M2(xx,xm+=t));R xx+xnt;}                        //!< (expand)alloc
ZS bl(K x,I i,I n){i*=xt;Z(i>xnt,i=xnt);Z(0<n,xp(x,n),MV(i,n,i),xn+=n);R xx+i;}                        //!< insert (bl)anks
ZK xy(K x,I i,_*y){S s=bl(x,i,1);SW(xt,C(1,*((S)s)=*(S)y)C(SZK,*((K*)s)=(K)y));Rx}                     //!< (ins)ert y at x[i]
ZK ct(K x,I i,I n){P(i>=xn,x)I t=xn;Z(i+n>=xn,X(xn-i,xn),xn=i)X(i,n),t=(i+n)*xt,MV(0,i,t),xn-=n;Rx}    //!< (cut)out chars x[i..i+n]
ZK tk(K x,I n){P(n>xn,drp(xn,x))X(n,xn-n),xn=n;Rx}                                                     //!< take|drop
ZK va(K x,K y){*((K*)xp(x,1))=y,++xn;Rx}                                                               //!< append y to a
ZK gc(K x){rr(gc)I d=xm-xnt;Z(d,xx=M2(xx,xm=xnt),ws-=d);Rx}                                            //!< compact unused ram
ZG eq(K x,K y){P(xn-yn,0)N(xn,P(Xg-Yg,0))R 1;}                                                         //!< compare
ZK sw(K*k,K y){R r0(*k),*k=y;}                                                                         //!< free x and replace with y
ZK go(){R s0=r1(ss(""));}
ZK ext(){R0;}


*/

//! roll your own
// #define go()         //!< optional early init
// #define ext()        //!< optional teardown
// #define tak(i,x)     //!< drop x[i..xn]
// #define drp(i,x)     //!< drop x[0..i]
// #define ins(i,c)     //!< insert c at r[i]
// #define cmp(x,y)     //!< fast compare
// #define cut(i,n)     //!< cut r[i..i+n]
// #define r0(x)        //!< release x
// ZG rleql(K x,K y)    //!< equality test
// #define S0           //!< empty string
// #define ss           //!< K from string
// #define WS           //!< current heap size
// ZK Sn(S s,I n)       //!< new line of len n

//:~

#define tak(i,x)     //!< drop x[i..xn]
#define drp(i,x)    (0)//!< drop x[0..i]
#define ins(i,c)    (0)//!< insert c at r[i]
#define cut(i,n)    (0) //!< cut r[i..i+n]
