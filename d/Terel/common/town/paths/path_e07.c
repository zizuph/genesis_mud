/*
    Standard path for the town of Calathin, in the Terel domain

    Based on Vader's original path room (path_n01.c). Mortricia 920723
 */

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)       break_string(message, 70)

create_room()
{
    set_short("A small path");

    set_long(BS(
        "You are standing on a small path. There are trees, scattered " +
        "rather sparsely, on both sides of the path. The path continues " +
        "northwest and southwest. To the east you see a ruined house.\n"));

    add_item(({"tree", "trees"}), BS("These tall pines really do well in " +
        "this kind of climate. They are all covered with snow.\n"));

    add_item(({"snow"}), BS("The snow reflects the sunlight off the top of " +
        "the trees, giving it a silver color.\n"));

    add_item(({"path"}), BS("It's not that much beaten by shoes or wheels, " +
        "but the locals probably use it every now and then.\n"));

    add_item(({"ruin", "ruins", "ruined house"}), BS(
        "Yes, it's a ruin. That's about all you can figure out from your " +
        "position.\n"));

    add_exit(TOWNDIR + "paths/path_e06", "northwest", 0);
    add_exit(TOWNDIR + "paths/path_e08", "southwest", 0);
    add_exit(TOWNDIR + "mansion/porch", "east", 0);

}
