#ifndef TA_TEST_PRIV_H
#define TA_TEST_PRIV_H

#ifndef TA_LIBC_H
   #include "ta_libc.h"
#endif

#ifndef TA_ERROR_NUMBER_H
   #include "ta_error_number.h"
#endif

ErrorNumber test_period( TA_UDBase *unifiedDatabase );
ErrorNumber test_ascii ( void );
ErrorNumber test_yahoo ( void );
ErrorNumber test_pm    ( void );
ErrorNumber test_datasource_merge( void );

ErrorNumber freeLib( TA_Libc *libHandle, TA_UDBase  *uDBase );
ErrorNumber allocLib( TA_Libc **libHandlePtr, TA_UDBase **uDBasePtr );

void reportError( const char *str, TA_RetCode retCode );

/* Global Temporary Used by the ta_func_xxx function. */
 

typedef struct
{
   TA_Real *in;

   TA_Real *out0;
   TA_Real *out1;
   TA_Real *out2;
} TestBuffer;


/* That's quite a lot of global data, but who cares for
 * regression testing... it simplify memory alloc/dealloc.
 */
#define NB_GLOBAL_BUFFER 5
extern TestBuffer gBuffer[NB_GLOBAL_BUFFER];

/* Maximum number of element that can be written
 * at a gBuffer[n].ptr
 */
#define MAX_NB_TEST_ELEMENT 280

/* Must be called once to initialize the gBuffer. */
void initGlobalBuffer( void );

/* Will set to NAN all elements of gBuffer. */
void clearAllBuffers( void );

/* Initialize the 'gBuffer[i].in' with the provided data. */
void setInputBuffer( unsigned int i, const TA_Real *data, unsigned int nbElement );

/* Check that a buffer (within a TestBuffer) is not containing
 * NAN within the specified range (it also checks that all value
 * outside the range are untouched).
 *
 * Return TA_TEST_PASS if all ok.
 */
ErrorNumber checkForNAN( const TA_Real *buffer,
                         unsigned int nbElement );

/* Check that the 'data' is equal to the provided 
 * originalInput.
 *
 * The data must be one of the 'gBuffer[n].buffer'.
 *
 * It is also checked that all value outside of the
 * nbElement range are not-a-number.
 *
 * Return TA_TEST_PASS if no difference are found.
 */
ErrorNumber checkDataSame( const TA_Real *data,
                           const TA_Real *originalInput,
                           unsigned int nbElement );

/* Check that the content of the first buffer
 * is found in the second buffer (when the elements
 * in the first buffer is NAN, no check is done for
 * this paricular element).
 *
 * Return TA_TEST_PASS if no difference are found.
 */
ErrorNumber checkSameContent( TA_Real *buffer1,
                              TA_Real *buffer2 );

ErrorNumber checkExpectedValue( const TA_Real *data,
                                TA_RetCode retCode, TA_RetCode expectedRetCode,
                                unsigned int outBegIdx, unsigned int expectedBegIdx,
                                unsigned int outNbElement, unsigned int expectedNbElement,
                                TA_Real oneOfTheExpectedOutReal,
                                unsigned int oneOfTheExpectedOutRealIndex );

#define CHECK_EXPECTED_VALUE(bufid,id) \
   { \
      errNb = checkExpectedValue( bufid, \
                                  retCode, test->expectedRetCode, \
                                  outBegIdx, test->expectedBegIdx, \
                                  outNbElement, test->expectedNbElement, \
                                  test->oneOfTheExpectedOutReal##id, \
                                  test->oneOfTheExpectedOutRealIndex##id );  \
      if( errNb != TA_TEST_PASS ) \
      { \
         printf( "Fail for output id=%d\n", id ); \
         return errNb; \
      } \
   }

#define CLEAR_EXPECTED_VALUE(id) \
   { \
      retCode = TA_UNKNOWN_ERR; \
      outBegIdx = 0;\
      outNbElement = 0;\
   }


/* A systematic test can be done for most of the possible
 * range that a TA function can be called with. This test
 * is common to all TA function and can be easily done
 * with a RangeTestFunction. 
 *
 * The RangeTestFunction is making abstraction of the
 * TA function (handles the inputs, the parameters etc...)
 * The RangeTestFunction must call the TA function for
 * the requested startIdx/endIdx range and put the output
 * in the provided buffer.
 * 
 * The RangeTestFunction must also set the outBegIdx and
 * outNbElement for verification.
 *
 * Opaque data (for mostly passing optional parameters) are
 * pass through the pointer 'void * opaqueData'.
 */

#define MAX_RANGE_SIZE 252
#define MAX_RANGE_END  (MAX_RANGE_SIZE-1)

typedef TA_RetCode (*RangeTestFunction)( TA_Libc *libHandle, 
                                         TA_Integer startIdx,
                                         TA_Integer endIdx,
                                         TA_Real *outputBuffer,
                                         TA_Integer *outBegIdx,
                                         TA_Integer *outNbElement,
                                         TA_Integer *lookback,
                                         void *opaqueData,
                                         unsigned int outputNb );

ErrorNumber doRangeTest( TA_Libc *libHandle,
                         RangeTestFunction testFunction,
                         TA_FuncUnstId unstId,
                         void *opaqueData,
                         unsigned int nbOutput );

/* Compare two TA_Real and verify that they are
 * identiqual within the specified epsilon.
 */
#define TA_REAL_EQ(x,v,EPSILON) (((v - EPSILON) < x) && (x <( v + EPSILON)))

/* Print out info about a retCode */
void printRetCode( TA_RetCode retCode );

#endif

