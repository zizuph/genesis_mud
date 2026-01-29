/* Ashlar, 4 Oct 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include "../guild/guild.h"

inherit TEMPLE_BASE;

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "You are at the intersection of two corridors, one leading " +
    "southeast and northwest, the other northeast and southwest. " +
    "To the west is a large door set in a curving wall, around which " +
    "the corridors lead northwest and southwest.\n";
}

void
create_neraka_room()
{
    set_short("at an intersection of corridors in the temple");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"door","large door"}),
    "The large door is made of oak inlaid with metal. It is set in the " +
    "curving wall to the west.\n");

    add_item(({"curving wall"}),
    "The curving wall indicates that it houses a near-circular chamber " +
    "within.\n");

    reset_room();

    add_exit(NTEMPLE + "d5", "northwest");
    add_exit(NTEMPLE + "d14", "northeast");
    add_exit(NTEMPLE + "workshop", "southeast");
    add_exit(NTEMPLE + "d6", "southwest");
    add_exit(NTEMPLE + "abbey", "west");
}


