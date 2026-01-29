inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    string location, extraline;

    location = "On top of the southern part of the outer wall. ";
    extraline = "The outer wall runs northwest and east, and a stairway "+
    "leads down to the outer courtyard. ";

    set_short_desc("On top of the outer wall of the keep");
    set_extra_long(location + LONG_DESC1 + extraline);
    set_inside_keep(1);

    ON_WALL;
    add_item(({"clefts","cleft"}),BSN("The clefts give a narrow "+
	"view of the gorge."));
    TOWER;
    WINDOWS;
    PARAPET;
    COURTYARD;
    KEEP;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    BOTH_WALLS;


    add_exit(ROH_DIR+"horn/on_walls/o_wall6","northwest",0);
    add_exit(ROH_DIR+"horn/on_walls/o_wall4","east",0);
    add_exit(ROH_DIR+"horn/burg/outer_court4","down",0);
}

