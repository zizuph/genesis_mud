/*
    Standard path for the town of Calathin, in the Terel domain

    Based on Vader's original path room (path_n01.c). Mortricia 920723
 */

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)       break_string(message, 70)

reset_room()
{
    object knife;

    if (present("knife"))
        return;

    knife = clone_object(TOWNDIR + "paths/rusty_knife");
    knife -> move(this_object());
}

create_room()
{
    set_short("A small path");

    set_long(BS(
        "You are standing on a small path. There are trees, scattered " +
        "rather sparsely, on both sides of the path. The path continues " +
        "northwest and southeast. There is a track going east. You also " +
        "notice that the roofs of some houses glitter through the " +
        "trees in the southwest direction.\n"));

    add_item(({"tree", "trees"}), BS("These tall pines really do well in " +
        "this kind of climate. They are all covered with snow.\n"));

    add_item(({"snow"}), BS("The snow reflects the sunlight off the top of " +
        "the trees, giving it a silver color.\n"));

    add_item(({"path"}), BS("It's not that much beaten by shoes or wheels, " +
        "but the locals probably use it every now and then.\n"));

    add_exit(TOWNDIR + "paths/path_e03", "northwest", 0);
    add_exit(TOWNDIR + "paths/path_e05", "southeast", 0);
    add_exit(TOWNDIR + "paths/track_n01", "east", 0);

    clone_object(TOWNDIR + "paths/rusty_knife") -> move(this_object());

    reset_room();
}
