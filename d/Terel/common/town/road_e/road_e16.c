/*
    This is a standard east road. Mortricia 920723
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define TO              this_object()

reset_room()
{
    object swordsman, officer;

    if(!present("swordsman")) {
        swordsman = clone_object(TOWNDIR + "road_e/swordsman");
        swordsman -> move(TO);
    }
    if(!present("officer")) {
        officer = clone_object(TOWNDIR + "road_e/officer");
        officer -> move(TO);
    }
    return;
}

create_room()
{
    set_short("The east road");

    set_long(BS(
        "This icy and snowy road will take you eastwards. There are some " +
        "trees here and there. The road goes along a river.\n"));

    add_item(({"tree", "trees"}), BS("These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n"));

    add_item(({"snow"}), BS("The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n"));

    add_item(({"river", "water"}), BS("The river streams fast, otherwise " +
        "it would have been covered with an ice layer. The water is real " +
        "cold.  The river seems to slow down a bit here.\n"));

    add_prop(ROOM_HAS_WATER, 1);

    add_exit(TOWNDIR + "road_e/road_e15", "northwest", 0);
    add_exit(TOWNDIR + "road_e/road_e16", "east", "@@later");

    reset_room();
}

later() {
    write(BS("The road is flooded by water from the river. Please, come back " +
        "later when the water level is lower.\n"));
    return 1;
}
