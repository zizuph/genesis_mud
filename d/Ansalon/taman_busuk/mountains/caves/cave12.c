#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#include <stdproperties.h>

inherit CAVE_BASE;

void
create_cave_room()
{
    set_short("a cave under the Taman Busuk mountains");
    set_long("You are standing in a narrow cave under the Taman " +
    "Busuk mountains. The uneven floor makes walking treacherous, " +
    "and the soft dripping of water gives the cave an eerie " +
    "atmosphere. North of here, the cave ceiling has caved in, " +
    "closing off that exit.\n");

    add_cave_items();

    add_item(({"floor", "uneven floor"}),
    "The uneven floor makes walking treacherous. Rocks are scattered " +
    "throughout, and there is no cleared path that you can see.\n");

    add_item(({"cavein","cave-in"}),
    "The cave-in seals off the north exit completely.\n");

    remove_prop(ROOM_I_LIGHT);

    add_exit(CAVE_DIR + "cave11", "south");
    add_exit("", "north", "@@no_go");
}

int
no_go()
{
    write("You could not possibly clear out all those rocks, " +
    "and there is no way to pass them by.\n");

    return 1;
}
