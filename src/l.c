//! femtoline copyright (c) 2020 regents of kparc, bsd-2-clause
#include"l.h"

Z_ rlf();
ZI rlp();
ZI rlb(UI n);
#define R0 R(K)0;

_ rl1(char*p){Tc(),go(),x=rlr(),PT=p,_rl(0);}I rl0(){pf("sigint *** ws=%d\n",wss());ext();R wss();} //!< init free

I _rl(char*p){Z(p,PT=p);R
  rlp(),
  //x=va(x,r=kC(0)),
  //,
  v=LE=HL=ST=0,
  r=LN("kelas",5),ljp(0),v=0,
  //L0(),txpt(),
  rlf(),1;}        //!< next line

//ZG rlq(){K y=H(xn-2);P(!y,0)R cmp(r,y);}                          //!< same as previous?
//ZK rlc(){P(!rn||rlq(),--xn,r)R rla(H_=r);}    //!< commit to history   //drp(1==xn-HMX,x)
//ZG rlq(){K y;P(!(y=H(xn-2)),0)R cmp(r,y);}                          //!< same as previous?
//ZK rlc(){P(!rn||rlq(),--xn,r)R drp(1==xn-HMX,x),rla(H_=r);}        //!< commit to history
//ZK rlc(){P(!rn||rlq(),--xn,r0(r))R drp(1==xn-HMX,x),rla(H_=r);}        //!< commit to history
ZI rlb(UI n){R!n||LMX<n?n:10>n?txN('\b',n):txe(n,'D');}           //!< move caret (b)ack
Z_ rlf(){nl(),txpt(),lfl(r),rlb(rn-v);}                           //!< (f)ull line reset
Z_ rlt(){txn(EL),lff(r,v,rn-v),v+=ff,rlb(rn-v);}                  //!< redraw the (t)ail
Z_ rld(){rlb(bk),v-=bk;Z(rfc,rlt())lff(r,v,ff),v+=ff;}            //!< re(d)raw and move
ZI rlp(){P(!x,x)N(xn-!DBG,txhl(Xk,i))R0;}                         //!< history (p)rinter
ZI rlw(){I d,t=v;rwd(' '==_Rv)rwd(' '-_Rv)R lct(d=t-v),v=t,d;}   //!< erase last (w)ord
ZI rlh(I d){P(2>xn,0)P(rll(d),bk=v,ff=rn;rfc=1)R 0;}              //!< (h)istory browser
ZI rlj(I m){P(!rn,0)R rfc0,bk=v,ff=m?vmv(r,v,m):bb(r,v);}         //!< (j)ump or balance

#define U(c,e...)  Z(c,e,rlf();next)
K rl(){I c;NX:c=RX();bk=ff=0,rfc=1;SW(ST,                         //!< parse a byte
  C(noesc,                                                        //!< normal stdin
   Z(in(" ~"),lin(c),ff=v<rn;xesc)                                 //!< insert ascii
   //P(cNL,nl(),rlc())                                            //!< commit eol ⏎
   U(cNL,rlf())                                                   //!< commit eol ⏎
   U(cTAB&&1<xn,rlp())                                            //!< show history
   U(cR,pf(hlp))                                                  //!< display help  ^R
   P(cC,EOT)P(!rn&&In(1,5),NOP)                                   //!< sigint | nop  ^C
   SW(c,                                                          //!< ^* sequences
    cL(pf(ED),rlf())                                              //!< clear screen  ^L
    cW(bk=rlw())                                                  //!< erase a word  ^W
    //cT(Z(1<rn,swp(),ff=2,bk=eol?2:!!v,rfc0))                      //!< swap 2 chars  ^T
    cU(ldp(),bk=v)cK(ltk())                                     //!< kill to home  ^U ^K
    cA(home)cE(end)cD(del)                                        //!< home end del  ^A ^E ^D
    cB(rlj(0))cN(rlj(-1))cP(rlj(1))                               //!< mis(b)alance  ^B ^N ^P
    cBSP(Z(v,bk=1,lbs()))                                        //!< backspace  ⌫
    cESC(M(esc)),rlu(c)))                                         //!< escape / utf
  C(esc,M(cBKT?ebkt:cEO?esco:noesc))                              //!< nxt substate
  C(ebkt,rfc0;                                                    //!< eseq E [ ...
   Z(in("09"),LE=c,M(ebkt0))                                      //!< nxt substate
   Z(in("AB"),rlh(c+c-0x83))                                      //!< hist up down  ↑  ↓
   SW(c,rfc=1;
    eC(lfw(),ff=v<rn)
    eD(lbk(),bk=!!v)                       //!< left | right  ←  →
    eH(HOME:ljp(0),bk=v)
    eF(END:ff=rn-v,ljp(rn-1)))
   xesc)           //!< actual h | e  ⇱  ⇲
  C(ebkt0,rfc0;Z('~'==c,                                          //!< eseq E [ 0-9
   Z(le('3'),DEL:ldl(),rfc=rn>v));xesc)                          //!< delete key ⌦
  //Z(es2("17"),home)Z(es2("48"),end)                             //!< alt home|end  ^H ^F
  C(esco,                                                         //!< eseq E [ O ..
   SW(c,eH(home)eF(end),xesc)),                                   //!< alt home|end
  XESC:ST=noesc)                                                  //!< default case
 clp(),
 rld();next}                                                //!< partial draw

#if AW == 0
#define Pt "> "
#define F(opt) ("-+"[!!opt])

ZI oe(L x){P(EOT==x,0)P(NOP==x,1)R lfl(x),nl(),_rl(Pt);}
I main(I n,char**a){

 gb_test();

 pf("\nfemtoline %clc %caw %ctty %cbb %cfio %cutf mmx=%d (^r help)\n",F(!NOLIBC),F(AW),F(FTY),F(FBB),F(FIO),F(FUN),MMX());
 rl1(Pt);W(oe(rl()));R exit(rl0()),0;}
#endif

//:~
