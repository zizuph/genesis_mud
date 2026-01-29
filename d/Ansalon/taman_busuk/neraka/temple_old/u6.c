/* Ashlar, 06 Jul 98 */

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
    return "This is the upper end of a small staircase which " +
    "leads north. A metal ladder leads up a tall narrow shaft.\n";
}

void
create_neraka_room()
{
    set_short("top of staircase");
    set_long("@@long_descr");

    add_temple_items();
    add_item("staircase","The staircase leads north and down.\n");
    add_item(({"ladder","metal ladder"}),
        "The metal ladder leads up a tall narrow shaft.\n");
    add_item(({"shaft","tall narrow shaft"}),
        "The shaft leads up, probably to the roof of the temple.\n");

    reset_room();

    add_exit(NTEMPLE + "roof", "up", "@@go_up");
    add_exit(NTEMPLE + "u3", "north");
    add_exit(NTEMPLE + "u3", "down", 0, 1, 1);
}

int
go_up()
{
    write("You climb the metal ladder for a long time, and " +
    "finally emerge onto the roof of the temple.\n");

    return 0;
}
