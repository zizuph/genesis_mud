#include "/d/Rhovanion/defs.h"
inherit "/d/Rhovanion/lib/room";
inherit RHUN_DIR+"tower/inside/guard";
#include <stdproperties.h>

void create_room()
{
    set_short("Stairwell");
    set_long("This is the top of a stairwell of wide"
        +" steps, made of the same dark red stone as the rest of this"
        +" tower.  They lead down from here,  or you may follow"
        +" a dim passageway back to the east.\n");

    add_exit(RHUN_DIR+"tower/inside/3captain_room", "east", 0);
    add_exit(RHUN_DIR+"tower/inside/2up_room","down",0);

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}
