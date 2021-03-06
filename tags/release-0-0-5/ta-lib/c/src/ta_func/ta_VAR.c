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

int TA_VAR_Lookback( TA_Integer    optInTimePeriod_0, /* From 1 to TA_INTEGER_MAX */
                     TA_Real       optInNbDev_1 )  /* From TA_REAL_MIN to TA_REAL_MAX */

/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert lookback code here. */
   (void)optInNbDev_1;

   return optInTimePeriod_0-1;
}

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/*
 * TA_VAR - Variance
 * 
 * Input  = TA_Real
 * Output = TA_Real
 * 
 * Optional Parameters
 * -------------------
 * optInTimePeriod_0:(From 1 to TA_INTEGER_MAX)
 *    Number of period
 * 
 * optInNbDev_1:(From TA_REAL_MIN to TA_REAL_MAX)
 *    Nb of deviations
 * 
 * 
 */

TA_RetCode TA_VAR( TA_Libc      *libHandle,
                   TA_Integer    startIdx,
                   TA_Integer    endIdx,
                   const TA_Real inReal_0[],
                   TA_Integer    optInTimePeriod_0, /* From 1 to TA_INTEGER_MAX */
                   TA_Real       optInNbDev_1, /* From TA_REAL_MIN to TA_REAL_MAX */
                   TA_Integer   *outBegIdx,
                   TA_Integer   *outNbElement,
                   TA_Real       outReal_0[] )
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
{
   /* Insert local variables here. */

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   (void)libHandle; /* Get ride of warning if unused. */

#ifndef TA_FUNC_NO_RANGE_CHECK

   /* Validate the requested output range. */
   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx))
      return TA_OUT_OF_RANGE_END_INDEX;

   /* Validate the parameters. */
   if( !inReal_0 ) return TA_BAD_PARAM;
   /* min/max are checked for optInTimePeriod_0. */
   if( optInTimePeriod_0 == TA_INTEGER_DEFAULT )
      optInTimePeriod_0 = 5;
   else if( (optInTimePeriod_0 < 1) || (optInTimePeriod_0 > 2147483647) )
      return TA_BAD_PARAM;

   if( optInNbDev_1 == TA_REAL_DEFAULT )
      optInNbDev_1 = 1.000000e+0;
   else if( (optInNbDev_1 < -3.000000e+37) || (optInNbDev_1 > 3.000000e+37) )
      return TA_BAD_PARAM;

   if( outReal_0 == NULL )
      return TA_BAD_PARAM;

#endif /* TA_FUNC_NO_RANGE_CHECK */

/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */
   return TA_INT_VAR( startIdx,
                      endIdx,
                      inReal_0,
                      optInTimePeriod_0, /* From 1 to TA_INTEGER_MAX */                      
                      outBegIdx,
                      outNbElement,
                      outReal_0 );
}

TA_RetCode TA_INT_VAR( TA_Integer    startIdx,
                       TA_Integer    endIdx,
                       const TA_Real *inReal_0,
                       TA_Integer    optInTimePeriod_0, /* From 1 to TA_INTEGER_MAX */                       
                       TA_Integer   *outBegIdx,
                       TA_Integer   *outNbElement,
                       TA_Real      *outReal_0 )
{
   TA_Real periodTotal, tempReal, meanValue, devSum;
   int i, j, outIdx, trailingIdx, nbInitialElementNeeded;

   /* Validate the calculation method type and
    * identify the minimum number of price bar needed
    * to calculate at least one output.
    */
   nbInitialElementNeeded = (optInTimePeriod_0-1);

   /* Move up the start index if there is not
    * enough initial data.
    */
   if( startIdx < nbInitialElementNeeded )
      startIdx = nbInitialElementNeeded;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
   {
      *outBegIdx    = 0;
      *outNbElement = 0;
      return TA_SUCCESS;
   }

   /* Do the MA calculation using tight loops. */
   /* Add-up the initial period, except for the last value. */
   periodTotal = 0;
   trailingIdx = startIdx-nbInitialElementNeeded;
   
   i=trailingIdx;
   if( optInTimePeriod_0 > 1 )
   {
      while( i < startIdx )
         periodTotal += inReal_0[i++];
   }

   /* Proceed with the calculation for the requested range.
    * Note that this algorithm allows the inReal_0 and
    * outReal_0 to be the same buffer.
    */
   outIdx = 0;
   do
   {
      periodTotal += inReal_0[i++];
      tempReal = periodTotal;
      periodTotal -= inReal_0[trailingIdx++];
      meanValue = tempReal / optInTimePeriod_0;

      /* Square and add all the deviation over
       * the same period.
       */
      devSum = 0;
      for( j=i-optInTimePeriod_0; j < i; j++ )
      {
         tempReal  = inReal_0[j]-meanValue;
         tempReal *= tempReal;
         devSum   += tempReal;
      }

      /* Dividing the sum of deviation by the period
       * gives the variance.
       */
      outReal_0[outIdx++] = devSum / optInTimePeriod_0;
   } while( i <= endIdx );

   /* All done. Indicate the output limits and return. */
   *outNbElement = outIdx;
   *outBegIdx    = startIdx;

   return TA_SUCCESS;
}


