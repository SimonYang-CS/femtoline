#include<asm/unistd_64.h>

/*
#define __NR_read 0
#define __NR_write 1
#define __NR_open 2
#define __NR_close 3
#define __NR_fstat 5
#define __NR_mmap 9
#define __NR_munmap 11
#define __NR_exit 60
*/

#define F(n) .globl n;n:
#define S(n) F(n)mov %rcx,%r10;mov $__NR_##n,%rax;syscall;ret;

F(_start)lea 8(%rsp),%rdi;jmp main;

S(ioctl)
S(read)
S(write)
S(open)
S(close)
S(mmap)
S(munmap)
S(exit)
S(fstat)


//S(chdir)S(getcwd)S(ftruncate)
//S(sched_getaffinity)S(mkdir)S(rmdir)S(unlink)S(getdents)S(getdents64)
//S(socket)S(setsockopt)S(shutdown)S(bind)S(connect)S(listen)S(accept)
//S(epoll_create1)S(epoll_ctl)S(epoll_wait)
//S(clock_gettime)
//S(fork)S(pipe)S(socketpair)S(dup2)S(kill)S(wait4)


//:~
