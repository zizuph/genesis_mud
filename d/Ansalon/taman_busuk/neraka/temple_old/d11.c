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
    return "You are standing in a corridor leading southeast and west. " +
    "A smaller corridor leads northeast. The walls of this corridor " +
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
    add_item("floor","The floor seems almost untrod by mortal feet, " +
    "especially so to the southeast.\n");

    reset_room();

    add_exit(NTEMPLE + "workshop", "northeast");
    add_exit(NTEMPLE + "d13", "southeast");
    add_exit(NTEMPLE + "d10", "west");
}


