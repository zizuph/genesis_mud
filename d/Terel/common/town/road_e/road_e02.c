/*
    This is a standard east road. Mortricia 920723
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)

create_room()
{
    set_short("The east road");

    set_long(BS(
        "You are standing on the east road of Calathin. There are some " +
        "trees here and there. To the south you see a river. There is " +
        "a wooden signpost standing here.\n"));

    add_item(({"tree", "trees"}), BS("These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n"));

    add_item(({"snow"}), BS("The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n"));

    add_item(({"river", "water"}), BS("The river streams fast, otherwise " +
        "it would have been covered with an ice layer. The water is real " +
        "cold.\n"));

   add_item(({"sign", "signpost"}), "Maybe you can read the sign?\n");

   add_cmd_item(({"sign", "signpost"}), "read",
        "The sign reads:\n" +
        "Northwest:  To town of Calathin.\n" +
        "East:       Eastern wilderness.\n" +
        "Southeast:  Enchanted forest and Port Lorusel.\n");

    add_exit(TOWNDIR + "road_e/road_e01", "northwest", 0);
    add_exit(TOWNDIR + "road_e/road_e03", "east", 0);
   add_exit(TOWNDIR + "road_s/road_s01", "southeast", 0);
}
