# getsiblings

Linux system call for getting list of sibling process IDs of a process.

Rasit Ozdemir

#### Adding System Call
You need the recompile the kernel in order to add the system call. You need the following steps:
* Get kernel source 5.10.0 (Any Debian bullseye 5.10.x version may work)
* Before compilation edit arch/x86/entry/syscalls/syscall 32.tbl. Add following lines: <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```441      i386      getsiblings      sys_getsiblings```
  *  Edit arch/x86/entry/syscalls/syscall 64.tbl. Add following in common section: <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```441      common      getsiblings      sys_getsiblings```
* Place sibling.c under kernel directory (chosen as a standard place, actually it can be anywhere with a proper Makefile).
* Add following line in kernel/Makefile <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```obj-y += sibling.o```
* Copy your systems config as kernel configuration under source top directory: <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```cp /boot/config-‘uname -r‘ .config```
* For compatibility with the test setup I provide, change these in the Makefile:
```
VERSION = 5
PATCHLEVEL = 10
SUBLEVEL = 0
EXTRAVERSION = -10-amd64
```
* Run make -j 4 bzImage which builds kernel at arch/x86/boot/bzImage which can be installed as /boot/vmlinuz-5.10.0-10-amd64 (use a different name, i.e. add -newK not to loose your pretty kernel)

Now you can install this kernel and boot Linux system.
