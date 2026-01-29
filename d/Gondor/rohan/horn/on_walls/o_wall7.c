inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"
#include "/d/Gondor/common/mordor/sys/clock.h"

#define BELOWROOM ROH_DIR + "horn/gorge/n_path4"

int sunrise();

void create_helmsdeep_room()
{
    string location, extraline;

    location = "On top of the western part of the outer wall. ";
    extraline = "The northern cliff is just to the west, extending all "+
    "the way to the wall. The outer wall runs south, and stairs "+
    "lead up to the inner wall and down to the outer courtyard. ";

    set_short_desc("On top of the outer wall of the keep");
    set_extra_long(location + LONG_DESC1 + extraline);
    set_inside_keep(1);

    set_below_desc("Two furlongs north of the keep is the "+
    "Dike, an old trench functioning as an outer fortification. Beyond "+
    "the Dike the Coomb begins. You are above the postern door. ");
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

    add_item( "stairs", BSN("The stone stairs are narrow and high. "+
    	"Only a tall person can comfortably use them."));

    add_exit(ROH_DIR + "horn/on_walls/o_wall6", "south", 0);
    add_exit(ROH_DIR + "horn/on_walls/i_wall6", "up", 0, 2);
    add_exit(ROH_DIR + "horn/burg/outer_court6", "down", 0);

    CLOCK->notify_dawn(sunrise);
}

int sunrise()
{
    object *people;
    int i;

    CLOCK->notify_dawn(sunrise);
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

