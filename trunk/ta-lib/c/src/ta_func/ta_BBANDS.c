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

#include <string.h>

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

int TA_BBANDS_Lookback( TA_Integer    optInTimePeriod_0, /* From 1 to TA_INTEGER_MAX */
                        TA_Real       optInNbDevUp_1, /* From TA_REAL_MIN to TA_REAL_MAX */
                        TA_Real       optInNbDevDn_2, /* From TA_REAL_MIN to TA_REAL_MAX */
                        TA_Integer    optInMethod_3,
                        TA_Integer    optInCompatibility_4 ) 
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert lookback code here. */
   (void)optInNbDevUp_1;
   (void)optInNbDevDn_2;

   /* The lookback is driven by the middle band moving average. */
   return TA_MA_Lookback( optInTimePeriod_0,
                          optInMethod_3,
                          optInCompatibility_4 );
}

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/*
 * TA_BBANDS - Bollinger Bands
 * 
 * Input  = TA_Real
 * Output = TA_Real, TA_Real, TA_Real
 * 
 * Optional Parameters
 * -------------------
 * optInTimePeriod_0:(From 1 to TA_INTEGER_MAX)
 *    Number of period
 * 
 * optInNbDevUp_1:(From TA_REAL_MIN to TA_REAL_MAX)
 *    Deviation multiplier for upper band
 * 
 * optInNbDevDn_2:(From TA_REAL_MIN to TA_REAL_MAX)
 *    Deviation multiplier for lower band
 * 
 * optInMethod_3:
 *    Type of Moving Average
 * 
 * optInCompatibility_4:
 *    Make function compatible to some software
 * 
 * 
 */

TA_RetCode TA_BBANDS( TA_Libc      *libHandle,
                      TA_Integer    startIdx,
                      TA_Integer    endIdx,
                      const TA_Real inReal_0[],
                      TA_Integer    optInTimePeriod_0, /* From 1 to TA_INTEGER_MAX */
                      TA_Real       optInNbDevUp_1, /* From TA_REAL_MIN to TA_REAL_MAX */
                      TA_Real       optInNbDevDn_2, /* From TA_REAL_MIN to TA_REAL_MAX */
                      TA_Integer    optInMethod_3,
                      TA_Integer    optInCompatibility_4,
                      TA_Integer   *outBegIdx,
                      TA_Integer   *outNbElement,
                      TA_Real       outRealUpperBand_0[],
                      TA_Real       outRealMiddleBand_1[],
                      TA_Real       outRealLowerBand_2[] )
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
{
   /* Insert local variables here. */
   TA_RetCode retCode;
   int i;
   TA_Real tempReal;
   TA_Real *tempBuffer1, *tempBuffer2;
   register TA_Real tempReal2;

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

   if( optInNbDevUp_1 == TA_REAL_DEFAULT )
      optInNbDevUp_1 = 2.000000e+0;
   else if( (optInNbDevUp_1 < -3.000000e+37) || (optInNbDevUp_1 > 3.000000e+37) )
      return TA_BAD_PARAM;

   if( optInNbDevDn_2 == TA_REAL_DEFAULT )
      optInNbDevDn_2 = 2.000000e+0;
   else if( (optInNbDevDn_2 < -3.000000e+37) || (optInNbDevDn_2 > 3.000000e+37) )
      return TA_BAD_PARAM;

   if( optInMethod_3 == TA_INTEGER_DEFAULT )
      optInMethod_3 = 0;
   else if( (optInMethod_3 < 0) || (optInMethod_3 > 4) )
      return TA_BAD_PARAM;

   if( optInCompatibility_4 == TA_INTEGER_DEFAULT )
      optInCompatibility_4 = 0;
   else if( (optInCompatibility_4 < 0) || (optInCompatibility_4 > 1) )
      return TA_BAD_PARAM;

   if( outRealUpperBand_0 == NULL )
      return TA_BAD_PARAM;

   if( outRealMiddleBand_1 == NULL )
      return TA_BAD_PARAM;

   if( outRealLowerBand_2 == NULL )
      return TA_BAD_PARAM;

#endif /* TA_FUNC_NO_RANGE_CHECK */

/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */

   /* Identify TWO temporary buffer among the outputs.
    *
    * These temporary buffers allows to perform the
    * calculation without any memory allocation.
    *
    * Whenever possible, make the tempBuffer1 be the
    * middle band output. This will save one copy operation.
    */
   if( inReal_0 == outRealUpperBand_0 )
   {
      tempBuffer1 = outRealMiddleBand_1;
      tempBuffer2 = outRealLowerBand_2;
   }
   else if( inReal_0 == outRealLowerBand_2 )
   {
      tempBuffer1 = outRealMiddleBand_1;
      tempBuffer2 = outRealUpperBand_0;
   }
   else if( inReal_0 == outRealMiddleBand_1 )
   {
      tempBuffer1 = outRealLowerBand_2;
      tempBuffer2 = outRealUpperBand_0;
   }
   else
   {
      tempBuffer1 = outRealMiddleBand_1;
      tempBuffer2 = outRealUpperBand_0;
   }

   /* Check that the caller is not doing tricky things. 
    * (like using the input buffer in two output!)
    */
   if( (tempBuffer1 == inReal_0) || (tempBuffer2 == inReal_0) )
      return TA_BAD_PARAM;

   /* Calculate the middle band, which is a moving average.
    * The other two bands will simply add/substract the
    * standard deviation from this middle band.
    */
   retCode = TA_MA( libHandle,
                    startIdx, endIdx,
                    inReal_0,
                    optInTimePeriod_0,
                    optInMethod_3,
                    optInCompatibility_4,
                    outBegIdx, outNbElement, tempBuffer1 );

   if( (retCode != TA_SUCCESS) || (*outNbElement == 0) )
   {
      *outNbElement = 0;
      return retCode;
   }

   /* Calculate the standard deviation into the temporary buffer
    * The result is put in tempBuffer2.
    */
   if( optInCompatibility_4 == TA_BBANDS_CLASSIC )
   {
      /* The classic approach is not always using the true standard
       * variation.
       * - in the case that the MA method is a SMA it will
       *   be a true standard deviation.
       * - in the case that the MA method is not a SMA, the
       *   part which is being a SMA in the variance calculation
       *   is also replaced by the choosen MA method.
       */            
       TA_INT_stddev_using_precalc_ma( inReal_0,
                                       tempBuffer1, *outBegIdx, *outNbElement,
                                       optInTimePeriod_0, tempBuffer2 );
   }
   else
   {
      /* Other implementation (Metastock here) always use the SMA
       * in the variance calculation regardless the MA method
       * choosen for the middle band.
       */
      retCode = TA_STDDEV( libHandle,
                           *outBegIdx, endIdx, inReal_0,
                           optInTimePeriod_0, 1.0,
                           outBegIdx, outNbElement, tempBuffer2 );

      if( retCode != TA_SUCCESS )
      {
         *outNbElement = 0;
         return retCode;
      }
   }

   /* Copy the MA calculation into the middle band ouput, unless
    * the calculation was done into it already!
    */
   if( tempBuffer1 != outRealMiddleBand_1 )
      memcpy( outRealMiddleBand_1, tempBuffer1, sizeof(TA_Real)*(*outNbElement) );
   
   /* Now do a tight loop to calculate the upper/lower band at
    * the same time. 
    *
    * All the following 5 loops are doing the same, except there
    * is an attempt to speed optimize by eliminating uneeded
    * multiplication.
    */
   if( optInNbDevUp_1 == optInNbDevDn_2 )
   {
      if(  optInNbDevUp_1 == 1.0 )
      {
         /* No standard deviation multiplier needed. */
         for( i=0; i < *outNbElement; i++ )
         {
            tempReal  = tempBuffer2[i];
            tempReal2 = outRealMiddleBand_1[i];
            outRealUpperBand_0[i] = tempReal2 + tempReal;
            outRealLowerBand_2[i] = tempReal2 - tempReal;
         }
      }
      else
      {
         /* Upper/lower band use the same standard deviation multiplier. */
         for( i=0; i < *outNbElement; i++ )
         {
            tempReal  = tempBuffer2[i] * optInNbDevUp_1;
            tempReal2 = outRealMiddleBand_1[i];
            outRealUpperBand_0[i] = tempReal2 + tempReal;
            outRealLowerBand_2[i] = tempReal2 - tempReal;
         }
      }
   }
   else if( optInNbDevUp_1 == 1.0 )
   {
      /* Only lower band has a standard deviation multiplier. */
      for( i=0; i < *outNbElement; i++ )
      {
         tempReal  = tempBuffer2[i];
         tempReal2 = outRealMiddleBand_1[i];
         outRealUpperBand_0[i] = tempReal2 + tempReal;
         outRealLowerBand_2[i] = tempReal2 - (tempReal * optInNbDevDn_2);
      }
   }
   else if( optInNbDevDn_2 == 1.0 )
   {
      /* Only upper band has a standard deviation multiplier. */
      for( i=0; i < *outNbElement; i++ )
      {
         tempReal  = tempBuffer2[i];
         tempReal2 = outRealMiddleBand_1[i];
         outRealLowerBand_2[i] = tempReal2 - tempReal;
         outRealUpperBand_0[i] = tempReal2 + (tempReal * optInNbDevUp_1);
      }
   }
   else
   {
      /* Upper/lower band have distinctive standard deviation multiplier. */
      for( i=0; i < *outNbElement; i++ )
      {
         tempReal  = tempBuffer2[i];
         tempReal2 = outRealMiddleBand_1[i];
         outRealUpperBand_0[i] = tempReal2 + (tempReal * optInNbDevUp_1);
         outRealLowerBand_2[i] = tempReal2 - (tempReal * optInNbDevDn_2);
      }
   }
   
   return TA_SUCCESS;
}

