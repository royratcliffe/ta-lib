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
 *  112400 MF   First version.
 *
 */

/* Description:
 *     Test RSI function.
 */

/**** Headers ****/
#include <stdio.h>
#include <string.h>

#include "ta_test_priv.h"
#include "ta_test_func.h"
#include "ta_utility.h"

/**** External functions declarations. ****/
/* None */

/**** External variables declarations. ****/
/* None */

/**** Global variables definitions.    ****/
/* None */

/**** Local declarations.              ****/
typedef struct
{
   TA_Integer doRangeTestFlag;

   TA_Integer unstablePeriod;

   TA_Integer startIdx;
   TA_Integer endIdx;

   TA_Integer optInTimePeriod_0;
   TA_Integer optInCompatibility;

   TA_RetCode expectedRetCode;

   TA_Integer oneOfTheExpectedOutRealIndex0;
   TA_Real    oneOfTheExpectedOutReal0;

   TA_Integer expectedBegIdx;
   TA_Integer expectedNbElement;
} TA_Test;

typedef struct
{
   const TA_Test *test;
   const TA_Real *close;
} TA_RangeTestParam;

/**** Local functions declarations.    ****/
static ErrorNumber do_test( TA_Libc *libHandle,
                            const TA_History *history,
                            const TA_Test *test );

/**** Local variables definitions.     ****/

static TA_Test tableTest[] =
{
   /**********************/
   /*      RSI TEST      */
   /**********************/
   { 1, 0, 0, 251, 14, TA_RSI_CLASSIC, TA_SUCCESS,      0, 49.14,  14,  252-14 }, /* First Value */
   { 0, 0, 0, 251, 14, TA_RSI_CLASSIC, TA_SUCCESS,      1, 52.32,  14,  252-14 },
   { 0, 0, 0, 251, 14, TA_RSI_CLASSIC, TA_SUCCESS,      2, 46.07,  14,  252-14 },
   { 0, 0, 0, 251, 14, TA_RSI_CLASSIC, TA_SUCCESS, 252-15, 49.63,  14,  252-14 },  /* Last Value */

   /* No output value. */
   { 0, 0, 1, 1,  14, TA_RSI_CLASSIC, TA_SUCCESS, 0, 0, 0, 0},

   /* One value tests. */
   { 0, 0, 14,  14, 14, TA_RSI_CLASSIC, TA_SUCCESS, 0, 49.14,     14, 1},

   /* Index too low test. */
   { 0, 0, 0,  15, 14, TA_RSI_CLASSIC, TA_SUCCESS, 0, 49.14,     14, 2},
   { 0, 0, 1,  15, 14, TA_RSI_CLASSIC, TA_SUCCESS, 0, 49.14,     14, 2},
   { 0, 0, 2,  16, 14, TA_RSI_CLASSIC, TA_SUCCESS, 0, 49.14,     14, 3},
   { 0, 0, 2,  16, 14, TA_RSI_CLASSIC, TA_SUCCESS, 1, 52.32,     14, 3},
   { 0, 0, 2,  16, 14, TA_RSI_CLASSIC, TA_SUCCESS, 2, 46.07,     14, 3},
   { 0, 0, 0,  14, 14, TA_RSI_CLASSIC, TA_SUCCESS, 0, 49.14,     14, 1},
   { 0, 0, 0,  13, 14, TA_RSI_CLASSIC, TA_SUCCESS, 0, 49.14,     14, 0},

   /* Test with 1 unstable price bar. Test for period 1, 2, 14 */
   { 0, 1, 0, 251, 14, TA_RSI_CLASSIC, TA_SUCCESS,      0,     52.32,  15,  252-(14+1) },
   { 0, 1, 0, 251, 14, TA_RSI_CLASSIC, TA_SUCCESS,      1,     46.07,  15,  252-(14+1) },
   { 0, 1, 0, 251, 14, TA_RSI_CLASSIC, TA_SUCCESS, 252-(15+1), 49.63,  15,  252-(14+1) },  /* Last Value */

   /* Test with 2 unstable price bar. Test for period 1, 2, 14 */
   { 0, 2, 0, 251, 14, TA_RSI_CLASSIC, TA_SUCCESS,      0,     46.07,  16,  252-(14+2) },
   { 0, 2, 0, 251, 14, TA_RSI_CLASSIC, TA_SUCCESS, 252-(15+2), 49.63,  16,  252-(14+2) },  /* Last Value */

   /* Test some limit case with unstable period. */
   { 0, 1,   0,   0,  1, TA_RSI_CLASSIC, TA_SUCCESS,   0,  0,   0, 0 }, /* no data */
   { 0, 252, 0,   0,  1, TA_RSI_CLASSIC, TA_SUCCESS,   0,  0,   0, 0 }, /* no data */
   { 0, 300, 0,   0,  1, TA_RSI_CLASSIC, TA_SUCCESS,   0,  0,   0, 0 }, /* no data */

   /**********************/
   /* RSI Metastock TEST */
   /**********************/
   { 1, 0, 0, 251, 14, TA_RSI_METASTOCK, TA_SUCCESS,      0, 47.11,  13,  252-13 }, /* First Value */
   { 0, 0, 0, 251, 14, TA_RSI_METASTOCK, TA_SUCCESS,      1, 49.14,  13,  252-13 },
   { 0, 0, 0, 251, 14, TA_RSI_METASTOCK, TA_SUCCESS,      2, 52.32,  13,  252-13 },
   { 0, 0, 0, 251, 14, TA_RSI_METASTOCK, TA_SUCCESS,      3, 46.07,  13,  252-13 },
   { 0, 0, 0, 251, 14, TA_RSI_METASTOCK, TA_SUCCESS, 252-14, 49.63,  13,  252-13 }, /* Last Value */

   /* No output value. */
   { 0, 0, 1, 1,  14, TA_RSI_METASTOCK, TA_SUCCESS, 0, 0, 0, 0},

   /* One value tests. */
   { 0, 0, 13, 13, 14, TA_RSI_METASTOCK, TA_SUCCESS, 0, 47.11, 13, 1},
   { 0, 0, 13, 13, 14, TA_RSI_METASTOCK, TA_SUCCESS, 0, 47.11, 13, 1},

   /* Index too low test. */
   { 0, 0, 0,  15, 14, TA_RSI_METASTOCK, TA_SUCCESS, 0, 47.11,     13, 3},
   { 0, 0, 1,  15, 14, TA_RSI_METASTOCK, TA_SUCCESS, 0, 47.11,     13, 3},
   { 0, 0, 2,  16, 14, TA_RSI_METASTOCK, TA_SUCCESS, 0, 47.11,     13, 4},
   { 0, 0, 2,  16, 14, TA_RSI_METASTOCK, TA_SUCCESS, 1, 49.14,     13, 4},
   { 0, 0, 2,  16, 14, TA_RSI_METASTOCK, TA_SUCCESS, 2, 52.32,     13, 4},
   { 0, 0, 0,  14, 14, TA_RSI_METASTOCK, TA_SUCCESS, 0, 47.11,     13, 2},
   { 0, 0, 0,  13, 14, TA_RSI_METASTOCK, TA_SUCCESS, 0, 47.11,     13, 1},
   { 0, 0, 0,  12, 14, TA_RSI_METASTOCK, TA_SUCCESS, 0, 47.11,     13, 0},

   /* Test with 1 unstable price bar. Test for period 1, 2, 14 */
   { 0, 1, 0, 251, 14, TA_RSI_METASTOCK, TA_SUCCESS,      0,     49.14,  14,  252-(13+1) },
   { 0, 1, 0, 251, 14, TA_RSI_METASTOCK, TA_SUCCESS,      1,     52.32,  14,  252-(13+1) },
   { 0, 1, 0, 251, 14, TA_RSI_METASTOCK, TA_SUCCESS, 252-(14+1), 49.63,  14,  252-(13+1) },  /* Last Value */

   /* Test with 2 unstable price bar. Test for period 1, 2, 14 */
   { 0, 2, 0, 251, 14, TA_RSI_METASTOCK, TA_SUCCESS,      0,     52.32,  15,  252-(13+2) },
   { 0, 2, 0, 251, 14, TA_RSI_METASTOCK, TA_SUCCESS, 252-(14+2), 49.63,  15,  252-(13+2) },  /* Last Value */


   /* Test some limit case with unstable period. */
   { 1, 1,   0,   0,  1, TA_RSI_METASTOCK, TA_SUCCESS,   0,  0,   0, 0 }, /* no data */
   { 0, 252, 0,   0,  1, TA_RSI_METASTOCK, TA_SUCCESS,   0,  0,   0, 0 }, /* no data */
   { 0, 300, 0,   0,  1, TA_RSI_METASTOCK, TA_SUCCESS,   0,  0,   0, 0 }, /* no data */

};

#define NB_TEST (sizeof(tableTest)/sizeof(TA_Test))

/**** Global functions definitions.   ****/
ErrorNumber test_func_rsi( TA_Libc *libHandle, TA_History *history )
{
   unsigned int i;
   ErrorNumber retValue;

   /* Re-initialize all the unstable period to zero. */
   TA_SetUnstablePeriod( libHandle, TA_FUNC_UNST_ALL, 0 );

   for( i=0; i < NB_TEST; i++ )
   {
      if( (int)tableTest[i].expectedNbElement > (int)history->nbBars )
      {
         printf( "%s Failed Bad Parameter for Test #%d (%d,%d)\n", __FILE__,
                 i, tableTest[i].expectedNbElement, history->nbBars );
         return TA_TESTUTIL_TFRR_BAD_PARAM;
      }

      retValue = do_test( libHandle, history, &tableTest[i] );
      if( retValue != 0 )
      {
         printf( "%s Failed Test #%d (Code=%d)\n", __FILE__,
                 i, retValue );
         return retValue;
      }
   }

   /* Re-initialize all the unstable period to zero. */
   TA_SetUnstablePeriod( libHandle, TA_FUNC_UNST_ALL, 0 );

   /* All test succeed. */
   return TA_TEST_PASS; 
}

/**** Local functions definitions.     ****/
static TA_RetCode rangeTestFunction( TA_Libc *libHandle, 
                              TA_Integer startIdx,
                              TA_Integer endIdx,
                              TA_Real *outputBuffer,
                              TA_Integer *outBegIdx,
                              TA_Integer *outNbElement,
                              TA_Integer *lookback,
                              void *opaqueData,
                              unsigned int outputNb )
{
   TA_RetCode retCode;
   TA_RangeTestParam *testParam;

   (void)outputNb;
  
   testParam = (TA_RangeTestParam *)opaqueData;   

   retCode = TA_RSI( libHandle,
                     startIdx,
                     endIdx,
                     testParam->close,
                     testParam->test->optInTimePeriod_0,
                     testParam->test->optInCompatibility,                    
                     outBegIdx,
                     outNbElement,
                     outputBuffer );

   *lookback = TA_RSI_Lookback( testParam->test->optInTimePeriod_0,
                    testParam->test->optInCompatibility );

   return retCode;
}

static ErrorNumber do_test( TA_Libc *libHandle,
                            const TA_History *history,
                            const TA_Test *test )
{
   TA_RetCode retCode;
   ErrorNumber errNb;
   TA_Integer outBegIdx;
   TA_Integer outNbElement;
   TA_RangeTestParam testParam;

   /* Set to NAN all the elements of the gBuffers.  */
   clearAllBuffers();

   /* Build the input. */
   setInputBuffer( 0, history->close, history->nbBars );
   setInputBuffer( 1, history->close, history->nbBars );
   
   /* Set the unstable period requested for that test. */
   retCode = TA_SetUnstablePeriod( libHandle, TA_FUNC_UNST_RSI, test->unstablePeriod );
   if( retCode != TA_SUCCESS )
      return TA_TEST_TFRR_SETUNSTABLE_PERIOD_FAIL;

   /* Make a simple first call. */
   retCode = TA_RSI( libHandle,
                     test->startIdx,
                     test->endIdx,
                     gBuffer[0].in,
                     test->optInTimePeriod_0,
                     test->optInCompatibility,                     
                     &outBegIdx,
                     &outNbElement,
                     gBuffer[0].out0 );

   errNb = checkDataSame( gBuffer[0].in, history->close,history->nbBars );
   if( errNb != TA_TEST_PASS )
      return errNb;

   CHECK_EXPECTED_VALUE( gBuffer[0].out0, 0 );

   outBegIdx = outNbElement = 0;

   /* Make another call where the input and the output are the
    * same buffer.
    */
   retCode = TA_RSI( libHandle,
                     test->startIdx,
                     test->endIdx,
                     gBuffer[1].in,
                     test->optInTimePeriod_0,
                     test->optInCompatibility,                     
                     &outBegIdx,
                     &outNbElement,
                     gBuffer[1].in );

   /* The previous call should have the same output as this call.
    *
    * checkSameContent verify that all value different than NAN in
    * the first parameter is identical in the second parameter.
    */
   errNb = checkSameContent( gBuffer[0].out0, gBuffer[1].in );
   if( errNb != TA_TEST_PASS )
      return errNb;

   CHECK_EXPECTED_VALUE( gBuffer[1].in, 0 );

   if( errNb != TA_TEST_PASS )
      return errNb;

   /* Do a systematic test of most of the
    * possible startIdx/endIdx range.
    */
   testParam.test  = test;
   testParam.close = history->close;

   if( test->doRangeTestFlag )
   {
      errNb = doRangeTest( libHandle,
                           rangeTestFunction, 
                           TA_FUNC_UNST_RSI,
                           (void *)&testParam, 1, 0 );
      if( errNb != TA_TEST_PASS )
         return errNb;
   }

   return TA_TEST_PASS;
}

