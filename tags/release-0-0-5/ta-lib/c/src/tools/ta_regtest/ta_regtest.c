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
 *  063001 MF   First version (initial framework only).
 *
 */

/* Description:
 *    Perform regression testing of the TA-LIB.
 */

/**** Headers ****/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
/* None */

/**** Local functions declarations.    ****/
static int testTAFunction_ALL( TA_Libc *libHandle, TA_History *history );
static ErrorNumber test_with_simulator( void );
static ErrorNumber testHistoryAlloc( void );

/**** Local variables definitions.     ****/
/* None */

/**** Global functions definitions.   ****/
int main( int argc, char **argv )
{
   ErrorNumber retValue;

   (void)argv;

   printf( "\n" );
   printf( "ta_regtest V%s - Regression Testing of TA-Lib code\n", TA_GetVersionString() );
   printf( "\n" );

   if( argc > 1 )
   {
      printf( "Usage: ta_regtest\n" );
      printf( "\n" );
      printf( "   No parameter needed.\n" );
      printf( "\n" );
      printf( "   This tool will execute a series of tests to\n" );
      printf( "   make sure that the library is behaving as\n" );
      printf( "   expected.\n\n");

      printf( "   ** Must be run from the 'bin' directory.\n\n" );

      printf( "   On success, the exit code is 0.\n" );
      printf( "   On failure, the exit code is a number that can be\n" );
      printf( "   found in c/src/tools/ta_regtest/ta_error_number.h\n" );

      return TA_REGTEST_BAD_USER_PARAM;
   }

   /* Test Performance Measurements. */
   retValue = test_pm();
   if( retValue != TA_TEST_PASS )
   {
      printf( "Failed: Performance Measurements Tests (error number = %d)\n", retValue );
      return retValue;
   }
      
   /* Test history alloc. */
   retValue = testHistoryAlloc();
   if( retValue != TA_TEST_PASS )
   {
      printf( "Failed TA_HistoryAlloc test with code=%d\n", retValue );
      return retValue;
   }

   /* Some tests are using randomness. */
   srand( (unsigned)time( NULL ) );

   /* Perform the tests who simply used the TA_SIMULATOR data
    * to perform their test.
    */
   retValue = test_with_simulator();
   if( retValue != TA_TEST_PASS )
      return retValue;

   /* Test the ASCII data source. */
   retValue = test_ascii();
   if( retValue != TA_TEST_PASS )
      return retValue;

   /* Test the Yahoo! data source. */
   retValue = test_yahoo();
   if( retValue != TA_TEST_PASS )
      return retValue;

   retValue = test_datasource_merge();
   if( retValue != TA_TEST_PASS )
      return retValue;


   printf( "\n* All tests succeed. Enjoy the library. *\n" );

   return TA_TEST_PASS; /* Everything succeed !!! */
}

/**** Local functions definitions.     ****/
static ErrorNumber test_with_simulator( void )
{
   TA_Libc    *libHandle;
   TA_UDBase  *uDBase;
   TA_History *history;
   TA_AddDataSourceParam param;
   TA_RetCode  retCode;
   ErrorNumber retValue;

   /* Initialize the library. */
   retValue = allocLib( &libHandle, &uDBase );
   if( retValue != TA_TEST_PASS )
      return retValue;

   /* Add a datasource using pre-defined data.
    * This data is embedded in the library and does
    * not required any external data provider.
    * The test functions may assume that this data will
    * be unmodified forever by TA-LIB.
    */
   memset( &param, 0, sizeof( TA_AddDataSourceParam ) );
   param.id = TA_SIMULATOR;
   retCode = TA_AddDataSource( uDBase, &param );

   if( retCode != TA_SUCCESS )
   {
      printf( "TA_AddDataSource failed [%d]\n", retCode );
      freeLib( libHandle, uDBase );
      return TA_REGTEST_ADDDATASOURCE_FAILED;
   }

   /* Regression testing of the functionality provided
    * by ta_period.c
    */
   retValue = test_period( uDBase );
   if( retValue != TA_TEST_PASS )
   {
      freeLib( libHandle, uDBase );
      return retValue;
   }

   /* Allocate the reference historical data. */
   retCode = TA_HistoryAlloc( uDBase, 
                              "TA_SIM_REF", "DAILY_REF_0",
                              TA_DAILY, 0, 0, TA_ALL,
                              &history );

   if( retCode != TA_SUCCESS )
   {
      printf( "TA_HistoryAlloc failed [%d]\n", retCode );
      freeLib( libHandle, uDBase );
      return TA_REGTEST_HISTORYALLOC_FAILED;
   }

   /* Perform testing of each of the TA Functions. */
   retValue = testTAFunction_ALL( libHandle, history );
   if( retValue != TA_TEST_PASS )
   {
      TA_HistoryFree( history );
      freeLib( libHandle, uDBase );
      return retValue;
   }

   /* Clean-up and exit. */

   retCode = TA_HistoryFree( history );
   if( retCode != TA_SUCCESS )
   {
      printf( "TA_HistoryFree failed [%d]\n", retCode );
      freeLib( libHandle, uDBase );
      return TA_REGTEST_HISTORYFREE_FAILED;
   }


   retValue = freeLib( libHandle, uDBase );
   if( retValue != TA_TEST_PASS )
      return retValue;

   return TA_TEST_PASS; /* All test succeed. */
}

static int testTAFunction_ALL( TA_Libc *libHandle, TA_History *history )
{
   ErrorNumber retValue;

   printf( "Testing the TA functions\n" );

   initGlobalBuffer();

   /* Just validate that the history is not too big for the
    * global temporary buffers used troughout the testing.
    */
   if( history->nbBars >= MAX_NB_TEST_ELEMENT )
   {
      printf( "Buffer too small to proceed with tests [%d >= %d]\n",
              history->nbBars, MAX_NB_TEST_ELEMENT );
      return -1;
   }

   /* Make tests for each TA functions. */

   #define PRINTF_TEST_HDR      printf( "    %22s: Testing...", TEST_ID );
   #define PRINTF_TEST_SUCCESS  printf( "done.\n" );

   /* Test MOM and ROC function */
   #define TEST_ID "MOM,ROC,ROCR"
   PRINTF_TEST_HDR;
   retValue = test_func_mom_roc( libHandle, history );
   if( retValue != TA_TEST_PASS )
      return retValue;
   PRINTF_TEST_SUCCESS;
   #undef TEST_ID

   /* Test RSI */
   #define TEST_ID "RSI"
   PRINTF_TEST_HDR;
   retValue = test_func_rsi( libHandle, history );
   if( retValue != TA_TEST_PASS )
      return retValue;
   PRINTF_TEST_SUCCESS;
   #undef TEST_ID

   /* Test min/max functions. */
   #define TEST_ID "MIN,MAX,"
   PRINTF_TEST_HDR;
   retValue = test_func_minmax( libHandle, history );
   if( retValue != TA_TEST_PASS )
      return retValue;
   PRINTF_TEST_SUCCESS;
   #undef TEST_ID

   /* Test all moving averages functions. */
   #define TEST_ID "All Moving Averages"
   PRINTF_TEST_HDR;
   retValue = test_func_ma( libHandle, history );
   if( retValue != TA_TEST_PASS )
      return retValue;
   PRINTF_TEST_SUCCESS;
   #undef TEST_ID

   /* Test TRANGE and ATR functions. */
   #define TEST_ID "TRANGE,ATR"
   PRINTF_TEST_HDR;   
   retValue = test_func_trange( libHandle, history );
   if( retValue != TA_TEST_PASS )
      return retValue;
   PRINTF_TEST_SUCCESS;
   #undef TEST_ID

   /* Test Price Oscillator */
   #define TEST_ID "PO,APO"
   PRINTF_TEST_HDR;
   retValue = test_func_po( libHandle, history );
   if( retValue != TA_TEST_PASS )
      return retValue;
   PRINTF_TEST_SUCCESS;
   #undef TEST_ID

   /* Test MACD and MACDFIX functions */
   #define TEST_ID "MACD,MACDFIX"
   PRINTF_TEST_HDR;
   retValue = test_func_macd( libHandle, history );
   if( retValue != TA_TEST_PASS )
      return retValue;
   PRINTF_TEST_SUCCESS;
   #undef TEST_ID

   /* Test STDDEV and VAR functions */
   #define TEST_ID "STDDEV,VAR"
   PRINTF_TEST_HDR;
   retValue = test_func_stddev( libHandle, history );
   if( retValue != TA_TEST_PASS )
      return retValue;
   PRINTF_TEST_SUCCESS;
   #undef TEST_ID

   /* Test BBANDS function */
   #define TEST_ID "BBANDS"
   PRINTF_TEST_HDR;
   retValue = test_func_bbands( libHandle, history );
   if( retValue != TA_TEST_PASS )
      return retValue;
   PRINTF_TEST_SUCCESS;
   #undef TEST_ID

   /* Test stochastic */
   #define TEST_ID "STOCH"
   PRINTF_TEST_HDR;
   retValue = test_func_stoch( libHandle, history );
   if( retValue != TA_TEST_PASS )
      return retValue;
   PRINTF_TEST_SUCCESS;
   #undef TEST_ID

   /* Test TRIX */
   #define TEST_ID "TRIX"
   PRINTF_TEST_HDR;
   retValue = test_func_per_ema( libHandle, history );
   if( retValue != TA_TEST_PASS )
      return retValue;
   PRINTF_TEST_SUCCESS;
   #undef TEST_ID

   /* Test a group of simple functions just taking a "period" as parameter. */
   #define TEST_ID "CCI"
   PRINTF_TEST_HDR;
   retValue = test_func_per_hlc( libHandle, history );
   if( retValue != TA_TEST_PASS )
      return retValue;
   PRINTF_TEST_SUCCESS;
   #undef TEST_ID
      
   return TA_TEST_PASS; /* All test succeed. */
}

static ErrorNumber testHistoryAlloc( void )
{
   TA_Libc *libHandle;
   TA_UDBase *unifiedDatabase;
   TA_History *data;
   TA_RetCode retCode;
   TA_InitializeParam param;
   TA_AddDataSourceParam addParam;

   memset( &param, 0, sizeof( TA_InitializeParam ) );
   param.logOutput = stdout;
   retCode = TA_Initialize( &libHandle, &param );

   if( retCode != TA_SUCCESS )
   {
      printf( "Cannot initialize TA-LIB (%d)!", retCode );
      return TA_REGTEST_HISTORYALLOC_0;
   }

   /* Create an unified database. */
   if( TA_UDBaseAlloc( libHandle, &unifiedDatabase ) != TA_SUCCESS )
   {
      TA_Shutdown( libHandle );
      return TA_REGTEST_HISTORYALLOC_1;
   }

   
   /* USE SIMULATOR DATA */
   memset( &addParam, 0, sizeof( TA_AddDataSourceParam ) );
   addParam.id = TA_SIMULATOR;

   addParam.flags = TA_NO_FLAGS;
   retCode = TA_AddDataSource( unifiedDatabase, &addParam );

   /* Now, display all daily close price available
    * for the DAILY_REF_0 symbol.
    */
   if( retCode != TA_SUCCESS )
      return TA_REGTEST_ADDDSOURCE_FAILED;
   
   #define CHECK_FIELDSUBSET(field) \
            retCode = TA_HistoryAlloc( unifiedDatabase, \
                                       "TA_SIM_REF", "DAILY_REF_0", \
                                       TA_DAILY, 0, 0, \
                                       field, &data ); \
            if( retCode == TA_SUCCESS ) \
            { \
               if( (field) & TA_OPEN ) \
               { \
                  if( !data->open ) \
                     return TA_REGTEST_HISTORYALLOC_2; \
                  if( data->open[0] != 92.5 ) \
                     return TA_REGTEST_HISTORYALLOC_3; \
               } \
               else \
               { \
                  if( data->open ) \
                     return TA_REGTEST_HISTORYALLOC_4; \
               } \
               if( (field) & TA_HIGH ) \
               { \
                  if( !data->high ) \
                     return TA_REGTEST_HISTORYALLOC_5; \
                  if( data->high[0] != 93.25 ) \
                     return TA_REGTEST_HISTORYALLOC_6; \
               } \
               else \
               { \
                  if( data->high ) \
                     return TA_REGTEST_HISTORYALLOC_7; \
               } \
               if( (field) & TA_LOW ) \
               { \
                  if( !data->low ) \
                     return TA_REGTEST_HISTORYALLOC_8; \
                  if( data->low[0] != 90.75 ) \
                     return TA_REGTEST_HISTORYALLOC_9; \
               } \
               else \
               { \
                  if( data->low ) \
                     return TA_REGTEST_HISTORYALLOC_10; \
               } \
               if( (field) & TA_CLOSE ) \
               { \
                  if( !data->close ) \
                     return TA_REGTEST_HISTORYALLOC_11; \
                  if( data->close[0] != 91.50 ) \
                     return TA_REGTEST_HISTORYALLOC_12; \
               } \
               else \
               { \
                  if( data->close ) \
                     return TA_REGTEST_HISTORYALLOC_13; \
               } \
               if( (field) & TA_VOLUME ) \
               { \
                  if( !data->volume ) \
                     return TA_REGTEST_HISTORYALLOC_14; \
                  if( data->volume[0] != 4077500) \
                     return TA_REGTEST_HISTORYALLOC_15; \
               } \
               else \
               { \
                  if( data->volume ) \
                     return TA_REGTEST_HISTORYALLOC_16; \
               } \
               if( (field) & TA_TIMESTAMP ) \
               { \
                  if( !data->timestamp ) \
                     return TA_REGTEST_HISTORYALLOC_17; \
               } \
               else \
               { \
                  if( data->timestamp ) \
                     return TA_REGTEST_HISTORYALLOC_18; \
               } \
               TA_HistoryFree( data ); \
            } \
            else \
            { \
               printf( "Cannot TA_HistoryAlloc for TA_SIM_REF (%d)!", retCode ); \
               return TA_REGTEST_HISTORYALLOC_19; \
            }

         /* 6 Fields */
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_CLOSE|TA_HIGH|TA_LOW|TA_VOLUME)

         /* 5 Fields */
         CHECK_FIELDSUBSET(TA_OPEN|TA_CLOSE|TA_HIGH|TA_LOW|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_CLOSE|TA_HIGH|TA_LOW|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_HIGH|TA_LOW|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_CLOSE|TA_LOW|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_CLOSE|TA_HIGH|TA_VOLUME)

         /* 4 Fields */
         CHECK_FIELDSUBSET(TA_CLOSE|TA_HIGH|TA_LOW|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_OPEN|TA_HIGH|TA_LOW|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_OPEN|TA_CLOSE|TA_LOW|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_OPEN|TA_CLOSE|TA_HIGH|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_OPEN|TA_CLOSE|TA_HIGH|TA_LOW)

         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_HIGH|TA_LOW|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_CLOSE|TA_LOW|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_CLOSE|TA_HIGH|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_CLOSE|TA_HIGH|TA_LOW)

         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_LOW|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_HIGH|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_HIGH|TA_LOW)

         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_CLOSE|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_CLOSE|TA_LOW)

         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_CLOSE|TA_HIGH)

         /* 3 Fields */
         CHECK_FIELDSUBSET(TA_HIGH|TA_LOW|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_CLOSE|TA_LOW|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_CLOSE|TA_HIGH|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_CLOSE|TA_HIGH|TA_LOW)

         CHECK_FIELDSUBSET(TA_OPEN|TA_LOW|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_OPEN|TA_HIGH|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_OPEN|TA_HIGH|TA_LOW)

         CHECK_FIELDSUBSET(TA_OPEN|TA_CLOSE|TA_VOLUME)
         CHECK_FIELDSUBSET(TA_OPEN|TA_CLOSE|TA_LOW)

         CHECK_FIELDSUBSET(TA_OPEN|TA_CLOSE|TA_HIGH)

         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_HIGH)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_LOW)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_CLOSE)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN|TA_VOLUME)

         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_HIGH|TA_LOW)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_HIGH|TA_CLOSE)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_HIGH|TA_VOLUME)

         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_LOW|TA_CLOSE)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_LOW|TA_VOLUME)

         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_CLOSE|TA_VOLUME)

         /* Two field. */
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_OPEN)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_HIGH)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_LOW)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_CLOSE)
         CHECK_FIELDSUBSET(TA_TIMESTAMP|TA_VOLUME)

         CHECK_FIELDSUBSET(TA_OPEN|TA_HIGH)
         CHECK_FIELDSUBSET(TA_OPEN|TA_LOW)
         CHECK_FIELDSUBSET(TA_OPEN|TA_CLOSE)
         CHECK_FIELDSUBSET(TA_OPEN|TA_VOLUME)

         CHECK_FIELDSUBSET(TA_HIGH|TA_LOW)
         CHECK_FIELDSUBSET(TA_HIGH|TA_CLOSE)
         CHECK_FIELDSUBSET(TA_HIGH|TA_VOLUME)

         CHECK_FIELDSUBSET(TA_LOW|TA_CLOSE)
         CHECK_FIELDSUBSET(TA_LOW|TA_VOLUME)

         CHECK_FIELDSUBSET(TA_CLOSE|TA_VOLUME)

         /* One Field */
         CHECK_FIELDSUBSET(TA_TIMESTAMP);
         CHECK_FIELDSUBSET(TA_OPEN);
         CHECK_FIELDSUBSET(TA_HIGH)
         CHECK_FIELDSUBSET(TA_LOW)
         CHECK_FIELDSUBSET(TA_CLOSE)
         CHECK_FIELDSUBSET(TA_VOLUME)

   #undef CHECK_FIELDSUBSET

   /* Clean-up and exit. */
   TA_UDBaseFree( unifiedDatabase );
   TA_Shutdown( libHandle );
   return TA_SUCCESS;
}
