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
 *  EKO      echo999@ifrance.com
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  010802 MF   Template creation.
 *  051103 EKO  Found bug and fix related to outFastD.
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
/* Generated */    #include "TA-Lib-Core.h"
/* Generated */    #define TA_INTERNAL_ERROR(Id) (NAMESPACE(TA_RetCode)TA_INTERNAL_ERROR)
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
/* Generated */ int Core::STOCHF_Lookback( int           optInFastK_Period, /* From 1 to 100000 */
/* Generated */                          int           optInFastD_Period, /* From 1 to 100000 */
/* Generated */                          TA_MAType     optInFastD_MAType ) /* Generated */ 
/* Generated */ #else
/* Generated */ int TA_STOCHF_Lookback( int           optInFastK_Period, /* From 1 to 100000 */
/* Generated */                       int           optInFastD_Period, /* From 1 to 100000 */
/* Generated */                       TA_MAType     optInFastD_MAType ) /* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert lookback code here. */
   int retValue;
   
   /* Account for the initial data needed for Fast-K. */
   retValue = (optInFastK_Period - 1);
         
   /* Add the smoothing being done for Fast-D */
   retValue += TA_MA_Lookback( optInFastD_Period, optInFastD_MAType );

   return retValue;
}

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/*
 * TA_STOCHF - Stochastic Fast
 * 
 * Input  = High, Low, Close
 * Output = double, double
 * 
 * Optional Parameters
 * -------------------
 * optInFastK_Period:(From 1 to 100000)
 *    Time period for building the Fast-K line
 * 
 * optInFastD_Period:(From 1 to 100000)
 *    Smoothing for making the Fast-D line. Usually set to 3
 * 
 * optInFastD_MAType:
 *    Type of Moving Average for Fast-D
 * 
 * 
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum class Core::TA_RetCode Core::STOCHF( int    startIdx,
/* Generated */                                           int    endIdx,
/* Generated */                                           cli::array<double>^ inHigh,
/* Generated */                                           cli::array<double>^ inLow,
/* Generated */                                           cli::array<double>^ inClose,
/* Generated */                                           int           optInFastK_Period, /* From 1 to 100000 */
/* Generated */                                           int           optInFastD_Period, /* From 1 to 100000 */
/* Generated */                                           TA_MAType     optInFastD_MAType,
/* Generated */                                           [OutAttribute]int^ outBegIdx,
/* Generated */                                           [OutAttribute]int^ outNbElement,
/* Generated */                                           cli::array<double>^  outFastK,
/* Generated */                                           cli::array<double>^  outFastD )
/* Generated */ #else
/* Generated */ TA_RetCode TA_STOCHF( int    startIdx,
/* Generated */                       int    endIdx,
/* Generated */                       const double inHigh[],
/* Generated */                       const double inLow[],
/* Generated */                       const double inClose[],
/* Generated */                       int           optInFastK_Period, /* From 1 to 100000 */
/* Generated */                       int           optInFastD_Period, /* From 1 to 100000 */
/* Generated */                       TA_MAType     optInFastD_MAType,
/* Generated */                       int          *outBegIdx,
/* Generated */                       int          *outNbElement,
/* Generated */                       double        outFastK[],
/* Generated */                       double        outFastD[] )
/* Generated */ #endif
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
{
	/* insert local variable here */
   TA_RetCode retCode;
   double lowest, highest, tmp, diff;
   ARRAY_REF( tempBuffer );
   int outIdx, lowestIdx, highestIdx;
   int lookbackTotal, lookbackK, lookbackFastD;
   int trailingIdx, today, i;

   #if !defined( _MANAGED ) && !defined(USE_SINGLE_PRECISION_INPUT)
   int bufferIsAllocated;
   #endif

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    /* Validate the requested output range. */
/* Generated */    if( startIdx < 0 )
/* Generated */       return NAMESPACE(TA_RetCode)TA_OUT_OF_RANGE_START_INDEX;
/* Generated */    if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */       return NAMESPACE(TA_RetCode)TA_OUT_OF_RANGE_END_INDEX;
/* Generated */ 
/* Generated */    /* Validate the parameters. */
/* Generated */    /* Verify required price component. */
/* Generated */    if(!inHigh||!inLow||!inClose)
/* Generated */       return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */ 
/* Generated */    /* min/max are checked for optInFastK_Period. */
/* Generated */    if( (int)optInFastK_Period == TA_INTEGER_DEFAULT )
/* Generated */       optInFastK_Period = 5;
/* Generated */    else if( ((int)optInFastK_Period < 1) || ((int)optInFastK_Period > 100000) )
/* Generated */       return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */ 
/* Generated */    /* min/max are checked for optInFastD_Period. */
/* Generated */    if( (int)optInFastD_Period == TA_INTEGER_DEFAULT )
/* Generated */       optInFastD_Period = 3;
/* Generated */    else if( ((int)optInFastD_Period < 1) || ((int)optInFastD_Period > 100000) )
/* Generated */       return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */ 
/* Generated */    #if !defined(_MANAGED)
/* Generated */    if( (int)optInFastD_MAType == TA_INTEGER_DEFAULT )
/* Generated */       optInFastD_MAType = 0;
/* Generated */    else if( ((int)optInFastD_MAType < 0) || ((int)optInFastD_MAType > 8) )
/* Generated */       return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */ 
/* Generated */    #endif /* !defined(_MANAGED) */
/* Generated */    if( !outFastK )
/* Generated */       return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */ 
/* Generated */    if( !outFastD )
/* Generated */       return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */

   /* With stochastic, there is a total of 4 different lines that
    * are defined: FASTK, FASTD, SLOWK and SLOWD.
    *
    * The D is the signal line usually drawn over its
    * corresponding K function.
    *
    *                    (Today's Close - LowestLow)
    *  FASTK(Kperiod) =  --------------------------- * 100
    *                     (HighestHigh - LowestLow)
    *   
    *  FASTD(FastDperiod, MA type) = MA Smoothed FASTK over FastDperiod
    * 
    *  SLOWK(SlowKperiod, MA type) = MA Smoothed FASTK over SlowKperiod
    *
    *  SLOWD(SlowDperiod, MA Type) = MA Smoothed SLOWK over SlowDperiod
    *
    * The HighestHigh and LowestLow are the extreme values among the
    * last 'Kperiod'.
    *  
    * SLOWK and FASTD are equivalent when using the same period.
    *
    * The following shows how these four lines are made available in TA-LIB:
    *
    *  TA_STOCH  : Returns the SLOWK and SLOWD
    *  TA_STOCHF : Returns the FASTK and FASTD
    *
    * The TA_STOCH function correspond to the more widely implemented version
    * found in many software/charting package. The TA_STOCHF is more rarely
    * used because its higher volatility cause often whipsaws.
    */

   /* Identify the lookback needed. */
   lookbackK      = optInFastK_Period-1;
   lookbackFastD  = TA_MA_Lookback( optInFastD_Period, optInFastD_MAType );
   lookbackTotal  = lookbackK + lookbackFastD;

   /* Move up the start index if there is not
    * enough initial data.
    */
   if( startIdx < lookbackTotal )
      startIdx = lookbackTotal;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
   {
      /* Succeed... but no data in the output. */
      VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
      VALUE_HANDLE_DEREF_TO_ZERO(outNbElement);
      return NAMESPACE(TA_RetCode)TA_SUCCESS;
   }

   /* Do the K calculation:
    *
    *    Kt = 100 x ((Ct-Lt)/(Ht-Lt))
    *
    * Kt is today stochastic
    * Ct is today closing price.
    * Lt is the lowest price of the last K Period (including today)
    * Ht is the highest price of the last K Period (including today)
    */

   /* Proceed with the calculation for the requested range.
    * Note that this algorithm allows the input and
    * output to be the same buffer.
    */
   outIdx = 0;

   /* Calculate just enough K for ending up with the caller 
    * requested range. (The range of k must consider all
    * the lookback involve with the smoothing).
    */
   trailingIdx = startIdx-lookbackTotal;
   today       = trailingIdx+lookbackK;
   lowestIdx   = highestIdx = -1;
   diff = highest = lowest  = 0.0;

   /* Allocate a temporary buffer large enough to
    * store the K.
    *
    * If the output is the same as the input, great
    * we just save ourself one memory allocation.
    */
   #if !defined( _MANAGED ) && !defined(USE_SINGLE_PRECISION_INPUT)
      bufferIsAllocated = 0;
   #endif

   #if defined(USE_SINGLE_PRECISION_INPUT)
      /* Always alloc, since output is of different type and
       * its allocated size is not guarantee to be as large as
       * the input.
       */
      ARRAY_ALLOC( tempBuffer, endIdx-today+1 );
   #else
      if( (outFastK == inHigh) || 
          (outFastK == inLow)  || 
          (outFastK == inClose) )
      {
         tempBuffer = outFastK;
      }
      else if( (outFastD == inHigh) ||
               (outFastD == inLow)  ||
               (outFastD == inClose) )
      {
         tempBuffer = outFastD;
      }
      else
      {
         #if !defined( _MANAGED )
            bufferIsAllocated = 1;
         #endif
         ARRAY_ALLOC(tempBuffer, endIdx-today+1 );
      }
   #endif

   /* Do the K calculation */
   while( today <= endIdx )
   {
      /* Set the lowest low */
      tmp = inLow[today];
      if( lowestIdx < trailingIdx )
      {
         lowestIdx = trailingIdx;
         lowest = inLow[lowestIdx];
         i = lowestIdx;
         while( ++i<=today )
         {
            tmp = inLow[i];
            if( tmp < lowest )
            {
               lowestIdx = i;
               lowest = tmp;
            }
         }
         diff = (highest - lowest)/100.0;
      }
      else if( tmp <= lowest )
      {
         lowestIdx = today;
         lowest = tmp;
         diff = (highest - lowest)/100.0;
      }

      /* Set the highest high */
      tmp = inHigh[today];
      if( highestIdx < trailingIdx )
      {
         highestIdx = trailingIdx;
         highest = inHigh[highestIdx];
         i = highestIdx;
         while( ++i<=today )
         {
            tmp = inHigh[i];
            if( tmp > highest )
            {
               highestIdx = i;
               highest = tmp;
            }
         }
         diff = (highest - lowest)/100.0;
      }
      else if( tmp >= highest )
      {
         highestIdx = today;
         highest = tmp;
         diff = (highest - lowest)/100.0;
      }

      /* Calculate stochastic. */
      if( diff != 0.0 )
        tempBuffer[outIdx++] = (inClose[today]-lowest)/diff;
      else
        tempBuffer[outIdx++] = 0.0;

      trailingIdx++;
      today++; 
   }

   /* Fast-K calculation completed. This K calculation is returned
    * to the caller. It is smoothed to become Fast-D.
    */
   retCode = TA_MA( 0, outIdx-1,
                    tempBuffer, optInFastD_Period,
                    optInFastD_MAType, 
                    outBegIdx, outNbElement, outFastD );


   if( (retCode != NAMESPACE(TA_RetCode)TA_SUCCESS ) || ((int)VALUE_HANDLE_DEREF(outNbElement)) == 0 )
   {
      #if defined(USE_SINGLE_PRECISION_INPUT)
         ARRAY_FREE( tempBuffer ); 
      #else
         ARRAY_FREE_COND( bufferIsAllocated, tempBuffer ); 
      #endif
      /* Something wrong happen? No further data? */
      VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
      VALUE_HANDLE_DEREF_TO_ZERO(outNbElement);
      return retCode; 
   }

   /* Copy tempBuffer into the caller buffer. 
    * (Calculation could not be done directly in the
    *  caller buffer because more input data then the
    *  requested range was needed for doing %D).
    */
   ARRAY_MEMMOVE( outFastK, 0, tempBuffer, lookbackFastD, (int)VALUE_HANDLE_DEREF(outNbElement) );

   /* Don't need K anymore, free it if it was allocated here. */
   #if defined(USE_SINGLE_PRECISION_INPUT)
      ARRAY_FREE( tempBuffer ); 
   #else
      ARRAY_FREE_COND( bufferIsAllocated, tempBuffer ); 
   #endif

   if( retCode != NAMESPACE(TA_RetCode)TA_SUCCESS )
   {
      /* Something wrong happen while processing %D? */
      VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
      VALUE_HANDLE_DEREF_TO_ZERO(outNbElement);
      return retCode;
   }

   /* Note: Keep the outBegIdx relative to the
    *       caller input before returning.
    */
   VALUE_HANDLE_DEREF(outBegIdx) = startIdx;

   return NAMESPACE(TA_RetCode)TA_SUCCESS;
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
/* Generated */ enum class Core::TA_RetCode Core::STOCHF( int    startIdx,
/* Generated */                                           int    endIdx,
/* Generated */                                           cli::array<float>^ inHigh,
/* Generated */                                           cli::array<float>^ inLow,
/* Generated */                                           cli::array<float>^ inClose,
/* Generated */                                           int           optInFastK_Period, /* From 1 to 100000 */
/* Generated */                                           int           optInFastD_Period, /* From 1 to 100000 */
/* Generated */                                           TA_MAType     optInFastD_MAType,
/* Generated */                                           [OutAttribute]int^ outBegIdx,
/* Generated */                                           [OutAttribute]int^ outNbElement,
/* Generated */                                           cli::array<double>^  outFastK,
/* Generated */                                           cli::array<double>^  outFastD )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_STOCHF( int    startIdx,
/* Generated */                         int    endIdx,
/* Generated */                         const float  inHigh[],
/* Generated */                         const float  inLow[],
/* Generated */                         const float  inClose[],
/* Generated */                         int           optInFastK_Period, /* From 1 to 100000 */
/* Generated */                         int           optInFastD_Period, /* From 1 to 100000 */
/* Generated */                         TA_MAType     optInFastD_MAType,
/* Generated */                         int          *outBegIdx,
/* Generated */                         int          *outNbElement,
/* Generated */                         double        outFastK[],
/* Generated */                         double        outFastD[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */    TA_RetCode retCode;
/* Generated */    double lowest, highest, tmp, diff;
/* Generated */    ARRAY_REF( tempBuffer );
/* Generated */    int outIdx, lowestIdx, highestIdx;
/* Generated */    int lookbackTotal, lookbackK, lookbackFastD;
/* Generated */    int trailingIdx, today, i;
/* Generated */    #if !defined( _MANAGED ) && !defined(USE_SINGLE_PRECISION_INPUT)
/* Generated */    int bufferIsAllocated;
/* Generated */    #endif
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return NAMESPACE(TA_RetCode)TA_OUT_OF_RANGE_START_INDEX;
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return NAMESPACE(TA_RetCode)TA_OUT_OF_RANGE_END_INDEX;
/* Generated */     if(!inHigh||!inLow||!inClose)
/* Generated */        return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */     if( (int)optInFastK_Period == TA_INTEGER_DEFAULT )
/* Generated */        optInFastK_Period = 5;
/* Generated */     else if( ((int)optInFastK_Period < 1) || ((int)optInFastK_Period > 100000) )
/* Generated */        return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */     if( (int)optInFastD_Period == TA_INTEGER_DEFAULT )
/* Generated */        optInFastD_Period = 3;
/* Generated */     else if( ((int)optInFastD_Period < 1) || ((int)optInFastD_Period > 100000) )
/* Generated */        return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */     #if !defined(_MANAGED)
/* Generated */     if( (int)optInFastD_MAType == TA_INTEGER_DEFAULT )
/* Generated */        optInFastD_MAType = 0;
/* Generated */     else if( ((int)optInFastD_MAType < 0) || ((int)optInFastD_MAType > 8) )
/* Generated */        return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */     #endif 
/* Generated */     if( !outFastK )
/* Generated */        return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */     if( !outFastD )
/* Generated */        return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */  #endif 
/* Generated */    lookbackK      = optInFastK_Period-1;
/* Generated */    lookbackFastD  = TA_MA_Lookback( optInFastD_Period, optInFastD_MAType );
/* Generated */    lookbackTotal  = lookbackK + lookbackFastD;
/* Generated */    if( startIdx < lookbackTotal )
/* Generated */       startIdx = lookbackTotal;
/* Generated */    if( startIdx > endIdx )
/* Generated */    {
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outNbElement);
/* Generated */       return NAMESPACE(TA_RetCode)TA_SUCCESS;
/* Generated */    }
/* Generated */    outIdx = 0;
/* Generated */    trailingIdx = startIdx-lookbackTotal;
/* Generated */    today       = trailingIdx+lookbackK;
/* Generated */    lowestIdx   = highestIdx = -1;
/* Generated */    diff = highest = lowest  = 0.0;
/* Generated */    #if !defined( _MANAGED ) && !defined(USE_SINGLE_PRECISION_INPUT)
/* Generated */       bufferIsAllocated = 0;
/* Generated */    #endif
/* Generated */    #if defined(USE_SINGLE_PRECISION_INPUT)
/* Generated */       ARRAY_ALLOC( tempBuffer, endIdx-today+1 );
/* Generated */    #else
/* Generated */       if( (outFastK == inHigh) || 
/* Generated */           (outFastK == inLow)  || 
/* Generated */           (outFastK == inClose) )
/* Generated */       {
/* Generated */          tempBuffer = outFastK;
/* Generated */       }
/* Generated */       else if( (outFastD == inHigh) ||
/* Generated */                (outFastD == inLow)  ||
/* Generated */                (outFastD == inClose) )
/* Generated */       {
/* Generated */          tempBuffer = outFastD;
/* Generated */       }
/* Generated */       else
/* Generated */       {
/* Generated */          #if !defined( _MANAGED )
/* Generated */             bufferIsAllocated = 1;
/* Generated */          #endif
/* Generated */          ARRAY_ALLOC(tempBuffer, endIdx-today+1 );
/* Generated */       }
/* Generated */    #endif
/* Generated */    while( today <= endIdx )
/* Generated */    {
/* Generated */       tmp = inLow[today];
/* Generated */       if( lowestIdx < trailingIdx )
/* Generated */       {
/* Generated */          lowestIdx = trailingIdx;
/* Generated */          lowest = inLow[lowestIdx];
/* Generated */          i = lowestIdx;
/* Generated */          while( ++i<=today )
/* Generated */          {
/* Generated */             tmp = inLow[i];
/* Generated */             if( tmp < lowest )
/* Generated */             {
/* Generated */                lowestIdx = i;
/* Generated */                lowest = tmp;
/* Generated */             }
/* Generated */          }
/* Generated */          diff = (highest - lowest)/100.0;
/* Generated */       }
/* Generated */       else if( tmp <= lowest )
/* Generated */       {
/* Generated */          lowestIdx = today;
/* Generated */          lowest = tmp;
/* Generated */          diff = (highest - lowest)/100.0;
/* Generated */       }
/* Generated */       tmp = inHigh[today];
/* Generated */       if( highestIdx < trailingIdx )
/* Generated */       {
/* Generated */          highestIdx = trailingIdx;
/* Generated */          highest = inHigh[highestIdx];
/* Generated */          i = highestIdx;
/* Generated */          while( ++i<=today )
/* Generated */          {
/* Generated */             tmp = inHigh[i];
/* Generated */             if( tmp > highest )
/* Generated */             {
/* Generated */                highestIdx = i;
/* Generated */                highest = tmp;
/* Generated */             }
/* Generated */          }
/* Generated */          diff = (highest - lowest)/100.0;
/* Generated */       }
/* Generated */       else if( tmp >= highest )
/* Generated */       {
/* Generated */          highestIdx = today;
/* Generated */          highest = tmp;
/* Generated */          diff = (highest - lowest)/100.0;
/* Generated */       }
/* Generated */       if( diff != 0.0 )
/* Generated */         tempBuffer[outIdx++] = (inClose[today]-lowest)/diff;
/* Generated */       else
/* Generated */         tempBuffer[outIdx++] = 0.0;
/* Generated */       trailingIdx++;
/* Generated */       today++; 
/* Generated */    }
/* Generated */    retCode = TA_MA( 0, outIdx-1,
/* Generated */                     tempBuffer, optInFastD_Period,
/* Generated */                     optInFastD_MAType, 
/* Generated */                     outBegIdx, outNbElement, outFastD );
/* Generated */    if( (retCode != NAMESPACE(TA_RetCode)TA_SUCCESS ) || ((int)VALUE_HANDLE_DEREF(outNbElement)) == 0 )
/* Generated */    {
/* Generated */       #if defined(USE_SINGLE_PRECISION_INPUT)
/* Generated */          ARRAY_FREE( tempBuffer ); 
/* Generated */       #else
/* Generated */          ARRAY_FREE_COND( bufferIsAllocated, tempBuffer ); 
/* Generated */       #endif
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outNbElement);
/* Generated */       return retCode; 
/* Generated */    }
/* Generated */    ARRAY_MEMMOVE( outFastK, 0, tempBuffer, lookbackFastD, (int)VALUE_HANDLE_DEREF(outNbElement) );
/* Generated */    #if defined(USE_SINGLE_PRECISION_INPUT)
/* Generated */       ARRAY_FREE( tempBuffer ); 
/* Generated */    #else
/* Generated */       ARRAY_FREE_COND( bufferIsAllocated, tempBuffer ); 
/* Generated */    #endif
/* Generated */    if( retCode != NAMESPACE(TA_RetCode)TA_SUCCESS )
/* Generated */    {
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outNbElement);
/* Generated */       return retCode;
/* Generated */    }
/* Generated */    VALUE_HANDLE_DEREF(outBegIdx) = startIdx;
/* Generated */    return NAMESPACE(TA_RetCode)TA_SUCCESS;
/* Generated */ }
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }} // Close namespace TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/

