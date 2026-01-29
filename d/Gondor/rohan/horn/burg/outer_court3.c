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
    extraline = "To the south is the rear-gate of the keep, and to the northeast "+
    "is the great gate. To the west the courtyard bends "+
    "north around the inner wall. ";

    set_short_desc("The outer courtyard of the Hornburg");
    set_extra_long(location + LONGDESC1 + extraline);
    set_inside_keep(1);

    GUARDS;
    WALL;
    TOWER;
    WINDOWS;
    COURTYARD;
    COBBLESTONES;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    BOTH_WALLS;

    add_exit(ROH_DIR+"horn/burg/outer_court4","west",0);
    add_exit(ROH_DIR+"horn/burg/outer_court1","northeast",0);
    add_exit(ROH_DIR+"horn/burg/outer_court2","east",0);

    door = clone_object(ROH_DIR + "horn/doors/rear_gate_out");
    door->move(TO);
}

