//! femtoline copyright (c) 2020 regents of kparc, bsd-2-clause
#include"l.h"

Z_ rlp();
_ rl1(char*p){Tc(),go(),x=rlr(),PT=p,_rl(0);}I rl0(){r0(x);
 pf("sigint *** ws=%d\b",WS);ext();R WS;}     //!< init free
I _rl(char*p){Z(p,PT=p);R
  //x=va(x,r=kC(0)),
  rlp(),v=LE=HL=ST=0,txpt(),1;}       //!< next line

ZG rlq(){K y=H(xn-2);P(!y,0)R cmp(r,y);}                        //!< same as previous?
ZK rlc(){P(!rn||rlq(),--xn,r1(r))R rla(r1(H_=r));}    //!< commit to history   //drp(1==xn-HMX,x)
//ZG rlq(){K y;P(!(y=H(xn-2)),0)R cmp(r,y);}                          //!< same as previous?
//ZK rlc(){P(!rn||rlq(),--xn,r)R drp(1==xn-HMX,x),rla(H_=r);}        //!< commit to history
//ZK rlc(){P(!rn||rlq(),--xn,r0(r))R drp(1==xn-HMX,x),rla(H_=r);}        //!< commit to history
ZI rlb(UI n){R!n||LMX<n?n:10>n?txN('\b',n):txe(n,'D');}           //!< move caret (b)ack
Z_ rlt(){pf(EL);red(rG+v,rn-v),v+=ff,rlb(rn-v);}                 //!< redraw the (t)ail
ZK rld(){rlb(bk),v-=bk;Z(rfc,rlt())cya(rG+v,ff),v+=ff;R(K)0;}     //!< re(d)raw and move
ZK rlf(){R txpt(),txk(r),rlb(rn-v),(K)0;}                         //!< (f)ull line reset
Z_ rlp(){N(xn-!DBG,txhl(Xk,i))}                                   //!< history (p)rinter
ZI rlw(){I d,t=v;rwd(' '==_Rv)rwd(' '-_Rv)R cut(v,d=t-v),v=t,d;}  //!< erase last (w)ord
ZI rlh(I d){P(2>xn,0)P(rll(d),bk=v,ff=rn;rfc=1)R 0;}              //!< (h)istory browser
ZI rlj(I m){P(!rn,0)R rfc0,bk=v,ff=m?vmv(r,v,m):bb(r,v);}         //!< (j)ump or balance

K rl(){G c;NX:c=RX();bk=ff=0,rfc=1;SW(ST,                         //!< parse a byte
  C(noesc,                                                        //!< normal stdin
   Z(in(" ~"),ins(v,&c),ff=1){                                    //!< insert ascii
   P(cNL,nl(),rlc())                                              //!< commit eol ⏎
   P(cTAB&&1<xn,nl(),rlp(),rlf())                                 //!< show history
   P(cC,EOT)P(!rn&&In(1,5),NOP)                                   //!< sigint | nop  ^C
   P(cR,nl(),pf(hlp),rlf())}SW(c,                                 //!< display help  ^R
   cL(pf(ED),rlf())                                               //!< clear screen  ^L
   cW(bk=rlw())                                                   //!< erase a word  ^W
   cT(Z(1<rn,swp()ff=2,bk=eol?2:!!v,rfc0))                        //!< swap 2 chars  ^T
   cU(drp(bk=v,r))cK(tak(v,r))                                    //!< kill to home  ^U ^K
   cA(home)cE(end)cD(del)                                         //!< home end del  ^A ^E ^D
   cB(rlj(0))cN(rlj(-1))cP(rlj(1))                                //!< mis(b)alance  ^B ^N ^P
   cBSP(Z(v,cut(v-1,1),bk1))                                      //!< backspace  ⌫
   cESC(M(esc)),rlu(c)))                                          //!< utf8 or junk
  C(esc,M(cBKT?ebkt:cEO?esco:noesc))                              //!< esc substate
  C(ebkt,rfc0;SW(c,                                               //!< eseq E [ ...
   eC(ff=v<rn)eD(bk=!!v)                                          //!< left | right  ←  →
   eH(HOME:bk=v)eF(END:ff=rn-v))                                  //!< actual h | e  ⇱  ⇲
   Z(in("AB"),rlh(c+c-0x83));                                     //!< hist up down  ↑  ↓
   Z(in("09"),LE=c,M(ebkt0))xesc)                                 //!< esc substate
  C(ebkt0,rfc0;Z('~'==c,                                          //!< eseq E [ 0-9
   Z(le('3'),DEL:cut(v,rfc=rn>v)));xesc)                          //!< delete key ⌦
  //Z(es2("17"),home)Z(es2("48"),end)                             //!< alt home|end  ^H ^F
  C(esco,                                                         //!< eseq E [ O ..
   SW(c,eH(home)eF(end),xesc)),                                   //!< alt home|end
  XESC:M(noesc))                                                  //txi(c),tx(' ');
 clp(),rld();next}                                                //!< partial draw

#if AW == 0
#define Pt "> "

#define F(opt)   ("-+"[!!opt])
ZI txban(){R pf("\nfemtoline %clc %caw %cpf %ctty %cbb %cfio %cutf mmx=%d (^r help)\n",F(NOLIBC),F(AW),F(FPF),F(FTY),F(FBB),F(FIO),F(FUN),MMX());}
ZI oe(K x){P(EOT==x,0)P(NOP==x,1)R txk(x),nl(),_rl(Pt);}

I main(I n,char**a){
  txban();
  R 0;
  rl1(Pt);W(oe(rl()));R rl0();}
#endif

//:~
