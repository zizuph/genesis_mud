/*
 * /d/Avenir/common/common.h
 *
 * This is a legacy defines header file.
 * It should not be used any longer and exists solely
 * for files which already #include it.
 *
 * All defines/macros/etc have been relegated to other
 * files and this file has been modified to include those
 * instead of creating a multi-versioned duplicated mess.
 *
 *     --= Lucius Kane, Oct 2008
 */
#ifndef _AVENIR_COMMON
#define _AVENIR_COMMON

#include <composite.h>
#include <filter_funs.h>                 /* filter functions */
#include <macros.h>                      /* macros like VBFC and QNAME */
#include <ss_types.h>                    /* stats and skills */
#include <stdproperties.h>               /* self-explanatory */
#include <wa_types.h>

// -*****DIRECTORY DEFINITIONS*****-

#include "/d/Avenir/include/paths.h"

// -*****LIVING, ROOM & OBJECT DEFINITIONS*****-

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/macros.h"

/* These definitions should not be used in new code.
 *
 * WAS: #define BS(x)         break_string(x, 75)
 */
#define BS(x)	(x)
#define BSN(x)	(BS(x) + "\n")
#define NFN(x)	NF(BSN(x))

#endif  /* _AVENIR_COMMON */
