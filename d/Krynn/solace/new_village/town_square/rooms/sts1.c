/*
* STS Room 1
* Created by Leia
* May 30, 2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit SQUARE_BASE;

void
reset_solace_room()
{
}

void
create_solace_room()
{
    set_add_trees();
    add_item(({"buildings"}), "There are several run-down buildings in the area. One in particular seems to stand out from the rest.\n");
    add_item(({"building"}), "This particular building seems more ravaged than the rest. The building has many boarded up windows as well as a blackened sign on its front.\n");
    add_item(({"windows"}), "Most of the windows are tightly boarded up, however one seems to be missing a board.\n");
    add_item(({"window"}), "Leaning close to the window, you peer inside. It's pretty dark inside, however, you can just barely make out a forge. This used to be a smithy!\n");
    add_item(({"forge"}), "You can barely make out a dark, blackened forge.\n");
    add_item(({"sign"}), "The sign above the door has been blackened by fire. Tracing your fingers over the raised bumps, you can discern the words \"Ironforge's Smithy\".\n");
    add_item(({"door"}), "The door is chained closed and has a large locking mechanism on the front.\n");
    add_item(({"lock", "mechanism", "locking mechanism"}), "The locking mechanism is very intricately crafted. The person who made it obviously wanted to keep everyone out. He must also have been a master smith.\n");
    add_exit(NORTHSTS1, "north");
    add_exit(SOUTHSTS1, "south");
    add_exit(ROOM2, "east");
    add_exit(WESTSTS1, "west");
    add_exit(NESTS1, "northeast");
    add_exit(ROOM4, "southeast");
    reset_solace_room();
}
