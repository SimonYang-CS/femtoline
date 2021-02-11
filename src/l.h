//! femtoline copyright (c) 2020 regents of kparc, bsd-2-clause

#include"../o.h"          //!< options

//!         init         readline  prompt    free
extern void rl1(char*);K rl();int _rl(char*),rl0();

enum{noesc,esc,ebkt,ebkt0,esco};        //!< line states
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
#define next              goto NX;           //!< read next byte

//! history
#define H(i)              (xn?IN(0,i,xn-1)?xK[i]:0:0) //!< get item
#define H_                xK[xn-1]        //!< last line in history
#define hp                xn-1-HL         //!< inverted history pos
#define QH(n)             IN(0,hp+n,xn-1)   //!< validate new index
#define rll(n)            QH(n)?(HL-=n,r=H(hp)):0 //<! selector

//#define CTL(ctl,a...)     C(ctl,  a)

//! ctrl+key
#define cA(a...)          C(1,  a)
#define cB(a...)          C(2,  a)
#define cD(a...)          C(4,  a)
#define cE(a...)          C(5,  a)
#define cK(a...)          C(11, a)
#define cL(a...)          C(12, a)
#define cN(a...)          C(14, a)
#define cP(a...)          C(16, a)
#define cT(a...)          C(20, a)
#define cU(a...)          C(21, a)
#define cW(a...)          C(23, a)

//! plain keystroke
#define cESC(a...)        C( 27,a)
#define cBSP(a...)        C(127,a)
#define cC                 ( 3==c)
#define cF                 ( 6==c)         //!< nyi
#define cR                 (18==c)
#define cTAB               ( 9==c)
#define cEO                (79==c)
#define cBKT               (91==c)
#define cNL              ('\n'==c)

//! esc [ c
#define eC(a...)          C('C',a)
#define eD(a...)          C('D',a)
#define eH(a...)          C('H',a)
#define eF(a...)          C('F',a)

#define EOL               "\r\n"
#define EOT               (K)0x04         //!< (E)nd (O)f (T)ransmission
#define NOP               (K)0x00         //!< request next byte
#define EBKT              "\x1b["         //!< dec vt100 escape sequence
#define EL                "\x1b[K"        //!< (E)rase (L)ine to the end
#define ED                "\x1b[H\x1b[2J" //!< (E)rase (D)isplay command

//! ansi color
enum {Amb=227,Red=196,Cya=207};
#define clr(c)            pf("\x1b[38;5;%dm",c) //<! color on
#define off()             pf("\x1b[0m")         //<! color off
#define txnC(c,s,n)       txC(c,txn(s,n))
#define red(s,n)          txnC(Red,s,n)
#define cya(s,n)          txnC(Cya,s,n)
#define amb(s,n)          txnC(Amb,s,n)
#define redQ(q,e...)      ((q)?txC(Red,(e)):(e))      //!< conditional
#if CLR
#define txC(c,e...)       (clr(c),e,off())
#else
#define txC(c,e...)       (e)
#endif

#define cRED(cond)       ((cond)?"\x1b[38;5;196m":"")
#define cOFF()           "\x1b[0m"


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

//! feature code
#include"f.h"

I txfatal(S s)            {R pf((S)"fatal: %s\n",s),exit(1),1;}
#define txk(x)            ((x&&xn)?pf("%.*s",xn,xG):0)
#define nl(x)             pf("\n")
#define txe(n,c)          pf("%s%d%c",EBKT,n,c)       //!< E [ n CMD
#define txpt()            pf(PT)                      //!< prompt

#if DBG
ZI txhl(K y,UI i)         {R pf("%c%3d %3d %s%p%s ","* "[hp-i],i,yr,cRED(s0==y),(J)y,cOFF())+txk(y)+nl()}; //!< history line
#define txws()            pf(" %d ",WS)               //!< current alloc
#else
ZI txhl(K y,UI i)         {R pf("%4d ",i)+txk(y)+nl();}
#define txws()            (0)
#endif

//! refcard ^R
static char*hlp="\n"
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
  "  show history    tab\n\n"
//" quit session     esc-esc\n"
;

//! alloc limit
ZI MMX(){I lsz = MX(64,LMX) + 8,       //!< single line, minimum of 64 bytes + overhead
           hmx = MX( 0,HMX) + 1,       //!< line count + current line buffer
           mlh = lsz * hmx +           //!< total worst case line storage
                 hmx * sizeof(char*),  //!< history ring buffer
           mlm = MLM?MX(256,MLM):mlh;  //!< if MLM is defined, no less than 256 bytes
           R MN(mlm,mlh);}             //!< effective alloc limit, MLM takes precedence if set


//:~
