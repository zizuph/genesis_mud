/* Ashlar, 21 Aug 98
   Inside of tower where dragons land
*/

#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit INNER_IN;

void
create_neraka_room()
{
    set_short("inside a tall tower in Neraka");
    set_long("You are inside a tall tower in Neraka, serving as a " +
    "landing for dragonriders. This, the lower level, is " +
    "a sort of a waiting lounge. Comfortable chairs line the walls, " +
    "except where a circular staircase lead up to the roof. " +
    "A door leads east, out of the tower.\n");

    add_exit(NINNER + "r37", "east");
    add_exit(NINNER + "tower_roof", "up");

    add_item(({"chairs","chair","comfortable chairs"}),
    "The chairs look very comfortable. Unfortunately, they are occupied, " +
    "every single one of them.\n");

    add_item(({"wall","walls"}),"Of the walls, nothing can be said that " +
    "has not already been said about walls elsewhere.\n");

    add_item(({"staircase","circular staircase"}),
    "The circular staircase is most singular, being that there is only " +
    "one of it, here. It leads, in a roundabout fashion, up to the " +
    "roof.\n");

    add_item("door","The door leads east, out of the tower. It is " +
    "sturdy, made of wood.\n");
}


