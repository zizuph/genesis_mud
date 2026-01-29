inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    object door;
    string location, extraline;

    location = "The eastern part of the outer courtyard. ";
    extraline = "A door is set into the wall to the southeast, "+
    	"and a flight of steps lead up to the top of the outer wall. ";

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

    add_exit(ROH_DIR+"horn/burg/outer_court3","west",0);
    add_exit(ROH_DIR+"horn/burg/outer_court1","north",0);
    add_exit(ROH_DIR+"horn/on_walls/o_wall2","up",0,2);

    door = clone_object(ROH_DIR + "horn/doors/wall_door_out");
    door->move(TO);
}

