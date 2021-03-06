#ifndef TA_CSI_H
#define TA_CSI_H

#ifndef TA_SOURCE_H
   #include "ta_source.h"
#endif

#ifndef TA_DATA_UDB_H
   #include "ta_data_udb.h"
#endif

/* See ta_source.h and ta_source.c for more information about these
 * functions.
 */
TA_RetCode TA_CSI_InitializeSourceDriver( void );

TA_RetCode TA_CSI_ShutdownSourceDriver( void );

TA_RetCode TA_CSI_GetParameters( TA_DataSourceParameters *param );

TA_RetCode TA_CSI_OpenSource( const TA_AddDataSourceParamPriv *param,
                              TA_DataSourceHandle **handle );

TA_RetCode TA_CSI_CloseSource( TA_DataSourceHandle *handle );


TA_RetCode TA_CSI_GetFirstCategoryHandle( TA_DataSourceHandle *handle,
                                          TA_CategoryHandle   *categoryHandle );

TA_RetCode TA_CSI_GetFirstSymbolHandle( TA_DataSourceHandle *handle,
                                        TA_CategoryHandle   *categoryHandle,
                                        TA_SymbolHandle     *symbolHandle );

TA_RetCode TA_CSI_GetNextSymbolHandle( TA_DataSourceHandle *handle,
                                       TA_CategoryHandle   *categoryHandle,
                                       TA_SymbolHandle     *symbolHandle,
                                       unsigned int index );

TA_RetCode TA_CSI_GetHistoryData( TA_DataSourceHandle *handle,
                                  TA_CategoryHandle   *categoryHandle,
                                  TA_SymbolHandle     *symbolHandle,
                                  TA_Period            period,
                                  const TA_Timestamp  *start,
                                  const TA_Timestamp  *end,
                                  TA_Field             fieldToAlloc,
                                  TA_ParamForAddData  *paramForAddData );

TA_RetCode TA_CSIM_InitializeSourceDriver( void );

TA_RetCode TA_CSIM_ShutdownSourceDriver( void );

TA_RetCode TA_CSIM_GetParameters( TA_DataSourceParameters *param );

TA_RetCode TA_CSIM_OpenSource( const TA_AddDataSourceParamPriv *param,
                              TA_DataSourceHandle **handle );

TA_RetCode TA_CSIM_CloseSource( TA_DataSourceHandle *handle );


TA_RetCode TA_CSIM_GetFirstCategoryHandle( TA_DataSourceHandle *handle,
                                          TA_CategoryHandle   *categoryHandle );

TA_RetCode TA_CSIM_GetFirstSymbolHandle( TA_DataSourceHandle *handle,
                                        TA_CategoryHandle   *categoryHandle,
                                        TA_SymbolHandle     *symbolHandle );

TA_RetCode TA_CSIM_GetNextSymbolHandle( TA_DataSourceHandle *handle,
                                       TA_CategoryHandle   *categoryHandle,
                                       TA_SymbolHandle     *symbolHandle,
                                       unsigned int index );

TA_RetCode TA_CSIM_GetHistoryData( TA_DataSourceHandle *handle,
                                  TA_CategoryHandle   *categoryHandle,
                                  TA_SymbolHandle     *symbolHandle,
                                  TA_Period            period,
                                  const TA_Timestamp  *start,
                                  const TA_Timestamp  *end,
                                  TA_Field             fieldToAlloc,
                                  TA_ParamForAddData  *paramForAddData );

#endif

