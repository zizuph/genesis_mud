/*
    This is a standard south road. Mortricia 920723
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)

create_room()
{
    set_short("The southern road");

    set_long(BS(
        "This icy road will take you to the southern parts of Calathin. " +
        "There are a few trees scattered around the road. " +
        "The road continues north and south. Far south you " +
        "see a large forest.\n"));

    add_item(({"tree", "trees"}), BS("These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n"));

    add_item(({"snow"}), BS("The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n"));
    add_item(({"forest"}), BS("The forest must be quite extended, "+
	"since it reaches almost over the whole southern horizon, but " +
	"that is about all you can figure out from here.\n"));

    add_exit(TOWNDIR + "road_s/road_s07", "north", 0);
    add_exit(TOWNDIR + "road_s/road_s09", "south", 0);
}
