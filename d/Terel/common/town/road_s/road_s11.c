/*
    This is a standard south road. Mortricia 920723
 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define CAMP_DIR        "/d/Terel/mortricia/camp/"
#define BS(message)     break_string(message, 70)

create_room()
{
    set_short("The southern road, close to great forest");

    set_long(BS(
        "You are now standing in the southern parts of Calathin. " +
        "There are trees scattered around the road, except to the west " +
	"where you see some sort of a camp. " +
        "The road continues north and south. To the south you " +
        "see a great forest.\n"));

    add_item(({"tree", "trees", "conifers", "conifer"}), BS("Some of the " +
	"conifers look very old, " +
        "but there are a few saplings as well. The trees grow thicker " +
	"here.\n"));
    add_item(({"snow"}), BS("The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n"));
    add_item(({"forest"}), BS("The forest looks dark, "+
	"perhaps even a bit enchanted. " +
	"The forest consists mostly of conifers.\n"));
    add_item(({"camp"}), BS("You see some carriages and people, but " +
	"you have to go closer in order to find out more about it.\n"));

    add_prop("_npc_horse_cmd", 1);

    add_exit(TOWNDIR + "road_s/road_s10", "north", 0);
    add_exit(CAMP_DIR + "entrance",       "west", 0);
    add_exit("/d/Terel/enchanted/n_edge6",         "south", 0);
}
