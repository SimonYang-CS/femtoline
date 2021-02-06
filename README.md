## femtoline

yet another readline.

### build

```
$ make c t
$ make c r
```

### test

```
femtoline -lc -aw +bb +fio -utf (^r help)
>
  erase a word    ^w
  clear screen    ^l
  fix a (t)ypo    ^t
  catch sigint    ^c
  test balance    ^b
  goto {[(;)]}    ^np
  alt home end    ^ae
  kill<=>caret    ^udk
  show history    tab
>
```

`^B` jumps to matching bracket or to the first misbalanced bracket on the line.


### faq

* unicode nyi
* multiline nyi
* bsd-2-clause

`//:~`
