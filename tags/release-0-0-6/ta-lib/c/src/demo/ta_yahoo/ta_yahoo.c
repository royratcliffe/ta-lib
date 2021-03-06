/* Simple application for accessing Yahoo! Web Site using TA-LIB. */

/* To see how data is fetched from Yahoo! see print_data(). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ta_libc.h"

typedef enum
{
   DISPLAY_SYMBOLS,
   DISPLAY_CATEGORIES,
   DISPLAY_HISTORIC_DATA
} Action;

void print_usage( char *str ) 
{
   printf( "\n" );
   printf( "ta_yahoo V%s - Fetch stock market data from Yahoo!\n", TA_GetVersionString() );
   printf( "\n" );
   printf( "Usage: ta_yahoo -c\n" );
   printf( "       ta_yahoo -s <category>\n" );
   printf( "       ta_yahoo -d{d,w,m,q,y} <category> <symbol>\n" );
   printf( "\n" );
   printf( "  -c  Display all supported categories\n" );
   printf( "  -s  Display all symbols for a given category\n" );
   printf( "  -dd Fetch and display daily data\n" );
   printf( "  -dw Fetch and display weekly data\n" );
   printf( "  -dm Fetch and display monthly data\n" );
   printf( "  -dq Fetch and display quarterly data\n" );
   printf( "  -dy Fetch and display yearly data\n" );
   printf( "\n" );
   printf( "  Stock output is \"Date,Open,High,Low,Close,Volume\"\n" );
   printf( "  Funds output is \"Date,Close\". Date are \"mm-dd-yyyy\"\n" );
   printf( "\n" );
   printf( "  Examples: ta_yahoo -s US.NASDAQ.FUND\n" );
   printf( "            ta_yahoo -dd US.NASDAQ.STOCK MSFT\n" );
   printf( "\n" );
   printf( "  This utility may create files \"y_xx.dat\" to speed\n" );
   printf( "  up subsequent remote access. These are automatically\n" );
   printf( "  re-generated and can be safely deleted.\n" );
   printf( "\n" );
   printf( "  * Data cannot be resdistributed. You must respect\n" );
   printf( "  * Yahoo! terms of service (www.yahoo.com)\n" );
   printf( "\n" );
   printf( "  Online help: http://www.ta-lib.org\n" );
   printf( "\n" );
   printf( "Error: [%s]\n", str );
}

void print_error( TA_RetCode retCode )
{
   TA_RetCodeInfo retCodeInfo;

   TA_SetRetCodeInfo( retCode, &retCodeInfo );
   printf( "\nError %d=%s:[%s]\n", retCode,
           retCodeInfo.enumStr,
           retCodeInfo.infoStr );
}

int print_data( TA_UDBase *udb,
                const char *country,
                const char *category,
                const char *symbol,
                TA_Period period )
{
   TA_RetCode retCode;
   TA_AddDataSourceParam addSourceParam;
   TA_History *history;
   unsigned int i;

   /* Setup Yahoo! datasource. */
   memset( &addSourceParam, 0, sizeof( TA_AddDataSourceParam ) );
   addSourceParam.id = TA_YAHOO_WEB;
   addSourceParam.location = country;
   retCode = TA_AddDataSource( udb, &addSourceParam );
   if( retCode != TA_SUCCESS )
   {
      print_error( retCode );
      return -1;
   }

   /* Get the historical data. */
   retCode = TA_HistoryAlloc( udb, category, symbol,
                              period, 0, 0, TA_ALL,
                              &history );
   if( retCode != TA_SUCCESS )
   {
      print_error( retCode );
      return -1;
   }

   if( history->nbBars == 0 )
   {
      printf( "No data available" );
   }
   else
   {
      for( i=0; i < history->nbBars; i++ )
      {
         printf( "%d-%d-%d", TA_GetMonth(&history->timestamp[i]),
                             TA_GetDay(&history->timestamp[i]),
                             TA_GetYear(&history->timestamp[i]) );
         if( history->open )
            printf( ",%.2f", history->open[i] );
         if( history->high )
            printf( ",%.2f", history->high[i] );
         if( history->low )
            printf( ",%.2f", history->low[i] );
         if( history->close )
            printf( ",%.2f", history->close[i] );
         if( history->volume )
            printf( ",%d", history->volume[i] );
         printf( "\n" );
      }
   }

   /* Get ride of the historical data and return. */
   TA_HistoryFree( history );

   return 0;
}


int print_categories( TA_UDBase *udb )
{
   TA_RetCode retCode;
   TA_AddDataSourceParam addYahooParam;
   unsigned int i;
   TA_StringTable *table;
   const char *listCountry[] = {"US","CA","UK","DE","ES","FR","IT","NO","SE",NULL};

   memset( &addYahooParam, 0, sizeof( TA_AddDataSourceParam ) );
   addYahooParam.id = TA_YAHOO_WEB;

   i=0;
   while( listCountry[i++] != NULL )
   {
      addYahooParam.location = listCountry[i];
      retCode = TA_AddDataSource( udb, &addYahooParam );
      if( retCode != TA_SUCCESS )
      {
         print_error( retCode );
         return -1;
      }
   }
   
   retCode = TA_CategoryTableAlloc( udb, &table );
   if( retCode != TA_SUCCESS )
   {
      print_error( retCode );
      return -1;
   } 

   for( i=0; i < table->size; i++ )
   {
      if( strcmp( table->string[i], "ZZ.OTHER.OTHER" ) )
         printf( "%s\n", table->string[i] );
   }

   TA_CategoryTableFree( table );

   return 0;
}

int print_symbols( TA_UDBase *udb,
                   const char *country,
                   const char *category )
{
   TA_RetCode retCode;
   TA_AddDataSourceParam addYahooParam;
   unsigned int i;
   TA_StringTable *table;

   memset( &addYahooParam, 0, sizeof( TA_AddDataSourceParam ) );
   addYahooParam.id = TA_YAHOO_WEB;
   addYahooParam.location = country;

   retCode = TA_AddDataSource( udb, &addYahooParam );
   if( retCode != TA_SUCCESS )
   {
      print_error( retCode );
      return -1;
   }

   retCode = TA_SymbolTableAlloc( udb, category, &table );
   if( retCode != TA_SUCCESS )
   {
      print_error( retCode );
      return -1;
   } 

   for( i=0; i < table->size; i++ )
   {
      /* Display all categories... except the default one. */
      if( strcmp( table->string[i], "ZZ.OTHER.OTHER" ) )
         printf( "%s\n", table->string[i] );
   }

   TA_SymbolTableFree( table );
  
   return 0;
}

int main( int argc, char *argv[] )
{
   Action theAction;
   TA_InitializeParam initParam;
   TA_Libc *libHandle;
   TA_UDBase *udb;
   TA_RetCode retCode;
   TA_Period period;

   int retValue;
   unsigned int i, stringSize;

   char country[TA_CAT_COUNTRY_MAX_LENGTH+1];
   char category[TA_CATEGORY_MAX_LENGTH+1];
   char symbol[TA_SYMBOL_MAX_LENGTH+1];

   /* Verify that there is the minimum required number 
    * of parameters.
    */
   if( argc < 2 )
   {
      print_usage( "Missing parameters" );
      return -1;
   }

   /* Verify that there are not too many parameters */
   if( argc > 4 )
   {
      print_usage( "Too Many parameters" );
      return -1;
   }

   /* Daily data by default. */
   period = TA_DAILY;

   /* Check for the switch, and identify what needs to be done. */
   if( strcmp( "-c", argv[1] ) == 0 )
      theAction = DISPLAY_CATEGORIES;
   else if( strcmp( "-s", argv[1] ) == 0 )
      theAction = DISPLAY_SYMBOLS;
   else if( strcmp( "-d", argv[1] ) == 0 )
      theAction = DISPLAY_HISTORIC_DATA;
   else if( strcmp( "-dd", argv[1] ) == 0 )
      theAction = DISPLAY_HISTORIC_DATA;
   else if( strcmp( "-dw", argv[1] ) == 0 )
   {
      theAction = DISPLAY_HISTORIC_DATA;
      period = TA_WEEKLY;
   }
   else if( strcmp( "-dm", argv[1] ) == 0 )
   {
      theAction = DISPLAY_HISTORIC_DATA;
      period = TA_MONTHLY;
   }
   else if( strcmp( "-dq", argv[1] ) == 0 )
   {
      theAction = DISPLAY_HISTORIC_DATA;
      period = TA_QUARTERLY;
   }
   else if( strcmp( "-dy", argv[1] ) == 0 )
   {
      theAction = DISPLAY_HISTORIC_DATA;
      period = TA_YEARLY;
   }
   else
   {
      print_usage( "Switch not recognized" );
      return -1;
   }

   /* Verify that there is at least a symbol and category 
    * on the command line (when applicable).
    */
   switch( theAction )
   {
   case DISPLAY_SYMBOLS:
   case DISPLAY_HISTORIC_DATA:
      if( argc < 3 )
      {
         print_usage( "Category string missing" );
         return -1;
      }
      break;
   case DISPLAY_CATEGORIES:
      /* Nothing to do. */
      break;
   }

   if( theAction == DISPLAY_HISTORIC_DATA )
   {
      if( argc < 4 )
      {
         print_usage( "Symbol string missing" );
         return -1;
      }
   }

   /* Identify country when needed. */
   switch( theAction )
   {
   case DISPLAY_HISTORIC_DATA:
   case DISPLAY_SYMBOLS:
      country[0] = argv[2][0];
      country[1] = argv[2][1];
      country[2] = '\0';
      break;
   case DISPLAY_CATEGORIES:
      country[0] = '\0';
   }

   /* Initialize TA-LIB and create an unified database. */
   memset( &initParam, 0, sizeof( TA_InitializeParam ) );
   initParam.userLocalDrive = ".";

   retCode = TA_Initialize( &libHandle, &initParam );
   if( retCode != TA_SUCCESS )
   {
      print_error( retCode );
      return -1;
   }

   retCode = TA_UDBaseAlloc( libHandle, &udb );
   if( retCode != TA_SUCCESS )
   {
      print_error( retCode );
      TA_Shutdown( libHandle );
      return -1;
   }

   /* Do 'theAction' after making an uppercase copy
    * of the symbol and category.
    */
   switch( theAction )
   {
   case DISPLAY_HISTORIC_DATA:       
       stringSize = strlen(argv[2]);
       if( stringSize > TA_CATEGORY_MAX_LENGTH )
          stringSize = TA_CATEGORY_MAX_LENGTH;
       for( i=0; i < stringSize; i++ )
          category[i] = toupper(argv[2][i]);
       category[stringSize] = '\0';

       stringSize = strlen(argv[3]);
       if( stringSize > TA_SYMBOL_MAX_LENGTH )
          stringSize = TA_SYMBOL_MAX_LENGTH;
       for( i=0; i < stringSize; i++ )
          symbol[i] = toupper(argv[3][i]);
       symbol[stringSize] = '\0';

       retValue = print_data(udb,country,category,symbol,period);
       break;

   case DISPLAY_SYMBOLS:
       stringSize = strlen(argv[2]);
       if( stringSize > TA_CATEGORY_MAX_LENGTH )
          stringSize = TA_CATEGORY_MAX_LENGTH;
       for( i=0; i < stringSize; i++ )
          category[i] = toupper(argv[2][i]);
       category[stringSize] = '\0';

       retValue = print_symbols(udb,country,category);
       break;
   case DISPLAY_CATEGORIES:
       retValue = print_categories(udb);
       break;
   default:
       retValue = -1;
       break;
   }

   /* Clean-up and exit. */
   TA_UDBaseFree( udb );
   TA_Shutdown( libHandle );
   return retValue;
}
