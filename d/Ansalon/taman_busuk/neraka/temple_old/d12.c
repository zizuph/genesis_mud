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
    return "You are at the south end of a corridor in the lower level " +
    "of the temple. To the southwest, the corridor opens up into a " +
    "strange cavern.\n";
}

void
create_neraka_room()
{
    set_short("the south end of a corridor");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"strange cavern","cavern"}),
    "It is oddly lit, and seems to be full of plants.\n");

    reset_room();

    add_exit(NTEMPLE + "d10", "north");
    add_exit(NTEMPLE + "garden", "southwest");
}


