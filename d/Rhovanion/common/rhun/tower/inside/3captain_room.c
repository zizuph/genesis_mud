inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"

static object captain;

void reset_room()
{
    reset_euid();

    if (!objectp(captain))
    {
        captain = clone_object(RHUN_DIR+"npc/easterling_captain");
        captain->arm_me();
        captain->move(TO, 1);
        tell_room(TO, QCTNAME(captain)+" arrives.\n");
    }
}

void create_room()
{
    set_short("Captain's room");
    set_long("This is a large, square room at the top of this tower of " +
        "dark red stone, which stands within the forest northeast of the " +
        "Sea of Rhun.  The leader of the this regiment of the Easterling army "+
        "apparently resides and does his work here.  A stairwell lies just "+
        "back to the west.\n");

    add_exit(RHUN_DIR+"tower/inside/3up_room", "west", 0);

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}
