inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

#define BELOWROOM ROH_DIR + "horn/burg/outer_court6"

void create_helmsdeep_room()
{
    string location, extraline;

    location = "On top of the eastern part of the inner wall. ";
    extraline = "The wall runs north and southwest, and a stairway "+
    "leads down to the courtyard. ";

    set_short_desc("On top of the inner wall of the keep");
    set_extra_long(location + LONG_DESC2 + extraline);
    set_inside_keep(1);

    set_below_desc("You have a good view of the eastern side of the "+
    "outer courtyard. ");
    set_below_room(BELOWROOM);

    add_item(({"clefts","cleft"}), down_there);
    ON_WALL;
    TOWER;
    PARAPET;
    COURTYARD;
    KEEP;
    WINDOWS;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    INNER_WALL;

    add_exit(ROH_DIR + "horn/on_walls/i_wall4", "north", 0);
    add_exit(ROH_DIR + "horn/on_walls/i_wall2", "southwest", 0);
    add_exit(ROH_DIR + "horn/burg/inner_court2", "down", 0);
} 

