//! femtoline copyright (c) 2020 regents of kparc, bsd-2-clause
#include"l.h"

_ rl1(char*p){Tc(),x=rlr(),PT=p,_rl(0);}I rl0(){R tcs(tco),r0(x),WS;}     //!< init free
I _rl(char*p){Z(p,PT=p);R x=va(x,r=S0),v=LE=HL=ST=0,txs((char*)PT),1;}    //!< next line

ZG rlq(){K y=H(xn-2);P(!y,0)R rleql(r,y);}                        //!< same as previous?
ZK rlc(){P(!rn||rlq(),--xn,r)R drp(1==xn-HN,x),rla(r1(H_=r));}    //!< commit to history
ZI rlb(UI n){R!n||LMX<n?n:10>n?txN('\b',n):txe(n,'D');}           //!< move caret (b)ack
Z_ rlt(){txs(EL);red(rG+v,rn-v),v+=ff,rlb(rn-v);}                 //!< redraw the (t)ail
ZK rld(){rlb(bk),v-=bk;Z(rfc,rlt())cya(rG+v,ff),v+=ff;R(K)0;}     //!< re(d)raw and move
ZK rlf(){R txs(PT),txk(r),rlb(rn-v),(K)0;}                        //!< (f)ull line reset
Z_ rlp(){N(xn-1,txN(' ',2),txi(i),tx_(),txk(Xk),nl())}            //!< history (p)rinter
ZI rlw(){I d,t=v;rwd(' '==_Rv)rwd(' '-_Rv)R cut(v,d=t-v),v=t,d;}  //!< erase last (w)ord
ZI rlh(I d){P(2>xn,0)P(rll(d),bk=v,ff=rn;rfc=1)R 0;}              //!< (h)istory browser
ZI rlj(I m){P(!rn,0)R rfc0,bk=v,ff=m?vmv(r,v,m):bb(r,v);}         //!< (j)ump or balance

K rl(G c){bk=ff=0,rfc=1;SW(ST,                                    //!< parse a byte
  C(noesc,                                                        //!< normal stdin
   Z(in(" ~"),ins(v,&c),ff=1)                                     //!< insert ascii
   P(cNL,nl(),rlc())                                              //!< commit eol ⏎
   P(cTAB&&1<xn,nl(),rlp(),rlf())                                 //!< show history
   P(cC||!rn&&In(1,5),(K)0)                                       //!< sigint | nop  ^C
   P(cR,nl(),txs(hlp),rlf())SW(c,                                 //!< display help  ^R
   cL(txs(ED),rlf())                                              //!< clear screen  ^L
   cW(bk=rlw())                                                   //!< erase a word  ^W
   cT(Z(1<rn,swp()ff=2,bk=eol?2:!!v,rfc0))                        //!< swap 2 chars  ^T
   cU(drp(bk=v,r))cK(tak(v,r))                                    //!< kill to home  ^U ^K
   cA(home)cE(end)cD(del)                                         //!< home end del  ^A ^E ^D
   cB(rlj(0))cN(rlj(-1))cP(rlj(1))                                //!< mis(b)alance  ^B ^N ^P
   cBSP(Z(v,cut(v-1,1),bk1))                                      //!< backspace  ⌫
   cESC(M(esc)),rlu(c)))                                          //!< utf8 or junk
  C(esc,M(cBKT?ebkt:cEO?esco:noesc))                              //!< esc substate
  C(ebkt,rfc0;SW(c,                                               //!< eseq E [ ...
   C('C',ff=v<rn)C('D',bk=!!v)                                    //!< left | right  ←  →
   C('H',HOME:bk=v)C('F',END:ff=rn-v))                            //!< actual h | e  ⇱  ⇲
   Z(in("AB"),rlh(c+c-0x83));                                     //!< hist up down  ↑  ↓
   Z(in("09"),LE=c,M(ebkt0))xesc)                                 //!< esc substate
  C(ebkt0,rfc0;Z('~'==c,                                          //!< eseq E [ 0-9
   Z(le('3'),DEL:cut(v,rfc=rn>v)));xesc)                          //!< delete key ⌦
  //Z(es2("17"),home)Z(es2("48"),end)                             //!< alt home|end
  //C(esco,SW(c,C('H',home)C('F',end),xesc))                      //!< alt home|end
  C(esco,xesc),                                                   //!< eseq E [ O ..
  XESC:M(noesc))                                                  //txi(c),tx(' ');
 R clp(),rld();}                                                  //!< partial draw

#define Pt "> "
ZI txB(){R txs("\nfemtoline")+txf("lc",!NOLIBC)+txf("aw",AW)+txf("bb",FBB)+txf("fio",FIO)+txf("utf",FUN)+txs(" (^r help)\n");}
ZI oe(K x){P(!x,1)R txk(x),nl(),_rl(Pt);}I main(I n,char**a){txB(),rl1(Pt);W(oe(rl(getchar()))){};R rl0();}

//:~
