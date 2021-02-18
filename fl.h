//! femtoline copyright (c) 2020 regents of kparc, bsd-2-clause

#include"src/_.h"

//!         init         readline  prompt    free
extern void rl1(char*);K rl();int _rl(char*),rl0();

//! config
#define LMX               64*1          //!< max line byte length (multiples of 64)
#define HMX               32            //!< max lines of history (>=0)
#define MLM               8*1024        //!< hard malloc limit (>=256 or zero)

#ifndef AW
#define AW                0             //!< use k9 backend
#endif

//! feature flags
#define FUN               0             //!< unicode support
#define FBB               0             //!< bracket balancer
#define FTY               1             //!< set tty raw mode
#define FIO               0             //!< persist sessions
#define DBG               0             //!< refcount debug
#define CLR               1             //!< partial redraw debug
#define FHF               ".k"          //!< history filename

//! malloc
#include"src/m.h"

//! nolibc
#include"src/c.h"

//! printf
#include"src/pf.h"

//! line buffer
#include"src/b.h"

//! features
#include"src/f.h"



//:~
