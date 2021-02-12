//! femtoline copyright (c) 2020 regents of kparc, bsd-2-clause

//! config
#define LMX               64*1          //!< max line byte length (multiples of 64)
#define HMX               32            //!< max lines of history (>=0)
#define MLM               8*1024        //!< hard malloc limit (>=256 or zero)

#ifndef AW
#define AW                0             //!< use k9 backend
#endif

//! feature flags
#define FUN               0             //!< unicode support
#define FBB               1             //!< bracket balancer
#define FTY               1             //!< set tty raw mode
#define FIO               0             //!< persist sessions
#define FPF               1             //!< use own printf
#define DBG               0             //!< refcount debug
#define CLR               1             //!< partial redraw debug
#define FHF               ".k"          //!< history filename

#if NOLIBC
#define M1(n)             aw_malloc(n)
#define M2(a,n)           aw_realloc(a,n)
#define M0                aw_free
#define TX                wb            //!< putchar
#define RX                rb            //!< getchar

#else
#include<stdio.h>
#define M1(n)             malloc(n)
#define M2(a,n)           realloc(a,n)
#define M0                free
#define TX                putchar
#define RX                getchar
#define FPF               printf
#endif

//! line buffer backend
#if AW
#include"src/w.h"
#else
#include"src/k.h"
#endif

//:~
