//! femtoline copyright (c) 2020 regents of kparc, bsd-2-clause

//! unicode prims
#if FUN
#define uff              (0x3f&*s++)
#define U4(c)            0xf0==(0xf8&c)
#define U3(c)            0xe0==(0xf0&c)
#define U2(c)            0xc0==(0xe0&c)
#define ubc(c)           UB[UN++]=c,UB[UN]=0 //!< accumulate
static UI cpt(S s)       {R U4(*s)?(0x07&*s++)<<18|uff<<12|uff<<6|uff:U3(*s)?(0x0f&*s++)<<12|uff<<6|uff:U2(*s)?(0x1f&*s++)<<6|uff:0;}
static UI rlu(G c)       {UI u=0;ubc(c);P(2>UN,0)if(u=cpt(UB))txn(UB,UN);if(u||4==UN)UN=0;R u;} //!< attempt to parse utfbuf
#else
#define LC()
static UI rlu(G c){R 0;}
#endif//FU8

//! raw terminal
#if FTC
#include<sys/ioctl.h>
#include<termios.h>
//#include <locale.h>
//#define LC()            setlocale(LC_ALL,"C.UTF-8")
//#define tc1(t)          cfmakeraw(&t);//!
static struct termios tco,tcn; //!< old new
#define tcg(t)            ioctl(0,TCGETS,&t)
#define tcs(t)            ioctl(0,TCSETS,&t)
#define tc1(t)            t.c_lflag&=~(ICANON|ECHO|ISIG),t.c_cc[VMIN]=1,t.c_cc[VTIME]=0;tcs(t) //!< blocking read(), disable echo, escapes and sighandlers
#define rltc()            tcg(tco),tcn=tco,tc1(tcn); //!< LC();todo !isatty(0)
Z_ Tc(){go();rltc();}
#else
Z_ Tc(){go();}
#endif

//! bracket balancer
#if FBB
#define Jp (x-rG)
#define Qb(c,a...)          P(c,ftx(7),a) //!< send audio bell on bracket misbalance
//! class                   !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
ZG cl(G c){P(!c,0)R 128>c?"  q     ()                 ;                               ( )                             ( ) "[c-32]:0;}
ZS bq(S x){W((x=sch(++x,'"'))&&!({I i=0;W('\\'==x[--i]){};1&i;})){};R x;} //!< ffwd quoted string w/escapes
ZI bb(K r,I c){G b[16];I p[16],a,n=0,t=-1;S s,x=rG-1;W(a=*++x)SW(cl(a),C('q',s=bq(x);Qb(!s,x,Jp)c=Jp==c?s-rG:s-rG==c?Jp:c,x=s;)
 C('(',Qb(16==++n,Jp)p[n]=Jp,b[n]=*x;Z(c==Jp,t=Jp))C(')',Qb(!n,Jp)Qb(b[n]!=*x-1-*x/64,p[n])c=Jp==c?p[n]:p[n]==t?Jp:c,--n))Qb(n,p[n])R c;}
ZI vmv(K r,I c,I n){I i=c+n;xnc(i,n,!sch((S)"(;)",cl(Rg)))R MN(MX(0,i),rn);} //!< move caret to next|prev {[(;)]}
#else
ZI bb(K r,I c){R c;}
ZI vmv(K r,I c,I n){R c;}
#endif//FBB

//! persistence
#if FIO
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
ZJ rlfsk(FILE*d,J j,I f){R fseek(d,j,f);}ZJ rlfsz(char*x){FILE*f=fopen(x,"a+");P(!f,0)rlfsk(f,0,SEEK_END);J r=ftell(f);R fclose(f),r;}
ZK rla(K r){R r;I d=open(FHF,O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);P(0>d,r)write(d,rG,MN(rn,LMX));write(d,"\n",1);R close(d),r;}  //!< append
_*rlm1(char*f,J*n){*n=rlfsz(f);I d=open(f,O_RDWR,O_CREAT,0);_*r=mmap(0,1+*n,PROT_READ,MAP_SHARED,d,0);R close(d),r;}_ rlm0(_*a,J n){munmap(a,n);}
ZK rlr(){J j,l,n=0;S s,y=s=(S)rlm1(FHF,&n);P(!y||!n,kK(0));I c;K r=kK(c=HMX);N(c,Rk=s0)             //!< restore HMX lines of history from file
//c=-c;j=-1; N(n+1,Z('\n'==Yg||n==i,l=i-j-1;Z(IN(1,l,LMX),rK[HMX+c++]=Sn(y+j+1,l);Z(!c,goto EX));j=i))EX:R rlm0(y,n),drp(c,r);}   //!< top down
  j= n;_N(n,l='\n'==y[i];Z(l||!i,l+=i;Z(IN(1,j-l,LMX),rK[--c]=Sn(y+l,j-l);Z(!c,goto EX));j=i))                                   //!< bottom up
  EX:R rlm0(y,n),drp(c,r),r;}
#else
ZK rlr(){R kK(0);}ZK rla(K r){R r;}
#endif//FIO

///:~
