/* TA-LIB Copyright (c) 1999-2006, Mario Fortier
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
 *  AC       Angelo Ciceri
 *
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  120904 AC   Creation           
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
/* Generated */    namespace TicTacTec { namespace TA { namespace Lib {
/* Generated */ #elif defined( _JAVA )
/* Generated */    #include "ta_defs.h"
/* Generated */    #define TA_INTERNAL_ERROR(Id) (NAMESPACE(TA_RetCode)TA_INTERNAL_ERROR)
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
/* Generated */ int Core::CDLDARKCLOUDCOVER_Lookback( double        optInPenetration )  /* From 0 to TA_REAL_MAX */
/* Generated */ 
/* Generated */ #elif defined( _JAVA )
/* Generated */ public int CDLDARKCLOUDCOVER_Lookback( double        optInPenetration )  /* From 0 to TA_REAL_MAX */
/* Generated */ 
/* Generated */ #else
/* Generated */ int TA_CDLDARKCLOUDCOVER_Lookback( double        optInPenetration )  /* From 0 to TA_REAL_MAX */
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert local variable here */

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */    if( optInPenetration == TA_REAL_DEFAULT )
/* Generated */       optInPenetration = 5.000000e-1;
/* Generated */    else if( (optInPenetration < 0.000000e+0) ||/* Generated */  (optInPenetration > 3.000000e+37) )
/* Generated */       return -1;
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/

   /* insert lookback code here. */
    UNUSED_VARIABLE(optInPenetration);

    return TA_CANDLEAVGPERIOD(TA_BodyLong) + 1;
}

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
/*
 * TA_CDLDARKCLOUDCOVER - Dark Cloud Cover
 * 
 * Input  = Open, High, Low, Close
 * Output = int
 * 
 * Optional Parameters
 * -------------------
 * optInPenetration:(From 0 to TA_REAL_MAX)
 *    Percentage of penetration of a candle within another candle
 * 
 * 
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum class Core::TA_RetCode Core::CDLDARKCLOUDCOVER( int    startIdx,
/* Generated */                                                      int    endIdx,
/* Generated */                                                      cli::array<double>^ inOpen,
/* Generated */                                                      cli::array<double>^ inHigh,
/* Generated */                                                      cli::array<double>^ inLow,
/* Generated */                                                      cli::array<double>^ inClose,
/* Generated */                                                      double        optInPenetration, /* From 0 to TA_REAL_MAX */
/* Generated */                                                      [Out]int%    outBegIdx,
/* Generated */                                                      [Out]int%    outNbElement,
/* Generated */                                                      cli::array<int>^  outInteger )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public TA_RetCode CDLDARKCLOUDCOVER( int    startIdx,
/* Generated */                                      int    endIdx,
/* Generated */                                      double       inOpen[],
/* Generated */                                      double       inHigh[],
/* Generated */                                      double       inLow[],
/* Generated */                                      double       inClose[],
/* Generated */                                      double        optInPenetration, /* From 0 to TA_REAL_MAX */
/* Generated */                                      MInteger     outBegIdx,
/* Generated */                                      MInteger     outNbElement,
/* Generated */                                      int           outInteger[] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_CDLDARKCLOUDCOVER( int    startIdx,
/* Generated */                                  int    endIdx,
/* Generated */                                  const double inOpen[],
/* Generated */                                  const double inHigh[],
/* Generated */                                  const double inLow[],
/* Generated */                                  const double inClose[],
/* Generated */                                  double        optInPenetration, /* From 0 to TA_REAL_MAX */
/* Generated */                                  int          *outBegIdx,
/* Generated */                                  int          *outNbElement,
/* Generated */                                  int           outInteger[] )
/* Generated */ #endif
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
{
   /* Insert local variables here. */
    double BodyLongPeriodTotal;
    int i, outIdx, BodyLongTrailingIdx, lookbackTotal;

/**** START GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    /* Validate the requested output range. */
/* Generated */    if( startIdx < 0 )
/* Generated */       return NAMESPACE(TA_RetCode)TA_OUT_OF_RANGE_START_INDEX;
/* Generated */    if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */       return NAMESPACE(TA_RetCode)TA_OUT_OF_RANGE_END_INDEX;
/* Generated */ 
/* Generated */    #if !defined(_MANAGED) && !defined(_JAVA)
/* Generated */    /* Verify required price component. */
/* Generated */    if(!inOpen||!inHigh||!inLow||!inClose)
/* Generated */       return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */ 
/* Generated */    #endif /* !defined(_MANAGED) && !defined(_JAVA)*/
/* Generated */    if( optInPenetration == TA_REAL_DEFAULT )
/* Generated */       optInPenetration = 5.000000e-1;
/* Generated */    else if( (optInPenetration < 0.000000e+0) ||/* Generated */  (optInPenetration > 3.000000e+37) )
/* Generated */       return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */ 
/* Generated */    #if !defined(_MANAGED) && !defined(_JAVA)
/* Generated */    if( !outInteger )
/* Generated */       return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */ 
/* Generated */    #endif /* !defined(_MANAGED) && !defined(_JAVA) */
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/

   /* Identify the minimum number of price bar needed
    * to calculate at least one output.
    */

   lookbackTotal = LOOKBACK_CALL(CDLDARKCLOUDCOVER)(optInPenetration);

   /* Move up the start index if there is not
    * enough initial data.
    */
   if( startIdx < lookbackTotal )
      startIdx = lookbackTotal;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
   {
      VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
      VALUE_HANDLE_DEREF_TO_ZERO(outNbElement);
      return NAMESPACE(TA_RetCode)TA_SUCCESS;
   }

   /* Do the calculation using tight loops. */
   /* Add-up the initial period, except for the last value. */
   BodyLongPeriodTotal = 0;
   BodyLongTrailingIdx = startIdx - TA_CANDLEAVGPERIOD(TA_BodyLong);

   i = BodyLongTrailingIdx;
   while( i < startIdx ) {
        BodyLongPeriodTotal += TA_CANDLERANGE( TA_BodyLong, i-1 );
        i++;
   }
   i = startIdx;

   /* Proceed with the calculation for the requested range.
    * Must have:
    * - first candle: long white candle
    * - second candle: black candle that opens above previous day high and closes within previous day real body; 
    * Greg Morris wants the close to be below the midpoint of the previous real body
    * The meaning of "long" is specified with TA_SetCandleSettings, the penetration of the first real body is specified
    * with optInPenetration
    * outInteger is negative (-1 to -100): dark cloud cover is always bearish
    * the user should consider that a dark cloud cover is significant when it appears in an uptrend, while 
    * this function does not consider it
    */
   outIdx = 0;
   do
   {
        if( TA_CANDLECOLOR(i-1) == 1 &&                                                     // 1st: white
            TA_REALBODY(i-1) > TA_CANDLEAVERAGE( TA_BodyLong, BodyLongPeriodTotal, i-1 ) && //      long
            TA_CANDLECOLOR(i) == -1 &&                                                      // 2nd: black
            inOpen[i] > inHigh[i-1] &&                                                      //      open above prior high
            inClose[i] > inOpen[i-1] &&                                                     //      close within prior body
            inClose[i] < inClose[i-1] - TA_REALBODY(i-1) * optInPenetration
          )
            outInteger[outIdx++] = -100;
        else
            outInteger[outIdx++] = 0;
        /* add the current range and subtract the first range: this is done after the pattern recognition 
         * when avgPeriod is not 0, that means "compare with the previous candles" (it excludes the current candle)
         */
        BodyLongPeriodTotal += TA_CANDLERANGE( TA_BodyLong, i-1 ) - TA_CANDLERANGE( TA_BodyLong, BodyLongTrailingIdx-1 );
        i++; 
        BodyLongTrailingIdx++;
   } while( i <= endIdx );

   /* All done. Indicate the output limits and return. */
   VALUE_HANDLE_DEREF(outNbElement) = outIdx;
   VALUE_HANDLE_DEREF(outBegIdx)    = startIdx;

   return NAMESPACE(TA_RetCode)TA_SUCCESS;
}

/**** START GENCODE SECTION 5 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #define  USE_SINGLE_PRECISION_INPUT
/* Generated */ #if !defined( _MANAGED ) && !defined( _JAVA )
/* Generated */    #undef   TA_PREFIX
/* Generated */    #define  TA_PREFIX(x) TA_S_##x
/* Generated */ #endif
/* Generated */ #undef   INPUT_TYPE
/* Generated */ #define  INPUT_TYPE float
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum class Core::TA_RetCode Core::CDLDARKCLOUDCOVER( int    startIdx,
/* Generated */                                                      int    endIdx,
/* Generated */                                                      cli::array<float>^ inOpen,
/* Generated */                                                      cli::array<float>^ inHigh,
/* Generated */                                                      cli::array<float>^ inLow,
/* Generated */                                                      cli::array<float>^ inClose,
/* Generated */                                                      double        optInPenetration, /* From 0 to TA_REAL_MAX */
/* Generated */                                                      [Out]int%    outBegIdx,
/* Generated */                                                      [Out]int%    outNbElement,
/* Generated */                                                      cli::array<int>^  outInteger )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public TA_RetCode CDLDARKCLOUDCOVER( int    startIdx,
/* Generated */                                      int    endIdx,
/* Generated */                                      float        inOpen[],
/* Generated */                                      float        inHigh[],
/* Generated */                                      float        inLow[],
/* Generated */                                      float        inClose[],
/* Generated */                                      double        optInPenetration, /* From 0 to TA_REAL_MAX */
/* Generated */                                      MInteger     outBegIdx,
/* Generated */                                      MInteger     outNbElement,
/* Generated */                                      int           outInteger[] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_CDLDARKCLOUDCOVER( int    startIdx,
/* Generated */                                    int    endIdx,
/* Generated */                                    const float  inOpen[],
/* Generated */                                    const float  inHigh[],
/* Generated */                                    const float  inLow[],
/* Generated */                                    const float  inClose[],
/* Generated */                                    double        optInPenetration, /* From 0 to TA_REAL_MAX */
/* Generated */                                    int          *outBegIdx,
/* Generated */                                    int          *outNbElement,
/* Generated */                                    int           outInteger[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */     double BodyLongPeriodTotal;
/* Generated */     int i, outIdx, BodyLongTrailingIdx, lookbackTotal;
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return NAMESPACE(TA_RetCode)TA_OUT_OF_RANGE_START_INDEX;
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return NAMESPACE(TA_RetCode)TA_OUT_OF_RANGE_END_INDEX;
/* Generated */     #if !defined(_MANAGED) && !defined(_JAVA)
/* Generated */     if(!inOpen||!inHigh||!inLow||!inClose)
/* Generated */        return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */     #endif 
/* Generated */     if( optInPenetration == TA_REAL_DEFAULT )
/* Generated */        optInPenetration = 5.000000e-1;
/* Generated */     else if( (optInPenetration < 0.000000e+0) ||  (optInPenetration > 3.000000e+37) )
/* Generated */        return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */     #if !defined(_MANAGED) && !defined(_JAVA)
/* Generated */     if( !outInteger )
/* Generated */        return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */     #endif 
/* Generated */  #endif 
/* Generated */    lookbackTotal = LOOKBACK_CALL(CDLDARKCLOUDCOVER)(optInPenetration);
/* Generated */    if( startIdx < lookbackTotal )
/* Generated */       startIdx = lookbackTotal;
/* Generated */    if( startIdx > endIdx )
/* Generated */    {
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outNbElement);
/* Generated */       return NAMESPACE(TA_RetCode)TA_SUCCESS;
/* Generated */    }
/* Generated */    BodyLongPeriodTotal = 0;
/* Generated */    BodyLongTrailingIdx = startIdx - TA_CANDLEAVGPERIOD(TA_BodyLong);
/* Generated */    i = BodyLongTrailingIdx;
/* Generated */    while( i < startIdx ) {
/* Generated */         BodyLongPeriodTotal += TA_CANDLERANGE( TA_BodyLong, i-1 );
/* Generated */         i++;
/* Generated */    }
/* Generated */    i = startIdx;
/* Generated */    outIdx = 0;
/* Generated */    do
/* Generated */    {
/* Generated */         if( TA_CANDLECOLOR(i-1) == 1 &&                                                     // 1st: white
/* Generated */             TA_REALBODY(i-1) > TA_CANDLEAVERAGE( TA_BodyLong, BodyLongPeriodTotal, i-1 ) && //      long
/* Generated */             TA_CANDLECOLOR(i) == -1 &&                                                      // 2nd: black
/* Generated */             inOpen[i] > inHigh[i-1] &&                                                      //      open above prior high
/* Generated */             inClose[i] > inOpen[i-1] &&                                                     //      close within prior body
/* Generated */             inClose[i] < inClose[i-1] - TA_REALBODY(i-1) * optInPenetration
/* Generated */           )
/* Generated */             outInteger[outIdx++] = -100;
/* Generated */         else
/* Generated */             outInteger[outIdx++] = 0;
/* Generated */         BodyLongPeriodTotal += TA_CANDLERANGE( TA_BodyLong, i-1 ) - TA_CANDLERANGE( TA_BodyLong, BodyLongTrailingIdx-1 );
/* Generated */         i++; 
/* Generated */         BodyLongTrailingIdx++;
/* Generated */    } while( i <= endIdx );
/* Generated */    VALUE_HANDLE_DEREF(outNbElement) = outIdx;
/* Generated */    VALUE_HANDLE_DEREF(outBegIdx)    = startIdx;
/* Generated */    return NAMESPACE(TA_RetCode)TA_SUCCESS;
/* Generated */ }
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }}} // Close namespace TicTacTec.TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 5 - DO NOT DELETE THIS LINE ****/

