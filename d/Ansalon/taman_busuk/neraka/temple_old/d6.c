/* Ashlar, 30 Sep 97 */

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
    return "This is the north end of a corridor in the lower level of " +
    "the temple. To the north is a large door set in a curving wall, " +
    "around which smaller corridors lead northwest and northeast.\n";
}

void
create_neraka_room()
{
    set_short("at an intersection of corridors in the temple");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"door","large door"}),
    "The large door is made of oak inlaid with metal. It is set in the " +
    "curving wall to the north.\n");

    add_item(({"curving wall"}),
    "The curving wall indicates that it houses a near-circular chamber " +
    "within.\n");

    reset_room();

    add_exit(NTEMPLE + "d10", "south");
    add_exit(NTEMPLE + "d3", "northwest");
    add_exit(NTEMPLE + "abbey", "north");
    add_exit(NTEMPLE + "d4", "northeast");
}


