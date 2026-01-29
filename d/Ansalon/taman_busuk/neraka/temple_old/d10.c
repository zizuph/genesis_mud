/* Ashlar, 1 Oct 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit TEMPLE_BASE;

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "This is an intersection between two corridors, one running " +
    "north and south, the other one going east from here. To the west " +
    "is a doorway leading into the library.\n";
}

void
create_neraka_room()
{
    set_short("an intersection between two corridors");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"doorway","small doorway"}),
    "The doorway is decorated with a wooden frame painted white.\n");
    add_item(({"frame","wooden frame","white frame"}),
    "The frame is made of wood, but you cannot discern the type of " +
    "wood. The white paint contrasts nicely with the darker walls.\n");

    reset_room();

    add_exit(NTEMPLE + "d6", "north");
    add_exit(NTEMPLE + "d11", "east");
    add_exit(NTEMPLE + "d12", "south");
    add_exit(NTEMPLE + "library", "west");
}


