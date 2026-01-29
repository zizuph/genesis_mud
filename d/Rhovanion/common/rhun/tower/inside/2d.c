inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_room()
{
    set_short("Dark passage");
    set_long("You find yourself walking through a"
        +" dark corridor made of thick red stones of a heavy shade."
        +"  This tower is apparently a base for some group of Easterlings."
        +"  You may follow the passageway from here to the northeast or"
        +" west.\n");

    add_exit(RHUN_DIR+"tower/inside/2e", "northeast", 0);
    add_exit(RHUN_DIR+"tower/inside/2c", "west", 0);

    add_prop(ROOM_I_INSIDE, 1);
}
