/*
 * LCADRF.H - External include file for the API that provides access methods
 * supporting the LonMark Device Resource Files, read-only access and catalog.
 *
 * Copyright (C) 1996 - 2012 Echelon Corporation.  All rights reserved.
 *
 * Use of this source code is subject to the terms of the Echelon Example Software
 * License Agreement which is available at www.echelon.com/license/examplesoftware/.
 *
 * Implementation by RLE
 */


#ifndef _LCADRF
#define _LCADRF


#ifdef __cplusplus
extern "C" {
#endif



// Beginning of platform-specific, conditionally compiled code
// Three #define symbols control the conditionally compiled code:
// _WINDOWS_ - is automatically defined in the Windows environment
// LCADRF_INTERNAL - is automatically defined in the DRF API source code,
//	and it should not appear elsewhere
// STATIC_DRF_LIB - is not normally defined in the Windows environment
//	but can be defined if you want to compile & use the source code
//	as a static library included in the program, rather than as a DLL.
//	The benefits of DLL usage include automatic upgrade & compatibility
//	if file formats change, easier program maintenance (just update the
//	DLL), and other benefits.


#if defined(_WINDOWS_) || defined(_WINDOWS)

// This section is platform-specific for Windows only

#ifdef STATIC_DRF_LIB
    #define DLL_FN
#else
    #ifdef LCADRF_INTERNAL
	#define  DLL_FN    __declspec(dllexport) __stdcall
    #else
	#define  DLL_FN    __declspec(dllimport) __stdcall
    #endif
#endif

#define  LDRF_FN   TLdrfErrCodes DLL_FN


#else

// This section is for non-Windows only

#define  LDRF_FN   TLdrfErrCodes

#endif


#ifndef WINDOWS_TYPES
#define WINDOWS_TYPES
#if (!defined(_WINDOWS_))
typedef  char *		  LPSTR;
typedef  const char *	  LPCSTR;
#endif
#endif


// End of platform-specific code




/* This is the set of error codes that the Ldrf functions return */
typedef enum eLdrfErrCodes {
    LDRF_ERR_NONE = 0,
    LDRF_ERR_PARAM,
    LDRF_ERR_FILE_TYPE,
    LDRF_ERR_CRC,
    LDRF_ERR_NOT_FOUND,
    /* 5 */
    LDRF_ERR_FILE_INFO,
    LDRF_ERR_SYS,
    LDRF_ERR_TRUNC,
    LDRF_ERR_STALE,
    LDRF_ERR_VERSION,
    /* 10 */
    LDRF_ERR_FMT_VERSION,
    LDRF_ERR_NEW,
    LDRF_ERR_WRITE,
    LDRF_ERR_NO_ACCESS,
    LDRF_ERR_FULL,
    /* 15 */
    LDRF_ERR_DUPLICATE,
    LDRF_ERR_NOT_CATALOG,
    LDRF_ERR_NOT_RESOURCE,
    LDRF_ERR_NOT_TYPE,
    LDRF_ERR_NOT_FPT,
    /* 20 */
    LDRF_ERR_NOT_FORMAT,
    LDRF_ERR_TYPE_TREE,
    LDRF_ERR_INCOMPLETE,
    LDRF_ERR_SEQUENCE,
    LDRF_ERR_NOT_SELECTED,
    /* 25 */
    LDRF_ERR_NO_MORE_NODES,
    LDRF_ERR_INTERNAL,
    LDRF_ERR_UNIMPL,
    LDRF_ERR_STRING_SERVICE,
    LDRF_ERR_EMPTY_RECORD,
} TLdrfErrCodes;


/* This is the set of Device Resource File types */
typedef enum eLdrfFileType {
    LDRF_WILD_CARD = 0,
    LDRF_CATALOG = 1,
    LDRF_LANG_RESOURCE,
    LDRF_TYPE,
    LDRF_FPT,
    LDRF_FORMAT
} TLdrfFileType;


/* This is the set of NVTTypes available for type tree nodes */
typedef enum eNVTType {
    NVT_TYPE_UNKNOWN = 0,	/* Backward compatibility only */
    NVT_TYPE_SIGNED_CHAR,
    NVT_TYPE_UNSIGNED_CHAR,
    NVT_TYPE_SIGNED_SHORT,	/* (Neuron C - 8-bit) */
    NVT_TYPE_UNSIGNED_SHORT,	/* (Neuron C - 8-bit) */
    NVT_TYPE_SIGNED_LONG,	/* (Neuron C - 16-bit) */
    NVT_TYPE_UNSIGNED_LONG,	/* (Neuron C - 16-bit) */
    NVT_TYPE_ENUM,
    NVT_TYPE_ARRAY,
    NVT_TYPE_STRUCT,
    NVT_TYPE_UNION,
    NVT_TYPE_BITF,
    NVT_TYPE_FLOAT,		/* (Neuron C - 32-bit) */
    NVT_TYPE_SIGNED_QUAD,	/* (Neuron C - 32-bit) */
    NVT_TYPE_REFERENCE,
#define LAST_UNCONDITIONAL_TYPE (NVT_TYPE_REFERENCE)
    NVT_TYPE_UNSIGNED_QUAD,	/* (Neuron C - 32-bit) - Currently unsupported */
    NVT_TYPE_DOUBLE_FLOAT,	/* (Not supported in Neuron C - 64-bit float */
    NVT_TYPE_SIGNED_INT64, 
    NVT_TYPE_UNSIGNED_INT64,
/* Must stay last !! */
    FIRST_UNDEFINED_TYPE
} TNVTType;

#ifndef TBOOL_DEFINED
typedef enum eBool {
    F=0, T=1
} TBool;
#define TBOOL_DEFINED
#endif


typedef  unsigned char	 TUByte;
typedef  unsigned short  TUShort;
typedef  unsigned long	 TULong;

typedef  signed char	 TByte;
typedef  signed short	 TShort;
typedef  signed long	 TLong;

#ifndef TBOOLBYTE_DEFINED
typedef TUByte		TBoolByte;  /* Boolean	- stored in a byte */
#define TBOOLBYTE_DEFINED
#endif

typedef  struct sLdrfFileInfo	   TLdrfFileInfo;
typedef  struct sLdrfTypeTree	   TLdrfTypeTree;
typedef  struct sLdrfStringService TLdrfStringService;

// Structures used internally to support 64 bit values in the
// portable API *implementation*
typedef struct
{
    unsigned char  value[8];
} __drf_uint64;

typedef struct
{
    signed char   value[8];
} __drf_int64;

// Interface definitions for 64 bit values.  On hosts with native 
// 64 bit support, override the API definitions by defining __DRF_UINT64 
// and __DRF_INT64 prior to including lcaldrf.h.
#ifndef __DRF_UINT64
#  define   __DRF_UINT64   __drf_uint64
#endif // __DRF_UINT64
#define __DRF_PUINT64	   __DRF_UINT64*
#ifndef __DRF_INT64
#  define   __DRF_INT64    __drf_int64
#endif // __DRF_INT64
#define __DRF_PINT64	   __DRF_INT64*


typedef  TUByte *		PUByte;
typedef  TUByte *		PUByteArray;
typedef  TUShort *		PUShort;
typedef  TULong *		PULong;
typedef  TByte *		PByte;
typedef  TShort *		PShort;
typedef  TLong *		PLong;
typedef  TBool *		PBool;
typedef  TBoolByte *		PBoolByte;
typedef  TNVTType *		PNVTType;
typedef  TLdrfFileInfo *	PLdrfFileInfo;
typedef  TLdrfTypeTree *	PLdrfTypeTree;
typedef  TLdrfStringService *	PLdrfStringService;


/* These functions are used for basic and general file actions */

LDRF_FN LdrfCheckHeaderCRC  ( PLdrfFileInfo pInfo );

LDRF_FN LdrfCheckDataCRC    ( PLdrfFileInfo pInfo );

LDRF_FN LdrfCheckCRC	    ( PUByteArray pBlock, TULong size, TUShort oldCRC );

LDRF_FN LdrfSupportedFormats ( TLdrfFileType fileType,
			      PUByte pMajFmtLow, PUByte pMajFmtHigh );

LDRF_FN LdrfOpenFile	    ( LPCSTR path, TLdrfFileType fileType,
			      TUShort majorVersion, TBool checkCRC,
			      PLdrfFileInfo * ppInfo );

LDRF_FN LdrfEnableEmptyEntries ( PLdrfFileInfo pInfo );
LDRF_FN LdrfEnableExtendedSNVTID(PLdrfFileInfo pInfo);

LDRF_FN LdrfGetFileHdrInfo  ( PLdrfFileInfo pInfo, PBool pUser,
			      LPSTR pDesc, PUShort pDescLen,
			      LPSTR pCreator, PUShort pCreLen,
			      LPSTR pURL, PUShort pURLLen,
			      PUByte pResDescScope, PULong pResDescIndex,
			      PUByte pResCreScope,  PULong pResCreIndex );

LDRF_FN LdrfSetFileHdrInfo  ( PLdrfFileInfo pInfo,
			      LPCSTR creator, LPCSTR phone, LPCSTR webid, LPCSTR URL,
			      TUByte resDescScope, TULong resDescIndex,
			      TUByte resCreScope,  TULong resCreIndex );

LDRF_FN LdrfGetFileVersion  ( PLdrfFileInfo pInfo,
			      PUByte pMajorFmtVer,   PUByte pMinorFmtVer,
			      PUShort pMajorDataVer, PUByte pMinorDataVer,
			      PUShort pYear, PUByte pMonth, PUByte pDay,
			      PUByte pHour, PUByte pMinute, PUByte pSecond,
			      PUByte pScope, PUByteArray * ppRefID );

LDRF_FN LdrfSetFileVersion  ( PLdrfFileInfo pInfo,
			      TUShort majorDataVer, TUByte minorDataVer,
			      TUByte scope, PUByteArray pRefID);

LDRF_FN LdrfCloseFile	    ( PLdrfFileInfo pInfo );



/* These functions are used for miscellaneous operations */

LDRF_FN LdrfGetDRFAPIErrorString ( TLdrfErrCodes errCodeIn,
			      LPSTR pErrorString, PUShort pLength );

LDRF_FN LdrfGetDRFAPIVersion ( PUShort pMajor, PUShort pMinor, PUShort pFix );

LDRF_FN LdrfGetNextSupportedNVTType ( PLdrfFileInfo pInfo, PNVTType pNVTType );

LDRF_FN LdrfGetTypeNameString ( TNVTType nvtType,
			      LPSTR pTypeNameString, PUShort pLength );

LDRF_FN LdrfLookupTypeNameString ( LPCSTR pTypeNameString, PNVTType pNVTType );



/* These functions are used for Catalog access */

LDRF_FN LdrfOpenCatalog     ( LPCSTR directory, TBool readOnly, PLdrfFileInfo * ppInfo );

LDRF_FN LdrfGetCatalogInfo  ( PLdrfFileInfo pInfo, PBool pStale, PUShort pNumDirec,
			      PUShort pNumLangFiles, PUShort pNumTypeFiles,
			      PUShort pNumFPTFiles,  PUShort pNumFormatFiles );

LDRF_FN LdrfCloseCatalog    ( PLdrfFileInfo pInfo );

LDRF_FN LdrfCatalogAddDir   ( PLdrfFileInfo pInfo, LPCSTR newDir );

LDRF_FN LdrfCatalogGetDir   ( PLdrfFileInfo pInfo, TUShort index,
			      LPSTR pDirName, PUShort pLength );

LDRF_FN LdrfCatalogRmvDir   ( PLdrfFileInfo pInfo, LPCSTR oldDir );

LDRF_FN LdrfCatalogRefresh  ( PLdrfFileInfo pInfo );

LDRF_FN LdrfCatalogAddFile  ( PLdrfFileInfo pInfo, LPCSTR newFile );

LDRF_FN LdrfCatalogGetFile  ( PLdrfFileInfo pInfo, TLdrfFileType fileType, TUShort index,
			      PUByte pMatchScope, PUByteArray * ppProgID, PUShort pDirIndex,
			      PUShort pMajorVersion, PUByte pMinorVersion, PULong pLocale,
			      LPSTR pFileName, PUShort pLength );

LDRF_FN LdrfCatalogRmvFile  ( PLdrfFileInfo pInfo, LPCSTR oldFile );

LDRF_FN LdrfSearchCatalog   ( PLdrfFileInfo pInfo, PUByteArray pProgID,
			      TUByte matchScope, TLdrfFileType fileType,
			      TULong locale, LPSTR pFile, PUShort pLength,
			      PUShort pMajorVersion, PUByte pMinorVersion );

LDRF_FN LdrfMatchProgID     ( TUByte fileScope, PUByteArray pFileRefID, PUByteArray pProgID );

LDRF_FN LdrfCatalogDependencyCode ( PLdrfFileInfo pInfo, PUByteArray pProgID,
				    PULong pDepCode );



/* These functions are used for language/string resource file access */

LDRF_FN LdrfGetLangFileInfo    ( PLdrfFileInfo pInfo,
				 PULong pLocale, PULong pNumResources );

LDRF_FN LdrfGetResourceString  ( PLdrfFileInfo pInfo, TULong index,
				 LPSTR pString, PUShort pLength );

LDRF_FN LdrfValidateResourceString ( PLdrfFileInfo pInfo, TULong index );

LDRF_FN LdrfFindEmptyResourceString ( PLdrfFileInfo pInfo, PULong pIndex );

LDRF_FN LdrfGetNumLanguages    ( LPCSTR pInfDirectory, PUShort pNumLanguages );

LDRF_FN LdrfGetLanguageInfo    ( LPCSTR pInfDirectory, TULong myLocale,
				 TUShort key, LPCSTR pCatDirectory,
				 PULong pMSLocaleID, PULong pLocale,
				 PUByteArray pFileExtension,
				 LPSTR pString, PUShort pLength );

LDRF_FN LdrfGetLanguageKeyFromLocale ( LPCSTR pInfDirectory,
				 TULong locale, PUShort pKey );

LDRF_FN LdrfGetLanguageKeyFromMSLocaleID ( LPCSTR infDirectory,
				 TULong MSLocaleID, PUShort pKey );

LDRF_FN LdrfGetLanguageKeyFromExtension ( LPCSTR pInfDirectory,
				 PUByteArray fileExtension, PUShort pKey );

LDRF_FN LdrfStartStringService ( TULong locale, LPCSTR directory,
				 PLdrfStringService * ppService );

LDRF_FN LdrfAddStringServiceLocale ( PLdrfStringService pService,
				     TULong locale );

LDRF_FN LdrfStopStringService  ( PLdrfStringService * ppService );

LDRF_FN LdrfStringServiceRequest ( PLdrfStringService pService,
				   PUByteArray pProgID,
				   TUByte scope, TULong index,
				   LPSTR string, PUShort pLength );



/* These functions are used for type file access */

LDRF_FN LdrfGetTypeFileInfo	( PLdrfFileInfo pInfo,
				  PUShort pResDep0, PUShort pResDep1, PUShort pResDep2,
				  PUShort pResDep3, PUShort pResDep4, PUShort pResDep5,
				  PUShort pResDep6,
				  PUShort pTypDep0, PUShort pTypDep1, PUShort pTypDep2,
				  PUShort pTypDep3, PUShort pTypDep4, PUShort pTypDep5,
				  PUShort pTypDep6,
				  PUShort pNumNVTs, PUShort pNumCPTs,
				  PUShort pNumEnumSets );

LDRF_FN LdrfExtendedDataTypeAware ( PLdrfFileInfo pInfo,
				    TNVTType dataType );

LDRF_FN LdrfSelectEnumSet	( PLdrfFileInfo pInfo, TUShort index,
				  LPSTR pTag, PUShort pTagLen,
				  LPSTR pFile, PUShort pFileLen );

LDRF_FN LdrfValidateEnumSet	( PLdrfFileInfo pInfo, TUShort index );

LDRF_FN LdrfSelectEnumSetByTag	( PLdrfFileInfo pInfo, LPCSTR tag, PUShort pIndex );

LDRF_FN LdrfSelectEnumSetByFile ( PLdrfFileInfo pInfo, LPCSTR file, PUShort pIndex );

LDRF_FN LdrfGetEnumMemberCount	( PLdrfFileInfo pInfo, PUShort pNumMembers );

LDRF_FN LdrfGetEnumMember   ( PLdrfFileInfo pInfo, TByte enumValue,
			      LPSTR pString, PUShort pLength,
			      PUByte pResScope, PULong pResIndex );

LDRF_FN LdrfGetEnumValue    ( PLdrfFileInfo pInfo, LPCSTR string,
			      PByte pValue );

LDRF_FN LdrfGetEnumMemberByIndex ( PLdrfFileInfo pInfo, TUShort index, PByte pEnumValue,
				   LPSTR pString, PUShort pLength,
				   PUByte pResScope, PULong pResIndex );

LDRF_FN LdrfGetNVT	    ( PLdrfFileInfo pInfo, TUShort index,
			      PLdrfTypeTree * ppTypeTree );

LDRF_FN LdrfGetNVTEx	( PLdrfFileInfo pInfo, TUShort index,
			              PLdrfTypeTree * ppTypeTree, PUShort pFlags );

LDRF_FN LdrfValidateNVT     ( PLdrfFileInfo pInfo, TUShort index );

LDRF_FN LdrfFindEmptyNVT    ( PLdrfFileInfo pInfo, PUShort pIndex );

LDRF_FN LdrfGetNVTByName    ( PLdrfFileInfo pInfo, LPCSTR name,
			      PUShort pIndex, PLdrfTypeTree * ppTypeTree );

LDRF_FN LdrfGetNVTByNameEx  ( PLdrfFileInfo pInfo, LPCSTR name,
			      PUShort pIndex, PLdrfTypeTree * ppTypeTree, PUShort pFlags );

LDRF_FN LdrfGetNVTObsolete  ( PLdrfFileInfo pInfo, TUShort index,
			      PBoolByte pObsolete );

LDRF_FN LdrfGetCPT	    ( PLdrfFileInfo pInfo, TUShort index,
			      PLdrfTypeTree * ppTypeTree, PBool pInheritable,
			      PUByteArray * ppMin, PUByteArray * ppMax,
			      PUByteArray * ppInit, PUShort pByteArrayLen );

LDRF_FN LdrfGetCPTEx    ( PLdrfFileInfo pInfo, TUShort index,
			      PLdrfTypeTree * ppTypeTree, PBool pInheritable,
			      PUByteArray * ppMin, PUByteArray * ppMax,
			      PUByteArray * ppInit, PUByteArray * ppInvalid, PUShort pByteArrayLen );

LDRF_FN LdrfGetCPTEx2    ( PLdrfFileInfo pInfo, TUShort index,
			      PLdrfTypeTree * ppTypeTree, PBool pInheritable,
			      PUByteArray * ppMin, PUByteArray * ppMax,
			      PUByteArray * ppInit, PUByteArray * ppInvalid, PUShort pByteArrayLen,
                  PUShort pFlags);


LDRF_FN LdrfValidateCPT     ( PLdrfFileInfo pInfo, TUShort index );

LDRF_FN LdrfFindEmptyCPT    ( PLdrfFileInfo pInfo, PUShort pIndex );

LDRF_FN LdrfGetCPTByName    ( PLdrfFileInfo pInfo, LPCSTR name, PUShort pIndex,
			      PLdrfTypeTree * ppTypeTree, PBool pInheritable,
			      PUByteArray * ppMin, PUByteArray * ppMax,
			      PUByteArray * ppInit, PUShort pByteArrayLen );

LDRF_FN LdrfGetCPTByNameEx  ( PLdrfFileInfo pInfo, LPCSTR name, PUShort pIndex,
			      PLdrfTypeTree * ppTypeTree, PBool pInheritable,
			      PUByteArray * ppMin, PUByteArray * ppMax,
			      PUByteArray * ppInit, PUByteArray * ppInvalid, PUShort pByteArrayLen );

LDRF_FN LdrfGetCPTByNameEx2 ( PLdrfFileInfo pInfo, LPCSTR name, PUShort pIndex,
			      PLdrfTypeTree * ppTypeTree, PBool pInheritable,
			      PUByteArray * ppMin, PUByteArray * ppMax,
			      PUByteArray * ppInit, PUByteArray * ppInvalid, PUShort pByteArrayLen,
                  PUShort pFlags);

LDRF_FN LdrfGetCPTObsolete  ( PLdrfFileInfo pInfo, TUShort index,
			      PBoolByte pObsolete );

LDRF_FN LdrfFreeByteArray   ( PUByteArray pByteArray );


/* These functions are used to manipulate type trees */

LDRF_FN LdrfFreeTypeTree	( PLdrfTypeTree pTypeTree );

LDRF_FN LdrfNewTypeTreeNode	( TNVTType newNodeType, LPCSTR name,
				  TUByte resNmScope,  TULong resNmIndex,
				  TUByte resCmtScope, TULong resCmtIndex,
				  TUByte resUntScope, TULong resUntIndex,
				  PLdrfTypeTree * ppTypeTree );

LDRF_FN LdrfSetScalarInvalidValue ( PLdrfTypeTree pTypeTree,
				  TLong pInvalidValue );

LDRF_FN LdrfSetScalar64InvalidValue(PLdrfTypeTree pTypeTree, 
                  __DRF_INT64 invalidValue);

LDRF_FN LdrfSetScalarDetails	( PLdrfTypeTree pTypeTree,
				  TLong minValid, TLong maxValid,
				  TShort scaleA, TShort scaleB, TShort scaleC );

LDRF_FN LdrfSetScalar64Details  ( PLdrfTypeTree pTypeTree,
				  __DRF_INT64 minValid, __DRF_INT64 maxValid,
				  TShort scaleA, TShort scaleB, TShort scaleC );

LDRF_FN LdrfSetFloatDetails	( PLdrfTypeTree pTypeTree,
				  float minValid, float maxValid );

LDRF_FN LdrfSetDoubleFloatDetails ( PLdrfTypeTree pTypeTree,
				    double minValid, double maxValid );

LDRF_FN LdrfSetBitfieldDetails	( PLdrfTypeTree pTypeTree,
				  TUByte bitfSize, TUByte bitfOffset, TBool bitfSigned,
				  TLong minValid, TLong maxValid,
				  TShort scaleA, TShort scaleB, TShort scaleC );

LDRF_FN LdrfSetEnumDetails	( PLdrfTypeTree pTypeTree,
				  TUByte enumScope, TUShort enumIndex,
				  TLong minValid, TLong maxValid );

LDRF_FN LdrfSetArrayDetails	( PLdrfTypeTree pTypeTree, TUShort numElements );

LDRF_FN LdrfSetStructUnionDetails( PLdrfTypeTree pTypeTree, TUShort numFields );

LDRF_FN LdrfSetReferenceDetails ( PLdrfTypeTree pTypeTree,
				  TUByte typeScope, TUShort typeIndex, TUShort typeSize );

LDRF_FN LdrfScanTypeTree	( PLdrfTypeTree pTypeTree, PUShort pTypeSize, PBool pHasRefs );

LDRF_FN LdrfFindTypeTreeNode	( PLdrfTypeTree pTypeTree, TBool relative, LPCSTR pFieldName );

LDRF_FN LdrfReadTypeTreeNode	( PLdrfTypeTree pTypeTree, PNVTType pNodeType,
				  PUShort pTypeOffset, PUShort pTypeSize,
				  LPSTR pName, PUShort pLength,
				  PUByte pResNmScope,  PULong pResNmIndex,
				  PUByte pResCmtScope, PULong pResCmtIndex,
				  PUByte pResUntScope, PULong pResUntIndex );

LDRF_FN LdrfGetScalarInvalidValue ( PLdrfTypeTree pTypeTree,
				  PBoolByte pInvalidValuePresent, PLong pInvalidValue );

LDRF_FN LdrfGetScalar64InvalidValue(PLdrfTypeTree pTypeTree, PBoolByte pInvalidValuePresent, 
                  __DRF_PINT64 pInvalidValue);

LDRF_FN LdrfGetScalarDetails	( PLdrfTypeTree pTypeTree,
				  PLong pMinValid, PLong pMaxValid,
				  PShort pScaleA, PShort pScaleB, PShort pScaleC );

LDRF_FN LdrfGetScalar64Details	( PLdrfTypeTree pTypeTree,
				  __DRF_PINT64 pMinValid, __DRF_PINT64 pMaxValid,
				  PShort pScaleA, PShort pScaleB, PShort pScaleC );

LDRF_FN LdrfGetFloatDetails	( PLdrfTypeTree pTypeTree,
				  float * pMinValid, float * pMaxValid );

LDRF_FN LdrfGetDoubleFloatDetails ( PLdrfTypeTree pTypeTree,
				    double * pMinValid, double * pMaxValid );

LDRF_FN LdrfGetBitfieldDetails	( PLdrfTypeTree pTypeTree,
				  PUByte pBitfSize, PUByte pBitfOffset, PBool pBitfSigned,
				  PLong pMinValid, PLong pMaxValid,
				  PShort pScaleA, PShort pScaleB, PShort pScaleC );

LDRF_FN LdrfGetEnumDetails	( PLdrfTypeTree pTypeTree,
				  PUByte pEnumScope, PUShort pEnumIndex,
				  PLong pMinValid, PLong pMaxValid );

LDRF_FN LdrfGetArrayDetails	( PLdrfTypeTree pTypeTree, TBool multiple,
				  PUShort pNumElements );

LDRF_FN LdrfGetStructUnionDetails( PLdrfTypeTree pTypeTree, PUShort pNumFields );

LDRF_FN LdrfGetReferenceDetails ( PLdrfTypeTree pTypeTree,
				  PUByte pTypeScope, PUShort pTypeIndex );

LDRF_FN LdrfGraftReference	( PLdrfTypeTree pTypeTree,
				  PLdrfTypeTree pReferentTree );

LDRF_FN LdrfResolveAllTypeTreeRefs ( PLdrfFileInfo pCatalogInfo,
				  PUByteArray	   pProgID,
				  PLdrfTypeTree    pTypeTree,
				  PUShort	   pTypeSize );

LDRF_FN LdrfApplyValOverride	( PLdrfTypeTree pTypeTree,
				  PUByteArray pValMin, PUByteArray pValMax );

LDRF_FN LdrfApplyValOverrideEx	( PLdrfTypeTree pTypeTree,
				  PUByteArray pValMin, PUByteArray pValMax, PUByteArray pValInvalid );


/* These functions are used to access FPT files */

LDRF_FN LdrfGetFPTFileInfo ( PLdrfFileInfo pInfo,
			     PUShort pResDep0, PUShort pResDep1, PUShort pResDep2,
			     PUShort pResDep3, PUShort pResDep4, PUShort pResDep5,
			     PUShort pResDep6,
			     PUShort pTypDep0, PUShort pTypDep1, PUShort pTypDep2,
			     PUShort pTypDep3, PUShort pTypDep4, PUShort pTypDep5,
			     PUShort pTypDep6,
			     PUShort pNumFPTs );

LDRF_FN LdrfGetFPT	   ( PLdrfFileInfo pInfo, TUShort index,
			     PUShort pKey, LPSTR pName, PUShort pLength,
			     PUByte pResNmScope,  PULong pResNmIndex,
			     PUByte pResCmtScope, PULong pResCmtIndex,
			     PUByte pManNVs, PUByte pOptNVs, PUByte pManCPs, PUByte pOptCPs,
			     PUByte pPrincipalNV );

LDRF_FN LdrfGetFPTEx	   ( PLdrfFileInfo pInfo, TUShort index,
			     PUShort pKey, LPSTR pName, PUShort pLength,
			     PUByte pResNmScope,  PULong pResNmIndex,
			     PUByte pResCmtScope, PULong pResCmtIndex,
			     PUByte pManNVs, PUByte pOptNVs, PUByte pManCPs, PUByte pOptCPs,
			     PUByte pPrincipalNV, PUShort pFlags );

LDRF_FN LdrfValidateFPT    ( PLdrfFileInfo pInfo, TUShort index );

LDRF_FN LdrfFindEmptyFPT   ( PLdrfFileInfo pInfo, PUShort pIndex );

LDRF_FN LdrfGetFPTByName   ( PLdrfFileInfo pInfo, LPCSTR name,
			     PUShort pIndex, PUShort pKey,
			     PUByte pResNmScope,  PULong pResNmIndex,
			     PUByte pResCmtScope, PULong pResCmtIndex,
			     PUByte pManNVs, PUByte pOptNVs, PUByte pManCPs, PUByte pOptCPs,
			     PUByte pPrincipalNV );

LDRF_FN LdrfGetFPTByNameEx   ( PLdrfFileInfo pInfo, LPCSTR name,
			     PUShort pIndex, PUShort pKey,
			     PUByte pResNmScope,  PULong pResNmIndex,
			     PUByte pResCmtScope, PULong pResCmtIndex,
			     PUByte pManNVs, PUByte pOptNVs, PUByte pManCPs, PUByte pOptCPs,
			     PUByte pPrincipalNV, PUShort pFlags );

LDRF_FN LdrfGetFPTByKey    ( PLdrfFileInfo pInfo, TUShort key,
			     PUShort pIndex, LPSTR pName, PUShort pLength,
			     PUByte pResNmScope, PULong pResNmIndex,
			     PUByte pResCmtScope, PULong pResCmtIndex,
			     PUByte pManNVs, PUByte pOptNVs, PUByte pManCPs, PUByte pOptCPs,
			     PUByte pPrincipalNV );

LDRF_FN LdrfGetFPTByKeyEx    ( PLdrfFileInfo pInfo, TUShort key,
			     PUShort pIndex, LPSTR pName, PUShort pLength,
			     PUByte pResNmScope, PULong pResNmIndex,
			     PUByte pResCmtScope, PULong pResCmtIndex,
			     PUByte pManNVs, PUByte pOptNVs, PUByte pManCPs, PUByte pOptCPs,
			     PUByte pPrincipalNV, PUShort pFlags );

LDRF_FN LdrfGetFPTObsolete ( PLdrfFileInfo pInfo, TUShort index,
			     PBoolByte pObsolete );

LDRF_FN LdrfGetFPTInherit  ( PLdrfFileInfo pInfo, TUShort index,
			     PBoolByte pInherit );


/* FPT NVs info includes a byte containing an encoded direction bit, polled bit, and service
 * type (3 bits).  The last three bits are used internally to indicate presence or absence of
 * invalid, minimum and maximum validation ranges (but these values are masked before returning.
 * NOTE: These flags are also used in "LdrfSetFPTNV()", for the "dirPollServ"
 * parameter.  See usage notes below! */

#define FPTNV_DIR_INPUT   0x80
#define FPTNV_POLLED	  0x40
/* LdrfSetFPTNV usage Note! Choose at most one of these service type
 *	bit flags below. */
#define FPTNV_SERV_ACK	  0x20
#define FPTNV_SERV_UNACKR 0x10
#define FPTNV_SERV_UNACK  0x08
/* The Request/Response service type doesn't apply to output NV members
   of FPTs. It is the mandatory service type for polled input NVs and 
   that is governed by the direction and polled bits. So, the bit-mask
   0x04 is not required to represent FPTNV_SERV_REQRSP. We shall use it
   instead for invalid value override. */
//#define FPTNV_SERV_REQRSP 0x04 
/* LdrfSetFPTNV usage Note! Do not set either of these bits.
 *	These are for internal use only. */
#define FPTNV_INVALID_VAL_RG  0x04
#define FPTNV_MIN_VAL_RG  0x02
#define FPTNV_MAX_VAL_RG  0x01

LDRF_FN LdrfGetFPTNV	  ( PLdrfFileInfo pInfo,
			    TUShort FPTIndex, TUShort NVIndex,
			    LPSTR pNVName, PUShort pLength, PBool pMandatory,
			    PUByte pResNmScope,  PULong pResNmIndex,
			    PUByte pResCmtScope, PULong pResCmtIndex,
			    PUByte pNVTScope, PUShort pNVTIndex,
			    PUByte pDirPollServ, PUShort pByteArrayLen,
			    PUByteArray * ppValMin, PUByteArray * ppValMax );

LDRF_FN LdrfGetFPTNVEx	  ( PLdrfFileInfo pInfo,
			    TUShort FPTIndex, TUShort NVIndex,
			    LPSTR pNVName, PUShort pLength, PBool pMandatory,
			    PUByte pResNmScope,  PULong pResNmIndex,
			    PUByte pResCmtScope, PULong pResCmtIndex,
			    PUByte pNVTScope, PUShort pNVTIndex,
			    PUByte pDirPollServ, PUShort pByteArrayLen,
			    PUByteArray * ppValMin, PUByteArray * ppValMax, PUByteArray * ppValInvalid );

LDRF_FN LdrfGetFPTNVEx2	  ( PLdrfFileInfo pInfo,
			    TUShort FPTIndex, TUShort NVIndex,
			    LPSTR pNVName, PUShort pLength, PBool pMandatory,
			    PUByte pResNmScope,  PULong pResNmIndex,
			    PUByte pResCmtScope, PULong pResCmtIndex,
			    PUByte pNVTScope, PUShort pNVTIndex,
			    PUByte pDirPollServ, PUShort pByteArrayLen,
			    PUByteArray * ppValMin, PUByteArray * ppValMax, PUByteArray * ppValInvalid,
                PUShort pFlags);

LDRF_FN LdrfGetFPTNVMemberNumber ( PLdrfFileInfo pInfo,
				   TUShort FPTIndex, TUShort NVIndex,
				   PUShort pNVMemberNumber );

LDRF_FN LdrfGetFPTNVIndex ( PLdrfFileInfo pInfo,
			    TUShort FPTIndex, TUShort NVMemberNumber,
			    PUShort pNVIndex );

/* FPT CPs info includes a byte containing six flags that indicate modification restrictions,
 * and a bit used to indicate that the CP is an array. */

// #define FPTCP_ARRAY_FLG    0x80 - This item is obsolete.  2 Oct 2002
#define FPTCP_DEVSPEC_FLG  0x20
#define FPTCP_MFG_FLG	   0x10
#define FPTCP_RESET_FLG    0x08
#define FPTCP_CONST_FLG    0x04
#define FPTCP_OFFLINE_FLG  0x02
#define FPTCP_OBJ_DSBL_FLG 0x01

LDRF_FN LdrfGetFPTCP	  ( PLdrfFileInfo pInfo,
			    TUShort FPTIndex, TUShort CPIndex, PUShort pAppliesTo,
			    LPSTR pCPName, PUShort pLength, PBool pMandatory,
			    PUByte pResNmScope,  PULong pResNmIndex,
			    PUByte pResCmtScope, PULong pResCmtIndex,
			    PUByte pCPTScope, PUShort pCPTIndex,
			    PUByte pModifyArray,
			    PUShort pByteArrayLen, PUByteArray * ppDefault,
			    PUByteArray * ppValMin, PUByteArray * ppValMax );

LDRF_FN LdrfGetFPTCPEx	  ( PLdrfFileInfo pInfo,
			    TUShort FPTIndex, TUShort CPIndex, PUShort pAppliesTo,
			    LPSTR pCPName, PUShort pLength, PBool pMandatory,
			    PUByte pResNmScope,  PULong pResNmIndex,
			    PUByte pResCmtScope, PULong pResCmtIndex,
			    PUByte pCPTScope, PUShort pCPTIndex,
			    PUByte pModifyArray,
			    PUShort pByteArrayLen, PUByteArray * ppDefault,
			    PUByteArray * ppValMin, PUByteArray * ppValMax, PUByteArray * ppValInvalid );

LDRF_FN LdrfGetFPTCPEx2	  ( PLdrfFileInfo pInfo,
			    TUShort FPTIndex, TUShort CPIndex, PUShort pAppliesTo,
			    LPSTR pCPName, PUShort pLength, PBool pMandatory,
			    PUByte pResNmScope,  PULong pResNmIndex,
			    PUByte pResCmtScope, PULong pResCmtIndex,
			    PUByte pCPTScope, PUShort pCPTIndex,
			    PUByte pModifyArray,
			    PUShort pByteArrayLen, PUByteArray * ppDefault,
			    PUByteArray * ppValMin, PUByteArray * ppValMax, PUByteArray * ppValInvalid,
                PUShort pFlags);

LDRF_FN LdrfGetFPTCPByAttributes ( PLdrfFileInfo pInfo,
				   TUShort FPTIndex, TUShort appliesTo,
				   TUByte  CPTScope, TUShort CPTIndex,
				   PUShort pCPIndex,
				   LPSTR pCPName, PUShort pLength, PBool pMandatory,
				   PUByte pResNmScope,	PULong pResNmIndex,
				   PUByte pResCmtScope, PULong pResCmtIndex,
				   PUByte pModifyArray,
				   PUShort pByteArrayLen, PUByteArray * ppDefault,
				   PUByteArray * ppValMin, PUByteArray * ppValMax );

LDRF_FN LdrfGetFPTCPByAttributesEx ( PLdrfFileInfo pInfo,
				   TUShort FPTIndex, TUShort appliesTo,
				   TUByte  CPTScope, TUShort CPTIndex,
				   PUShort pCPIndex,
				   LPSTR pCPName, PUShort pLength, PBool pMandatory,
				   PUByte pResNmScope,	PULong pResNmIndex,
				   PUByte pResCmtScope, PULong pResCmtIndex,
				   PUByte pModifyArray,
				   PUShort pByteArrayLen, PUByteArray * ppDefault,
				   PUByteArray * ppValMin, PUByteArray * ppValMax, PUByteArray * ppValInvalid  );

LDRF_FN LdrfGetFPTCPMemberNumber ( PLdrfFileInfo pInfo,
				   TUShort FPTIndex, TUShort CPIndex,
				   PUShort pCPMemberNumber );

LDRF_FN LdrfGetFPTCPIndex ( PLdrfFileInfo pInfo,
			    TUShort FPTIndex, TUShort CPMemberNumber,
			    PUShort pCPIndex );

LDRF_FN LdrfGetFPTCPArrayDetails ( PLdrfFileInfo pInfo,
				   TUShort FPTIndex, TUShort CPIndex,
				   PUShort pMinArraySize, PUShort pMaxArraySize,
				   PBool pDetailsAreDefaults );


// This item was part of the "drfcat.c" module but was moved here at request
// of others who, from time to time, needed access to the name of the catalog.
#define CATALOG_NAME "LDRF.CAT"



#ifdef __cplusplus
} /* end of: extern "C" */
#endif


#endif
