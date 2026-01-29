/* Ashlar, 30 Sep 97 */

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
    return "You stand in a corridor in the lower levels of the temple. " +
    "The corridor runs from the east to the west, and doorways " +
    "lead off in different directions.\n";
}

void
create_neraka_room()
{
    set_short("a corridor within the temple");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"doorway","small doorway"}),
    "The doorway is decorated with a wooden frame painted white.\n");
    add_item(({"frame","wooden frame","white frame"}),
    "The frame is made of wood, but you cannot discern the type of " +
    "wood. The white paint contrasts nicely with the darker walls.\n");

    reset_room();

    add_exit(NTEMPLE + "d1", "west");
    add_exit(NTEMPLE + "d3", "east", "@@go_east");
    add_exit(NTEMPLE + "board", "south");
    add_exit(NTEMPLE + "shop", "north");
    add_exit(NTEMPLE + "store", "northwest");
}

int
go_east()
{
    write("You feel a chill passing through you as you go east, and " +
    "you realise that part of the corridor was warded.\n");
    return 0;
}
