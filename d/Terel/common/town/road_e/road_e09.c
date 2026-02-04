/*
    This is a standard east road. Mortricia 920723
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

public void
create_room()
{
    set_short("The east road");

    set_long(
        "This icy and snowy road will take you eastwards. There are some " +
        "trees here and there. There are some bushes to the north. " +
        "The road goes along a river.\n");

    add_item(({"tree", "trees"}), "These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n");

    add_item(({"snow"}), "The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n");

    add_item(({"river", "water"}), "The river streams fast, otherwise " +
        "it would have been covered with an ice layer. The water is real " +
        "cold.\n");
        
    add_item(({"thorn", "bushes", "thorns"}), "The thorn-bushes seem " +
             "very thick. You doubt something can be hidden there.\n");

    add_exit(TOWNDIR + "road_e/road_e08", "west", 0);
    add_exit(TOWNDIR + "road_e/road_e10", "east", 0);
}
