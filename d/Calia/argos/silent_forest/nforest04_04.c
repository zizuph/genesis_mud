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
#define COORDY 4


void
create_room()
{
    int loc_type, cliffs;
    string extra_long;

    loc_type = MM_FOREST;
    cliffs = ADDCLIFF;
    extra_long = "";            
    set_cliff_dir("southeast and east");
    set_exit_desc(3, "south, north and northwest");
    
    make_me_forest(extra_long, loc_type, cliffs);

    add_exit(SFDIR + "nforest03_03.c", "northwest", 0, FOREST_FATIGUE, EXITNOTOBVIOUS);
    add_exit(SFDIR + "nforest04_03.c", "north", 0, FOREST_FATIGUE, EXITNOTOBVIOUS);
    add_exit(SFDIR + "nforest04_05.c", "south", 0, FOREST_FATIGUE, EXITNOTOBVIOUS);

}
