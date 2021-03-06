/* 
 * This utility may need some clean-up. It has been quickly written for
 * helping to the automatisation of repetitive task for the TA-LIB
 * developpers. 
 *
 * This utility have no used for an end-user of the TA-LIB.
 * It is useful only to people integrating TA function in
 * TA-Lib.
 *
 * Note: All directory in this code is relative to the 'bin'
 *       directory. So you must run the executable from ta-lib/c/bin.
 *       
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ta_common.h"
#include "ta_abstract.h"
#include "ta_system.h"
#include "sfl.h"

#define FILE_READ  1
#define FILE_WRITE 0

#ifndef min
   #define min(a, b)  (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
   #define max(a, b)  (((a) > (b)) ? (a) : (b))
#endif

typedef struct
{
   FILE *file;
   FILE *templateFile;
} FileHandle;

FileHandle *gOutFunc_H;        /* For "ta_func.h"  */
FileHandle *gOutFrame_H;       /* For "ta_frame.h" */
FileHandle *gOutGroupIdx_C;    /* For "ta_group_idx.c" */
FileHandle *gOutFunc_C;        /* For "ta_x.c" where 'x' is TA function name. */
FileHandle *gOutRetCode_C;     /* For "ta_retcode.c" */
FileHandle *gOutRetCode_CSV;   /* For "ta_retcode.csv" */
FileHandle *gOutFuncList_TXT;  /* For "func_list.txt" */
static TA_Libc *gLibHandle = NULL;

typedef void (*TA_ForEachGroup)( TA_Libc *libHandle,
                                 const char *groupName,
                                 unsigned int index,
                                 unsigned int isFirst, /* Boolean */
                                 unsigned int isLast   /* Boolean */
                                );

static unsigned int forEachGroup( TA_Libc *libHandle,
                                  TA_ForEachGroup forEachGroupfunc,
                                  void *opaqueData );

static void doForEachFunction( TA_Libc *libHandle,
                               const TA_FuncInfo *funcInfo,
                               void *opaqueData );

static void doForEachUnstableFunction( TA_Libc *libHandle,
                                       const TA_FuncInfo *funcInfo,
                                       void *opaqueData );

static int gen_retcode( void );

static void printIndent( FILE *out, unsigned int indent );
static void printFunc( FILE *out,
                       const char *importInfo, /* Can be NULL */
                       const TA_FuncInfo *funcInfo,
                       unsigned int prototype, /* Boolean */
                       unsigned int frame,     /* Boolean */
                       unsigned int semiColonNeeded, /* Boolean */
                       unsigned int validationCode,   /* Boolean */
                       unsigned int lookbackPrototype /* Boolean */
                      );

static void printCallFrame  ( FILE *out, const TA_FuncInfo *funcInfo );
static void printFrameHeader( FILE *out, const TA_FuncInfo *funcInfo );

static void printExternReferenceForEachFunction( TA_Libc *libHandle,
                                                 const TA_FuncInfo *info,
                                                 void *opaqueData );

static void printFunctionAddress( TA_Libc *libHandle,
                                  const TA_FuncInfo *info,
                                  void *opaqueData );

static void printPerGroupList( TA_Libc *libHandle,
                               const char *groupName,
                               unsigned int index,
                               unsigned int isFirst,
                               unsigned int isLast
                             );

static void printGroupListAddress(  TA_Libc *libHandle,
                                    const char *groupName,
                                    unsigned int index,
                                    unsigned int isFirst,
                                    unsigned int isLast
                                 );
static void printGroupSize(  TA_Libc *libHandle,
                             const char *groupName,
                             unsigned int index,
                             unsigned int isFirst,
                             unsigned int isLast
                           );
static void printGroupSizeAddition(  TA_Libc *libHandle,
                                     const char *groupName,
                                     unsigned int index,
                                     unsigned int isFirst,
                                     unsigned int isLast
                                  );
static int printUnstablePeriodCode( void );

static int createTemplate( const char *name, FileHandle *in, FileHandle *out );
static void writeFuncFile( const TA_FuncInfo *funcInfo );
static void doFuncFile( const TA_FuncInfo *funcInfo );
static void printOptInputValidation( FILE *out,
                                     const char *name,
                                     unsigned int paramNb,
                                     const TA_OptInputParameterInfo *optInputParamInfo );
static int skipToGenCode( const char *dstName, FILE *out, FILE *templateFile );
static void printDefines( FILE *out, const TA_FuncInfo *funcInfo );

static void printFuncHeaderDoc( FILE *out,
                                const TA_FuncInfo *funcInfo,
                                const char *prefix );

char gToOpen[1024];
char gTempBuf[2048];
char gTempBuf2[2048];
char gTempBuf3[2048];
char gTempDoubleToStr[50];

/* Because Microsoft and Borland does not display
 * the value of a double in the same way (%e), this
 * function attempts to eliminate difference. This
 * is done to avoid annoying difference with CVS. 
 */
const char *doubleToStr( TA_Real value );

const char *gCurrentGroupName;

static int genCode(int argc, char* argv[]);

int main(int argc, char* argv[])
{
   int retValue;

   if( argc > 1 )
   {
         /* There is no parameter needed for this tool. */
         printf( "\n" );
         printf( "gen_code V%s - Generates many TA-LIB source files\n", TA_GetVersionString() );
         printf( "\n" );
         printf( "Usage: gen_code\n");
         printf( "\n" );         
         printf( "  No parameter needed.\n" );
         printf( "\n" );         
         printf( "  This utility is useful only for developers modifying\n" );
         printf( "  the source code of the TA-Lib.\n" );
         printf( "\n" );         
         printf( "  A lots of code is generated from the information\n" );
         printf( "  provided by the interface definitions found\n" );
         printf( "  in ta-lib/c/src/ta_abstract/tables.\n" );
         printf( "\n" );
         printf( "  From these tables, the following files are\n" );
         printf( "  produced:\n" );
         printf( "     1) ta-lib/c/include/ta_func.h\n" );
         printf( "     2) ta-lib/c/include/func_list.txt\n" );
         printf( "     3) ta-lib/c/ta_common/ta_retcode.*\n" );
         printf( "     4) ta-lib/c/src/ta_abstract/ta_group_idx.c\n");     
         printf( "     5) ta-lib/c/ta_abstract/frames/*.*\n");
         printf( "\n" );
         printf( "  Also, regenerate the function header, parameter and\n" );
         printf( "  validation code of all TA Func in c/src/ta_func.\n" );
         printf( "\n" );
         printf( "** Must be directly run from the 'bin' directory.\n" );
         exit(-1);
   }

   printf( "Generating and refreshing TA functions..." );
   retValue = genCode( argc, argv );

   if( gLibHandle )
      TA_Shutdown( gLibHandle );

   return retValue;
}


/* The following I/O function allows to manipulate
 * more easily files.
 *
 * When opening the file, the caller can specifiy a
 * path relative to the position of the binary.
 * That is: ta-lib\c\bin
 *
 * 'templateFile' allows to create a new file using
 * a template. This template must contain one
 * line starting with '%%%GENCODE%%%'.
 * All character before this string are added to the output
 * file on fileOpen, and all character after this string are
 * added to the output file on fileClose. Obviously, all
 * character added to the file between fileOpen/fileClose
 * will replace the "%%%GENCODE%%%" line.
 *
 * 'templateFile' is ignored when FILE_READ is specified.
 *
 * On failure, simply exit the software.
 */
static void init_gToOpen( const char *filePath )
{
   int sepChar;
   char *ptr;

   sepChar = TA_SeparatorASCII();

#if 0
   unsigned int strLen;
   char oneCharBuf[2];

   oneCharBuf[1] = '\0';

   strcpy( gToOpen, "..\\" );
   strLen = strlen( gToOpen );
   if( strLen > 0 )
   {
      if( (gToOpen[strLen-1] != '\\') &&
          (gToOpen[strLen-1] != '/') )
      {
         oneCharBuf[0] = (char)sepChar;
         strcat( gToOpen, oneCharBuf );
      }
   }
#endif
   strcpy( gToOpen, filePath );

   /* Replace all directory separator with the
    * one applicable for this OS.
    */
   ptr = gToOpen;
   while( *ptr != '\0' )
   {
      if( (*ptr == '\\') || (*ptr == '/') )
         *ptr = (char)sepChar;
      ptr++;
   }
}


static  FileHandle *fileOpen( const char *fileToOpen,
                              const char *templateFile,
                              const int readOnly )
{
   FileHandle *retValue;

   if( (fileToOpen == NULL) ||
       (readOnly && (templateFile != NULL)) )
   {
      printf( "Internal error line %d", __LINE__ );
      return (FileHandle *)NULL;
   }

   retValue = malloc( sizeof( FileHandle ) );

   retValue->file = NULL;
   retValue->templateFile = NULL;

   init_gToOpen( fileToOpen );

   /* Ok.. let's try to open the file now. */
   retValue->file = fopen( gToOpen, readOnly ? "r":"w" );
   if( retValue->file == NULL )
   {
      return (FileHandle *)NULL;
   }

   /* Handle the template. */
   if( templateFile )
   {
      init_gToOpen( templateFile );
      retValue->templateFile = fopen( gToOpen, "r" );
      if( retValue->templateFile == NULL )
      {
         printf( "\nCannot open template [%s]\n", gToOpen );
         return (FileHandle *)NULL;
      }

      /* Copy the header part of the template. */
      if( skipToGenCode( fileToOpen, retValue->file, retValue->templateFile ) != 0 )
      {
         free( retValue );
         retValue = NULL;
      }
   }

   return retValue;
}

static void fileClose( FileHandle *handle )
{
   /* Write remaining template info. */
   if( handle->templateFile )
   {
      while( fgets( gTempBuf, 2048, handle->templateFile ) != NULL )
      {
         if( fputs( gTempBuf, handle->file ) == EOF )
         {
            printf( "Cannot write to output file! Disk Full? " );
            break;
         }
      }

      /* Make sure the last line of th eoutput 
       * finish with a carriage return. This may
       * avoid warning from some compilers.
       */
      if( gTempBuf[0] != '\n' )
         fprintf( handle->file, "\n" );

      fclose( handle->templateFile );
   }

   fclose( handle->file );
   free( handle );
}

static int genCode(int argc, char* argv[])
{
   TA_RetCode retCode;
   unsigned int nbGroup;
   TA_InitializeParam param;

   (void)argc; /* Get ride of compiler warning */
   (void)argv; /* Get ride of compiler warning */

   printf( "\n" );

   /* Create ta_retcode.c */
   if( gen_retcode() != 0 )
   {
      printf( "\nCannot generate src/ta_common/ta_retcode.c\n" );
      return -1;
   }

   memset( &param, 0, sizeof( TA_InitializeParam ) );
   param.logOutput = stdout;
   retCode = TA_Initialize( &gLibHandle, &param );
   if( retCode != TA_SUCCESS )
   {
      printf( "\nCannot initialize the library\n");
      return -1;
   }

   /* Create "ta_func.h" */
   gOutFunc_H = fileOpen( "..\\include\\ta_func.h",
                          "..\\src\\ta_abstract\\templates\\ta_func.h.template",
                          FILE_WRITE );

   if( gOutFunc_H == NULL )
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   /* Create the "func_list.txt" */
   gOutFuncList_TXT = fileOpen( "..\\include\\func_list.txt",
                                NULL,
                                FILE_WRITE );

   if( gOutFuncList_TXT == NULL )
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }


   /* Create the "ta_frame.h" */
   gOutFrame_H = fileOpen( "..\\src\\ta_abstract\\frames\\ta_frame.h",
                           "..\\src\\ta_abstract\\templates\\ta_frame.h.template",
                           FILE_WRITE );

   if( gOutFrame_H == NULL )
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   /* Process each function. */
   retCode = TA_ForEachFunc( gLibHandle, doForEachFunction, NULL );

   if( retCode != TA_SUCCESS )
   {
      printf( "Failed [%d]\n", retCode );
      return -1;
   }

   printUnstablePeriodCode();
         
   fileClose( gOutFuncList_TXT );
   fileClose( gOutFunc_H );
   fileClose( gOutFrame_H );

   if( retCode != TA_SUCCESS )
   {
      printf( "Failed [%d]\n", retCode );
      return -1;
   }


   /* Create the "ta_group_idx.c" file. */
   gOutGroupIdx_C = fileOpen( "..\\src\\ta_abstract\\ta_group_idx.c",
                              "..\\src\\ta_abstract\\templates\\ta_group_idx.c.template",
                              FILE_WRITE );

   if( gOutGroupIdx_C == NULL )
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   retCode = TA_ForEachFunc( gLibHandle, printExternReferenceForEachFunction, NULL );
   if( retCode != TA_SUCCESS )
   {
      fileClose( gOutGroupIdx_C );
      return -1;
   }

   nbGroup = forEachGroup( gLibHandle, printPerGroupList, NULL );

   fprintf( gOutGroupIdx_C->file, "const TA_FuncDef **TA_PerGroupFuncDef[%d] = {\n", nbGroup );
   forEachGroup( gLibHandle, printGroupListAddress, NULL );
   fprintf( gOutGroupIdx_C->file, "};\n\n" );

   fprintf( gOutGroupIdx_C->file, "const unsigned int TA_PerGroupSize[%d] = {\n", nbGroup );
   forEachGroup( gLibHandle, printGroupSize, NULL );
   fprintf( gOutGroupIdx_C->file, "};\n\n" );

   fprintf( gOutGroupIdx_C->file, "const unsigned int TA_TotalNbFunction =\n" );
   forEachGroup( gLibHandle, printGroupSizeAddition, NULL );

   fileClose( gOutGroupIdx_C );

   return 0;
}

static unsigned int forEachGroup( TA_Libc *libHandle,
                                  TA_ForEachGroup forEachGroupFunc,
                                  void *opaqueData )
{
   TA_RetCode retCode;
   TA_StringTable *table;
   unsigned int i;   

   (void)opaqueData; /* Get ride of compiler warning */

   retCode = TA_GroupTableAlloc( libHandle, &table );
   if( retCode != TA_SUCCESS )
      return 0;

   for( i=0; i < table->size; i++ )
   {
      forEachGroupFunc( libHandle,
                        table->string[i],
                        i,
                        i==0? 1:0,
                        i==(table->size-1)? 1:0 );
   }
   
   retCode = TA_GroupTableFree ( table );
   if( retCode != TA_SUCCESS )
      return 0;

   return i;
}

static void doForEachFunction( TA_Libc *libHandle,
                               const TA_FuncInfo *funcInfo,
                               void *opaqueData )
{
   static const char *prevGroup = NULL;
   FileHandle *frameOut;

   (void)opaqueData; /* Get ride of compiler warning */
   (void)libHandle;  /* Get ride of compiler warning */

   /* Add this function to the "func_list.txt" */
   fprintf( gOutFuncList_TXT->file, "%-12s%s\n", funcInfo->name, funcInfo->hint );
  
   fprintf( gOutFunc_H->file, "\n" );

   if( (prevGroup == NULL) || (prevGroup != funcInfo->group) )
   {
      printf( "Processing Group [%s]\n", funcInfo->group );
      fprintf( gOutFunc_H->file, "\n/******************************************\n" );
      fprintf( gOutFunc_H->file, " * Group: [%s]\n", funcInfo->group );
      fprintf( gOutFunc_H->file, " ******************************************/\n\n" );

      prevGroup = funcInfo->group;
   }

   printf( "Processing Func  [TA_%s]\n", funcInfo->name );

   fprintf( gOutFunc_H->file, "/*\n" );
   printFuncHeaderDoc( gOutFunc_H->file, funcInfo, " * " );
   fprintf( gOutFunc_H->file, " */\n" );

   /* Print the defines corresponding to this function. */
   printDefines( gOutFunc_H->file, funcInfo );

   /* Print the function prototype. */
   printFunc( gOutFunc_H->file, NULL, funcInfo, 1, 0, 1, 0, 0 );
   fprintf( gOutFunc_H->file, "\n" );

   /* Print the corresponding lookback function prototype. */
   printFunc( gOutFunc_H->file, NULL, funcInfo, 1, 0, 1, 0, 1 );

   /* Create the frame for TA_CallFunc. */
   sprintf( gTempBuf, "..\\src\\ta_abstract\\frames\\ta_%s_frame.c", funcInfo->name );

   frameOut = fileOpen( gTempBuf,
                        "..\\src\\ta_abstract\\templates\\ta_x_frame.c.template",
                        FILE_WRITE );

   printCallFrame( frameOut->file, funcInfo );

   printFrameHeader( gOutFrame_H->file, funcInfo );
   fprintf( gOutFrame_H->file, ";\n\n" );

   fileClose( frameOut );

   doFuncFile( funcInfo );
}

static void doForEachUnstableFunction( TA_Libc *libHandle,
                                       const TA_FuncInfo *funcInfo,
                                       void *opaqueData )
{
   unsigned int *i;

   (void)libHandle;

   i = (unsigned int *)opaqueData;

   if( funcInfo->flags & TA_FUNC_FLG_UNST_PER )
   {
      fprintf( gOutFunc_H->file, "    /* %03d */  TA_FUNC_UNST_%s,\n", *i, funcInfo->name );
      (*i)++;
   }
}

static void printIndent( FILE *out, unsigned int indent )
{
   unsigned int i;

   for( i=0; i < indent; i++ )
      fprintf( out, " " );
}

static void printDefines( FILE *out, const TA_FuncInfo *funcInfo )
{
   TA_RetCode retCode;
   const TA_OptInputParameterInfo *optInputParamInfo;
   unsigned int i, j;
   unsigned int paramNb;
   const char *paramName;
   const char *defaultParamName;
   TA_IntegerList *intList;
   TA_RealList    *realList;

   /* Go through the optional parameter and print
    * the corresponding define for the TA_OptInput_IntegerList
    * and TA_OptInput_RealList having a string.
    */
   paramNb = 0;
   for( i=0; i < funcInfo->nbOptInput; i++ )
   {
      retCode = TA_SetOptInputParameterInfoPtr( funcInfo->handle,
                                                i, &optInputParamInfo );

      if( retCode != TA_SUCCESS )
      {
         printf( "[%s] invalid 'optional input' information\n", funcInfo->name );
         return;
      }

      paramName = optInputParamInfo->paramName;

      /* TA_MA: Value for parameter */

      switch( optInputParamInfo->type )
      {
      case TA_OptInput_RealList:
         defaultParamName = "optInReal";
         break;
      case TA_OptInput_IntegerList:
         defaultParamName = "optInInteger";
         break;
      default:
         paramNb++;
         continue; /* Skip other type of parameter */
      }

      if( !paramName )
         paramName = defaultParamName;

      /* Output a comment to guide the user. */
      fprintf( out, "\n/* TA_%s: Optional Parameter %s_%d */\n",
               funcInfo->name, paramName, paramNb );

      switch( optInputParamInfo->type )
      {
      case TA_OptInput_IntegerList:
         intList = (TA_IntegerList *)optInputParamInfo->dataSet;
         for( j=0; j < intList->nbElement; j++ )
         {
            strcpy( gTempBuf, intList->data[j].string );
            strconvch( gTempBuf, ' ', '_' );
            trim( gTempBuf );
            strupc( gTempBuf );
            fprintf( out, "#define TA_%s_%s %d\n",
                     funcInfo->name,
                     gTempBuf,
                     intList->data[j].value );

         }
         fprintf( out, "\n" );
         break;
      case TA_OptInput_RealList:
         realList = (TA_RealList *)optInputParamInfo->dataSet;
         for( j=0; j < realList->nbElement; j++ )
         {
            strcpy( gTempBuf, realList->data[j].string );
            strconvch( gTempBuf, ' ', '_' );
            trim( gTempBuf );
            strupc( gTempBuf );
            fprintf( out, "#define TA_%s_%s %s\n",
                     funcInfo->name,
                     gTempBuf,
                     doubleToStr(realList->data[j].value) );

         }
         fprintf( out, "\n" );
         break;
      default:
         /* Do nothing */
         break;
      }

      paramNb++;
   }
}

static void printFunc( FILE *out,
                       const char *importInfo, /* Can be NULL */
                       const TA_FuncInfo *funcInfo,
                       unsigned int prototype, /* Boolean */
                       unsigned int frame,     /* Boolean */
                       unsigned int semiColonNeeded, /* Boolean */
                       unsigned int validationCode, /* Boolean */
                       unsigned int lookbackPrototype /* Boolean */
                      )
{
   TA_RetCode retCode;
   unsigned int i, j, k, indent, lastParam;
   unsigned int paramNb;
   const char *paramName;
   const char *defaultParamName;
   const TA_InputParameterInfo *inputParamInfo;
   const TA_OptInputParameterInfo *optInputParamInfo;
   const TA_OutputParameterInfo *outputParamInfo;
   char *typeString;

   typeString = "";
   defaultParamName = "";

   if( prototype )
   {
      if( lookbackPrototype )
      {
         fprintf( out, "%sint TA_%s_Lookback( ",
                  importInfo == NULL? "" : importInfo, funcInfo->name );
         indent = 15 + strlen(funcInfo->name) + 3;
      }
      else
      {
         fprintf( out, "%sTA_RetCode TA_%s( TA_Libc      *libHandle,\n",
                  importInfo == NULL? "" : importInfo, funcInfo->name );
         indent = 13 + strlen(funcInfo->name) + 3;
      }
   }
   else if( frame )
   {
      fprintf( out, "%sTA_%s( libHandle,\n",
               importInfo == NULL? "" : importInfo, funcInfo->name );
      indent = 4 + strlen(funcInfo->name);
   }
   else if( validationCode )
   {
      indent = 3;
   }
   else
   {
      printf( "printFunc has nothing to do?\n" );
      return;
   }

   if( importInfo )
      indent += strlen(importInfo);
   if( frame )
      indent -= 5;

   if( prototype && !lookbackPrototype )
   {
      printIndent( out, indent );
      fprintf( out, "TA_Integer    startIdx,\n" );
      printIndent( out, indent );
      fprintf( out, "TA_Integer    endIdx,\n" );
   }
   else if( frame )
   {
      printIndent( out, indent );
      fprintf( out, "startIdx,\n" );
      printIndent( out, indent );
      fprintf( out, "endIdx,\n" );
   }

   /* Go through all the input. */
   if( !lookbackPrototype )
   {
      paramNb = 0;
      for( i=0; i < funcInfo->nbInput; i++ )
      {
         retCode = TA_SetInputParameterInfoPtr( funcInfo->handle,
                                             i, &inputParamInfo );

         if( retCode != TA_SUCCESS )
         {
            printf( "[%s] invalid 'input' information (%d,%d)\n", funcInfo->name, i, paramNb );
            return;
         }

         paramName = inputParamInfo->paramName;

         switch( inputParamInfo->type )
         {
         case TA_Input_Price:
            /* Find how many component are requested. */
            j = 0;
            if( inputParamInfo->flags & TA_IN_PRICE_TIMESTAMP )
               j++;
            if( inputParamInfo->flags & TA_IN_PRICE_OPEN )
               j++;
            if( inputParamInfo->flags & TA_IN_PRICE_HIGH )
               j++;
            if( inputParamInfo->flags & TA_IN_PRICE_LOW )
               j++;
            if( inputParamInfo->flags & TA_IN_PRICE_CLOSE )
               j++;
            if( inputParamInfo->flags & TA_IN_PRICE_VOLUME )
               j++;
            if( inputParamInfo->flags & TA_IN_PRICE_OPENINTEREST )
               j++;

            if( j == 0 )
            {
               printf( "[%s] invalid 'price input' information (%d,%d)\n", funcInfo->name, i, paramNb );
               return;
            }

            if( validationCode )
            {
               printIndent( out, indent );
               fprintf( out, "/* Verify required price component. */\n" );
               printIndent( out, indent );
               fprintf( out, "if(" );
               k = 0;
               if( inputParamInfo->flags & TA_IN_PRICE_TIMESTAMP )
               {
                  k++;
                  fprintf( out, "!inTimestamp_%d%s", paramNb, k != j? "||":")");
               }

               if( inputParamInfo->flags & TA_IN_PRICE_OPEN )
               {
                  k++;
                  fprintf( out, "!inOpen_%d%s", paramNb, k != j? "||":")");
               }
               
               if( inputParamInfo->flags & TA_IN_PRICE_HIGH )
               {
                  k++;
                  fprintf( out, "!inHigh_%d%s", paramNb, k != j? "||":")");
               }

               if( inputParamInfo->flags & TA_IN_PRICE_LOW )
               {
                  k++;
                  fprintf( out, "!inLow_%d%s", paramNb, k != j? "||":")");
               }

               if( inputParamInfo->flags & TA_IN_PRICE_CLOSE )
               {
                  k++;
                  fprintf( out, "!inClose_%d%s", paramNb, k != j? "||":")");
               }

               if( inputParamInfo->flags & TA_IN_PRICE_VOLUME )
               {
                  k++;
                  fprintf( out, "!inVolume_%d%s", paramNb, k != j? "||":")");
               }

               if( inputParamInfo->flags & TA_IN_PRICE_OPENINTEREST )
               {
                  k++;
                  fprintf( out, "!inOpenInterest_%d%s", paramNb, k != j? "||":")");
               }

               fprintf( out, "\n" );
               printIndent( out, indent );
               fprintf( out, "   return TA_BAD_PARAM;\n\n" );
            }
            else
            {
               if( inputParamInfo->flags & TA_IN_PRICE_TIMESTAMP )
               {
                  printIndent( out, indent );
                  if( frame )
                     fprintf( out, "in[%d].p.in.data.inPrice.timestamp, /*", paramNb );
                  fprintf( out, "%-*s %s_%d%s",
                           prototype? 12 : 0,
                           prototype? "const TA_Timestamp" : "",                           
                           "inTimestamp",
                           paramNb,
                           prototype? "[]" : "" );
                  fprintf( out, "%s\n", frame? " */":"," );
               }

               if( inputParamInfo->flags & TA_IN_PRICE_OPEN )
               {
                  printIndent( out, indent );
                  if( frame )
                     fprintf( out, "in[%d].p.in.data.inPrice.open, /*", paramNb );
                  fprintf( out, "%-*s %s_%d%s",
                           prototype? 12 : 0,
                           prototype? "const TA_Real" : "",                           
                           "inOpen",
                           paramNb,
                           prototype? "[]" : "" );
                  fprintf( out, "%s\n", frame? " */":"," );
               }

               if( inputParamInfo->flags & TA_IN_PRICE_HIGH )
               {
                  printIndent( out, indent );
                  if( frame )
                     fprintf( out, "in[%d].p.in.data.inPrice.high, /*", paramNb );
                  fprintf( out, "%-*s %s_%d%s",
                           prototype? 12 : 0,
                           prototype? "const TA_Real" : "",                           
                           "inHigh",
                           paramNb,
                           prototype? "[]" : "" );
                  fprintf( out, "%s\n", frame? " */":"," );
               }

               if( inputParamInfo->flags & TA_IN_PRICE_LOW )
               {
                  printIndent( out, indent );
                  if( frame )
                     fprintf( out, "in[%d].p.in.data.inPrice.low, /*", paramNb );
                  fprintf( out, "%-*s %s_%d%s",
                           prototype? 12 : 0,
                           prototype? "const TA_Real" : "",
                           "inLow",
                           paramNb,
                           prototype? "[]" : "" );
                  fprintf( out, "%s\n", frame? " */":"," );
               }

               if( inputParamInfo->flags & TA_IN_PRICE_CLOSE )
               {
                  printIndent( out, indent );
                  if( frame )
                     fprintf( out, "in[%d].p.in.data.inPrice.close, /*", paramNb );
                  fprintf( out, "%-*s %s_%d%s",
                           prototype? 12 : 0,
                           prototype? "const TA_Real" : "",                           
                           "inClose",
                           paramNb,
                           prototype? "[]" : "" );
                  fprintf( out, "%s\n", frame? " */":"," );
               }

               if( inputParamInfo->flags & TA_IN_PRICE_VOLUME )
               {
                  printIndent( out, indent );
                  if( frame )
                     fprintf( out, "in[%d].p.in.data.inPrice.volume, /*", paramNb );
                  fprintf( out, "%-*s %s_%d%s",
                           prototype? 12 : 0,
                           prototype? "const TA_Integer" : "",
                           "inVolume",
                           paramNb,
                           prototype? "[]" : "" );
                  fprintf( out, "%s\n", frame? " */":"," );
               }

               if( inputParamInfo->flags & TA_IN_PRICE_OPENINTEREST )
               {
                  printIndent( out, indent );
                  if( frame )
                     fprintf( out, "in[%d].p.in.data.inPrice.openInterest, /*", paramNb );
                  fprintf( out, "%-*s %s_%d%s",
                           prototype? 12 : 0,
                           prototype? "const TA_Integer" : "",
                           "inOpenInterest",
                           paramNb,
                           prototype? "[]" : "" );
                  fprintf( out, "%s\n", frame? " */":"," );
               }
            }
            break;
         case TA_Input_Real:
            typeString = "const TA_Real";
            defaultParamName = "inReal";
            break;
         case TA_Input_Integer:
            typeString = "const TA_Integer";
            defaultParamName = "inInteger";
            break;
         /*case TA_Input_Timestamp:
            typeString = "const TA_Timestamp";
            defaultParamName = "inTimestamp";
            break;*/
         default:
            if( !paramName )
               paramName = "inParam";
            printf( "[%s,%s_%d] invalid 'input' type(%d)\n",
                    funcInfo->name, paramName, paramNb,
                    inputParamInfo->type );
            return;
         }

         if( inputParamInfo->type != TA_Input_Price )
         {
            printIndent( out, indent );
            if( validationCode )
               fprintf( out, "if( !%s_%d ) return TA_BAD_PARAM;\n", inputParamInfo->paramName, paramNb );
            else
            {
               if( frame )
                  fprintf( out, "in[%d].p.in.data.%s, /*", paramNb, defaultParamName );
               fprintf( out, "%-*s %s_%d%s",
                        prototype? 12 : 0,
                        prototype? typeString : "",                        
                        inputParamInfo->paramName,
                        paramNb, prototype? "[]" : "" );
               fprintf( out, "%s\n", frame? " */":"," );
            }
         }
         paramNb++;
      }
   }

   /* Go through all the optional input */
   paramNb = 0;
   lastParam = 0;
   for( i=0; i < funcInfo->nbOptInput; i++ )
   {
      if( (i == (funcInfo->nbOptInput-1)) && lookbackPrototype )
         lastParam = 1;

      retCode = TA_SetOptInputParameterInfoPtr( funcInfo->handle,
                                                i, &optInputParamInfo );

      if( retCode != TA_SUCCESS )
      {
         printf( "[%s] invalid 'optional input' information\n", funcInfo->name );
         return;
      }

      paramName = optInputParamInfo->paramName;

      switch( optInputParamInfo->type )
      {
      case TA_OptInput_RealRange:
      case TA_OptInput_RealList:
         typeString = "TA_Real";
         defaultParamName = "optInReal";
         break;
      case TA_OptInput_IntegerRange:
      case TA_OptInput_IntegerList:
         typeString = "TA_Integer";
         defaultParamName = "optInInteger";
         break;
      default:
         if( !paramName )
            paramName = "optInParam";
         printf( "[%s,%s_%d] invalid 'optional input' type(%d)\n",
                 funcInfo->name, paramName, paramNb,
                 optInputParamInfo->type );
         return;
      }

      if( !paramName )
         paramName = defaultParamName;

      if( validationCode )
         printOptInputValidation( out, paramName, paramNb, optInputParamInfo );
      else
      {
         if( !(lookbackPrototype && (i == 0 )) )
            printIndent( out, indent );

         if( frame )
            fprintf( out, "optIn[%d].p.optIn.data.%s, /*", paramNb, defaultParamName );
         fprintf( out, "%-*s %s_%d",
                  prototype? 13 : 0,
                  prototype? typeString : "",
                  paramName, paramNb );
         if( frame )
            fprintf( out, " */\n" );
         else            
         {
            switch( optInputParamInfo->type )
            {
            case TA_OptInput_RealRange:
               if( lookbackPrototype && lastParam )
                  fprintf( out, " )%s ", semiColonNeeded? ";":"" );
               else
                  fprintf( out, "," );

               if( ((TA_RealRange *)(optInputParamInfo->dataSet))->min == TA_REAL_MIN )
                  fprintf( out, " /* From TA_REAL_MIN" );
               else
                  fprintf( out, " /* From %.*e",
                           ((TA_RealRange *)(optInputParamInfo->dataSet))->precision,
                           ((TA_RealRange *)(optInputParamInfo->dataSet))->min );

               if( ((TA_RealRange *)(optInputParamInfo->dataSet))->max == TA_REAL_MAX )
                  fprintf( out, " to TA_REAL_MAX */\n" );
               else
               {
                  fprintf( out, " to %.*e%s */\n", 
                          ((TA_RealRange *)(optInputParamInfo->dataSet))->precision,
                          ((TA_RealRange *)(optInputParamInfo->dataSet))->max,
                          optInputParamInfo->flags & TA_OPTIN_IS_PERCENT? " %":"" );
               }
               break;
            case TA_OptInput_IntegerRange:
               if( lookbackPrototype && lastParam )
                  fprintf( out, " )%s ", semiColonNeeded? ";":"" );
               else
                  fprintf( out, "," );

               if( ((TA_IntegerRange *)(optInputParamInfo->dataSet))->min == TA_INTEGER_MIN )
                  fprintf( out, " /* From TA_INTEGER_MIN" );
               else
               {
                  fprintf( out, " /* From %d",
                           ((TA_IntegerRange *)(optInputParamInfo->dataSet))->min );
               }

               if( ((TA_IntegerRange *)(optInputParamInfo->dataSet))->max == TA_INTEGER_MAX )
                  fprintf( out, " to TA_INTEGER_MAX */\n" );
               else
               {
                  fprintf( out, " to %d */\n", 
                          ((TA_IntegerRange *)(optInputParamInfo->dataSet))->max );
               }
               break;
            default:
               if( lookbackPrototype && lastParam )
                  fprintf( out, " )%s ", semiColonNeeded? ";":"" );
               else
                  fprintf( out, ",\n" );
            }
         }
      }

      paramNb++;
   }

   if( lookbackPrototype && (funcInfo->nbOptInput == 0) )
   {
      fprintf( out, "void )%s\n", semiColonNeeded? ";":"" );
   }

   /* Go through all the output */

#if 0
/* !!! This code was when I was considering to have a lookback output
 * !!! for each output. Sicne I decide that all outputs were
 * !!! using the "worst case" of lookback among all th output,
 * !!! All this code is not needed. I leave the code here for a couple
 * !!! of version just in case I change my mind....
 */
   if( lookbackPrototype )
   {       
      paramNb = 0;
      lastParam = 0;
      for( i=0; i < funcInfo->nbOutput; i++ )
      {
         if( i == (funcInfo->nbOutput-1) )
            lastParam = 1;

         retCode = TA_SetOutputParameterInfoPtr( funcInfo->handle,
                                                 i, &outputParamInfo );
         if( retCode != TA_SUCCESS )
         {
            printf( "[%s] invalid 'output' information\n", funcInfo->name );
            return;
         }

         if( funcInfo->nbOptInput != 0 )
            printIndent( out, indent );

         fprintf( out, "TA_Integer   *lookback_%d", paramNb++ );
         if( !lastParam )
            fprintf( out, ",\n" );
         else
            fprintf( out, " )%s\n", semiColonNeeded? ";":"" );
      }
#endif

   if( lookbackPrototype )
   {
      fprintf( out, "\n" );
   }
   else
   {
      paramNb = 0;
      lastParam = 0;

      if( !validationCode )
      {
            printIndent( out, indent );
            if( frame )
               fprintf( out, "outBegIdx, " );
            else
               fprintf( out, "%-*s %soutBegIdx",
                        prototype? 12 : 0,
                        prototype? "TA_Integer" : "",
                        prototype? "*" : "" );

            fprintf( out, "%s\n", frame? "":"," );

            printIndent( out, indent );
            if( frame )
               fprintf( out, "outNbElement, " );
            else
               fprintf( out, "%-*s %soutNbElement",
                        prototype? 12 : 0,
                        prototype? "TA_Integer" : "",
                        prototype? "*" : "" );
            fprintf( out, "%s\n", frame? "":"," );
      }

      for( i=0; i < funcInfo->nbOutput; i++ )
      {
         if( i == (funcInfo->nbOutput-1) )
            lastParam = 1;

         retCode = TA_SetOutputParameterInfoPtr( funcInfo->handle,
                                                 i, &outputParamInfo );

         if( retCode != TA_SUCCESS )
         {
            printf( "[%s] invalid 'output' information\n", funcInfo->name );
            return;
         }

         paramName = outputParamInfo->paramName;

         switch( outputParamInfo->type )
         {
         case TA_Output_Real:
            typeString = "TA_Real";
            defaultParamName = "outReal";
            break;
         case TA_Output_Integer:
            typeString = "TA_Integer";
            defaultParamName = "outInteger";
            break;
         case TA_Output_Draw:
            typeString = "TA_Draw";
            defaultParamName = "outDraw";
            break;
         default:
            if( !paramName )
               paramName = "outParam";
            printf( "[%s,%s_%d] invalid 'output' type(%d)\n",
                    funcInfo->name, paramName, paramNb,
                    outputParamInfo->type );
            return;
         }

         if( !paramName )
            paramName = defaultParamName;

         if( validationCode )
         {
            fprintf( out, "   if( %s_%d == NULL )\n", paramName, paramNb );
            fprintf( out, "      return TA_BAD_PARAM;\n\n" );
         }
         else
         {
            printIndent( out, indent );
            if( frame )
               fprintf( out, "out[%d].p.out.data.%s%s /*",
                        paramNb, defaultParamName,
                        lastParam? "":"," );

            fprintf( out, "%-*s  %s_%d%s",
                     prototype? 12 : 0,
                     prototype? typeString : "",                     
                     paramName, paramNb,
                     prototype? "[]" : "" );

            if( !lastParam )
               fprintf( out, "%s\n", frame? " */":"," );
            else
            {
               fprintf( out, "%s )%s\n",
                        frame? " */":"",
                        semiColonNeeded? ";":"" );
            }
         }

         paramNb++;
      }
   }
}

static void printCallFrame( FILE *out, const TA_FuncInfo *funcInfo )
{
   printFrameHeader( out, funcInfo );
   fprintf( out, "\n{\n" );

   if( funcInfo->nbOptInput == 0 )
       fprintf( out, "   (void)optIn; /* Get rid of compiler warning. */\n" );

   printFunc( out, "   return ", funcInfo, 0, 1, 1, 0, 0 );
   fprintf( out, "}\n" );
}


static void printFrameHeader( FILE *out, const TA_FuncInfo *funcInfo )
{
   fprintf( out, "TA_RetCode TA_%s_FramePP( TA_Libc            *libHandle,\n", funcInfo->name );
   fprintf( out, "                          TA_Integer          startIdx,\n" );
   fprintf( out, "                          TA_Integer          endIdx,\n" );
   fprintf( out, "                          TA_Integer         *outBegIdx,\n" );
   fprintf( out, "                          TA_Integer         *outNbElement,\n" );
   fprintf( out, "                          TA_ParamHolderPriv  in[],\n" );
   fprintf( out, "                          TA_ParamHolderPriv  optIn[],\n" );
   fprintf( out, "                          TA_ParamHolderPriv  out[] )" );
}

static void printExternReferenceForEachFunction( TA_Libc *libHandle,
                                                 const TA_FuncInfo *info,
                                                 void *opaqueData )
{
   (void)opaqueData; /* Get ride of compiler warning */
   (void)libHandle;  /* Get ride of compiler warning */

   fprintf( gOutGroupIdx_C->file, "extern const TA_FuncDef TA_DEF_%s;\n", info->name );
}

static void printPerGroupList( TA_Libc *libHandle,
                               const char *groupName,
                               unsigned int index,
                               unsigned int isFirst,
                               unsigned int isLast
                             )
{
   (void)isLast; /* Get ride of compiler warning. */
   (void)isFirst; /* Get ride of compiler warning. */

   fprintf( gOutGroupIdx_C->file,
           "\nconst TA_FuncDef *TA_PerGroupFunc_%d[] = {\n", index );

   gCurrentGroupName = groupName;
   TA_ForEachFunc( libHandle, printFunctionAddress, NULL );
   fprintf( gOutGroupIdx_C->file, "NULL };\n" );

   fprintf( gOutGroupIdx_C->file,
      "#define SIZE_GROUP_%d ((sizeof(TA_PerGroupFunc_%d)/sizeof(const TA_FuncDef *))-1)\n",
      index, index );
}

static void printFunctionAddress( TA_Libc *libHandle,
                                  const TA_FuncInfo *info,
                                  void *opaqueData )
{
   (void)opaqueData; /* Get ride of compiler warning. */
   (void)libHandle;  /* Get ride of compiler warning. */

   if( strcmp( info->group, gCurrentGroupName ) == 0 )
      fprintf( gOutGroupIdx_C->file, "&TA_DEF_%s,\n", info->name );
}

static void printGroupListAddress( TA_Libc *libHandle,
                                   const char *groupName,
                                   unsigned int index,
                                   unsigned int isFirst,
                                   unsigned int isLast
                                  )
{
   (void)isFirst;   /* Get ride of compiler warning. */
   (void)libHandle; /* Get ride of compiler warning. */

   if( groupName == NULL )
      fprintf( gOutGroupIdx_C->file, "NULL%s", isLast? "" : "," );
   else fprintf( gOutGroupIdx_C->file, "&TA_PerGroupFunc_%d[0]%s\n",
                 index, isLast? "" : "," );
}

static void printGroupSize( TA_Libc *libHandle,
                            const char *groupName,
                            unsigned int index,
                            unsigned int isFirst,
                            unsigned int isLast
                           )
{
   (void)isFirst;   /* Get ride of compiler warning. */
   (void)groupName; /* Get ride of compiler warning. */
   (void)libHandle; /* Get ride of compiler warning. */

   fprintf( gOutGroupIdx_C->file, "SIZE_GROUP_%d%s\n",
            index, isLast? "" : "," );
}

static void printGroupSizeAddition( TA_Libc *libHandle,
                                    const char *groupName,
                                    unsigned int index,
                                    unsigned int isFirst,
                                    unsigned int isLast
                                   )
{
   (void)isFirst;   /* Get ride of compiler warning. */
   (void)groupName; /* Get ride of compiler warning. */
   (void)libHandle; /* Get ride of compiler warning. */

   fprintf( gOutGroupIdx_C->file, "SIZE_GROUP_%d%s",
            index, isLast? ";" : "+\n" );
}

static void doFuncFile( const TA_FuncInfo *funcInfo )
{

   FileHandle *tempFile;
   unsigned int useTempFile;

   /* Check if the file already exist. */
   sprintf( gTempBuf, "..\\src\\ta_func\\ta_%s.c", funcInfo->name );

   gOutFunc_C = fileOpen( gTempBuf, NULL, FILE_READ );
   if( gOutFunc_C == NULL )
      useTempFile = 0;
   else
   {
      useTempFile = 1;
      /* Create a temporary template using it. */
      sprintf( gTempBuf, "..\\temp\\ta_%s.tmp", funcInfo->name );

      tempFile = fileOpen( gTempBuf, NULL, FILE_WRITE );
      if( tempFile == NULL )
      {
         printf( "Cannot create temporary file!\n" );
         return;
      }

      createTemplate( funcInfo->name, gOutFunc_C, tempFile );

      fileClose( tempFile );
      fileClose( gOutFunc_C );
   }

   /* Open the file using the template. */
   if( useTempFile )
      sprintf( gTempBuf2, "..\\temp\\ta_%s.tmp", funcInfo->name );
   else
      sprintf( gTempBuf2, "..\\src\\ta_abstract\\templates\\ta_x.c.template" );

   sprintf( gTempBuf, "..\\src\\ta_func\\ta_%s.c", funcInfo->name );

   gOutFunc_C = fileOpen( gTempBuf, gTempBuf2, FILE_WRITE );

   if( gOutFunc_C == NULL )
   {
      printf( "Cannot create [%s]\n", gTempBuf );
      return;
   }

   writeFuncFile( funcInfo );

   fileClose( gOutFunc_C );
}

static int createTemplate( const char *name, FileHandle *in, FileHandle *out )
{
   FILE *inFile;
   FILE *outFile;
   unsigned int skipSection;
   unsigned int sectionDone;

   (void)name;

   inFile = in->file;
   outFile = out->file;

   skipSection = 0;
   sectionDone = 0;
   while( fgets( gTempBuf, 2048, inFile ) )
   {
      if( strncmp( gTempBuf, "/**** START GENCODE SECTION", 27 ) == 0 )
      {
         skipSection = 1;
         fputs( gTempBuf, outFile );
         fputs( "%%%GENCODE%%%\n", outFile );
      }

      else if( strncmp( gTempBuf, "/**** END GENCODE SECTION", 25 ) == 0 )
      {
         if( skipSection )
         {
            skipSection = 0;
            sectionDone++;
         }
      }

      if( !skipSection )
      {
         if( fputs( gTempBuf, outFile ) == EOF )
         {
            printf( "Cannot write tmp file\n" );
            return -1;
         }
      }
   }

#if 0
   if( sectionDone != 2 )
   {
      printf( "Missing Section in file [%s]\n", name );
      return -1;
   }
#endif

   return 0;
}

static void writeFuncFile( const TA_FuncInfo *funcInfo )
{
   FILE *out;

   out = gOutFunc_C->file;
   fprintf( out, "/* All code within this section is automatically\n" );
   fprintf( out, " * generated by gen_code. Any modification will be lost\n" );
   fprintf( out, " * next time gen_code is run.\n" );
   fprintf( out, " */\n" );
   fprintf( out, "\n" );
   fprintf( out, "#ifndef TA_FUNC_H\n" );
   fprintf( out, "   #include \"ta_func.h\"\n" );
   fprintf( out, "#endif\n" );
   fprintf( out, "\n" );
   fprintf( out, "#ifndef TA_UTILITY_H\n" );
   fprintf( out, "   #include \"ta_utility.h\"\n" );
   fprintf( out, "#endif\n" );
   fprintf( out, "\n" );
   printFunc( out, NULL, funcInfo, 1, 0, 0, 0, 1 );
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   fprintf( out, "/*\n" );
   printFuncHeaderDoc( out, funcInfo, " * " );
   fprintf( out, " */\n" );
   fprintf( out, "\n" );
   printFunc( out, NULL, funcInfo, 1, 0, 0, 0, 0 );
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   fprintf( out, "\n   (void)libHandle; /* Get ride of warning if unused. */\n" );
   fprintf( out, "\n" );
   fprintf( out, "#ifndef TA_FUNC_NO_RANGE_CHECK\n" );
   fprintf( out, "\n" );
   fprintf( out, "   /* Validate the requested output range. */\n" );
   fprintf( out, "   if( startIdx < 0 )\n" );
   fprintf( out, "      return TA_OUT_OF_RANGE_START_INDEX;\n" );
   fprintf( out, "   if( (endIdx < 0) || (endIdx < startIdx))\n" );
   fprintf( out, "      return TA_OUT_OF_RANGE_END_INDEX;\n" );
   fprintf( out, "\n" );
   /* Generate the code for checking the parameters.
    * Also generates the code for setting up the
    * default values.
    */
   fprintf( out, "   /* Validate the parameters. */\n" );
   printFunc( out, NULL, funcInfo, 0, 0, 0, 1, 0 );

   fprintf( out, "#endif /* TA_FUNC_NO_RANGE_CHECK */\n" );
   fprintf( out, "\n" );
}

static void printOptInputValidation( FILE *out,
                                     const char *name,
                                     unsigned int paramNb,
                                     const TA_OptInputParameterInfo *optInputParamInfo )
{
   TA_Integer minInt, maxInt;
   TA_Real minReal, maxReal;
   unsigned int i;

   const TA_RealList     *realList;
   const TA_IntegerList  *integerList;
   const TA_RealRange *realRange;
   const TA_IntegerRange *integerRange;

   minInt  = maxInt  = (TA_Integer)0;
   minReal = maxReal = (TA_Real)0.0;

   switch( optInputParamInfo->type )
   {
   case TA_OptInput_RealRange:
      realRange = (const TA_RealRange *)optInputParamInfo->dataSet;
      minReal = realRange->min;
      maxReal = realRange->max;
      break;
   case TA_OptInput_IntegerRange:
      integerRange = (const TA_IntegerRange *)optInputParamInfo->dataSet;
      minInt = integerRange->min;
      maxInt = integerRange->max;
      break;
   case TA_OptInput_RealList:
      /* Go through the list to find the min/max. */
      realList = (const TA_RealList *)optInputParamInfo->dataSet;
      minReal = realList->data[0].value;
      maxReal = realList->data[0].value;
      for( i=0; i < realList->nbElement; i++ )
      {
         minReal = min( realList->data[i].value, minReal );
         maxReal = max( realList->data[i].value, maxReal );
      }
      break;
   case TA_OptInput_IntegerList:
      /* Go through the list to find the min/max. */
      integerList = (const TA_IntegerList *)optInputParamInfo->dataSet;
      minInt = integerList->data[0].value;
      maxInt = integerList->data[0].value;
      for( i=0; i < integerList->nbElement; i++ )
      {
         minInt = min( integerList->data[i].value, minInt );
         maxInt = max( integerList->data[i].value, maxInt );
      }
      break;
   }

   switch( optInputParamInfo->type )
   {
   case TA_OptInput_RealList:
      fprintf( out, "   /* min/max are checked for %s_%d. */\n", name, paramNb );
   case TA_OptInput_RealRange:
      fprintf( out, "   if( %s_%d == TA_REAL_DEFAULT )\n", name, paramNb );
      fprintf( out, "      %s_%d = %s;\n", name, paramNb, doubleToStr(optInputParamInfo->defaultValue) );
      fprintf( out, "   else if( (%s_%d < %s) ||", name, paramNb, doubleToStr(minReal) );
      fprintf( out, " (%s_%d > %s) )\n", name, paramNb, doubleToStr(maxReal) );
              
      break;
   case TA_OptInput_IntegerRange:
      fprintf( out, "   /* min/max are checked for %s_%d. */\n", name, paramNb );
   case TA_OptInput_IntegerList:
      fprintf( out, "   if( %s_%d == TA_INTEGER_DEFAULT )\n", name, paramNb );
      fprintf( out, "      %s_%d = %d;\n", name, paramNb, (int)optInputParamInfo->defaultValue );
      fprintf( out, "   else if( (%s_%d < %d) || (%s_%d > %d) )\n",
              name, paramNb, minInt,
              name, paramNb, maxInt );
      break;
   }

   fprintf( out, "      return TA_BAD_PARAM;\n\n" );
}


static int skipToGenCode( const char *dstName, FILE *out, FILE *templateFile )
{
   unsigned int headerWritten = 0;

   while( fgets( gTempBuf, 2048, templateFile ) )
   {
      if( strncmp( gTempBuf, "%%%GENCODE%%%", 13 ) == 0 )
      {
         headerWritten = 1;
         break;
      }
      if( fputs( gTempBuf, out ) == EOF )
      {
         printf( "Cannot write to [%s]\n", dstName );
         return -1;
      }
   }

   if( !headerWritten )
   {
      printf( "Line with string %%%%%%GENCODE%%%%%% Missing in [%s]", dstName );
      return -1;
   }

   return 0;
}

static void printFuncHeaderDoc( FILE *out,
                                const TA_FuncInfo *funcInfo,
                                const char *prefix )
{
   TA_RetCode retCode;
   unsigned int paramNb;
   const char *paramName;
   const char *defaultParamName;
   const TA_InputParameterInfo *inputParamInfo;
   const TA_OptInputParameterInfo *optInputParamInfo;
   const TA_OutputParameterInfo *outputParamInfo;
   int first;

   fprintf( out, "%sTA_%s - %s\n", prefix, funcInfo->name, funcInfo->hint );
   fprintf( out, prefix );

   fprintf( out, "\n%sInput  = ", prefix );
   for( paramNb=0; paramNb < funcInfo->nbInput; paramNb++ )
   {
      retCode = TA_SetInputParameterInfoPtr( funcInfo->handle,
                                             paramNb, &inputParamInfo );

      if( retCode != TA_SUCCESS )
      {
         printf( "[%s] invalid 'input' information\n", funcInfo->name );
         return;
      }

      switch( inputParamInfo->type )
      {
      case TA_Input_Price:
         first = 1;
         #define PRICE_PARAM(upperParam,lowerParam) \
         { \
            if( inputParamInfo->flags & TA_IN_PRICE_##upperParam ) \
            { \
               if( !first ) fprintf( out, ", " ); \
               fprintf( out, lowerParam ); \
               first = 0; \
            } \
         }

         PRICE_PARAM( OPEN,         "Open" );
         PRICE_PARAM( HIGH,         "High" );
         PRICE_PARAM( LOW,          "Low" );
         PRICE_PARAM( CLOSE,        "Close" );
         PRICE_PARAM( VOLUME,       "Volume" );
         PRICE_PARAM( OPENINTEREST, "OpenInterest" );
         PRICE_PARAM( TIMESTAMP,    "Timestamp" );

         #undef PRICE_PARAM

         break;
      case TA_Input_Integer:
         fprintf( out, "TA_Integer" );
         break;
      case TA_Input_Real:
         fprintf( out, "TA_Real" );
         break;
/*      case TA_Input_Timestamp:
         fprintf( out, "TA_Timestamp" );
         break;*/
      }
      if( paramNb+1 == funcInfo->nbInput )
         fprintf( out, "\n" );
      else
         fprintf( out, ", " );
   }

   fprintf( out, "%sOutput = ", prefix );
   for( paramNb=0; paramNb < funcInfo->nbOutput; paramNb++ )
   {
      retCode = TA_SetOutputParameterInfoPtr( funcInfo->handle,
                                              paramNb, &outputParamInfo );

      if( retCode != TA_SUCCESS )
      {
         printf( "[%s] invalid 'output' information\n", funcInfo->name );
         return;
      }

      switch( outputParamInfo->type )
      {
      case TA_Output_Real:
         fprintf( out, "TA_Real" );
         break;
      case TA_Output_Integer:
         fprintf( out, "TA_Integer" );
         break;
      case TA_Output_Draw:
         fprintf( out, "TA_Draw" );
         break;
      }
      if( paramNb+1 == funcInfo->nbOutput )
         fprintf( out, "\n" );
      else
         fprintf( out, ", " );
   }

   if( funcInfo->nbOptInput != 0 )
   {
      fprintf( out, "%s\n", prefix );
      fprintf( out, "%sOptional Parameters\n", prefix );
      fprintf( out, "%s-------------------\n", prefix );
  
      for( paramNb=0; paramNb < funcInfo->nbOptInput; paramNb++ )
      {
         retCode = TA_SetOptInputParameterInfoPtr( funcInfo->handle,
                                                paramNb, &optInputParamInfo );

         if( retCode != TA_SUCCESS )
         {
            printf( "[%s] invalid 'optional input' information\n", funcInfo->name );
            return;
         }

         paramName = optInputParamInfo->paramName;

         switch( optInputParamInfo->type )
         {
         case TA_OptInput_RealRange:
         case TA_OptInput_RealList:
            defaultParamName = "optInReal";
            break;
         case TA_OptInput_IntegerRange:
         case TA_OptInput_IntegerList:
            defaultParamName = "optInInteger";
            break;
         default:
            if( !paramName )
               paramName = "optInParam";
            printf( "[%s,%s_%d] invalid 'optional input' type(%d)\n",
                    funcInfo->name, paramName, paramNb,
                    optInputParamInfo->type );
            return;
         }

         if( !paramName )
            paramName = defaultParamName;

         fprintf( out, "%s%s_%d:", prefix, paramName, paramNb );
         switch( optInputParamInfo->type )
         {
         case TA_OptInput_RealRange:
               if( ((TA_RealRange *)(optInputParamInfo->dataSet))->min == TA_REAL_MIN )
                  fprintf( out, "(From TA_REAL_MIN" );
               else
               {
                  fprintf( out, "(From %.*e",
                           ((TA_RealRange *)(optInputParamInfo->dataSet))->precision,
                           ((TA_RealRange *)(optInputParamInfo->dataSet))->min );
               }

               if( ((TA_RealRange *)(optInputParamInfo->dataSet))->max == TA_REAL_MAX )
                  fprintf( out, " to TA_REAL_MAX)\n" );
               else
               {
                  fprintf( out, " to %.*e%s)\n", 
                          ((TA_RealRange *)(optInputParamInfo->dataSet))->precision,
                          ((TA_RealRange *)(optInputParamInfo->dataSet))->max,
                          optInputParamInfo->flags & TA_OPTIN_IS_PERCENT? " %":"" );
               }
               break;
         case TA_OptInput_IntegerRange:
               if( ((TA_IntegerRange *)(optInputParamInfo->dataSet))->min == TA_INTEGER_MIN )
                  fprintf( out, "(From TA_INTEGER_MIN" );
               else
               {
                  fprintf( out, "(From %d",
                           ((TA_IntegerRange *)(optInputParamInfo->dataSet))->min );
               }

               if( ((TA_IntegerRange *)(optInputParamInfo->dataSet))->max == TA_INTEGER_MAX )
                  fprintf( out, " to TA_INTEGER_MAX)\n" );
               else
               {
                  fprintf( out, " to %d)\n", 
                          ((TA_IntegerRange *)(optInputParamInfo->dataSet))->max );
               }
               break;
         default:
             fprintf( out, "\n" );
         }
         fprintf( out, "%s   %s\n", prefix, optInputParamInfo->hint );
         fprintf( out, "%s\n", prefix );
      }
   }

   fprintf( out, "%s\n", prefix );
}

static int printUnstablePeriodCode( void )
{
   TA_RetCode retCode;
   unsigned int id;

   fprintf( gOutFunc_H->file, "\n" );
   fprintf( gOutFunc_H->file, "/* Some TA functions takes a certain amount of input data\n" );
   fprintf( gOutFunc_H->file, " * before stabilizing and outputing meaningful data. This is\n" );
   fprintf( gOutFunc_H->file, " * a behavior pertaining to the algo of some TA functions and\n" );
   fprintf( gOutFunc_H->file, " * is not particular to the TA-Lib implementation.\n" );
   fprintf( gOutFunc_H->file, " * TA-Lib allows you to automatically strip off these unstable\n");
   fprintf( gOutFunc_H->file, " * data from your output and from any internal processing.\n" );
   fprintf( gOutFunc_H->file, " * (See documentation for more info)\n" );
   fprintf( gOutFunc_H->file, " *\n" );
   fprintf( gOutFunc_H->file, " * Examples:\n" );
   fprintf( gOutFunc_H->file, " *      TA_SetUnstablePeriod( libHandle, TA_FUNC_UNST_EMA, 30 );\n" );
   fprintf( gOutFunc_H->file, " *           Always strip off 30 price bar for the TA_EMA function.\n" );
   fprintf( gOutFunc_H->file, " *\n" );
   fprintf( gOutFunc_H->file, " *      TA_SetUnstablePeriod( libHandle, TA_FUNC_UNST_ALL, 30 );\n" );
   fprintf( gOutFunc_H->file, " *           Always strip off 30 price bar from ALL functions\n" );
   fprintf( gOutFunc_H->file, " *           having an unstable period.\n" );
   fprintf( gOutFunc_H->file, " *\n" );
   fprintf( gOutFunc_H->file, " */\n" );
   
   fprintf( gOutFunc_H->file, "typedef enum {\n" );

   /* Enumerate the function having an "unstable period". Give
    * to each an unique identifier.
    */
   id = 1;
   retCode = TA_ForEachFunc( gLibHandle, doForEachUnstableFunction, &id );

   fprintf( gOutFunc_H->file, "               TA_FUNC_UNST_ALL,\n");
   fprintf( gOutFunc_H->file, "               TA_FUNC_UNST_NONE=-1 } TA_FuncUnstId;\n" );

   if( retCode != TA_SUCCESS )
      return -1;

   fprintf( gOutFunc_H->file, "\n" );
   fprintf( gOutFunc_H->file, "TA_RetCode TA_SetUnstablePeriod( TA_Libc      *libHandle,\n" );
   fprintf( gOutFunc_H->file, "                                 TA_FuncUnstId id,\n" );
   fprintf( gOutFunc_H->file, "                                 unsigned int  unstablePeriod );\n" );
   fprintf( gOutFunc_H->file, "\n" );
   fprintf( gOutFunc_H->file, "unsigned int TA_GetUnstablePeriod( TA_Libc      *libHandle,\n" );
   fprintf( gOutFunc_H->file, "                                   TA_FuncUnstId id);\n" );
   fprintf( gOutFunc_H->file, "\n" );

   return 0;
}


static int gen_retcode( void )
{
   FileHandle *inHdr;
   char *ptr1, *ptr2;
   int step1Done;
   int retValue;
   TA_RetCode retCodeValue;
   char *retCodeEnum, *retCodeInfo;

   retValue = -1;

   /* Create "ta_retcode.c" */
   gOutRetCode_C = fileOpen( "..\\src\\ta_common\\ta_retcode.c",
                             "..\\src\\ta_abstract\\templates\\ta_retcode.c.template",
                             FILE_WRITE );

   if( gOutRetCode_C == NULL )
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   /* Create "ta_retcode.csv" */
   gOutRetCode_CSV = fileOpen( "..\\src\\ta_common\\ta_retcode.csv", NULL, FILE_WRITE );

   if( gOutRetCode_CSV == NULL )
   {
      fileClose( gOutRetCode_C );
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   inHdr = fileOpen( "..\\include\\ta_common.h", NULL, FILE_READ );
   if( inHdr == NULL )
   {
      fileClose( gOutRetCode_C );
      fileClose( gOutRetCode_CSV );
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   step1Done = 0;
   while( fgets( gTempBuf, sizeof( gTempBuf ), inHdr->file ) )
   {
      if( !step1Done )
      {
         if( stricstr( gTempBuf, "TA-LIB Error Code" ) != NULL )
            step1Done = 1;
      }
      else
      {
         if( stricstr( gTempBuf, "TA_UNKNOWN_ERR" ) != NULL )
         {
            retValue = 0;
            goto gen_retcode_exit;
         }

         ptr1 = stricstr( gTempBuf, "/*" );
         ptr2 = stricstr( gTempBuf, "/***" );
         if( ptr1 && !ptr2 )
         {
            ptr1 += 2;
            retCodeValue = atoi(ptr1);
            ptr1 = stricstr( ptr1, "TA_" );
            if( !ptr1 )
               goto gen_retcode_exit;
            retCodeEnum = ptr1;

            retCodeInfo = NULL;
            while( isdigit(*ptr1) || isalpha(*ptr1) || *ptr1 == '_' )
               ptr1++;
            if( *ptr1 != '\0' )
            {
               *ptr1 = '\0';
               ptr1++;
               if( *ptr1 != '\0' )
               {
                  retCodeInfo = stricstr( ptr1, "/* " );
                  if( retCodeInfo )
                  {
                     retCodeInfo += 3;
                     ptr1 = stricstr( retCodeInfo, "*/" );
                     if( ptr1 == NULL )
                        retCodeInfo = NULL;
                     else
                        *ptr1 = '\0';
                  }
               }                  
            }

            if( !retCodeInfo )
               retCodeInfo = "No Info";

            strcpy( gTempBuf, retCodeEnum );
            ptr1 = trim( gTempBuf );
            fprintf( gOutRetCode_C->file, "         {%d,\"%s\",", retCodeValue, ptr1 );                     
            fprintf( gOutRetCode_CSV->file, "%d,%s", retCodeValue, ptr1 );
            strcpy( gTempBuf, retCodeInfo );
            ptr1 = trim( gTempBuf );
            fprintf( gOutRetCode_C->file, "\"%s\"},\n", ptr1 );
            fprintf( gOutRetCode_CSV->file, ",%s\n", ptr1 );
         }
      }
   }

gen_retcode_exit:
   fileClose( inHdr );
   fileClose( gOutRetCode_C );

   return retValue; /* Success. */
}

const char *doubleToStr( TA_Real value )
{
   int length;
   int i, outIdx;
   sprintf( gTempDoubleToStr, "%e", value );

   /* Remove extra "0" added by Microsoft in the
    * exponential part.
    */
   length = strlen( gTempDoubleToStr );
   outIdx = 0;
   for( i=0; i < length; i++ )
   {
      /* Will skip two leading zero in the exponent */
      if( (i >= 2) &&
          (toupper(gTempDoubleToStr[i-2]) == 'E') &&
          ((gTempDoubleToStr[i-1] == '+')||(gTempDoubleToStr[i-1] == '-')) &&
          (gTempDoubleToStr[i] == '0') &&
          (gTempDoubleToStr[i+1] == '0') &&
          (isdigit(gTempDoubleToStr[i+2])) )
      {
         i++;
         continue;
      }

      /* Will skip one leading zero in the exponent */
      if( (i >= 2) &&
          (toupper(gTempDoubleToStr[i-2]) == 'E') &&
          ((gTempDoubleToStr[i-1] == '+')||(gTempDoubleToStr[i-1] == '-')) &&
          (gTempDoubleToStr[i] == '0') &&
          (isdigit(gTempDoubleToStr[i+1])))
      {
         continue;
      }

      gTempDoubleToStr[outIdx++] = gTempDoubleToStr[i];
   }
   gTempDoubleToStr[outIdx] = '\0';

   return gTempDoubleToStr;
}