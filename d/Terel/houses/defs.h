/*
 * Terel-specific Housing definitions file
 *
 * Lilith, March 2022
 *
 */

#ifndef TEREL_HOUSE_DEFS
#define TEREL_HOUSE_DEFS

#include "/d/Genesis/houses/defs.h"

#define GEN_HDIR    "/d/Genesis/houses/"
#define GEN_HOUSE   "/d/Genesis/houses/housebase"

#define HOUSE       "/d/Terel/houses/"
#define H1          HOUSE + "calathin1/"
#define DOOR        HOUSE + "doors/"
#define HOBJ        HOUSE + "obj/"
#define HELP        HOUSE + "help/"

#define NO_COFFIN_PLACEMENT     "_no_coffin_placement"

#define FILTER_SHOWN_COMPOSITE(x) \
    filter((x), &not() @ &->query_no_show_composite())
	
#endif TEREL_HOUSE_DEFS


#ifndef TP
#define TP this_player()
#define TO this_object()
#define ENV environment()
#endif