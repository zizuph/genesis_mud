/*
 * 
 * Forest location in northern parts of
 * the silent forest.
 *
 * Baldacin@Genesis, Dec 2003
 */
#include "ldefs.h"
inherit FORESTSTD;

#define COORDX 4
#define COORDY 1


void
create_room()
{
    int loc_type, cliffs;
    string extra_long;

    loc_type = MM_FOREST;
    cliffs = NOCLIFF;
    extra_long = "";            
    set_exit_desc(1, "south");
    
    make_me_forest(extra_long, loc_type, cliffs);

    add_exit(SFDIR + "nforest04_02.c", "south", 0, FOREST_FATIGUE, EXITNOTOBVIOUS);

}
