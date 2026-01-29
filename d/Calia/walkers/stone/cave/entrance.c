

inherit "/std/room";

#include <stdproperties.h>
#include "defs.h"

void
create_room()
{
    set_short("Inside a cavern");
    set_long("You are standing in an alcove of a large cavern. On the "+
        "south wall you see a large, polished, flat wall, entirely "+
        "covered in a gleaming crystal. Hundreds of stalactites hang "+
        "down from the ceiling high above you. To the north you see "+
        "another chamber.\n");

    add_item(({"wall","flat wall","large wall","polished wall",
        "polished flat wall","large flat wall","large polished flat wall"}),
        "Through the gleaming crystal wall you can see the altar standing "+
        "alone in the small cave. The altar looks remarkably like the one "+
        "used to gain access to this place.\n");

    add_item(({"stalactite","stalactites"}),"These crystalline creations "+
        "hang down from the ceiling far above.  It appears almost as if "+
        "the ceiling itself has melted and has formed these structures.\n");

    add_item("chamber","The chamber off to the north seems to be much "+
        "larger than this one.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);

    add_exit(CAVE+"gemroom","north",0,1);
}
