/*-------------------------------------------------------------------*/
/* write.c          */
/* Name: Kenar Vyas */
/*-------------------------------------------------------------------*/
#include "miniassembler.h"
#include <stdio.h>
/* Generates correct machine code needed for createdataA.c */
int main(void) {
   unsigned int uireg;
   unsigned int uiadd1;
   unsigned int uiadd2;
   
   /* mov w0, 'A'*/
   printf("Mov\n");
   uireg = 0;
   uiadd1 = 'A';
   printf("0x%08x\n", MiniAssembler_mov(uireg, uiadd1));
   
   /* adr x1, grad */
   printf("Adr\n");
   uireg = 1;
   uiadd1 = 0x420044;
   uiadd2 = 0x420060;
   printf("0x%08x\n", MiniAssembler_adr(uireg, uiadd1, uiadd2));        

   /* strb w0, [x1] */
   printf("strb\n");
   uireg = 0;
   uiadd1 = 1;
   printf("0x%08x\n", MiniAssembler_strb(uireg, uiadd1)); 

   /* b to main to printf */
   printf("b\n");
   uiadd1 = 0x400864;
   uiadd2 = 0x420068;
   printf("0x%08x\n", MiniAssembler_b(uiadd1, uiadd2)); 

   return 0;
}
