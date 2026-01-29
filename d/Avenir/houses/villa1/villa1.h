/*
 * Villa1 definitions file
 *
 * Lilith, Nov 2021
 *
 */

#ifndef AVENIR_VILLA1_DEFS
#define AVENIR_VILLA1_DEFS

#include "../defs.h"
#include <composite.h>

#define LOCATION        "the fortress guarding the Sybarus sea"
#define BEACH           "the seaside villas of Sybarus"
#define MAIN_ACCESS     (OUTPOST +"stairs_v1")
#define BEACH_ACCESS    (OUTPOST +"beach_v1") 
#define JUNK_ROOM       V1 +"entry"

#define FILTER_SHOWN_COMPOSITE(x) \
    filter((x), &not() @ &->query_no_show_composite())

#endif AVENIR_VILLA1_DEFS
