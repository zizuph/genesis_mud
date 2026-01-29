/*
 * 
 * Forest location in northern parts of
 * the silent forest.
 *
 * Baldacin@Genesis, Dec 2003
 */
#include "ldefs.h"
inherit FORESTSTD;

#define COORDX 2
#define COORDY 3


void
create_room()
{
    int loc_type, cliffs;
    string extra_long;

    loc_type = MM_FOREST;
    cliffs = NOCLIFF;
    extra_long = "";            
    set_exit_desc(2, "east and west");
    
    make_me_forest(extra_long, loc_type, cliffs);

    add_exit(SFDIR + "nforest01_03.c",  "west", 0, FOREST_FATIGUE, EXITNOTOBVIOUS);
    add_exit(SFDIR + "nforest03_03.c",  "east", 0, FOREST_FATIGUE, EXITNOTOBVIOUS);

}
