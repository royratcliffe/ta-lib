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
 *  AM       Adrian Michel <michel@pacbell.net>
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  120802 MF   Template creation.
 *  052603 MF   Adapt code to compile with .NET Managed C++
 *  050703 MF   Fix algorithm base on Adrian Michel bug report #748163
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
/* Generated */ int Core::AROON_Lookback( int           optInTimePeriod_0 )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #else
/* Generated */ int TA_AROON_Lookback( int           optInTimePeriod_0 )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert lookback code here. */
   return optInTimePeriod_0;
}

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/*
 * TA_AROON - Aroon
 * 
 * Input  = High, Low
 * Output = double, double
 * 
 * Optional Parameters
 * -------------------
 * optInTimePeriod_0:(From 2 to 100000)
 *    Number of period
 * 
 * 
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum Core::TA_RetCode Core::AROON( int    startIdx,
/* Generated */                                    int    endIdx,
/* Generated */                                    double       inHigh_0 __gc [],
/* Generated */                                    double       inLow_0 __gc [],
/* Generated */                                    int           optInTimePeriod_0, /* From 2 to 100000 */
/* Generated */                                    [OutAttribute]Int32 *outBegIdx,
/* Generated */                                    [OutAttribute]Int32 *outNbElement,
/* Generated */                                    double        outAroonDown_0 __gc [],
/* Generated */                                    double        outAroonUp_1 __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_AROON( int    startIdx,
/* Generated */                      int    endIdx,
/* Generated */                      const double inHigh_0[],
/* Generated */                      const double inLow_0[],
/* Generated */                      int           optInTimePeriod_0, /* From 2 to 100000 */
/* Generated */                      int          *outBegIdx,
/* Generated */                      int          *outNbElement,
/* Generated */                      double        outAroonDown_0[],
/* Generated */                      double        outAroonUp_1[] )
/* Generated */ #endif
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
{
	/* insert local variable here */
   double lowest, highest, tmp, factor;
   int outIdx;
   int trailingIdx, lowestIdx, highestIdx, today, i;

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
/* Generated */    /* Verify required price component. */
/* Generated */    if(!inHigh_0||!inLow_0)
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */    /* min/max are checked for optInTimePeriod_0. */
/* Generated */    if( (int)optInTimePeriod_0 == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod_0 = 14;
/* Generated */    else if( ((int)optInTimePeriod_0 < 2) || ((int)optInTimePeriod_0 > 100000) )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */    if( outAroonDown_0 == NULL )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */    if( outAroonUp_1 == NULL )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */

   /* This function is using a speed optimized algorithm
    * for the min/max logic.
    *
    * You might want to first look at how TA_MIN/TA_MAX works
    * and this function will become easier to understand.
    */

   /* Move up the start index if there is not
    * enough initial data.
    */
   if( startIdx < optInTimePeriod_0 )
      startIdx = optInTimePeriod_0;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
   {
      *outBegIdx    = 0;
      *outNbElement = 0;
      return TA_SUCCESS;
   }

   /* Proceed with the calculation for the requested range.
    * Note that this algorithm allows the input and
    * output to be the same buffer.
    */
   outIdx = 0;
   today       = startIdx;
   trailingIdx = startIdx-optInTimePeriod_0;
   lowestIdx   = -1;
   highestIdx  = -1;
   lowest      = 0.0;
   highest     = 0.0;
   factor      = (double)100.0/(double)optInTimePeriod_0;
   
   while( today <= endIdx )
   {
      /* Keep track of the lowestIdx */
      tmp = inLow_0[today];
      if( lowestIdx < trailingIdx )
      {
        lowestIdx = trailingIdx;
        lowest = inLow_0[lowestIdx];
        i = lowestIdx;
        while( ++i<=today )
        {
           tmp = inLow_0[i];
           if( tmp <= lowest )
           {
              lowestIdx = i;
              lowest = tmp;
           }
        }
      }
      else if( tmp <= lowest )
      {
        lowestIdx = today;
        lowest    = tmp;
      }

      /* Keep track of the highestIdx */
      tmp = inHigh_0[today];
      if( highestIdx < trailingIdx )
      {
        highestIdx = trailingIdx;
        highest = inHigh_0[highestIdx];
        i = highestIdx;
        while( ++i<=today )
        {
           tmp = inHigh_0[i];
           if( tmp >= highest )
           {
              highestIdx = i;
              highest = tmp;
           }
        }
      }
      else if( tmp >= highest )
      {
        highestIdx = today;
        highest = tmp;
      }

      /* Note: Do not forget that input and output buffer can be the same,
       *       so writing to the output is the last thing being done here.
       */
      outAroonUp_1[outIdx] = factor*(optInTimePeriod_0-(today-highestIdx));
      outAroonDown_0[outIdx] = factor*(optInTimePeriod_0-(today-lowestIdx));

      outIdx++;
      trailingIdx++;
      today++;  
   }

   /* Keep the outBegIdx relative to the
    * caller input before returning.
    */
   *outBegIdx    = startIdx;
   *outNbElement = outIdx;

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
/* Generated */ enum Core::TA_RetCode Core::AROON( int    startIdx,
/* Generated */                                    int    endIdx,
/* Generated */                                    float        inHigh_0 __gc [],
/* Generated */                                    float        inLow_0 __gc [],
/* Generated */                                    int           optInTimePeriod_0, /* From 2 to 100000 */
/* Generated */                                    [OutAttribute]Int32 *outBegIdx,
/* Generated */                                    [OutAttribute]Int32 *outNbElement,
/* Generated */                                    double        outAroonDown_0 __gc [],
/* Generated */                                    double        outAroonUp_1 __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_AROON( int    startIdx,
/* Generated */                        int    endIdx,
/* Generated */                        const float  inHigh_0[],
/* Generated */                        const float  inLow_0[],
/* Generated */                        int           optInTimePeriod_0, /* From 2 to 100000 */
/* Generated */                        int          *outBegIdx,
/* Generated */                        int          *outNbElement,
/* Generated */                        double        outAroonDown_0[],
/* Generated */                        double        outAroonUp_1[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */    double lowest, highest, tmp, factor;
/* Generated */    int outIdx;
/* Generated */    int trailingIdx, lowestIdx, highestIdx, today, i;
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return TA_OUT_OF_RANGE_START_INDEX;
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return TA_OUT_OF_RANGE_END_INDEX;
/* Generated */     if(!inHigh_0||!inLow_0)
/* Generated */        return TA_BAD_PARAM;
/* Generated */     if( (int)optInTimePeriod_0 == TA_INTEGER_DEFAULT )
/* Generated */        optInTimePeriod_0 = 14;
/* Generated */     else if( ((int)optInTimePeriod_0 < 2) || ((int)optInTimePeriod_0 > 100000) )
/* Generated */        return TA_BAD_PARAM;
/* Generated */     if( outAroonDown_0 == NULL )
/* Generated */        return TA_BAD_PARAM;
/* Generated */     if( outAroonUp_1 == NULL )
/* Generated */        return TA_BAD_PARAM;
/* Generated */  #endif 
/* Generated */    if( startIdx < optInTimePeriod_0 )
/* Generated */       startIdx = optInTimePeriod_0;
/* Generated */    if( startIdx > endIdx )
/* Generated */    {
/* Generated */       *outBegIdx    = 0;
/* Generated */       *outNbElement = 0;
/* Generated */       return TA_SUCCESS;
/* Generated */    }
/* Generated */    outIdx = 0;
/* Generated */    today       = startIdx;
/* Generated */    trailingIdx = startIdx-optInTimePeriod_0;
/* Generated */    lowestIdx   = -1;
/* Generated */    highestIdx  = -1;
/* Generated */    lowest      = 0.0;
/* Generated */    highest     = 0.0;
/* Generated */    factor      = (double)100.0/(double)optInTimePeriod_0;
/* Generated */    while( today <= endIdx )
/* Generated */    {
/* Generated */       tmp = inLow_0[today];
/* Generated */       if( lowestIdx < trailingIdx )
/* Generated */       {
/* Generated */         lowestIdx = trailingIdx;
/* Generated */         lowest = inLow_0[lowestIdx];
/* Generated */         i = lowestIdx;
/* Generated */         while( ++i<=today )
/* Generated */         {
/* Generated */            tmp = inLow_0[i];
/* Generated */            if( tmp <= lowest )
/* Generated */            {
/* Generated */               lowestIdx = i;
/* Generated */               lowest = tmp;
/* Generated */            }
/* Generated */         }
/* Generated */       }
/* Generated */       else if( tmp <= lowest )
/* Generated */       {
/* Generated */         lowestIdx = today;
/* Generated */         lowest    = tmp;
/* Generated */       }
/* Generated */       tmp = inHigh_0[today];
/* Generated */       if( highestIdx < trailingIdx )
/* Generated */       {
/* Generated */         highestIdx = trailingIdx;
/* Generated */         highest = inHigh_0[highestIdx];
/* Generated */         i = highestIdx;
/* Generated */         while( ++i<=today )
/* Generated */         {
/* Generated */            tmp = inHigh_0[i];
/* Generated */            if( tmp >= highest )
/* Generated */            {
/* Generated */               highestIdx = i;
/* Generated */               highest = tmp;
/* Generated */            }
/* Generated */         }
/* Generated */       }
/* Generated */       else if( tmp >= highest )
/* Generated */       {
/* Generated */         highestIdx = today;
/* Generated */         highest = tmp;
/* Generated */       }
/* Generated */       outAroonUp_1[outIdx] = factor*(optInTimePeriod_0-(today-highestIdx));
/* Generated */       outAroonDown_0[outIdx] = factor*(optInTimePeriod_0-(today-lowestIdx));
/* Generated */       outIdx++;
/* Generated */       trailingIdx++;
/* Generated */       today++;  
/* Generated */    }
/* Generated */    *outBegIdx    = startIdx;
/* Generated */    *outNbElement = outIdx;
/* Generated */    return TA_SUCCESS;
/* Generated */ }
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }} // Close namespace TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/

