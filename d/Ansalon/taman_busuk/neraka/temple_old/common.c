/* Ashlar, 04 Jul 98 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit TEMPLE_BASE;

string
long_descr()
{
    return "You are in a square room within the lower level of the temple. " +
    "The walls are bare stone in here, and so is the floor. You sense a " +
    "great magic in here, and you realise the source is a rather " +
    "ordinary-looking bulletin board standing in the middle of the " +
    "room.\n";
}

void
create_neraka_room()
{
    object bb;
    
    set_short("common boardroom");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"doorway","small doorway"}),
    "The doorway is decorated with a wooden frame painted white.\n");
    add_item(({"frame","wooden frame","white frame"}),
    "The frame is made of wood, but you cannot discern the type of " +
    "wood. The white paint contrasts nicely with the darker walls.\n");

    add_exit(NTEMPLE + "board", "northeast");

    bb = clone_object("/d/Genesis/obj/board");
    if (bb)
        bb->move(this_object());
}


