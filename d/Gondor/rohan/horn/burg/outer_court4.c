inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    object door;
    string location, extraline;

    location = "The southern part of the outer courtyard. ";
    extraline = "To the north is the gate to the inner courtyard, "+
    "and a stairway leads up to top of the wall. ";

    set_short_desc("The outer courtyard of the Hornburg");
    set_extra_long(location + LONGDESC1 + extraline);
    set_inside_keep(1);

    GUARDS;
    WALL;
    TOWER;
    WINDOWS;
    COURTYARD;
    COBBLESTONES;
    STAIRS;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    BOTH_WALLS;

    add_exit(ROH_DIR+"horn/burg/outer_court3","east",0);
    add_exit(ROH_DIR+"horn/burg/outer_court5","northwest",0);
    add_exit(ROH_DIR+"horn/on_walls/o_wall5","up",0,2);

    door = clone_object(ROH_DIR + "horn/doors/innerwall_gate_in");
    door->move(TO);
}

