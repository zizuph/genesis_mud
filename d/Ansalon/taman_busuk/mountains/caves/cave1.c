#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#include <stdproperties.h>

inherit CAVE_BASE;

void
create_cave_room()
{
    set_short("a cave entrance under the Taman Busuk mountains");
    set_long("You are standing in a small cave under the Taman " +
    "Busuk mountains. To the south is a crack leading outside, " +
    "and in the other end of the cave, a passage leads north.\n");

    add_cave_items();

    add_item("crack","It is a small crack set in the southern " +
    "wall. It seems to lead outside.\n");

    add_item("passage","The passage leads north, into darkness.\n");

    add_prop(ROOM_I_LIGHT, 1);

    add_exit(MOUNTAINS_DIR + "cave_link", "south");
    add_exit(CAVE_DIR + "cave2", "north");
}

