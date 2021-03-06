/* TA-LIB Copyright (c) 1999-2002, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* List of contributors:
 *
 *  Initial  Name/description
 *  -------------------------------------------------------------------
 *  MF       Mario Fortier
 *
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  020101 MF   First version.
 *
 */

/* Description:
 *   Provide a way to abstract the call of the TA functions.
 */

/**** Headers ****/
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include "ta_common.h"
#include "ta_memory.h"
#include "ta_abstract.h"
#include "ta_def_ui.h"
#include "ta_frame_priv.h"
#include "ta_trace.h"

#include <limits.h>

/**** External functions declarations. ****/
/* None */

/**** External variables declarations. ****/

/* The interface definition of all functions are accessible
 * through one of the following 26 tables.
 */
extern const TA_FuncDef *TA_DEF_TableA, *TA_DEF_TableB, *TA_DEF_TableC,
                        *TA_DEF_TableD, *TA_DEF_TableE, *TA_DEF_TableF,
                        *TA_DEF_TableG, *TA_DEF_TableH, *TA_DEF_TableI,
                        *TA_DEF_TableJ, *TA_DEF_TableK, *TA_DEF_TableL,
                        *TA_DEF_TableM, *TA_DEF_TableN, *TA_DEF_TableO,
                        *TA_DEF_TableP, *TA_DEF_TableQ, *TA_DEF_TableR,
                        *TA_DEF_TableS, *TA_DEF_TableT, *TA_DEF_TableU,
                        *TA_DEF_TableV, *TA_DEF_TableW, *TA_DEF_TableX,
                        *TA_DEF_TableY, *TA_DEF_TableZ;

extern const unsigned int TA_DEF_TableASize, TA_DEF_TableBSize,
                          TA_DEF_TableCSize, TA_DEF_TableDSize,
                          TA_DEF_TableESize, TA_DEF_TableFSize,
                          TA_DEF_TableGSize, TA_DEF_TableHSize,
                          TA_DEF_TableISize, TA_DEF_TableJSize,
                          TA_DEF_TableKSize, TA_DEF_TableLSize,
                          TA_DEF_TableMSize, TA_DEF_TableNSize,
                          TA_DEF_TableOSize, TA_DEF_TablePSize,
                          TA_DEF_TableQSize, TA_DEF_TableRSize,
                          TA_DEF_TableSSize, TA_DEF_TableTSize,
                          TA_DEF_TableUSize, TA_DEF_TableVSize,
                          TA_DEF_TableWSize, TA_DEF_TableXSize,
                          TA_DEF_TableYSize, TA_DEF_TableZSize;

#ifndef TA_GEN_CODE
   /* In gen_code, these value does not exist (they are generated by
    * gen_code itself!)
    * Consequently, the code must provide the same functionality
    * without using these.
    */
   extern const TA_FuncDef **TA_PerGroupFuncDef[];
   extern const unsigned int TA_PerGroupSize[];
#endif

/**** Global variables definitions.    ****/
/* None */

/**** Local declarations.              ****/
#ifndef min
   #define min(a, b)  (((a) < (b)) ? (a) : (b))
#endif

typedef struct 
{
   unsigned int magicNb;
   TA_Libc *libHandle;
} TA_StringTableGroupHidden;

typedef struct 
{
   unsigned int magicNb;
   TA_Libc *libHandle;
} TA_StringTableFuncHidden;


/**** Local functions declarations.    ****/


#ifdef TA_GEN_CODE
   static TA_RetCode getGroupId( TA_Libc *libHandle, const char *groupString, unsigned int *groupId );
   static TA_RetCode getGroupSize( TA_Libc *libHandle, TA_GroupId groupId, unsigned int *groupSize );
   static TA_RetCode getFuncNameByIdx( TA_Libc *libHandle,
                                       TA_GroupId groupId,
                                       unsigned int idx,
                                       const char **stringPtr );
#else
   static TA_RetCode getGroupId( const char *groupString, unsigned int *groupId );
   static TA_RetCode getGroupSize( TA_GroupId groupId, unsigned int *groupSize );
   static TA_RetCode getFuncNameByIdx( TA_GroupId groupId,
                                       unsigned int idx,
                                       const char **stringPtr );
#endif

/**** Local variables definitions.     ****/
TA_FILE_INFO;

static const TA_FuncDef **TA_DEF_Tables[26] =
{
   &TA_DEF_TableA, &TA_DEF_TableB, &TA_DEF_TableC, &TA_DEF_TableD, &TA_DEF_TableE,
   &TA_DEF_TableF, &TA_DEF_TableG, &TA_DEF_TableH, &TA_DEF_TableI, &TA_DEF_TableJ,
   &TA_DEF_TableK, &TA_DEF_TableL, &TA_DEF_TableM, &TA_DEF_TableN, &TA_DEF_TableO,
   &TA_DEF_TableP, &TA_DEF_TableQ, &TA_DEF_TableR, &TA_DEF_TableS, &TA_DEF_TableT,
   &TA_DEF_TableU, &TA_DEF_TableV, &TA_DEF_TableW, &TA_DEF_TableX, &TA_DEF_TableY,
   &TA_DEF_TableZ
};

static const unsigned int *TA_DEF_TablesSize[26] =
{
   &TA_DEF_TableASize, &TA_DEF_TableBSize, &TA_DEF_TableCSize,
   &TA_DEF_TableDSize, &TA_DEF_TableESize, &TA_DEF_TableFSize,
   &TA_DEF_TableGSize, &TA_DEF_TableHSize, &TA_DEF_TableISize,
   &TA_DEF_TableJSize, &TA_DEF_TableKSize, &TA_DEF_TableLSize,
   &TA_DEF_TableMSize, &TA_DEF_TableNSize, &TA_DEF_TableOSize,
   &TA_DEF_TablePSize, &TA_DEF_TableQSize, &TA_DEF_TableRSize,
   &TA_DEF_TableSSize, &TA_DEF_TableTSize, &TA_DEF_TableUSize,
   &TA_DEF_TableVSize, &TA_DEF_TableWSize, &TA_DEF_TableXSize,
   &TA_DEF_TableYSize, &TA_DEF_TableZSize
};

/**** Global functions definitions.   ****/
TA_RetCode TA_GroupTableAlloc( TA_Libc *libHandle, TA_StringTable **table )
{
   TA_PROLOG;
   TA_StringTable *stringTable;
   TA_StringTableGroupHidden *stringTableHidden;

   TA_TRACE_BEGIN( libHandle, TA_GroupTableAlloc );

   if( table == NULL )
   {
      TA_TRACE_RETURN( TA_BAD_PARAM );
   }

   *table = NULL;

   stringTable = (TA_StringTable *)TA_Malloc( libHandle, sizeof(TA_StringTable) );

   if( !stringTable )
   {
      TA_TRACE_RETURN( TA_ALLOC_ERR );
   }

   stringTableHidden = (TA_StringTableGroupHidden *)TA_Malloc( libHandle, sizeof(TA_StringTableGroupHidden) );
   if( !stringTableHidden )
   {
      TA_Free( libHandle, stringTable );
      TA_TRACE_RETURN( TA_ALLOC_ERR );
   }

   stringTableHidden->libHandle = libHandle;
   stringTableHidden->magicNb = TA_STRING_TABLE_GROUP_MAGIC_NB;
   stringTable->size = TA_NB_GROUP_ID;
   stringTable->string = &TA_GroupString[0];
   stringTable->hiddenData = stringTableHidden;

   /* From this point, TA_FuncTableFree can be safely called. */

   /* Success. Return the table to the caller. */
   *table = stringTable;

   TA_TRACE_RETURN( TA_SUCCESS );
}

TA_RetCode TA_GroupTableFree( TA_StringTable *table )
{
   TA_StringTableGroupHidden *stringTableHidden;
   TA_Libc *libHandle;

   if( table )
   {
      stringTableHidden = (TA_StringTableGroupHidden *)table->hiddenData;
      if( !stringTableHidden )
         return TA_INTERNAL_ERROR(1);
   
      if( stringTableHidden->magicNb != TA_STRING_TABLE_GROUP_MAGIC_NB )
         return TA_BAD_OBJECT;

      libHandle = stringTableHidden->libHandle;

      TA_Free( libHandle, stringTableHidden );
      TA_Free( libHandle, table );
   }

   return TA_SUCCESS;
}

TA_RetCode TA_ForEachFunc( TA_Libc *libHandle, TA_CallForEachFunc functionToCall, void *opaqueData )
{
   TA_PROLOG;
   TA_StringTable   *tableGroup;
   TA_StringTable   *tableFunc;
   const TA_FuncDef *funcDef;
   const TA_FuncHandle *funcHandle;
   TA_RetCode retCode;
   unsigned int i, j;

   const TA_FuncInfo *funcInfo;

   TA_TRACE_BEGIN( libHandle, TA_ForEachFunc );

   if( functionToCall == NULL )
   {
      TA_TRACE_RETURN( TA_BAD_PARAM );
   }
   
   /* Get all the group to iterate. */
   retCode = TA_GroupTableAlloc( libHandle, &tableGroup );

   if( retCode == TA_SUCCESS )
   {
      TA_ASSERT( libHandle, tableGroup != NULL );

      for( i=0; i < tableGroup->size; i++ )
      {
         TA_DEBUG_ASSERT( libHandle, tableGroup->string[i] != NULL );

         /* Get all the symbols to iterate for this category. */
         retCode = TA_FuncTableAlloc( libHandle, tableGroup->string[i], &tableFunc );


         if( retCode == TA_SUCCESS )
         {
            TA_DEBUG_ASSERT( libHandle, tableFunc != NULL );

            for( j=0; j < tableFunc->size; j++ )
            {
               TA_DEBUG_ASSERT( libHandle, tableFunc->string[j] != NULL );

               /* Get the function handle, and then the TA_FuncDef,
                * and then the TA_FuncInfo...
                */
               retCode = TA_GetFuncHandle( libHandle, tableFunc->string[j], &funcHandle );

               if( retCode != TA_SUCCESS )
                  continue;

               TA_DEBUG_ASSERT( libHandle, funcHandle != NULL );

               funcDef  = (const TA_FuncDef *)funcHandle;

               TA_DEBUG_ASSERT( libHandle, funcDef != NULL );

               funcInfo = funcDef->funcInfo;

               TA_DEBUG_ASSERT( libHandle, funcInfo != NULL );

               /* Call user provided function. */
               (*functionToCall)( libHandle, funcInfo, opaqueData );
            }
         }

         TA_FuncTableFree( tableFunc );
      }

      TA_GroupTableFree( tableGroup );
   }
   else
   {
      TA_TRACE_RETURN( TA_INTERNAL_ERROR(2) );
   }

   TA_TRACE_RETURN( TA_SUCCESS );
}

TA_RetCode TA_FuncTableAlloc( TA_Libc *libHandle, const char *group, TA_StringTable **table )
{
   TA_PROLOG;
   TA_RetCode retCode;
   unsigned int i;
   TA_StringTable *stringTable;
   unsigned int groupId; /* TA_GroupId */
   unsigned int groupSize;
   const char *stringPtr;
   TA_StringTableFuncHidden *stringTableHidden;
   TA_TRACE_BEGIN( libHandle, TA_FuncTableAlloc );

   if( (group == NULL) || (table == NULL ) )
   {
      TA_TRACE_RETURN( TA_BAD_PARAM );
   }

   *table = NULL;

   /* Get information on the group. */
   #ifdef TA_GEN_CODE
      retCode = getGroupId( libHandle, group, &groupId );
   #else
      retCode = getGroupId( group, &groupId );
   #endif
   if( retCode != TA_SUCCESS )
   {
      TA_TRACE_RETURN( retCode );
   }

   #ifdef TA_GEN_CODE
      retCode = getGroupSize( libHandle, (TA_GroupId)groupId, &groupSize );
   #else
      retCode = getGroupSize( (TA_GroupId)groupId, &groupSize );
   #endif
   if( retCode != TA_SUCCESS )
   {
      TA_TRACE_RETURN( retCode );
   }

   /* Allocate the table. */
   stringTable = (TA_StringTable *)TA_Malloc( libHandle, sizeof(TA_StringTable) );
   if( !stringTable )
   {
      TA_TRACE_RETURN( TA_ALLOC_ERR );
   }

   stringTableHidden = (TA_StringTableFuncHidden *)TA_Malloc( libHandle, sizeof(TA_StringTableFuncHidden) );
   if( !stringTable )
   {
      TA_Free( libHandle, stringTable );
      TA_TRACE_RETURN( TA_ALLOC_ERR );
   }

   stringTable->hiddenData = stringTableHidden;
   stringTableHidden->libHandle = libHandle;
   stringTableHidden->magicNb = TA_STRING_TABLE_FUNC_MAGIC_NB;

   /* From this point, TA_FuncTableFree can be safely called. */
   stringTable->size = groupSize;
   if( groupSize == 0 )
      stringTable->string = NULL;
   else
   {
      stringTable->string = (const char **)TA_Malloc( libHandle, (stringTable->size) *
                                                      sizeof(const char *) );

      if( stringTable->string == NULL )
      {
         TA_FuncTableFree( stringTable );
         TA_TRACE_RETURN( TA_ALLOC_ERR );
      }

      memset( (void *)stringTable->string, 0,
              (stringTable->size) * sizeof(const char *) );

      for( i=0; i < stringTable->size; i++ )
      {
         #ifdef TA_GEN_CODE
            retCode = getFuncNameByIdx( libHandle, (TA_GroupId)groupId, i, &stringPtr );
         #else
            retCode = getFuncNameByIdx( (TA_GroupId)groupId, i, &stringPtr );
         #endif

         if( retCode != TA_SUCCESS )
         {
            TA_FuncTableFree( stringTable );
            TA_TRACE_RETURN( TA_ALLOC_ERR );
         }

         (stringTable->string)[i] = stringPtr;
      }
   }

   /* Return the table to the caller. */
   *table = stringTable;

   TA_TRACE_RETURN( TA_SUCCESS );
}

TA_RetCode TA_FuncTableFree( TA_StringTable *table )
{
   TA_StringTableFuncHidden *stringTableHidden;
   TA_Libc *libHandle;

   if( table )
   {
      stringTableHidden = (TA_StringTableFuncHidden *)table->hiddenData;
      if( !stringTableHidden )
         return TA_INTERNAL_ERROR(3);
   
      if( stringTableHidden->magicNb != TA_STRING_TABLE_FUNC_MAGIC_NB )
         return TA_BAD_OBJECT;

      libHandle = stringTableHidden->libHandle;

      TA_Free( libHandle, stringTableHidden );

      if( table->string )
         TA_Free( libHandle, (void *)table->string );

      TA_Free( libHandle, table );
   }

   return TA_SUCCESS;
}

TA_RetCode TA_GetFuncHandle( TA_Libc *libHandle, const char *name, const TA_FuncHandle **handle )
{
   TA_PROLOG;
   char firstChar, tmp;
   const TA_FuncDef **funcDefTable;
   const TA_FuncDef *funcDef;
   const TA_FuncInfo *funcInfo;
   unsigned int i, funcDefTableSize;

   TA_TRACE_BEGIN( libHandle, TA_GetFuncHandle );

   /* A TA_FuncHandle is internally a TA_FuncDef. Let's find it
    * by using the alphabetical tables.
    */
   if( (name == NULL) || (handle == NULL) )
   {
      TA_TRACE_RETURN( TA_BAD_PARAM );
   }

   *handle = NULL;

   firstChar = name[0];

   if( firstChar == '\0' )
   {
      TA_TRACE_RETURN( TA_BAD_PARAM );
   }

   tmp = (char)tolower( firstChar );

   if( (tmp < 'a') || (tmp > 'z') )
   {
      TA_TRACE_RETURN( TA_FUNC_NOT_FOUND );
   }

   /* Identify the table. */
   tmp -= (char)'a';
   funcDefTable = TA_DEF_Tables[(int)tmp];

   /* Identify the table size. */
   funcDefTableSize = *TA_DEF_TablesSize[(int)tmp];
   if( funcDefTableSize < 1 )
   {
      TA_TRACE_RETURN( TA_FUNC_NOT_FOUND );
   }

   /* Iterate all entries of the table and return as soon as found. */
   for( i=0; i < funcDefTableSize; i++ )
   {
      funcDef = funcDefTable[i];
      TA_DEBUG_ASSERT( libHandle, funcDef != NULL );
      TA_DEBUG_ASSERT( libHandle, funcDef->funcInfo != NULL );

      funcInfo = funcDef->funcInfo;      
      TA_DEBUG_ASSERT( libHandle, funcInfo != NULL );
      
      if( strcmp( funcInfo->name, name ) == 0 )
      {
         *handle = (TA_FuncHandle *)funcDef;
         TA_TRACE_RETURN( TA_SUCCESS );
      }
   }

   TA_TRACE_RETURN( TA_FUNC_NOT_FOUND );
}

TA_RetCode TA_GetFuncInfo(  const TA_FuncHandle *handle,
                            const TA_FuncInfo **funcInfo )
{
   const TA_FuncDef *funcDef;

   /* Validate that this is a valid funcHandle. */
   funcDef = (const TA_FuncDef *)handle;
   if( funcDef->magicNumber != TA_FUNC_DEF_MAGIC_NB )
      return TA_INVALID_HANDLE;

   if( funcInfo == NULL )
      return TA_BAD_PARAM;

   if( funcDef == NULL )
   {
      *funcInfo = NULL;
      return TA_BAD_PARAM;
   }

   *funcInfo = funcDef->funcInfo;;

   return TA_SUCCESS;
}

TA_RetCode TA_SetInputParameterInfoPtr( const TA_FuncHandle *handle,
                                        unsigned int paramIndex,
                                        const TA_InputParameterInfo **info )
{
   const TA_FuncDef  *funcDef;
   const TA_FuncInfo *funcInfo;
   const TA_InputParameterInfo **inputTable;
   
   if( (handle == NULL) || (info == NULL) )
      return TA_BAD_PARAM;

   *info = NULL;

   /* Validate that this is a valid funcHandle. */
   funcDef = (const TA_FuncDef *)handle;
   if( funcDef->magicNumber != TA_FUNC_DEF_MAGIC_NB )
      return TA_INVALID_HANDLE;
   funcInfo = funcDef->funcInfo;

   if( paramIndex >= funcInfo->nbInput )
      return TA_BAD_PARAM;

   inputTable = (const TA_InputParameterInfo **)funcDef->input;

   *info = inputTable[paramIndex];

   return TA_SUCCESS;
}

TA_RetCode TA_SetOptInputParameterInfoPtr( const TA_FuncHandle *handle,
                                           unsigned int paramIndex,
                                           const TA_OptInputParameterInfo **info )
{
   const TA_FuncDef  *funcDef;
   const TA_FuncInfo *funcInfo;
   const TA_OptInputParameterInfo **inputTable;

   if( (handle == NULL) || (info == NULL) )
      return TA_BAD_PARAM;

   *info = NULL;

   /* Validate that this is a valid funcHandle. */
   funcDef = (const TA_FuncDef *)handle;
   if( funcDef->magicNumber != TA_FUNC_DEF_MAGIC_NB )
      return TA_INVALID_HANDLE;
   funcInfo = funcDef->funcInfo;

   if( paramIndex >= funcInfo->nbOptInput )
      return TA_BAD_PARAM;

   inputTable = (const TA_OptInputParameterInfo **)funcDef->optInput;

   *info = inputTable[paramIndex];

   return TA_SUCCESS;
}

TA_RetCode TA_SetOutputParameterInfoPtr( const TA_FuncHandle *handle,
                                         unsigned int paramIndex,
                                         const TA_OutputParameterInfo **info )
{
   const TA_FuncDef  *funcDef;
   const TA_FuncInfo *funcInfo;
   const TA_OutputParameterInfo **outputTable;

   if( (handle == NULL) || (info == NULL) )
      return TA_BAD_PARAM;

   *info = NULL;

   /* Validate that this is a valid funcHandle. */
   funcDef = (const TA_FuncDef *)handle;
   if( funcDef->magicNumber != TA_FUNC_DEF_MAGIC_NB )
      return TA_INVALID_HANDLE;

   funcInfo = funcDef->funcInfo;

   if( paramIndex >= funcInfo->nbOutput )
      return TA_BAD_PARAM;

   outputTable = (const TA_OutputParameterInfo **)funcDef->output;

   *info = outputTable[paramIndex];

   return TA_SUCCESS;
}

TA_RetCode TA_ParamHoldersAlloc( TA_Libc *libHandle,
                                 const TA_FuncHandle *handle,
                                 TA_ParamHolder **newInputParams,
                                 TA_ParamHolder **newOptInputParams,
                                 TA_ParamHolder **newOutputParams )
{
   TA_PROLOG;
   TA_FuncDef *funcDef;
   unsigned int allocSize, i;
   TA_ParamHolderPriv *input;
   TA_ParamHolderPriv *optInput;
   TA_ParamHolderPriv *output;

   const TA_InputParameterInfo    *inputInfo;
   const TA_OptInputParameterInfo *optInputInfo;
   const TA_OutputParameterInfo   *outputInfo;

   const TA_FuncInfo *funcInfo;

   TA_TRACE_BEGIN( libHandle, TA_ParamHoldersAlloc );

   /* Validate the parameters. */
   if( !handle || !newInputParams || !newOptInputParams || !newOutputParams)
   {
      TA_TRACE_RETURN( TA_BAD_PARAM );
   }

   *newInputParams    = NULL;
   *newOptInputParams = NULL;
   *newOutputParams   = NULL;

   /* Validate that this is a valid funcHandle. */
   funcDef = (TA_FuncDef *)handle;
   if( funcDef->magicNumber != TA_FUNC_DEF_MAGIC_NB )
   {
      TA_TRACE_RETURN( TA_INVALID_HANDLE );
   }

   /* Get the TA_FuncInfo. */
   funcInfo = funcDef->funcInfo;
   TA_DEBUG_ASSERT( libHandle, funcInfo != NULL );

   /* Allocate all the TA_ParamHolderPriv. */
   allocSize = (funcInfo->nbInput) * sizeof(TA_ParamHolderPriv);
   input = (TA_ParamHolderPriv *)TA_Malloc( libHandle, allocSize );

   if( input == NULL )
   {
      TA_TRACE_RETURN( TA_ALLOC_ERR );
   }

   if( funcInfo->nbOptInput == 0 )
      optInput = NULL;
   else
   {
      allocSize = (funcInfo->nbOptInput) * sizeof(TA_ParamHolderPriv);
      optInput = (TA_ParamHolderPriv *)TA_Malloc( libHandle, allocSize );

      if( optInput == NULL )
      {
         TA_Free( libHandle, optInput );
         TA_TRACE_RETURN( TA_ALLOC_ERR );
      }
   }

   allocSize = (funcInfo->nbOutput) * sizeof(TA_ParamHolderPriv);
   output = (TA_ParamHolderPriv *)TA_Malloc( libHandle, allocSize );

   if( output == NULL )
   {
      TA_Free( libHandle, input );
      TA_Free( libHandle, optInput );
      TA_TRACE_RETURN( TA_ALLOC_ERR );
   }

   /* Initialize the default values. */
   inputInfo    = funcDef->input;
   optInputInfo = funcDef->optInput;
   outputInfo   = funcDef->output;

   for( i=0; i < funcInfo->nbInput; i++ )
   {
      input[i].libHandle = libHandle;
      input[i].valueInitialize = 0;
      input[i].type = TA_PARAM_HOLDER_INPUT;

      memset( &input[i].p.in.data, 0, sizeof(union TA_ParamHolderInputData) );
      input[i].p.in.inputInfo = &inputInfo[i];

      input[i].function = 0;
   }

   for( i=0; i < funcInfo->nbOptInput; i++ )
   {
      optInput[i].libHandle = libHandle;
      optInput[i].valueInitialize = 0;
      optInput[i].type = TA_PARAM_HOLDER_OPTINPUT;

      memset( &optInput[i].p.optIn.data, 0, sizeof(union TA_ParamHolderOptInData) );
      optInput[i].p.optIn.optInputInfo = &optInputInfo[i];
      optInput[i].function = 0;
   }

   for( i=0; i < funcInfo->nbOutput; i++ )
   {
      output[i].libHandle = libHandle;
      output[i].valueInitialize = 0;
      output[i].type = TA_PARAM_HOLDER_OUTPUT;

      memset( &output[i].p.out.data, 0, sizeof(union TA_ParamHolderOutputData) );
      output[i].p.out.outputInfo = &outputInfo[i];

      output[i].function = 0;
   }

   input[0].function = funcDef->function;
   optInput[0].function = funcDef->function;
   output[0].function = funcDef->function;

   /* Succcess, return the result to the caller.
    * (Disguise as TA_ParamHolder for end-user).
    */
   *newInputParams    = (TA_ParamHolder *)input;
   *newOptInputParams = (TA_ParamHolder *)optInput;
   *newOutputParams   = (TA_ParamHolder *)output;

   TA_TRACE_RETURN( TA_SUCCESS );
}

TA_RetCode TA_ParamHoldersFree( TA_ParamHolder *inputParamsToFree,
                                TA_ParamHolder *optInputParamsToFree,
                                TA_ParamHolder *outputParamsToFree )
{
   TA_PROLOG;
   TA_Libc *libHandle;
   TA_ParamHolderPriv *input;
   TA_ParamHolderPriv *optInput;
   TA_ParamHolderPriv *output;

   input    = (TA_ParamHolderPriv *)inputParamsToFree;
   optInput = (TA_ParamHolderPriv *)optInputParamsToFree;
   output   = (TA_ParamHolderPriv *)outputParamsToFree;

   if( !input || !output )
      return TA_BAD_PARAM;

   if( (input->magicNumber != TA_PARAM_HOLDER_PRIV_MAGIC_NB) ||
       (output->magicNumber != TA_PARAM_HOLDER_PRIV_MAGIC_NB) )
      return TA_INVALID_PARAM_HOLDER;

   libHandle = input->libHandle;
   TA_TRACE_BEGIN( libHandle, TA_ParamHoldersFree );

   if( optInput )
   {
      if( optInput->magicNumber != TA_PARAM_HOLDER_PRIV_MAGIC_NB )
      {
         TA_TRACE_RETURN( TA_INVALID_PARAM_HOLDER );
      }
   }

   TA_Free( libHandle, input );
   if( optInput )
      TA_Free( libHandle, optInput );
   TA_Free( libHandle, output );

   TA_TRACE_RETURN( TA_SUCCESS );
}

#define SET_INPUT_PARAMETER(paramType) \
   TA_ParamHolderPriv *paramHolderPriv; \
   const TA_InputParameterInfo *paramInfo; \
\
   if( (param == NULL) || (value == NULL) ) \
      return TA_BAD_PARAM; \
\
   paramHolderPriv = (TA_ParamHolderPriv *)param; \
\
   /* Validate the TA_ParamHolderPriv. */ \
   if( paramHolderPriv->magicNumber != TA_PARAM_HOLDER_PRIV_MAGIC_NB ) \
      return TA_INVALID_PARAM_HOLDER; \
\
   /* Check correct function is used with correct type of parameter. */ \
   if( paramHolderPriv->type != TA_PARAM_HOLDER_INPUT ) \
      return TA_INVALID_PARAM_HOLDER_TYPE; \
\
   paramInfo = paramHolderPriv->p.in.inputInfo; \
\
   if( paramInfo->type != TA_Input_##paramType ) \
      return TA_INVALID_PARAM_HOLDER_TYPE; \
\
   /* keep a copy of the provided parameter. */ \
   paramHolderPriv->p.in.data.in##paramType = value; \
\
   /* Got/validate all the information required for this parameter. */ \
   paramHolderPriv->valueInitialize = 1; \
   return TA_SUCCESS;

TA_RetCode TA_SetInputParamIntegerPtr( TA_ParamHolder *param,                                       
                                       const TA_Integer *value )
{
   SET_INPUT_PARAMETER(Integer);
}

TA_RetCode TA_SetInputParamRealPtr( TA_ParamHolder *param,
                                    const TA_Real *value )
{
   SET_INPUT_PARAMETER(Real);
}

#undef SET_INPUT_PARAMETER

TA_RetCode TA_SetInputParamPricePtr( TA_ParamHolder     *param,
                                     const TA_Timestamp *timestamp,
                                     const TA_Real      *open,
                                     const TA_Real      *high,
                                     const TA_Real      *low,
                                     const TA_Real      *close,
                                     const TA_Integer   *volume,
                                     const TA_Integer   *openInterest )
{
   /* The following code is fundamentaly the same as
    * the SET_INPUT_PARAMETER.
    */
   TA_ParamHolderPriv *paramHolderPriv;
   const TA_InputParameterInfo *paramInfo;

   if( param == NULL )
      return TA_BAD_PARAM;

   /* Validate the TA_ParamHolderPriv. */
   paramHolderPriv = (TA_ParamHolderPriv *)param;

   if( paramHolderPriv->magicNumber != TA_PARAM_HOLDER_PRIV_MAGIC_NB )
      return TA_INVALID_PARAM_HOLDER;

   /* Check correct function is used with correct type of parameter. */
   if( paramHolderPriv->type != TA_PARAM_HOLDER_INPUT )
      return TA_INVALID_PARAM_HOLDER_TYPE;

   paramInfo = paramHolderPriv->p.in.inputInfo;

   if( paramInfo->type != TA_Input_Price )
      return TA_INVALID_PARAM_HOLDER_TYPE;

   /* Validate that the needed parameter are provided. */
   #define SET_PARAM_INFO(lowerParam,upperParam) \
   { \
      if( paramInfo->flags & TA_IN_PRICE_##upperParam ) \
      { \
         if( lowerParam == NULL ) \
            return TA_BAD_PARAM; \
         paramHolderPriv->p.in.data.inPrice.lowerParam = lowerParam; \
      } \
   }

   SET_PARAM_INFO(open, OPEN );
   SET_PARAM_INFO(high, HIGH );
   SET_PARAM_INFO(low, LOW );
   SET_PARAM_INFO(close, CLOSE );
   SET_PARAM_INFO(volume, VOLUME );
   SET_PARAM_INFO(openInterest, OPENINTEREST );
   SET_PARAM_INFO(timestamp, TIMESTAMP );

   #undef SET_PARAM_INFO

   /* Got/validate all the information required for this parameter. */
   paramHolderPriv->valueInitialize = 1;
   return TA_SUCCESS;
}

#define SET_OPT_INPUT_PARAMETER(paramType) \
   TA_ParamHolderPriv *paramHolderPriv; \
   const TA_OptInputParameterInfo *paramInfo; \
\
   if( param == NULL ) \
      return TA_BAD_PARAM; \
\
   paramHolderPriv = (TA_ParamHolderPriv *)param; \
\
   /* Validate the TA_ParamHolderPriv. */ \
   if( paramHolderPriv->magicNumber != TA_PARAM_HOLDER_PRIV_MAGIC_NB ) \
      return TA_INVALID_PARAM_HOLDER; \
\
   /* Check correct function is used with correct type of parameter. */ \
   if( paramHolderPriv->type != TA_PARAM_HOLDER_OPTINPUT ) \
      return TA_INVALID_PARAM_HOLDER_TYPE; \
\
   paramInfo = paramHolderPriv->p.optIn.optInputInfo; \
\
   if( (paramInfo->type != TA_OptInput_##paramType##Range) && \
       (paramInfo->type != TA_OptInput_##paramType##List) ) \
      return TA_INVALID_PARAM_HOLDER_TYPE; \
\
   /* keep a copy of the provided parameter. */ \
   paramHolderPriv->p.optIn.data.optIn##paramType = value; \
\
   /* Got/validate all the information required for this parameter. */ \
   paramHolderPriv->valueInitialize = 1; \
   return TA_SUCCESS;

TA_RetCode TA_SetOptInputParamInteger( TA_ParamHolder *param,
                                       TA_Integer value )
{
   SET_OPT_INPUT_PARAMETER(Integer);
}

TA_RetCode TA_SetOptInputParamReal( TA_ParamHolder *param,
                                    TA_Real value )
{
   SET_OPT_INPUT_PARAMETER(Real);
}
#undef SET_OPT_INPUT_PARAMETER

#define SET_OUTPUT_PARAMETER(paramType) \
   TA_ParamHolderPriv *paramHolderPriv; \
   const TA_OutputParameterInfo *paramInfo; \
\
   if( (param == NULL) || \
       (out == NULL) ) \
      return TA_BAD_PARAM; \
\
   paramHolderPriv = (TA_ParamHolderPriv *)param; \
\
   /* Validate the TA_ParamHolderPriv. */ \
   if( paramHolderPriv->magicNumber != TA_PARAM_HOLDER_PRIV_MAGIC_NB ) \
      return TA_INVALID_PARAM_HOLDER; \
\
   /* Check correct function is used with correct type of parameter. */ \
   if( paramHolderPriv->type != TA_PARAM_HOLDER_OUTPUT ) \
      return TA_INVALID_PARAM_HOLDER_TYPE; \
\
   paramInfo = paramHolderPriv->p.out.outputInfo; \
\
   if( paramInfo->type != TA_Output_##paramType ) \
      return TA_INVALID_PARAM_HOLDER_TYPE; \
\
   paramHolderPriv->p.out.data.out##paramType = out; \
\
   /* Got/validate all the information required for this parameter. */ \
   paramHolderPriv->valueInitialize = 1; \
   return TA_SUCCESS;

/* Setup the parameters indicating where to store the output. */
TA_RetCode TA_SetOutputParamIntegerPtr( TA_ParamHolder *param,
                                        TA_Integer     *out )
{
   SET_OUTPUT_PARAMETER(Integer);
}

TA_RetCode TA_SetOutputParamRealPtr( TA_ParamHolder *param,
                                     TA_Real        *out )
{
   SET_OUTPUT_PARAMETER(Real);
}

TA_RetCode TA_SetOutputParamDrawPtr( TA_ParamHolder *param,
                                     TA_Draw        *out )
{
   SET_OUTPUT_PARAMETER(Draw);
}
#undef SET_OUTPUT_PARAMETER

/* Finally, call a TA function with the parameters. */
TA_RetCode TA_CallFunc( const TA_FuncHandle *handle,
                        TA_Integer startIdx,
                        TA_Integer endIdx,
                        TA_Integer *outBegIdx,
                        TA_Integer *outNbElement,
                        const TA_ParamHolder *inputParams,
                        const TA_ParamHolder *optInputParams,
                        const TA_ParamHolder *outputParams )
{
   TA_PROLOG;
   TA_RetCode retCode;
   TA_ParamHolderPriv *inParamHolderPriv;
   TA_ParamHolderPriv *optInParamHolderPriv;
   TA_ParamHolderPriv *outParamHolderPriv;
   const TA_FuncDef *funcDef;
   const TA_FuncInfo *funcInfo;
   TA_FrameFunction function;
   unsigned int i;
   TA_Libc *libHandle;

   if( (handle == NULL) ||
       (inputParams == NULL)   ||
       (optInputParams == NULL) ||
       (outputParams == NULL) ||
       (outBegIdx == NULL) ||
       (outNbElement == NULL) )
      return TA_BAD_PARAM;

   /* Validate that this is a valid funcHandle. */
   funcDef = (const TA_FuncDef *)handle;
   if( funcDef->magicNumber != TA_FUNC_DEF_MAGIC_NB )
      return TA_INVALID_HANDLE;

   inParamHolderPriv = (TA_ParamHolderPriv *)inputParams;
   optInParamHolderPriv = (TA_ParamHolderPriv *)optInputParams;
   outParamHolderPriv = (TA_ParamHolderPriv *)outputParams;

   libHandle = inParamHolderPriv->libHandle;
   TA_TRACE_BEGIN( libHandle, TA_CallFunc );

   /* Validate the TA_ParamHolderPriv (only the first of each type will
    * be sufficient).
    */
   if( (inParamHolderPriv[0].magicNumber != TA_PARAM_HOLDER_PRIV_MAGIC_NB) ||
       (optInParamHolderPriv[0].magicNumber != TA_PARAM_HOLDER_PRIV_MAGIC_NB) ||
       (outParamHolderPriv[0].magicNumber != TA_PARAM_HOLDER_PRIV_MAGIC_NB) )
   {
      TA_TRACE_RETURN( TA_INVALID_PARAM_HOLDER );
   }

   if( (inParamHolderPriv[0].type != TA_PARAM_HOLDER_INPUT ) ||
       (optInParamHolderPriv[0].type != TA_PARAM_HOLDER_OPTINPUT ) ||
       (outParamHolderPriv[0].type != TA_PARAM_HOLDER_OUTPUT ) )
   {
      TA_TRACE_RETURN( TA_INVALID_PARAM_HOLDER_TYPE );
   }

   function = funcDef->function;
   if( (inParamHolderPriv[0].function != function ) ||
       (optInParamHolderPriv[0].function != function ) ||
       (outParamHolderPriv[0].function != function ) )
   {
      TA_TRACE_RETURN( TA_INVALID_PARAM_FUNCTION );
   }

   TA_DEBUG_ASSERT( libHandle, function != NULL );
   
   /* Check that all parameters are initialize (except the optInput). */
   funcInfo = funcDef->funcInfo;
   for( i=0; i < funcInfo->nbInput; i++ )
   {
      if( !inParamHolderPriv[i].valueInitialize )
      {
         TA_TRACE_RETURN( TA_INPUT_NOT_ALL_INITIALIZE );
      }
   }

   for( i=0; i < funcInfo->nbOutput; i++ )
   {
      if( !outParamHolderPriv[i].valueInitialize )
      {
         TA_TRACE_RETURN( TA_OUTPUT_NOT_ALL_INITIALIZE );
      }
   }

   /* Perform the function call. */
   retCode = (*function)( libHandle,
                          startIdx, endIdx,
                          outBegIdx, outNbElement,
                          inParamHolderPriv,
                          optInParamHolderPriv,
                          outParamHolderPriv );

   TA_TRACE_RETURN( retCode );
}

#if 0
/* Not yet implemented. */
TA_RetCode TA_AnalysisAlloc( const TA_FuncHandle  *handle,
                             const TA_ParamHolder *params,
                             TA_AnalysisBitmap     requestMap,
                             TA_AnalysisBitmap    *validMap,
                             TA_AnalysisBitmap   **newAnalysis );
TA_RetCode TA_AnalysisFree( TA_AnalysisBitmap *analysisToBeFreed );

TA_RetCode TA_AnalysisGetBitmap( const TA_FuncHandle *handle,
                                 TA_AnalysisBitmap   *validMap );

#endif

/**** Local functions definitions.     ****/
#ifdef TA_GEN_CODE
   static TA_RetCode getGroupId( TA_Libc *libHandle,const char *groupString, unsigned int *groupId )
#else
   static TA_RetCode getGroupId( const char *groupString, unsigned int *groupId )
#endif
{
   #ifdef TA_GEN_CODE
   TA_PROLOG;
   #endif

   unsigned int i;

   #ifdef TA_GEN_CODE
      TA_TRACE_BEGIN( libHandle, getgroupId );

      TA_ASSERT( libHandle, groupString != NULL );
      TA_ASSERT( libHandle, groupId != NULL );
   #endif

   for( i=0; i < TA_NB_GROUP_ID; i++ )
   {
      if( strcmp( TA_GroupString[i], groupString ) == 0 )
      {
         *groupId = i;
         #ifdef TA_GEN_CODE
            TA_TRACE_RETURN( TA_SUCCESS );
         #else
            return TA_SUCCESS;
         #endif
      }
   }

   #ifdef TA_GEN_CODE
      TA_TRACE_RETURN( TA_GROUP_NOT_FOUND );
   #else
      return TA_GROUP_NOT_FOUND;
   #endif
}

#ifdef TA_GEN_CODE
   static TA_RetCode getGroupSize( TA_Libc *libHandle, TA_GroupId groupId, unsigned int *groupSize )
#else
   static TA_RetCode getGroupSize( TA_GroupId groupId, unsigned int *groupSize )
#endif
{
   #ifdef TA_GEN_CODE
      /* Code used only when compiled with gen_code. */
      TA_PROLOG;
      unsigned int i, j;
      const TA_FuncDef **funcDefTable;
      const TA_FuncDef *funcDef;
      unsigned int tableSize;
      unsigned int nbFuncFound;

      TA_TRACE_BEGIN( libHandle, getGroupSize );

      TA_ASSERT( libHandle, groupId < TA_NB_GROUP_ID );

      TA_ASSERT( libHandle, groupId < TA_NB_GROUP_ID );
      TA_ASSERT( libHandle, groupSize != NULL );

      nbFuncFound = 0;
      for( i=0; i < 26; i++ )
      {
         funcDefTable = TA_DEF_Tables[i];
         tableSize = *(TA_DEF_TablesSize[i]);

         for( j=0; j < tableSize; j++ )
         {
            funcDef = funcDefTable[j];
            if( funcDef && (funcDef->groupId == groupId) )
               nbFuncFound++;
         }
      }

      *groupSize = nbFuncFound;

      TA_TRACE_RETURN( TA_SUCCESS );
   #else
      /* Optimized code in the final library. */
      *groupSize = TA_PerGroupSize[groupId];

      return TA_SUCCESS;
   #endif
}

#ifdef TA_GEN_CODE
   static TA_RetCode getFuncNameByIdx( TA_Libc *libHandle,
                                       TA_GroupId groupId,
                                       unsigned int idx,
                                       const char **stringPtr )
#else
   static TA_RetCode getFuncNameByIdx( TA_GroupId groupId,
                                       unsigned int idx,
                                       const char **stringPtr )
#endif
{
   #ifdef TA_GEN_CODE
      /* Code used only when compiled with gen_code. */
      TA_PROLOG;
      unsigned int curIdx;
      unsigned int i, j, found;
      const TA_FuncDef **funcDefTable;
      unsigned int tableSize;
      const TA_FuncInfo *funcInfo;

      TA_TRACE_BEGIN( libHandle, getFuncNameByIdx );

      TA_ASSERT( libHandle, stringPtr != NULL );

      curIdx = 0;
      found = 0;
      for( i=0; (i < 26) && !found; i++ )
      {
         funcDefTable = TA_DEF_Tables[i];
         tableSize = *(TA_DEF_TablesSize[i]);

         for( j=0; (j < tableSize) && !found; j++ )
         {
            if( funcDefTable[j]->groupId == groupId )
            {
               if( idx == curIdx )
               {
                  funcInfo = funcDefTable[j]->funcInfo;
                  TA_ASSERT( libHandle, funcInfo != NULL );
                  *stringPtr = funcInfo->name;
                  found = 1;
               }
               curIdx++;
            }
         }
      }

      TA_ASSERT( libHandle, found == 1 );
      TA_ASSERT( libHandle, *stringPtr != NULL );

      TA_TRACE_RETURN( TA_SUCCESS );
   #else
      /* Optimized code in the final library. */
      const TA_FuncDef **funcDefTable;
      const TA_FuncInfo *funcInfo;

      funcDefTable = TA_PerGroupFuncDef[groupId];
      funcInfo = funcDefTable[idx]->funcInfo;
      *stringPtr = funcInfo->name;

      return TA_SUCCESS;
   #endif
}
