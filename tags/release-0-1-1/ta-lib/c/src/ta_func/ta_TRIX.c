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
/* Generated */    #define TA_INTERNAL_ERROR(Id) (TA_INTERNAL_ERROR)
/* Generated */    namespace TA { namespace Lib {
/* Generated */ #else
/* Generated */    #include <string.h>
/* Generated */    #include <math.h>
/* Generated */    #include "ta_func.h"
/* Generated */    #include "ta_trace.h"
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
/* Generated */ int Core::TRIX_Lookback( int           optInTimePeriod )  /* From 1 to 100000 */
/* Generated */ 
/* Generated */ #else
/* Generated */ int TA_TRIX_Lookback( int           optInTimePeriod )  /* From 1 to 100000 */
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert lookback code here. */
   unsigned int emaLookback = TA_EMA_Lookback( optInTimePeriod );
   return (emaLookback*3) + TA_ROCR_Lookback( 1 );
}

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/*
 * TA_TRIX - 1-day Rate-Of-Change (ROC) of a Triple Smooth EMA
 * 
 * Input  = double
 * Output = double
 * 
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 1 to 100000)
 *    Number of period
 * 
 * 
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum Core::TA_RetCode Core::TRIX( int    startIdx,
/* Generated */                                   int    endIdx,
/* Generated */                                   double       inReal __gc [],
/* Generated */                                   int           optInTimePeriod, /* From 1 to 100000 */
/* Generated */                                   [OutAttribute]Int32 *outBegIdx,
/* Generated */                                   [OutAttribute]Int32 *outNbElement,
/* Generated */                                   double        outReal __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_TRIX( int    startIdx,
/* Generated */                     int    endIdx,
/* Generated */                     const double inReal[],
/* Generated */                     int           optInTimePeriod, /* From 1 to 100000 */
/* Generated */                     int          *outBegIdx,
/* Generated */                     int          *outNbElement,
/* Generated */                     double        outReal[] )
/* Generated */ #endif
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
{
   /* Insert local variables here. */
   double k;
   ARRAY_REF(tempBuffer);
   int totalLookback;
   int emaLookback, rocLookback;
   int nbElement, begIdx;
   TA_RetCode retCode;
   int nbElementToOutput;

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
/* Generated */    if( !inReal ) return TA_BAD_PARAM;
/* Generated */    /* min/max are checked for optInTimePeriod. */
/* Generated */    if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod = 30;
/* Generated */    else if( ((int)optInTimePeriod < 1) || ((int)optInTimePeriod > 100000) )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */    if( outReal == NULL )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */

   /* Adjust the startIdx to account for the lookback. */
   emaLookback   = TA_EMA_Lookback( optInTimePeriod );
   rocLookback   = TA_ROCR_Lookback( 1 );
   totalLookback = (emaLookback*3) + rocLookback;

   if( startIdx < totalLookback )
      startIdx = totalLookback;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
   {
      *outNbElement = 0;
      *outBegIdx = 0;
      return TA_SUCCESS; 
   }

   *outBegIdx = startIdx; 

   nbElementToOutput = (endIdx-startIdx)+1+totalLookback;

   /* Allocate a temporary buffer for performing
    * the calculation.
    */
   ARRAY_ALLOC(tempBuffer, nbElementToOutput );
   if( !tempBuffer )
   {
      *outNbElement = 0;
      *outBegIdx = 0;
      return TA_ALLOC_ERR;
   }

   /* Calculate the first EMA */   
   k = PER_TO_K(optInTimePeriod);  
   retCode = TA_PREFIX(INT_EMA)( (startIdx-totalLookback), endIdx, inReal,
                                 optInTimePeriod, k,
                                 &begIdx, &nbElement, tempBuffer );
   
   /* Verify for failure or if not enough data after
    * calculating the EMA.
    */
   if( (retCode != TA_SUCCESS) || (nbElement == 0) )
   {
      *outNbElement = 0;
      *outBegIdx = 0;
      ARRAY_FREE( tempBuffer );
      return retCode;
   }

   nbElementToOutput--; /* Make this variable zero base from now on. */

   /* Calculate the second EMA */   
   nbElementToOutput -= emaLookback;
   retCode = TA_INT_EMA( 0, nbElementToOutput, tempBuffer,
                         optInTimePeriod, k,
                         &begIdx, &nbElement, tempBuffer );
   
   /* Verify for failure or if not enough data after
    * calculating the EMA.
    */
   if( (retCode != TA_SUCCESS) || (nbElement == 0) )
   {
      *outNbElement = 0;
      *outBegIdx = 0;
      ARRAY_FREE( tempBuffer );
      return retCode;
   }

   /* Calculate the third EMA */   
   nbElementToOutput -= emaLookback;
   retCode = TA_INT_EMA( 0, nbElementToOutput, tempBuffer,
                         optInTimePeriod, k,
                         &begIdx, &nbElement, tempBuffer );
   
   /* Verify for failure or if not enough data after
    * calculating the EMA.
    */
   if( (retCode != TA_SUCCESS) || (nbElement == 0) )
   {
      *outNbElement = 0;
      *outBegIdx = 0;
      ARRAY_FREE( tempBuffer );
      return retCode;
   }

   /* Calculate the 1-day Rate-Of-Change */
   nbElementToOutput -= emaLookback;
   retCode = TA_ROC( 0, nbElementToOutput,
                      tempBuffer,
                      1,  &begIdx, outNbElement,
                      outReal );

   ARRAY_FREE( tempBuffer );
   /* Verify for failure or if not enough data after
    * calculating the rate-of-change.
    */
   if( (retCode != TA_SUCCESS) || (outNbElement == 0) )
   {
      *outNbElement = 0;
      *outBegIdx = 0;
      return retCode;
   }

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
/* Generated */ enum Core::TA_RetCode Core::TRIX( int    startIdx,
/* Generated */                                   int    endIdx,
/* Generated */                                   float        inReal __gc [],
/* Generated */                                   int           optInTimePeriod, /* From 1 to 100000 */
/* Generated */                                   [OutAttribute]Int32 *outBegIdx,
/* Generated */                                   [OutAttribute]Int32 *outNbElement,
/* Generated */                                   double        outReal __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_TRIX( int    startIdx,
/* Generated */                       int    endIdx,
/* Generated */                       const float  inReal[],
/* Generated */                       int           optInTimePeriod, /* From 1 to 100000 */
/* Generated */                       int          *outBegIdx,
/* Generated */                       int          *outNbElement,
/* Generated */                       double        outReal[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */    double k;
/* Generated */    ARRAY_REF(tempBuffer);
/* Generated */    int totalLookback;
/* Generated */    int emaLookback, rocLookback;
/* Generated */    int nbElement, begIdx;
/* Generated */    TA_RetCode retCode;
/* Generated */    int nbElementToOutput;
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return TA_OUT_OF_RANGE_START_INDEX;
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return TA_OUT_OF_RANGE_END_INDEX;
/* Generated */     if( !inReal ) return TA_BAD_PARAM;
/* Generated */     if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */        optInTimePeriod = 30;
/* Generated */     else if( ((int)optInTimePeriod < 1) || ((int)optInTimePeriod > 100000) )
/* Generated */        return TA_BAD_PARAM;
/* Generated */     if( outReal == NULL )
/* Generated */        return TA_BAD_PARAM;
/* Generated */  #endif 
/* Generated */    emaLookback   = TA_EMA_Lookback( optInTimePeriod );
/* Generated */    rocLookback   = TA_ROCR_Lookback( 1 );
/* Generated */    totalLookback = (emaLookback*3) + rocLookback;
/* Generated */    if( startIdx < totalLookback )
/* Generated */       startIdx = totalLookback;
/* Generated */    if( startIdx > endIdx )
/* Generated */    {
/* Generated */       *outNbElement = 0;
/* Generated */       *outBegIdx = 0;
/* Generated */       return TA_SUCCESS; 
/* Generated */    }
/* Generated */    *outBegIdx = startIdx; 
/* Generated */    nbElementToOutput = (endIdx-startIdx)+1+totalLookback;
/* Generated */    ARRAY_ALLOC(tempBuffer, nbElementToOutput );
/* Generated */    if( !tempBuffer )
/* Generated */    {
/* Generated */       *outNbElement = 0;
/* Generated */       *outBegIdx = 0;
/* Generated */       return TA_ALLOC_ERR;
/* Generated */    }
/* Generated */    k = PER_TO_K(optInTimePeriod);  
/* Generated */    retCode = TA_PREFIX(INT_EMA)( (startIdx-totalLookback), endIdx, inReal,
/* Generated */                                  optInTimePeriod, k,
/* Generated */                                  &begIdx, &nbElement, tempBuffer );
/* Generated */    if( (retCode != TA_SUCCESS) || (nbElement == 0) )
/* Generated */    {
/* Generated */       *outNbElement = 0;
/* Generated */       *outBegIdx = 0;
/* Generated */       ARRAY_FREE( tempBuffer );
/* Generated */       return retCode;
/* Generated */    }
/* Generated */    nbElementToOutput--; 
/* Generated */    nbElementToOutput -= emaLookback;
/* Generated */    retCode = TA_INT_EMA( 0, nbElementToOutput, tempBuffer,
/* Generated */                          optInTimePeriod, k,
/* Generated */                          &begIdx, &nbElement, tempBuffer );
/* Generated */    if( (retCode != TA_SUCCESS) || (nbElement == 0) )
/* Generated */    {
/* Generated */       *outNbElement = 0;
/* Generated */       *outBegIdx = 0;
/* Generated */       ARRAY_FREE( tempBuffer );
/* Generated */       return retCode;
/* Generated */    }
/* Generated */    nbElementToOutput -= emaLookback;
/* Generated */    retCode = TA_INT_EMA( 0, nbElementToOutput, tempBuffer,
/* Generated */                          optInTimePeriod, k,
/* Generated */                          &begIdx, &nbElement, tempBuffer );
/* Generated */    if( (retCode != TA_SUCCESS) || (nbElement == 0) )
/* Generated */    {
/* Generated */       *outNbElement = 0;
/* Generated */       *outBegIdx = 0;
/* Generated */       ARRAY_FREE( tempBuffer );
/* Generated */       return retCode;
/* Generated */    }
/* Generated */    nbElementToOutput -= emaLookback;
/* Generated */    retCode = TA_ROC( 0, nbElementToOutput,
/* Generated */                       tempBuffer,
/* Generated */                       1,  &begIdx, outNbElement,
/* Generated */                       outReal );
/* Generated */    ARRAY_FREE( tempBuffer );
/* Generated */    if( (retCode != TA_SUCCESS) || (outNbElement == 0) )
/* Generated */    {
/* Generated */       *outNbElement = 0;
/* Generated */       *outBegIdx = 0;
/* Generated */       return retCode;
/* Generated */    }
/* Generated */    return TA_SUCCESS;
/* Generated */ }
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }} // Close namespace TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/

