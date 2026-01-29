inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    string location, extraline;

    location = "On top of the southern part of the outer wall. ";
    extraline = "The outer wall runs west and east. ";

    set_short_desc("On top of the outer wall of the keep");
    set_extra_long(location + LONG_DESC1 + extraline);
    set_inside_keep(1);

    add_item(({"clefts","cleft"}),BSN("The clefts give a narrow "+
	"view of the gorge."));
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


    add_exit(ROH_DIR+"horn/on_walls/o_wall5","west",0);
    add_exit(ROH_DIR+"horn/on_walls/o_wall3","east",0);
}

