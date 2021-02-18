//! femtoline copyright (c) 2020 regents of kparc, bsd-2-clause

#include"b.h"

//#define      go()         //!< optional init nyi
//#define      ext()        //!< optional teardown nyi

#define Lb     b->s          //!< string buffer (aka start)
#define Lt     b->t          //!< total alloc
#define Lf     b->f          //!< front (bytes behind caret)
#define Lg     b->g          //!< gap size
#define Lfg    (Lf+Lg)
#define Lfb    (Lb+Lf)
#define Lfbg   (Lfb+Lg)
#define Ln     (Lt-Lg)       //!< string length
#define ZL     static L

//! basic gap buffer
_ gb_ini(L b,I n){Lt=Lg=n=n+!n;Lf=0;Lb=M1(n);}
L gb_new(I n){L r=(L)M1(SZ(gb));R gb_ini(r,n),r;}
_ gb_inC(L b,I c){Z(!Lg,I bak=Lt-Lf;Lg=Lt;Lb=M2(Lb,Lt*=2);mmv(Lfbg,Lfb,bak));Lb[Lf++]=c,--Lg;}
_ gb_inS(L b,S s,I n){Z(!s||!n,R)W(Lg<n)Lg=0,gb_inC(b,0),--Lf;mcp(Lfb,s,n),Lf+=n,Lg-=n;}
_ gb_mov(L b,I a){I l;S d,s;d=s=Lfb,l=0>a,a=MN(a,Ln*!l-Lf),d+=l?Lg+a:0,s+=l?a:Lg;Lf+=a,mmv(d,s,ABS(a));}
_ gb_bak(L b){Z(0<Lf,Lb[Lfg-1]=Lb[Lf-1];Lf--);}
_ gb_fwd(L b){I bak=Ln-Lf;Z(0<bak,Lb[Lf]=Lb[Lfg];Lf++);}
I gb_del(L b){R Lfg<Lt?Lg++:0;}
_ gb_bsp(L b){Z(Lf--,Lg++);}

L LN(S s,UI n)           {L r=gb_new(n);gb_inS(r,s,n);R r;}    //!< line from str
L L0()                   {R LN("",0);}                         //!< new empty line
I li(L b,UI i)           {R Lb[(Lf<=i)*Lg+i];}                 //!< item at i
I ln(L b)                {R Ln;}                               //!< line length
I lff(L b,UI i,UI n)     {Nj(n=MN(n,Ln-i),tx(li(b,i+j)));R n;} //!< flush line fragment
I lfl(L b)               {R txn(Lb,Lf)+txn(Lfbg,Lt-Lfg);}      //!< flush line

_ gb_test();

Z_ gb_dbg(L b){
	pf("\nfrt=%d gap=%d tot=%d ln=%d\n",Lf,Lg,Lt,Ln);
	tx('|');N(Lf,tx(li(b,i)))txN('_',Lg);
	N(Lt-Lfg,tx(li(b,Lf+i)))pf("|\n");}

#define O() gb_dbg(r)

_ gb_test() {

	R;

	L r=LN("kelas",5);ljp(0);O();

	lin('1');O();
	lin('2');O();

	R;

	r=LN("kelas",5);O();

	lin('K');O();
	lin('E');O();
	lin('L');O();

	lbk();O();
	lbk();O();

	exit(0);

	N(16,lbk(),O())
	N(16,lfw(),O())

/*
	pf("\ntxl:");txl(b);pf("\n");
	pf(" xfer0-3: (%d)\n",out(b,0,3));
	pf(" xfer3-12: (%d)\n",out(b,3,12));
	pf(" xfer7-100: (%d)\n",out(b,70,100));
	pf(" xfer7-100: (%d)\n",out(b,0,100));
	//gb_bak(b);
	//gb_inc(b,'a');O(b);
	//Nj(26,gb_inC(b,'a'+j),O(b));Nj(100,gb_bak(b),O(b));
	//pf("at(0)=%c\n",Lb[0]);
	//O(b);
*/

}

//_ vfre(V b){M0(Vb),Vb=0;}

//#define ins(i,c)    (0)//!< insert c at r[i]
//#define cut(i,n)    (0) //!< cut r[i..i+n]

// #define tak(i,x)     //!< drop x[i..xn]
// #define drp(i,x)     //!< drop x[0..i]
// #define cmp(x,y)     //!< fast compare
// #define cut(i,n)     //!< cut r[i..i+n]
// #define r0(x)        //!< release x
// ZG rleql(K x,K y)    //!< equality test
// #define ss           //!< K from string
// #define WS           //!< current heap size
// ZK Sn(S s,I n)       //!< new line of len n


//#define tak(i,x)     //!< drop x[i..xn]
//#define drp(i,x)    (0)//!< drop x[0..i]


/*
_ vout(V b,FILE*o){
    fwrite(Vb,1,Vf,o);
    S back_start=Vfbg;
    I back_len=Vt-Vfg;
    fwrite(back_start,1,back_len,o);}

_ vfre(V b){M0(Vb),Vb=0;}
*/

/*

//! simplest possible line buffer
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

/*
 Z(0>a,l=-a;Z(Lf<l,l=Lf);d=Lfbg-l; s=Lfb -l;   Lf-=l)
  {I bak=Ln-Lf;l=a;Z(bak<l,l=bak);d=Lfb;s=Lfbg;Lf+=l;}
 pf("d=(%s) s=(%s) l=%d\n",d,s,l);
 R mmv(d,s,l);

 Z(0>a,   Z(  -Lf<a, a=  -Lf);d=Lfbg+a; s=Lfb  +a; Lf+=a;)
  {       Z(Ln-Lf<a, a=Ln-Lf);d=Lfb   ; s=Lfbg   ; Lf+=a;}

 Z(0>a,   Z(t*Ln-Lf<a, a=t*Ln-Lf);Lf+=a   ; d=Lfbg ; s=Lfb  ;       )
  {       Z(t*Ln-Lf<a, a=t*Ln-Lf);          d=Lfb  ; s=Lfbg ; Lf+=a;}
*/

//:~
