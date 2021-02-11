//! malloc/free: list join (k[cifs] k[CIFS])
//! K is mturnnnn: (m)embucket, (t)ype, attrib(u)tes, (r)efcount, le(n)gth

#include"c.h"

ZK M[31],s0;ZJ W; //!< M memory buckets, W wssize

K m1(J n){K x,r;                //!< allocate a memory block
 I i=29-clz(n+7),j=i;             //!< i is the bucket id, log2((UI)n+7)
 //Nj(32,I i=j;txpi(j,4),txpi(i+7,4),txpi(clz(i+7),4), txpi(clzl(i+7),4),nl())nl();exit(0);
 P((x=M[i]),M[i]=xx,x);         //!< if there is an available block on top of the list M[i], pop and  and return
 W(!(x=++j<31                   //!< otherwise, scan for a free block of a larger size
   ?M[j]:                       //!< if one exists, use it, otherwise:
   8+(K)ma(0,16L<<(j=MX(18,i))))); //!< ..mmap more ram, at least 4mb + 8 bytes for mturnnnn preamble
 xm=i,M[j]=xx,r=x;              //!< assign bucket id to the new block and push it on top of the list M[j]
 //! fill smaller empty buckets as follows:
 W(i<j)                         //!< j-i are empty memory slots
  x+=16L<<xm,                   //!< the next unoccupied memory region x..
  M[*(J*)(x-8)=i++]=x,xx=0;     //!< ..is assigned to a bucket in a corresponding slot, with 8-byte foreword.
 R r;}                          //!< zero out the first element.

//V1(l0){if((J)xy)l0(xy),l0(xz);xx=M[xm],M[xm]=x;}K3(l1){K r=m1(24);R rt=8,rn=3,rx=x,ry=y,rz=z,r;}K1(l2){R kp((S)"[]");}//!< struct/fixedarray experiment

//!     0 1 2 3 4 5 6 7
//!     K c h i j e f s ()
J nt[]={8,1,2,4,8,4,8,8  };    //!< list int8 int16 int32 int64 real double sym
#define NX nt[xt]               //!< chijefs
K r1(K x){P(Ax,x)R++xr?x:(exit(1),(K)0L);}J wss(){R W;}
_ r0(K x){
 if(Ax||!x||KS==xt)R;           //!< if x is 0, an atom or a symbol, r0 is nop.
 //if(8==xt){l0(x);R;}          //!< (structs are nyi)
 if(xr){--xr;R;}                //!< once refcount is 0, return the object to the heap:
 if(!xt||KS<xt)                 //!< for mixed and non-symbol typed vectors...
  N1(xn,r0(Xx))                 //!< decrement refcounts of children recursively,
 W-=16L<<xm,xx=M[xm],M[xm]=x;}  //!< ...and place it on top of its M[xm] linked list.

//! allocate a vector of n items of type t
K tn(I t,I n){K x=m1(MX(1,n)*nt[KS<t?0:t]);R W+=16L<<xm,xu=0,xt=t,xn=n,x;}

//! vector factory:
 K kK(I n){R tn( 0,n);}                     //!< list of lists
 K kC(I n){R tn(KC,n);}                     //!< a char vector
ZK kI(I n){R tn(KI,n);}                     //!<  list of ints
ZK kJ(I n){R tn(KJ,n);}                     //!<   ...of longs
ZK kS(I n){R tn(KS,n);}                     //!< ...of symbols
 K pn(S s,I n){R(K)mcp((_*)kC(n),s,n);}     //!< char vector out of first n bytes of s
ZK kp(S s){R pn(s,sln(s));}                 //!< char vector out of a given string
ZK kc(J x){R(K)(KC<<48|x);}                 //!< char atom
ZK ki(UI x){R(K)(KI<<48|(J)x);}             //!< new int32
//ZK kf(F f){R*(K*)&f;}                       //!< new double
ZK ks(J x){R(K)(KS<<48|x);}                 //!< new symbol
//ZK _qs(S s){R(K)(QQ<<48|(J)s);}             //!< error atom, s is strerror
//ZK jc(K x,C c){R j2(x,kc(c));}              //!< append char to string
#define qs(s) _qs((S)(s))
K sr1(){R r1(s0);}

//! insert items of y after the i-th element of x:
K xiy(K x,I i,K y){
 mcp(xG+NX*i,(_*)y,NX*yn);      //!< NX is the native width of x item type
 if(!yt)N(yn,r1(Yk))            //!< if y is an mixed list, increase refcounts of items in y
 R Y0(x);}                      //!< recursively decrease refcounts of y and return x

K j2(K x,K y){                  //!< join two lists
 I m=xn,n=m+(Ay?1:yn);          //!< m is the old size, n is the new one (inc n by 1 if y is an atom)
 P(!m&&!xt,X0(y))               //!< if x is empty, decrease refcount of x and return y
 if(xr||8+NX*n>16L<<xm)         //!< if x has references, or there is not enough space left in the x's ram block...
   x=xiy(tn(xt,n),0,x);         //!< ..copy it to a new array of the size n
 else xu=0,xn=n;                //!< otherwise, the size of x to the new size, then:
 Ay?(K)mcp(xG+NX*m,(_*)&y,(I)NX)       //!< for atoms, append the new item via mcp
   :xiy(x,m,y);R x;}            //!< for lists, use xiy to append y items to the x's tail

//! posix wrappers
#ifdef USE_AW_MALLOC
_ aw_malloc_init(){s0=kC(0),W=0;}                     //!< seed allocation
_*aw_malloc(szt n){P(!n,(_*)0)R(_*)tn(KC,(I)n);}      //!< allocate a list of n bytes
_*aw_realloc(_*p,szt n){K x=(K)p;                     //!< if ptr is null, realloc() is same as malloc
    P(!x||!n,Z(x,aw_free(p));aw_malloc(n?n:1))        //!< if size is 0 and ptr is not, ptr is freed and a new 1b-sized object is allocated
    P(KC-xt,("`nyi"),(_*)0)                        //!< realloc only supports char-typed lists
    P(xn<=(I)n||(!xr&&8+NX*(J)n<16L<<xm),xu=0,xn=n,p) //!< if new size is less than current, or x has no refs and there is enough space in the block, set xn to requested length and return x
    R(_*)xiy(tn(xt,n),0,x);}                          //!< otherwise, copy x to a fresh list of the requested size and release the old one.
_*aw_calloc(szt n,szt sz){                            //!< allocate n*sz bytes and fill with zeroes:
    I nn=MX(1,n)*MX(1,sz);K x=tn(KC,nn);              //!< calculate new length and allocate a new list
    N(nn/8,xJ[i]=0LL)N(nn%8,xG[nn-i]=0)R(_*)x;}       //!< zero out first with 8-byte stride, then byte-wise
    //R mset((_*)x,0,nn);}                            //!< zero out using memset(3)
_ aw_free(_*p){r0((K)p);}
J aw_malloc_used(){R wss();}
#endif

//:~
