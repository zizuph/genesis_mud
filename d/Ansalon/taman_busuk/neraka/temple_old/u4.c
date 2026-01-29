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
        "You see a tapestry showing some sort of assembly on the north " +
        "wall and a tapestry with a flight of dragons on the south wall.\n");
    add_item(({"north tapestry","tapestry on the north wall",
    	"tapestry showing assembly","assembly tapestry"}),
    	"The tapestry on the north wall shows an assembly of five armoured " +
    	"figures sitting on five thrones, surrounded by large groups of " +
    	"soldiers.\n");
    add_item(({"south tapestry","tapestry on the south wall",
    	"tapestry with dragons", "dragons tapestry"}),
    	"The tapestry on the south wall depicts a flight of red dragons, " +
    	"razing a town with their fire.\n");

    add_item(({"carpet","thick carpet","blood-red carpet",
    	"thick blood-red carpet"}),
    	"The carpet stretches the full length of the hallway. It is thick " +
    	"and comfortable to walk on.\n");

    reset_room();

    add_exit(NTEMPLE + "u5", "east");
    add_exit(NTEMPLE + "u3", "west");
}


