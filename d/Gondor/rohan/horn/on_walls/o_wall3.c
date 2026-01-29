inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

#define BELOWROOM ROH_DIR + "horn/gorge/stairs"

void create_helmsdeep_room()
{
    string location, extraline;

    location = "On top of the southern part of the outer wall, above the "+
    "rear-gate of the keep. ";
    extraline = "The outer wall runs west and northeast. ";

    set_short_desc("On top of the outer wall of the keep");
    set_extra_long(location + LONG_DESC1 + extraline);
    set_inside_keep(1);

    set_below_desc("You have a good view of the stairs up to "+
    "the rear-gate. ");
    set_below_room(BELOWROOM);

    add_item(({"clefts","cleft"}), down_there);
    ON_WALL;
    TOWER;
    WINDOWS;
    PARAPET;
    COURTYARD;
    KEEP;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    BOTH_WALLS;


    add_exit(ROH_DIR+"horn/on_walls/o_wall4","west",0);
    add_exit(ROH_DIR+"horn/on_walls/o_wall2","northeast",0);
}

