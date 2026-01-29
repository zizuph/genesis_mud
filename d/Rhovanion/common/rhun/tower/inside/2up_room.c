inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_room()
{
    set_short("Stairwell");
    set_long("This is the middle of a stairwell of wide"
        +" steps, made of the same dark red stone as the rest of this"
        +" tower.  They lead up and down from here,  or you may follow"
        +" a dim passageway back to the south.\n");

    add_exit(RHUN_DIR+"tower/inside/2a", "south", 0);
    add_exit(RHUN_DIR+"tower/inside/3up_room", "up", 0);
    add_exit(RHUN_DIR+"tower/inside/1up_room","down",0);

    add_prop(ROOM_I_INSIDE, 1);
}
