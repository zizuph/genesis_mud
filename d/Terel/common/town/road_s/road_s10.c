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
        "There are trees scattered around the road. " +
        "The road continues northwest and south. To the south you " +
        "see a large forest.\n"));

    add_item(({"tree", "trees", "conifers", "conifer"}), BS("Some of the " +
	"conifers look very old, " +
        "but there are a few saplings as well. The trees grow thicker " +
	"here.\n"));
    add_item(({"snow"}), BS("The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n"));
    add_item(({"forest"}), BS("The forest looks dark, "+
	"perhaps even a bit enchanted. " +
	"The forest consists mostly of conifers.\n"));

    add_exit(TOWNDIR + "road_s/road_s09", "northwest", 0);
    add_exit(TOWNDIR + "road_s/road_s11", "south", 0);
}
