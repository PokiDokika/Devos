/* 
Taken from dietlibc
[bjrkk] FIXME: Should probably be rewritten..? 
*/

.text
.align 0

.global __memset_i386
.type __memset_i386,@function
.global __memcpy_i386
.type __memcpy_i386,@function

__memset_i386:
	pushl %edi
	movl 8(%esp),%edi
	movl 12(%esp),%eax
	movl 16(%esp),%ecx
	cld
	pushl %edi
	rep stosb
	popl %eax
	popl %edi
	ret
	
__memcpy_i386:
	pushl %esi
	pushl %edi
	movl 12(%esp),%edi
	movl 16(%esp),%esi
	movl 20(%esp),%ecx
	movl %edi, %eax
	cld
	rep movsb
	popl %edi
	popl %esi
	ret
