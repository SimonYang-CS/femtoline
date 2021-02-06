uj:{$[()~x;y;98h=@x;x,(!+x:.Q.ff[x;y])#.Q.ff[y;x];lj[(?(!x),!y)#x]y]}
lj:{$[`s=-2!y;aj[!+!y;x;0!y];.Q.ft[{$[&/j:(#y:. y)>i?:(!+i:!y)#x;.Q.fl[x]y i;+.[+x;(f;j);:;.+.Q.fl[((f:!+y)#x:.Q.ff[x]y)j]y i j:&j]]}[;y]]x]}
/lj:{.Q.ft[{.Q.fl[x]y(!+!y)#x}[;y]]x}
ij:{.Q.ft[{.Q.fl[x j]y i j:&(#y:. y)>i?:(!+i:!y)#x}[;y]]x}
pj:{.Q.ft[{x+0^y(!+!y)#x}[;y]]x}
aj:{.Q.ft[{.Q.fl[y](x_z)(x#z)bin x#y}[x,();;0!z]]y}
aj0:{.Q.ft[{.Q.fl[y]z(x#z)bin x#y}[x,();;0!z]]y}
asof:{f:!$[99=@y;y;+y];(f_x)(f#x)bin y}
wj[-1000 2000+\:trade`time;`sym`time;trade;(quote;(max;`ask);(min;`bid))] 1 or 2 fields (`sym`time xasc quote)
wj:{[w;f;y;z]e:+1_z;z:*z;i:$[1=#f,:();0|0 1+z[*f]bin/:w;(z[*f]?y[*f])|/:0 1+((f#z)bin@[f#y;*|f;:;]@)'w];y,'+f!+{[e;d;a;b]e@'d@\:a+!b-a}[*e;z f:*|e]/'+i}
wj1:{[w;f;y;z]e:+1_z;z:*z;i:$[1=#f,:();1+z[*f]bin/:w-1;(z[*f]?y[*f])|/:1+((f#z)bin@[f#y;*|f;:;]@)'w-1];y,'+f!+{[e;d;a;b]e@'d@\:a+!b-a}[*e;z f:*|e]/'+i}
fby:{@[(#y)#x[0]0#x 1;g;:;x[0]'x[1]g:.=y]};xgroup:{x,:();a:x#y:0!y;$[#x_:y;+:'x@=a;a!+f!(#f:!+x)#()]};ungroup:{$[#x:0!x;,/+:'x;x]}
ld:{x:("#!"~2#*x)_x:-1!'x;y{0N!x y}'"\n"/:'(&~^*:'x)_x@:&(#:'x)&~"/"=*:'x@:&~|':(b?"i"$-1)#b;}
wj1:{[w;f;y;z]e:+1_z;z:*z;i:$[1=#f,:();1+z[*f]bin/:w-1;(z[*f]?y[*f])|/:1+((f#z)bin@[f#y;*|f;:;]@)'w-1];y,'+f!+{[e;d;a;b]e@'d@\:a+!b-a}[*e;z f:*|e]/'+i}
wj[-1000 2000+\:trade`time;`sym`time;trade;(quote;(max;`ask);(min;`bid))] 1 or 2 fields (`sym`time xasc quote)
