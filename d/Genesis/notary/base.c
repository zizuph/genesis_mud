/*
 * Base object for notary services.
 * Simply a placeholder for all global variables that should exist
 * in all inheriting objects.
 * 
 * 2003-07-03 Dargoth
 *
 */
inherit "/std/object";

#include "notary.h"


/*  Global gdocInfo variable, usually holds all the document relevant info
 *
 *  DOCTITLE:string    - document title
 *  CONTENTS:string - document contents - text of agreement etc.
 *  EXPIRY: 0       - document expiry time as time() 
 *  BITFIELD:int    - document type and access bit values, as defined in notary.h
 *  SIGNERS:mapping - ([ "signer":"guild", ... ])
 *                      "signer" is query_real_name(),
 *                        "guild" QGSHORT(QRACE|QLAY|QOCC) 
 *                      /see notary.h for defines/
 *  SIGNERTITLES:mapping  - if any of signers chooses to sign fully,
 *                      his titles are stored here
 *  CREATETIME:int     - time() when the document was added to the index.
 */
mapping gdocInfo= ([DOCTITLE:EMPTYFIELD,  
                    CONTENTS:0,   
                    BITFIELD:0,
                    EXPIRY:0, 
                    SIGNERS:([ ]),
                    SIGNERTITLES:([]),
                    CREATETIME:0
                    ]);

