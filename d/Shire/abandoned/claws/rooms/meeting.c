inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>

void
create_room()
{
    set_short("Intersection");
    set_long("This is the place where the north-south tunnel and east-west "+
    "tunnel meets. The place is a well used meeting place for orcs that "+
    "travel throughout the northern parts of Middle-Earth. The hallway is "+
    "lit by a few oil-lamps, and some noise can be heard from southeast. "+
    "A gate is set in the southern wall, and lots of guards can be seen in "+
    "the guard-rooms on both sides of it. North the path seems to lead into "+
    "a brighter area, whilst east and west only darkness can be seen. "+
    "In the middle of this intersection, there is a large pool of water.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit("training", "southeast");
    add_exit("join", "south");
}
