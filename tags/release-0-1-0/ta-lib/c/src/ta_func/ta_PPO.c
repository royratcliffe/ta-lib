/* TA-LIB Copyright (c) 1999-2003, Mario Fortier
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
 *  112400 MF   Template creation.
 *  052603 MF   Adapt code to compile with .NET Managed C++
 *
 */

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
/* All code within this section is automatically
 * generated by gen_code. Any modification will be lost
 * next time gen_code is run.
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */    #using <mscorlib.dll>
/* Generated */    #include "Core.h"
/* Generated */    namespace TA { namespace Lib {
/* Generated */ #else
/* Generated */    #include <string.h>
/* Generated */    #include <math.h>
/* Generated */    #include "ta_func.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_UTILITY_H
/* Generated */    #include "ta_utility.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_MEMORY_H
/* Generated */    #include "ta_memory.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #define TA_PREFIX(x) TA_##x
/* Generated */ #define INPUT_TYPE   double
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ int Core::PPO_Lookback( int           optInFastPeriod_0, /* From 2 to 100000 */
/* Generated */                       int           optInSlowPeriod_1, /* From 2 to 100000 */
/* Generated */                       TA_MAType     optInMAType_2 ) /* Generated */ 
/* Generated */ #else
/* Generated */ int TA_PPO_Lookback( int           optInFastPeriod_0, /* From 2 to 100000 */
/* Generated */                    int           optInSlowPeriod_1, /* From 2 to 100000 */
/* Generated */                    TA_MAType     optInMAType_2 ) /* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert lookback code here. */
   (void)optInFastPeriod_0;

   /* Lookback is driven by the slow MA. */
   return TA_MA_Lookback( optInSlowPeriod_1, optInMAType_2 );
}

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/*
 * TA_PPO - Percentage Price Oscillator
 * 
 * Input  = double
 * Output = double
 * 
 * Optional Parameters
 * -------------------
 * optInFastPeriod_0:(From 2 to 100000)
 *    Number of period for the fast MA
 * 
 * optInSlowPeriod_1:(From 2 to 100000)
 *    Number of period for the slow MA
 * 
 * optInMAType_2:
 *    Type of Moving Average
 * 
 * 
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum Core::TA_RetCode Core::PPO( int    startIdx,
/* Generated */                                  int    endIdx,
/* Generated */                                  double       inReal_0 __gc [],
/* Generated */                                  int           optInFastPeriod_0, /* From 2 to 100000 */
/* Generated */                                  int           optInSlowPeriod_1, /* From 2 to 100000 */
/* Generated */                                  TA_MAType     optInMAType_2,
/* Generated */                                  [OutAttribute]Int32 *outBegIdx,
/* Generated */                                  [OutAttribute]Int32 *outNbElement,
/* Generated */                                  double        outReal_0 __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_PPO( int    startIdx,
/* Generated */                    int    endIdx,
/* Generated */                    const double inReal_0[],
/* Generated */                    int           optInFastPeriod_0, /* From 2 to 100000 */
/* Generated */                    int           optInSlowPeriod_1, /* From 2 to 100000 */
/* Generated */                    TA_MAType     optInMAType_2,
/* Generated */                    int          *outBegIdx,
/* Generated */                    int          *outNbElement,
/* Generated */                    double        outReal_0[] )
/* Generated */ #endif
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
{
   /* Insert local variables here. */
   ARRAY_REF(tempBuffer);
   TA_RetCode retCode;

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    /* Validate the requested output range. */
/* Generated */    if( startIdx < 0 )
/* Generated */       return TA_OUT_OF_RANGE_START_INDEX;
/* Generated */    if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */       return TA_OUT_OF_RANGE_END_INDEX;
/* Generated */ 
/* Generated */    /* Validate the parameters. */
/* Generated */    if( !inReal_0 ) return TA_BAD_PARAM;
/* Generated */    /* min/max are checked for optInFastPeriod_0. */
/* Generated */    if( (int)optInFastPeriod_0 == TA_INTEGER_DEFAULT )
/* Generated */       optInFastPeriod_0 = 12;
/* Generated */    else if( ((int)optInFastPeriod_0 < 2) || ((int)optInFastPeriod_0 > 100000) )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */    /* min/max are checked for optInSlowPeriod_1. */
/* Generated */    if( (int)optInSlowPeriod_1 == TA_INTEGER_DEFAULT )
/* Generated */       optInSlowPeriod_1 = 26;
/* Generated */    else if( ((int)optInSlowPeriod_1 < 2) || ((int)optInSlowPeriod_1 > 100000) )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */    #if !defined(_MANAGED)
/* Generated */    if( (int)optInMAType_2 == TA_INTEGER_DEFAULT )
/* Generated */       optInMAType_2 = 0;
/* Generated */    else if( ((int)optInMAType_2 < 0) || ((int)optInMAType_2 > 8) )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */    #endif /* !defined(_MANAGED) */
/* Generated */    if( outReal_0 == NULL )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */

   /* Allocate an intermediate buffer. */
   ARRAY_ALLOC( tempBuffer, endIdx-startIdx+1 );
   if( !tempBuffer )
      return TA_ALLOC_ERR;

   retCode = TA_PREFIX(INT_PO)( startIdx, endIdx, inReal_0,
                                optInFastPeriod_0, /* From 1 to 200 */
                                optInSlowPeriod_1, /* From 1 to 200 */
                                optInMAType_2,
                                outBegIdx,
                                outNbElement,
                                outReal_0,
                                tempBuffer,
                                1 /* Do percentage processing. */ );

   ARRAY_FREE( tempBuffer );
   
   return TA_SUCCESS;
}

/**** START GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #define  USE_SINGLE_PRECISION_INPUT
/* Generated */ #if !defined( _MANAGED )
/* Generated */    #undef   TA_PREFIX
/* Generated */    #define  TA_PREFIX(x) TA_S_##x
/* Generated */ #endif
/* Generated */ #undef   INPUT_TYPE
/* Generated */ #define  INPUT_TYPE float
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum Core::TA_RetCode Core::PPO( int    startIdx,
/* Generated */                                  int    endIdx,
/* Generated */                                  float        inReal_0 __gc [],
/* Generated */                                  int           optInFastPeriod_0, /* From 2 to 100000 */
/* Generated */                                  int           optInSlowPeriod_1, /* From 2 to 100000 */
/* Generated */                                  TA_MAType     optInMAType_2,
/* Generated */                                  [OutAttribute]Int32 *outBegIdx,
/* Generated */                                  [OutAttribute]Int32 *outNbElement,
/* Generated */                                  double        outReal_0 __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_PPO( int    startIdx,
/* Generated */                      int    endIdx,
/* Generated */                      const float  inReal_0[],
/* Generated */                      int           optInFastPeriod_0, /* From 2 to 100000 */
/* Generated */                      int           optInSlowPeriod_1, /* From 2 to 100000 */
/* Generated */                      TA_MAType     optInMAType_2,
/* Generated */                      int          *outBegIdx,
/* Generated */                      int          *outNbElement,
/* Generated */                      double        outReal_0[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */    ARRAY_REF(tempBuffer);
/* Generated */    TA_RetCode retCode;
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return TA_OUT_OF_RANGE_START_INDEX;
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return TA_OUT_OF_RANGE_END_INDEX;
/* Generated */     if( !inReal_0 ) return TA_BAD_PARAM;
/* Generated */     if( (int)optInFastPeriod_0 == TA_INTEGER_DEFAULT )
/* Generated */        optInFastPeriod_0 = 12;
/* Generated */     else if( ((int)optInFastPeriod_0 < 2) || ((int)optInFastPeriod_0 > 100000) )
/* Generated */        return TA_BAD_PARAM;
/* Generated */     if( (int)optInSlowPeriod_1 == TA_INTEGER_DEFAULT )
/* Generated */        optInSlowPeriod_1 = 26;
/* Generated */     else if( ((int)optInSlowPeriod_1 < 2) || ((int)optInSlowPeriod_1 > 100000) )
/* Generated */        return TA_BAD_PARAM;
/* Generated */     #if !defined(_MANAGED)
/* Generated */     if( (int)optInMAType_2 == TA_INTEGER_DEFAULT )
/* Generated */        optInMAType_2 = 0;
/* Generated */     else if( ((int)optInMAType_2 < 0) || ((int)optInMAType_2 > 8) )
/* Generated */        return TA_BAD_PARAM;
/* Generated */     #endif 
/* Generated */     if( outReal_0 == NULL )
/* Generated */        return TA_BAD_PARAM;
/* Generated */  #endif 
/* Generated */    ARRAY_ALLOC( tempBuffer, endIdx-startIdx+1 );
/* Generated */    if( !tempBuffer )
/* Generated */       return TA_ALLOC_ERR;
/* Generated */    retCode = TA_PREFIX(INT_PO)( startIdx, endIdx, inReal_0,
/* Generated */                                 optInFastPeriod_0, 
/* Generated */                                 optInSlowPeriod_1, 
/* Generated */                                 optInMAType_2,
/* Generated */                                 outBegIdx,
/* Generated */                                 outNbElement,
/* Generated */                                 outReal_0,
/* Generated */                                 tempBuffer,
/* Generated */                                 1  );
/* Generated */    ARRAY_FREE( tempBuffer );
/* Generated */    return TA_SUCCESS;
/* Generated */ }
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }} // Close namespace TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/
