//! femtoline copyright (c) 2020 regents of kparc, bsd-2-clause

#include"b.h"

//#include <time.h>

/*
//! start timer
ext clock_t clk_start();

//! milliseconds lapsed since last clk_start()
ext UJ clk_stop();

//! calculate ms difference between start and end
ext UJ clk_diff(clock_t s, clock_t e);
*/

/*
clock_t start,end;

clock_t clk_start() {
	R start = clock();
}

UJ clk_diff(clock_t s, clock_t e) {
	R(e - s) * 1E3 / CLOCKS_PER_SEC;
}

UJ clk_stop() {
	end = clock();
	UJ r = clk_diff(start,end);
	start = end; //< allow chained clk_stop()
	R r;
}
*/

//#define       go()         //!< optional early init
//#define       ext()        //!< optional teardown

#define Lb     b->s        //!< string buffer (aka start)
#define Lt     b->t        //!< total alloc
#define Lf     b->f        //!< front (bytes behind caret)
#define Lg     b->g        //!< gap size
#define Lfg    (Lf+Lg)
#define Lfb    (Lb+Lf)
#define Lfbg   (Lfb+Lg)
#define Ln     (Lt-Lg)     //!< string length, alloc-(front+gap)
#define ZL     static L

Z_ gb_ini(L b,I n){Lt=Lg=n=n+!n;Lf=0;Lb=M1(n);}
ZL gb_new(I n){L r=(L)M1(sizeof(gb));R gb_ini(r,n),r;}
Z_ gb_inC(L b,I c){Z(!Lg,I bak=Lt-Lf;Lg=Lt;Lb=M2(Lb,Lt*=2);Z(bak,mmv(Lfbg,Lfb,bak)));Lb[Lf++]=c,--Lg;}
Z_ gb_inS(L b,S s,I n){Z(!s||!n,R)W(Lg<n)Lg=0,gb_inC(b,0),--Lf;mcp(Lfb,s,n),Lf+=n,Lg-=n;}

/*
void
gapbuf_move(struct gapbuf *b, ptrdiff_t amt)
{
    size_t len;
    char *dst, *src;
    if (amt < 0) {
        len = -amt;
        if (len > b->front)
            len = b->front;
        dst = b->buf + b->front + b->gap - len;
        src = b->buf + b->front - len;
        b->front -= len;
    } else {
        size_t back = b->total - b->front - b->gap;
        len = amt;
        if (len > back)
            len = back;
        dst = b->buf + b->front;
        src = b->buf + b->front + b->gap;
        b->front += len;
    }
    memmove(dst, src, len);
}
*/

#define sgn(i) ((i>0)-(i<0))
#define clip(i,m,mm) MN(mm,MN(m,ABS(i)))
#define min(a,b) ({typeof(b)_a=(a),_b=(b);_a<_b?_a:_b;})
#define max(a,b) ({typeof(b)_a=(a),_b=(b);_a>_b?_a:_b;})

#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#if 1
I  gb_mov(L b,I a){I l;S d,s;
 Z(0>a,l=-a;Z(Lf<l,l=Lf);d=Lfbg-l; s=Lfb -l;   Lf-=l)
  {    l= a;Z(Ln<l,l=Ln);d=Lfb   ; s=Lfbg  ;   Lf+=l;}
 R mmv(d,s,l);}
#else
#include <stddef.h>
I  gb_mov(L b,I a){pf("\n\nmov a=%d\n",a);P(!a,a)S d,s;I t=0>a;

	//a=ABS(a);pf("mov: a=(%d) t=%d sgn=%d abs=%d clip=%d ln|f=%d Lf=%d\n",a,t,sgn(a),ABS(a),min(t?Lf:Ln,ABS(a)),t?Ln:Lf,Lf);

	a=ABS(a);a=CLAMP(a,Lf,Ln);

	pf("mov: t=(%d) a=(%d) Lf=%d Ln=%d\n",t,a,Lf,Ln);

	d=s=Lfb+a*t;Lf+=a;
	mmv(d+Lg*t,s+Lg*!t,a);R 0;}
#endif

Z_ gb_bak(L b){Z(0<Lf,Lb[Lfg-1]=Lb[Lf-1];Lf--);}
Z_ gb_fwd(L b){Z(0<Ln,Lb[Lf]=Lb[Lfg];Lf++);}
Z_ gb_del(L b){Z(Lfg<Lt,Lg++);}
Z_ gb_bsp(L b){Z(Lf--,Lg++);}

L sL(S s,UI n)             {L r=gb_new(n);gb_inS(r,s,n);R r;}                  //!< line from str
L L0()                     {R sL("",0);}                                       //!< new empty line
I ln(L b)                  {R Ln;}                                             //!< line length

L lin(L b,UI i,G g)        {R gb_mov(b,i-Lf),gb_inC(b,g),b;}                   //!< insert byte at b[i]
L lins(L b,UI i,S s,UI n)  {R gb_mov(b,i-Lf),gb_inS(b,s,n),b;}                 //!< insert str at b[i]

L lc(L b,UI i,UI n)        {gb_mov(b,i-Lf);N(n,gb_del(b));R b;}                //!< cut b[i..i+n]
G li(L b,UI i)             {R Lb[(Lf<i)*Lg+i];}                                //!< item at
I lp(L b,UI i,UI n)        {P(!n||Ln<=i,0)Nj(n=MN(n,Ln-i),tx(li(b,i+j)));R n;} //!< tx part
I lo(L b)                  {R txn(Lb,Lf)+txn(Lfbg,Lt-Lfg);}                    //!< tx whole
L lj(L b,UI i)             {R gb_mov(b,i-Lf);}                                 //!< (j)ump move caret to i

_ lbk(L b)            {gb_bak(b);}
_ lfw(L b)            {gb_fwd(b);}
_ lbs(L b)            {gb_bsp(b);}
_ ldl(L b)            {gb_del(b);}

_ lsw(L b,UI i,UI j)  {R;} //!< nyi swap

_ O(L b){
	pf("frt=%d gap=%d tot=%d ln=%d\n",Lf,Lg,Lt,Ln);

	tx('|');N(Lf,tx(li(b,i)))txN('_',Lg);

	//pf("adv=%d\n",Lt-Lfg);
	//pf("PAST=%c\n",at(b,Lf+Lg));
	N(Lt-Lfg,tx(li(b,Lf+i)))pf("|\n");
}

_ test() {

	L b=sL("kelas",5);O(b);

	lin(b,ln(b),'K');O(b);
	lin(b,ln(b),'E');O(b);
	lin(b,ln(b),'L');O(b);

	lbk(b);O(b);
	lbk(b);O(b);

	gb_mov(b,-5);O(b);pf("\nlo(%d): ",Ln);lo(b);pf("\n");

	exit(0);

	pf("lo: ");lo(b);pf("\n");

	exit(0);

	lbk(b);O(b);
	lbk(b);O(b);
	lbk(b);O(b);
	lbk(b);O(b);
	lbk(b);O(b);
	lbk(b);O(b);
	lbk(b);O(b);
	lbk(b);O(b);
	lbk(b);O(b);
	lbk(b);O(b);
	lbk(b);O(b);
	lbk(b);O(b);

	lfw(b);O(b);
	lfw(b);O(b);
	lfw(b);O(b);
	lfw(b);O(b);
	lfw(b);O(b);
	lfw(b);O(b);
	lfw(b);O(b);
	lfw(b);O(b);
	lfw(b);O(b);
	lfw(b);O(b);
	lfw(b);O(b);
	lfw(b);O(b);

/*
	pf("\ntxl:");txl(b);pf("\n");
	pf(" xfer0-3: (%d)\n",out(b,0,3));
	pf(" xfer3-12: (%d)\n",out(b,3,12));
	pf(" xfer7-100: (%d)\n",out(b,70,100));
	pf(" xfer7-100: (%d)\n",out(b,0,100));
	//gb_bak(b);
	//gb_inc(b,'a');O(b);
*/

	//Nj(26,gb_inC(b,'a'+j),O(b));Nj(100,gb_bak(b),O(b));
	pf("\ncheck (len=%d):",ln(b));N(ln(b),pf("(%c)",li(b,i)));

	//pf("at(0)=%c\n",Lb[0]);
	//O(b);




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
