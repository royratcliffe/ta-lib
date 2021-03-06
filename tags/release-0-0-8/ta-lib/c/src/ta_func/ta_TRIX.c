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
 *  112400 MF   Template creation.
 *
 */

#include "ta_memory.h"

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
/* All code within this section is automatically
 * generated by gen_code. Any modification will be lost
 * next time gen_code is run.
 */

#ifndef TA_FUNC_H
   #include "ta_func.h"
#endif

#ifndef TA_UTILITY_H
   #include "ta_utility.h"
#endif

int TA_TRIX_Lookback( TA_Integer    optInTimePeriod_0 )  /* From 1 to TA_INTEGER_MAX */

/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert lookback code here. */
   unsigned int emaLookback = TA_EMA_Lookback( optInTimePeriod_0 );
   return (emaLookback*3) + TA_ROCR_Lookback( 1 );
}

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/*
 * TA_TRIX - 1-day Rate-Of-Change (ROC) of a Triple Smooth EMA
 * 
 * Input  = TA_Real
 * Output = TA_Real
 * 
 * Optional Parameters
 * -------------------
 * optInTimePeriod_0:(From 1 to TA_INTEGER_MAX)
 *    Number of period
 * 
 * 
 */

TA_RetCode TA_TRIX( TA_Integer    startIdx,
                    TA_Integer    endIdx,
                    const TA_Real inReal_0[],
                    TA_Integer    optInTimePeriod_0, /* From 1 to TA_INTEGER_MAX */
                    TA_Integer   *outBegIdx,
                    TA_Integer   *outNbElement,
                    TA_Real       outReal_0[] )
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
{
   /* Insert local variables here. */
   TA_Real *tempBuffer, k;
   TA_Integer totalLookback;
   TA_Integer emaLookback, rocLookback;
   TA_Integer nbElement, begIdx;
   TA_RetCode retCode;
   TA_Integer nbElementToOutput;

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

#ifndef TA_FUNC_NO_RANGE_CHECK

   /* Validate the requested output range. */
   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx))
      return TA_OUT_OF_RANGE_END_INDEX;

   /* Validate the parameters. */
   if( !inReal_0 ) return TA_BAD_PARAM;
   /* min/max are checked for optInTimePeriod_0. */
   if( (TA_Integer)optInTimePeriod_0 == TA_INTEGER_DEFAULT )
      optInTimePeriod_0 = 30;
   else if( ((TA_Integer)optInTimePeriod_0 < 1) || ((TA_Integer)optInTimePeriod_0 > 2147483647) )
      return TA_BAD_PARAM;

   if( outReal_0 == NULL )
      return TA_BAD_PARAM;

#endif /* TA_FUNC_NO_RANGE_CHECK */

/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */

   /* Adjust the startIdx to account for the lookback. */
   emaLookback   = TA_EMA_Lookback( optInTimePeriod_0 );
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
   tempBuffer = TA_Malloc( nbElementToOutput * sizeof(TA_Real) );
   if( !tempBuffer )
   {
      *outNbElement = 0;
      *outBegIdx = 0;
      return TA_ALLOC_ERR;
   }

   /* Calculate the first EMA */   
   k = PER_TO_K(optInTimePeriod_0);  
   retCode = TA_INT_EMA( (startIdx-totalLookback), endIdx, inReal_0,
                         optInTimePeriod_0, k,
                         &begIdx, &nbElement, tempBuffer );
   
   /* Verify for failure or if not enough data after
    * calculating the EMA.
    */
   if( (retCode != TA_SUCCESS) || (nbElement == 0) )
   {
      *outNbElement = 0;
      *outBegIdx = 0;
      TA_Free(  tempBuffer );
      return retCode;
   }

   nbElementToOutput--; /* Make this variable zero base from now on. */

   /* Calculate the second EMA */   
   nbElementToOutput -= emaLookback;
   retCode = TA_INT_EMA( 0, nbElementToOutput, tempBuffer,
                         optInTimePeriod_0, k,
                         &begIdx, &nbElement, tempBuffer );
   
   /* Verify for failure or if not enough data after
    * calculating the EMA.
    */
   if( (retCode != TA_SUCCESS) || (nbElement == 0) )
   {
      *outNbElement = 0;
      *outBegIdx = 0;
      TA_Free(  tempBuffer );
      return retCode;
   }

   /* Calculate the third EMA */   
   nbElementToOutput -= emaLookback;
   retCode = TA_INT_EMA( 0, nbElementToOutput, tempBuffer,
                         optInTimePeriod_0, k,
                         &begIdx, &nbElement, tempBuffer );
   
   /* Verify for failure or if not enough data after
    * calculating the EMA.
    */
   if( (retCode != TA_SUCCESS) || (nbElement == 0) )
   {
      *outNbElement = 0;
      *outBegIdx = 0;
      TA_Free(  tempBuffer );
      return retCode;
   }

   /* Calculate the 1-day Rate-Of-Change */
   nbElementToOutput -= emaLookback;
   retCode = TA_ROC( 0, nbElementToOutput,
                      tempBuffer,
                      1,  &begIdx, outNbElement,
                      outReal_0 );

   TA_Free(  tempBuffer );
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

