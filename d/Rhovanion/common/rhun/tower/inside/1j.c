inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_room()
{
    set_short("Dark passage");
    set_long("This is a dimly lit hallway in a tall"
        +" tower of red brick.  It is apparently occupied by one of the"
        +" many races of Easterlings, men from Rhun and farther east, into"
        +" the wild lands.  The hall forks here, with branches leading off"
        +" to the east, west, and south.\n");

    add_exit(RHUN_DIR+"tower/inside/1i", "south", 0);
    add_exit(RHUN_DIR+"tower/inside/1up_room", "east", 0);
    add_exit(RHUN_DIR+"tower/inside/1k", "west", 0);

    add_prop(ROOM_I_INSIDE, 1);
}

