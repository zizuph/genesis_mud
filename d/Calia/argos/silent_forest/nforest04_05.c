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
#define COORDY 5


void
create_room()
{
    int loc_type, cliffs;
    string extra_long;

    loc_type = MM_FOREST;
    cliffs = ADDCLIFF;
    extra_long = "To the southeast a small opening is visible in the cliff wall.";    
    add_item(({"opening", "cave"}), "On the south cliff wall a small opening is visible.\n");           
    set_cliff_dir("south, southeast and east");
    set_exit_desc(2, "southeast and north");
    
    make_me_forest(extra_long, loc_type, cliffs);

    add_exit(SFDIR + "nforest04_04.c", "north", 0, FOREST_FATIGUE, EXITNOTOBVIOUS);
    add_exit(SFDIR + "cave04x11.c", "southeast", 0, FOREST_FATIGUE, EXITNOTOBVIOUS);
}
