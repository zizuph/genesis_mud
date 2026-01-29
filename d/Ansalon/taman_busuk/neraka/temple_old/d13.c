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
    return "You are standing at the end of a corridor leading northwest. " +
    "To the south stand an impressive pair of doors. " +
    "The walls of this corridor " +
    "are smoother than in the rest of the temple, and the floor " +
    "is not as worn.\n";
}

void
create_neraka_room()
{
    set_short("at an intersection of corridors in the temple");
    set_long("@@long_descr");

    add_temple_items();
    add_item("walls","The walls here are smooth.\n");
    add_item("floor","The floor seems almost untrod by mortal feet.\n");
    add_item(({"doors","pair of doors"}),
    "The doors are made of bronze, and looks quite heavy.\n");
    add_cmd_item(({"doors","pair of doors"}),
    "open","You do not have the strength to open them completely, but " +
    "you could probably open them far enough to go south if you wanted " +
    "to.\n");

    reset_room();

    add_exit(NTEMPLE + "d11", "northwest");
    add_exit(NTEMPLE + "chamber", "south");
}


