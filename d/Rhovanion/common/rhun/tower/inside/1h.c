#include "/d/Rhovanion/defs.h"
inherit "/d/Rhovanion/lib/room";
inherit RHUN_DIR+"tower/inside/guard";
#include <stdproperties.h>

void create_room()
{
    set_short("Dark passage");
    set_long("You find yourself walking through a"
        +" dark corridor made of thick red stones of a heavy shade."
        +"  This tower is apparently a base for some group of Easterlings."
        +"  You may follow the passageway from here to the west or south.\n");

    add_exit(RHUN_DIR+"tower/inside/1i", "west", 0);
    add_exit(RHUN_DIR+"tower/inside/1g", "south", 0);

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}
