//! femtoline copyright (c) 2020 regents of kparc, bsd-2-clause

//! config
#include<stdio.h>
#define ftx               putchar       //!< your sink goes here
#define LMX               256           //!< max line length in bytes
#define HMX               32            //!< max lines of history
#define MMX               8*1024        //!< max heap (can be less than L*H, nyi)
#define AW                0             //!< use k9 backend

//! feature flags
#define FUN               0             //!< unicode support
#define FBB               1             //!< bracket balancer
#define FIO               1             //!< persist sessions
#define DBG               0             //!< show partial redraws
#define NOLIBC            1             //!< partially nyi
#define FHF               ".k"          //!< history filename

//! backend
#if AW
#include"a.h"
#else
#include"k.h"
#endif

//! init nextbyte nextline free
extern _ rl1(char*);K rl(G);I _rl(char*),rl0();

enum{noesc,esc,ebkt,ebkt0,esco};        //! line states
typedef struct rls{G st;I hl;I ct;char*pt;G le;G un;G ub[5];}rls; //! curr state
static rls RL;ZK r,x;ZI bk,ff,rfc; //!< (s)tate cur(r)line (x)istory (b)ack(f)wd (r)edraw from caret

//! state accessors
#define ST                RL.st         //!< current state
#define HL                RL.hl         //!< history line
#define v                 RL.ct         //!< caret pos
#define PT                RL.pt         //!< prompt
#define LE                RL.le         //!< last esc char
#define UN                RL.un         //!< utf counter
#define UB                RL.ub         //!< utf buffer
#define M(m)              ST=m          //!< change state
#define rfc0              rfc=0         //!< skip redraw from caret
#define bk1               bk=1          //!< caret back by one char

//! state shortcuts
#define home              goto HOME
#define end               goto END
#define del               goto DEL
#define xesc              goto XESC          //!< leave escape mode

//! history
#define H(i)              (xn?IN(0,i,xn-1)?xK[i]:0:0) //!< get item
#define H_                xK[xn-1]        //!< last line in history
#define hp                xn-1-HL         //!< inverted history pos
#define QH(n)             IN(0,hp+n,xn-1)   //!< validate new index
#define rll(n)            QH(n)?(HL-=n,r=H(hp)):0 //<! selector

//! terminal conrols
#define CTL(ctl,a...)     C(ctl,  a)
#define cA(a...)          CTL(1,  a)
#define cB(a...)          CTL(2,  a)
#define cD(a...)          CTL(4,  a)
#define cE(a...)          CTL(5,  a)
#define cK(a...)          CTL(11, a)
#define cL(a...)          CTL(12, a)
#define cN(a...)          CTL(14, a)
#define cP(a...)          CTL(16, a)
#define cT(a...)          CTL(20, a)
#define cU(a...)          CTL(21, a)
#define cW(a...)          CTL(23, a)
#define cESC(a...)        CTL(27, a)
#define cBSP(a...)        CTL(127,a)
#define cC                ( 3==c)
#define cF                ( 6==c)         //!< nyi
#define cTAB              ( 9==c)
#define cR                (18==c)
#define cNL               ('\n'==c)
#define cEO               (79==c)
#define cBKT              (91==c)
#define EOL               "\r\n"
#define EOT               (K)0x04         //!< (E)nd (O)f (T)ransmission
#define NOP               (K)0x00         //!< request next byte
#define EBKT              "\x1b["         //!< dec vt100 escape sequence
#define EL                "\x1b[K"        //!< (E)rase (L)ine to the end
#define ED                "\x1b[H\x1b[2J" //!< (E)rase (D)isplay command

//! ansi color
enum {AMB=227,RED=196,CYA=207};
#define clr(c)            txs("\x1b[38;5;"),txi(c),ftx('m') //<! color on
#define off()             txs("\x1b[0m")                    //<! color off
#define txnC(c,s,n)       txC(c,txn(s,n))
#define red(s,n)          txnC(RED,s,n)
#define cya(s,n)          txnC(CYA,s,n)
#define amb(s,n)          txnC(AMB,s,n)
#if DBG
#define txC(c,e...)       (clr(c),e,off())
#else
#define txC(c,e...)       (e)
#endif

#define In(l,r)           IN(l,c,r)
#define in(r)             In(*r,r[1])
#define le(x)             LE==x                      //!< prev escape char

//! string manip (^wt)
#define eol               (v==rn)
#define xnc(x,n,c)        W(x&&!x-rn&&(c))x+=n;      //!< move x while cond
#define rwd(c)            xnc(v,-1,c)                //!< rewind caret while cond
#define clp()             ({ff+=MN(0,rn-v+bk-ff);})  //!< clamp ff to eol
#define vv                (v?eol?v-1:v:1)            //!< fixme can be better
#define Rvv               rG[vv]                     //!< byte under caret
#define _Rv               rG[vv-1]                   //!< previous byte
#define swp()             c=Rvv,Rvv=_Rv,_Rv=c;       //!< swap curr<>prev
#define lg(x)             999<x?4:99<x?3:9<x?2:1

//! tx (p)ad (i)nt (B)anner (n)bytes (s)tr (N)times (p)ad (p)ad(i)nt (k)str (_)space (nl)ine (M)ark (f)+- (ws)size (p)rompt (e)seq
#define txi(x)  txpi(x,0)
#define txi2(x) txpi(x,2)
#define txi3(x) txpi(x,3)
ZI iS(UI y,S x){I n;_N(n=lg(y),x[i]='0'+y%10ul;y/=10)R n;} //!< itoa
ZI txn(S x,I n){P(!n,n)N(n,ftx(x[i]));R n;}ZI txs(char*x){R txn((S)x,sln((S)x));}ZI txN(G c,I n){N(n,ftx(c))R n;}
ZI txp(S x,I n,I p){R txN(' ',MX(0,p-n))+txn(x,n);}ZI txpi(UI x,I p){G s[4];x=iS(x,s);R txp(s,x,MN(4,p));}
ZI txk(K x){R txn(xG,xn);}ZI tx_(){R ftx(' '),1;}ZI nl(){R txs(EOL);}ZI txM(char s[2],G c){R ftx(s[!!c]);}
ZI txf(char*s,G c){R tx_(),txM("+-",c),txs((char*)s);}ZI txws(){R DBG?tx_()+txi(WS)+tx_():0;}ZI txpt(){R txws()+txs(PT);}
ZI txe(UI n,G c){R txs(EBKT)+txi(n)+ftx(c);}//!< E [ n CMD

//! refcard ^R
static char*hlp=
  "  erase a word    ^w\n"
  "  clear screen    ^l\n"
  "  fix a (t)ypo    ^t\n"
  "  catch sigint    ^c\n"
 #if FBB
  "  test balance    ^b\n"
  "  goto {[(;)]}    ^np\n"
 #endif
  "  alt home end    ^ae\n"
  "  kill<=>caret    ^udk\n"
  "  show history    tab\n"
//" quit session     esc-esc\n"
;

//! unicode prims
#if FUN
#include <locale.h>
#define LC()             setlocale(LC_ALL,"C.UTF-8")
#define uff              (0x3f&*s++)
#define U4(c)            0xf0==(0xf8&c)
#define U3(c)            0xe0==(0xf0&c)
#define U2(c)            0xc0==(0xe0&c)
#define ubc(c)           UB[UN++]=c,UB[UN]=0 //!< accumulate
static UI cpt(S s){R U4(*s)?(0x07&*s++)<<18|uff<<12|uff<<6|uff:U3(*s)?(0x0f&*s++)<<12|uff<<6|uff:U2(*s)?(0x1f&*s++)<<6|uff:0;}
static UI rlu(G c){UI u=0;ubc(c);P(2>UN,0)if(u=cpt(UB))txn(UB,UN);if(u||4==UN)UN=0;R u;} //!< attempt to parse utfbuf
#else
#define LC()
static UI rlu(G c){R 0;}
#endif//FU8

//! terminal mode
#include<termios.h>
static struct termios tco,tcn;
#define tcg(t)            tcgetattr(0,&t)
#define tcs(t)            tcsetattr(0,TCSANOW,&t)
#define tc1(t)            t.c_lflag&=~(ICANON|ECHO|ISIG),tcs(t)
#define rltc()            LC();tcg(tco),tcn=tco,tc1(tcn)
Z_ Tc(){go();rltc();}

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
ZK rla(K r){I d=open(FHF,O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);P(0>d,r)write(d,rG,MN(rn,LMX));write(d,"\n",1);R close(d),r;}  //!< append
_*rlm1(char*f,J*n){*n=rlfsz(f);I d=open(f,O_RDWR,O_CREAT,0);_*r=mmap(0,1+*n,PROT_READ,MAP_SHARED,d,0);R close(d),r;}_ rlm0(_*a,J n){munmap(a,n);}
ZK rlr(){J j,l,n=0;S s,y=s=(S)rlm1(FHF,&n);P(!y||!n,kK(0));I c;K r=kK(c=HMX);N(c,Rk=S0)             //!< restore HMX lines of history from file
//c=-c;j=-1; N(n+1,Z('\n'==Yg||n==i,l=i-j-1;Z(IN(1,l,LMX),rK[HMX+c++]=Sn(y+j+1,l);Z(!c,goto EX));j=i))EX:R rlm0(y,n),drp(c,r);}   //!< top down
  j= n;_N(n,l='\n'==y[i];Z(l||!i,l+=i;Z(IN(1,j-l,LMX),XY(&rK[--c],Sn(y+l,j-l));Z(!c,goto EX));j=i))                                  //!< bottom up
  EX:R rlm0(y,n),drp(c,r),r;}
#else
ZK rlr(){R kK(0);}ZK rla(K r){R r;}
#endif//FIO


//:~
