#include <stdint.h>
#include <stddef.h>

typedef struct DT_Ptr
{
	unsigned short limit;
	void* base;
} __attribute__((packed)) DT_Ptr; 

static inline void CPU_Halt()               
{ 
	asm ("hlt"); 
}
static inline void CPU_EnableInterrupts()   
{ 
	asm ("sti"); 
}
static inline void CPU_ClearInterrupts()    
{ 
	asm ("cli"); 
}

static inline uint8_t IO_Inb(uint16_t port)
{
	uint8_t ret;
	asm ( "inb %1, %0"
				: "=a"(ret)
				: "Nd"(port) );
	return ret;
}
static inline void IO_Outb(uint16_t port, uint8_t val) 
{ 
	asm ( "outb %0, %1" : : "a"(val), "Nd"(port) ); 
}

static inline void IO_Wait() 
{ 
	asm ( "outb %%al, $0x80" : : "a"(0) ); 
}