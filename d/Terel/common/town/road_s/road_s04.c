/*
    This is a standard south road. Mortricia 920728
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)

object trav2;

reset_room()
{
    if (!trav2) {
        trav2 = clone_object(TOWNDIR + "road_e/traveller");
        trav2 -> move(this_object());
    }
}

create_room()
{
    set_short("The south road");

    set_long(BS(
        "This icy road will take you to the southern parts of Calathin. " +
        "There are a few trees scattered around the road. " +
        "The road continues to the northwest and to the south.\n"));

    add_item(({"tree", "trees"}), BS("These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n"));

    add_item(({"snow"}), BS("The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n"));

    add_exit(TOWNDIR + "road_s/road_s03", "northwest", 0);
    add_exit(TOWNDIR + "road_s/road_s05", "south", 0);

    reset_room();
}
