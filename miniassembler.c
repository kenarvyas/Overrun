/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero and Kenar Vyas                                 */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;
   unsigned int uiDispLo;
   unsigned int uiDispHi;
         
   uiInstr = 0x10000000;
   
   uiInstr |= uiReg;
    
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   uiDispLo = uiDisp & 0x3;
   uiDispLo = uiDispLo << 29;
   uiInstr |= uiDispLo;
   
   uiDispHi = uiDisp >> 2;
   uiDispHi = uiDispHi << 5;
   uiDispHi &= 0x00ffffe0;
   uiInstr |= uiDispHi;
   
   return uiInstr;
}

/* Return the machine language equivalent of "mov reg, immed" where
   reg is a W register.
   
   Parameters:
      uiReg: the number of reg.
      uiImmed: the immed value. */
   
unsigned int MiniAssembler_mov(unsigned int uiReg,
   unsigned int uiImmed)
{
   unsigned int uiInstr;
   unsigned int uiFrame;

   /* Basic instruction */
   uiInstr = 0x52800000;
   
   /* Finding displaced uiImmed */
   uiFrame = 0x00000000;
   uiImmed |= uiFrame;
   uiImmed = uiImmed << 5;

   /* Combining all */
   uiInstr |= uiReg;
   uiInstr |= uiImmed;

   return uiInstr;
}


/* Return the machine language equivalent of "strb fromreg,[toreg]", 
   where fromreg is a W register and toreg is a X register.

   Parameters:
      uiFromReg: the number of fromreg.
      uiToReg: the number of toreg. */

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
                                unsigned int uiToReg){

   unsigned int uiInstr;
   unsigned int uiFrame;

   /* Basic instruction */
   uiInstr = 0x39000000;
   
   /* Finding displaced uiToReg*/
   uiFrame = 0x00000000;
   uiToReg |= uiFrame;
   uiToReg = uiToReg << 5;

   /* Combining all */
   uiInstr |= uiFromReg;
   uiInstr |= uiToReg;

   return uiInstr;
}

/* Return the machine language equivalent of "b addr".
   
   Parameters:
      ulAddr: the address denoted by addr, that is, the address to
         which the branch should occur.
      ulAddrOfThisInstr: the address of the b instruction itself. */

unsigned int MiniAssembler_b(unsigned long ulAddr,
                             unsigned long ulAddrOfThisInstr){
   unsigned int uiInstr;
   signed int uiOffset;
   unsigned int uiFrame;

   /* Basic instruction */
   uiInstr = 0x14000000;
   
   /* Finding address offset */
   uiFrame = 0x03ffffff;
   uiOffset = (signed int) ulAddr - (signed int) ulAddrOfThisInstr;
   uiOffset = uiOffset >> 2;
   uiOffset = uiFrame & uiOffset;

   /* Combining */
   uiInstr |= uiOffset;

   return uiInstr;
}

