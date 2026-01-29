/* Ashlar, 21 Oct 97 */

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
    return "This is a wide hallway in the upper level of the temple. " +
    "The hallway leads east and west, the walls decorated with " +
    "tapestries. A thick blood-red carpet runs the length of the " +
    "hallway.\n";
}

void
create_neraka_room()
{
    set_short("wide hallway in the upper level of the temple");
    set_long("@@long_descr");

    add_temple_items();
    add_item("hallway","@@long_descr");
    add_item("tapestries",
        "You see a large tapestry with a dragon on the north wall and " +
        "a tapestry depicting a battle on the south wall.\n");
    add_item(({"north tapestry","tapestry on the north wall",
    	"tapestry with dragon","dragon tapestry"}),
    	"The tapestry on the north wall shows a huge green dragon " +
    	"circling above a tall white tower in a forest.\n");
    add_item(({"south tapestry","tapestry on the south wall",
    	"tapestry depicting battle", "battle tapestry"}),
    	"The tapestry on the south wall depicts a battle, where the " +
    	"Blue Dragonarmy fights the defenders of some unnamed city.\n");

    add_item(({"carpet","thick carpet","blood-red carpet",
    	"thick blood-red carpet"}),
    	"The carpet stretches the full length of the hallway. It is thick " +
    	"and comfortable to walk on.\n");

    reset_room();

    add_exit(NTEMPLE + "u3", "east");
    add_exit(NTEMPLE + "u1", "west");
}


