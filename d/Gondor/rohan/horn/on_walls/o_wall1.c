inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

#define BELOWROOM ROH_DIR + "horn/gorge/out_gate"

void create_helmsdeep_room()
{
    string location, extraline;

    location = "On top of the eastern part of the outer wall, above the "+
    	"great gate. ";
    extraline = "The outer wall runs south, while the inner wall is "+
    	"up a staircase to the northwest. ";

    set_short_desc("On top of the outer wall of the keep");
    set_extra_long(location + LONG_DESC1 + extraline);
    set_inside_keep(1);

    set_below_desc("You have a good view of the ground in front of "+
    "the great gate. ");
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

    add_item(({ "great gate", "gate" }), 
    "You are standing atop the gate so you can't see any details.\n");
    add_item("staircase",
    "The staircase is narrow and leads to the higher inner wall.\n");

    add_exit(ROH_DIR+"horn/on_walls/i_wall4","up", 0, 2);
    add_exit(ROH_DIR+"horn/on_walls/i_wall4","northwest", 0, 2, 1);
    add_exit(ROH_DIR+"horn/on_walls/i_wall4","up", 0, 2, 1);
    add_exit(ROH_DIR+"horn/on_walls/o_wall2","south", 0);
}

