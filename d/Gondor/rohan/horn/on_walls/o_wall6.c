inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    string location, extraline;

    location = "On top of the western part of the outer wall. ";
    extraline = "The outer wall runs north and southeast. The "+
    "northern cliff is just to the north, extending all the way to the "+
    "wall. ";

    set_short_desc("On top of the outer wall of the keep");
    set_extra_long(location + LONG_DESC1 + extraline);
    set_inside_keep(1);

    add_item(({"clefts","cleft"}),BSN("The clefts give a narrow "+
	"view of the northern cliff."));
    add_item( ({ "cliff", "cliffs", "northern cliff" }),
	BSN("The wall is built all the way to the cliff, "+
	"barring entrance to the Deep."));

    ON_WALL;
    TOWER;
    WINDOWS;
    PARAPET;
    COURTYARD;
    KEEP;
    GORGE;
    MOUNTAINS;
    BOTH_WALLS;


    add_exit(ROH_DIR+"horn/on_walls/o_wall5","southeast",0);
    add_exit(ROH_DIR+"horn/on_walls/o_wall7","north",0);
}

int sunrise()
{
    object *people;
    int i;

    people = FILTER_LIVE(all_inventory(TO));
    for (i = 0; i < sizeof(people); i++)
    {
        if (people[i]->id("_spy_orc"))
        {
             people[i]->move_living("M", ROH_DIR +"horn/hide_out");
             return 1;
        }
    }
    return 1;
}

int sunset()
{
    return 1;
}
