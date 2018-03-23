/*
 * LCADRFW.H - External include file for the API that provides access methods
 * supporting the LonMark Device Resource Files, writing feature.
 * Copyright (c) 1996 - 2002  Echelon Corporation
 * All Rights Reserved
 * Implementation by RLE
 */


#ifndef _LCADRFW
#define _LCADRFW


#include "lcadrf.h"


#ifdef __cplusplus
extern "C" {
#endif



/* These functions are used for basic and general file actions */

LDRF_FN LdrfEditFile	    ( LPCSTR path, TLdrfFileType fileType,
			      PLdrfFileInfo * ppInfo );


LDRF_FN LdrfEditFileVer     ( LPCSTR path, TLdrfFileType fileType,
			      TUByte majFmtForCreate,
			      PLdrfFileInfo * ppInfo );

LDRF_FN LdrfConvertFile     ( LPCSTR pathIn, LPCSTR pathOut,
			      TUByte toVersion, TBool checkCRC );


LDRF_FN LdrfPurgeFile	    ( LPCSTR pathIn, LPCSTR pathOut,
			      TBool checkCRC );



/* These functions are used for resource file access */

LDRF_FN LdrfSetLangFileInfo    ( PLdrfFileInfo pInfo, TULong locale );

LDRF_FN LdrfSetASCIIResource   ( PLdrfFileInfo pInfo, TBool shareDup, TULong index,
				 LPCSTR string, PULong pDupIndex );

LDRF_FN LdrfDeleteResourceString ( PLdrfFileInfo pInfo, TULong index );



/* These functions are used for type file access */

LDRF_FN LdrfSetTypeFileInfo	( PLdrfFileInfo pInfo,
				  TUShort resDep0, TUShort resDep1, TUShort resDep2,
				  TUShort resDep3, TUShort resDep4, TUShort resDep5,
				  TUShort resDep6,
				  TUShort typDep0, TUShort typDep1, TUShort typDep2,
				  TUShort typDep3, TUShort typDep4, TUShort typDep5,
				  TUShort typDep6 );

LDRF_FN LdrfSelectNewEnumSet	( PLdrfFileInfo pInfo, LPCSTR tag, LPCSTR file,
				  PUShort pIndex );

LDRF_FN LdrfChangeSelectedEnumSetTag  ( PLdrfFileInfo pInfo, LPCSTR pTag );

LDRF_FN LdrfChangeSelectedEnumSetFile ( PLdrfFileInfo pInfo, LPCSTR pFile );

LDRF_FN LdrfSetEnumMember   ( PLdrfFileInfo pInfo, TByte enumValue,
			      LPCSTR string, TUByte resScope, TULong resIndex );

LDRF_FN LdrfDeleteEnumMemberByIndex   ( PLdrfFileInfo pInfo, TUShort index );

LDRF_FN LdrfDeleteEnumSet   ( PLdrfFileInfo pInfo, TUShort index );

LDRF_FN LdrfSetNVT	    ( PLdrfFileInfo pInfo,
			      TUShort index, PLdrfTypeTree pTypeTree );

LDRF_FN LdrfSetNVTEx	    ( PLdrfFileInfo pInfo,
			      TUShort index, PLdrfTypeTree pTypeTree, TUShort flags );

LDRF_FN LdrfSetNVTObsolete  ( PLdrfFileInfo pInfo, TUShort index);

LDRF_FN LdrfDeleteNVT	    ( PLdrfFileInfo pInfo, TUShort index );

LDRF_FN LdrfSetCPT	    ( PLdrfFileInfo pInfo, TUShort index,
			      PLdrfTypeTree pTypeTree, TBool inheritable,
			      PUByteArray pMin, PUByteArray pMax,
			      PUByteArray pInit, TUShort byteArrayLen );

LDRF_FN LdrfSetCPTEx    ( PLdrfFileInfo pInfo, TUShort index,
			      PLdrfTypeTree pTypeTree, TBool inheritable,
			      PUByteArray pMin, PUByteArray pMax, 
			      PUByteArray pInit, PUByteArray pInvalid, TUShort byteArrayLen );

LDRF_FN LdrfSetCPTEx2   ( PLdrfFileInfo pInfo, TUShort index,
			      PLdrfTypeTree pTypeTree, TBool inheritable,
			      PUByteArray pMin, PUByteArray pMax, 
			      PUByteArray pInit, PUByteArray pInvalid, TUShort byteArrayLen,
                  TUShort flags);

LDRF_FN LdrfSetCPTObsolete  ( PLdrfFileInfo pInfo, TUShort index );

LDRF_FN LdrfDeleteCPT	    ( PLdrfFileInfo pInfo, TUShort index );



/* These functions are used to access FPT files */

LDRF_FN LdrfSetFPTFileInfo ( PLdrfFileInfo pInfo,
			     TUShort resDep0, TUShort resDep1, TUShort resDep2,
			     TUShort resDep3, TUShort resDep4, TUShort resDep5,
			     TUShort resDep6,
			     TUShort typDep0, TUShort typDep1, TUShort typDep2,
			     TUShort typDep3, TUShort typDep4, TUShort typDep5,
			     TUShort typDep6 );

LDRF_FN LdrfSetFPT	   ( PLdrfFileInfo pInfo, TUShort index, TUShort key, LPCSTR name,
			     TUByte resNmScope,  TULong resNmIndex,
			     TUByte resCmtScope, TULong resCmtIndex,
			     TUByte manNVs, TUByte optNVs, TUByte manCPs, TUByte optCPs,
			     TUByte principalNV );

LDRF_FN LdrfSetFPTEx ( PLdrfFileInfo pInfo, TUShort index, TUShort key, LPCSTR name,
			     TUByte resNmScope,  TULong resNmIndex,
			     TUByte resCmtScope, TULong resCmtIndex,
			     TUByte manNVs, TUByte optNVs, TUByte manCPs, TUByte optCPs,
			     TUByte principalNV, TUShort flags );

LDRF_FN LdrfSetFPTObsolete ( PLdrfFileInfo pInfo, TUShort index );

LDRF_FN LdrfClearFPTInherit( PLdrfFileInfo pInfo, TUShort index );

LDRF_FN LdrfSetFPTInherit  ( PLdrfFileInfo pInfo, TUShort index );

LDRF_FN LdrfDeleteFPT	   ( PLdrfFileInfo pInfo, TUShort index );


/* Usage note ... the "dirPollServ" in "LdrfSetFPTNV()" below is a bit
 * mask.  The bit definitions are explained in the include file "lcadrf.h"
 * with the function "LdrfGetFPTNV()". */

LDRF_FN LdrfSetFPTNV	   ( PLdrfFileInfo pInfo,
			     TUShort FPTIndex, TUShort NVMemberNumber,
			     LPCSTR NVName, TBool mandatory,
			     TUByte resNmScope,  TULong resNmIndex,
			     TUByte resCmtScope, TULong resCmtIndex,
			     TUByte NVTScope, TUShort NVTIndex,
			     TUByte dirPollServ, TUShort byteArrayLen,
			     PUByteArray pValMin, PUByteArray pValMax );

LDRF_FN LdrfSetFPTNVEx	   ( PLdrfFileInfo pInfo,
			     TUShort FPTIndex, TUShort NVMemberNumber,
			     LPCSTR NVName, TBool mandatory,
			     TUByte resNmScope,  TULong resNmIndex,
			     TUByte resCmtScope, TULong resCmtIndex,
			     TUByte NVTScope, TUShort NVTIndex,
			     TUByte dirPollServ, TUShort byteArrayLen,
			     PUByteArray pValMin, PUByteArray pValMax, PUByteArray pValInvalid  );

LDRF_FN LdrfSetFPTNVEx2	   ( PLdrfFileInfo pInfo,
			     TUShort FPTIndex, TUShort NVMemberNumber,
			     LPCSTR NVName, TBool mandatory,
			     TUByte resNmScope,  TULong resNmIndex,
			     TUByte resCmtScope, TULong resCmtIndex,
			     TUByte NVTScope, TUShort NVTIndex,
			     TUByte dirPollServ, TUShort byteArrayLen,
			     PUByteArray pValMin, PUByteArray pValMax, PUByteArray pValInvalid, 
                 TUShort flags  );

LDRF_FN LdrfChangeFPTNVMemberNumber ( PLdrfFileInfo pInfo, TUShort FPTIndex,
				      TUShort oldMemberNumber, TUShort newMemberNumber );

/* Usage note ... the "modifyArray" in "LdrfSetFPTCP()" below is a bit
 * mask.  The bit definitions are explained in the include file "lcadrf.h"
 * with the function "LdrfGetFPTCP()". */

LDRF_FN LdrfSetFPTCP	   ( PLdrfFileInfo pInfo,
			     TUShort FPTIndex, TUShort CPMemberNumber,
			     TUShort appliesTo,
			     LPCSTR CPName, TBool mandatory,
			     TUByte resNmScope,  TULong resNmIndex,
			     TUByte resCmtScope, TULong resCmtIndex,
			     TUByte CPTScope, TUShort CPTIndex,
			     TUByte modifyArray,
			     TUShort byteArrayLen, PUByteArray pDefault,
			     PUByteArray pValMin, PUByteArray pValMax );

LDRF_FN LdrfSetFPTCPEx	   ( PLdrfFileInfo pInfo,
			     TUShort FPTIndex, TUShort CPMemberNumber,
			     TUShort appliesTo,
			     LPCSTR CPName, TBool mandatory,
			     TUByte resNmScope,  TULong resNmIndex,
			     TUByte resCmtScope, TULong resCmtIndex,
			     TUByte CPTScope, TUShort CPTIndex,
			     TUByte modifyArray,
			     TUShort byteArrayLen, PUByteArray pDefault,
			     PUByteArray pValMin, PUByteArray pValMax, PUByteArray pValInvalid  );

LDRF_FN LdrfSetFPTCPEx2	   ( PLdrfFileInfo pInfo,
			     TUShort FPTIndex, TUShort CPMemberNumber,
			     TUShort appliesTo,
			     LPCSTR CPName, TBool mandatory,
			     TUByte resNmScope,  TULong resNmIndex,
			     TUByte resCmtScope, TULong resCmtIndex,
			     TUByte CPTScope, TUShort CPTIndex,
			     TUByte modifyArray,
			     TUShort byteArrayLen, PUByteArray pDefault,
			     PUByteArray pValMin, PUByteArray pValMax, PUByteArray pValInvalid,
                 TUShort flags);

LDRF_FN LdrfSetFPTCPArrayDetails    ( PLdrfFileInfo pInfo,
				      TUShort FPTIndex, TUShort CPIndex,
				      TUShort minArraySize, TUShort maxArraySize );

LDRF_FN LdrfChangeFPTCPMemberNumber ( PLdrfFileInfo pInfo, TUShort FPTIndex,
				      TUShort oldMemberNumber, TUShort newMemberNumber );


#ifdef __cplusplus
} /* end of: extern "C" */
#endif


#endif
