inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    string location, extraline;

    location = "The western part of the outer courtyard. ";
    extraline = "The courtyard extends north and southeast. ";

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

    add_exit(ROH_DIR+"horn/burg/outer_court6","north",0);
    add_exit(ROH_DIR+"horn/burg/outer_court4","southeast",0);
}

