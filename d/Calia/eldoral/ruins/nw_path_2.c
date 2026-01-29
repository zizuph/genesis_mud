#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("a narrow path in the northwest of " +
        CASTLE_NAME);
    set_long("You've reached the northwest corner of " +
        CASTLE_NAME+", travelling upon a grassy " +
        "path between the outer wall and the stone " +
        "foundation of the central buildings. The " +
        "stone walls are quite close together here, " +
        "and between them thick green grass grows " +
        "upon the path. The path continues eastwards " +
        "and southwards from here, and while neither " +
        "are particularly interesting, it looks " +
        "like the path further to the east has been " +
        "blocked by rubble, so it may be a dead " +
        "end.\n\n");

    add_item(({"sky", "mist"}),
        "High above you, the sky is obscured by a thick " +
        "layer of churning white mist.\n");
    add_item(({"ground", "floor"}),
        "The ground of the path is covered in thick grass, " +
        "making walking quite easy, so long as you don't " +
        "trip over any of the chunks of stone littering " +
        "the surface.\n");
    add_item(({"walls"}),
        "Massive walls of grey stone blocks rise on either " +
        "side of you. Both appear to have suffered a fair " +
        "amount of damage over the years, with gaping " +
        "cracks and holes where stone has crumbled or " +
        "fallen away completely.\n");
    add_item(({"chunks","stone","chunks of stone"}),
        "Scattered across the ground of the path, large " +
        "chunks of stone that have fallen from the walls " +
        "pose the threat of stubbing your toe.\n");
    add_item(({"cracks", "holes"}),
        "The walls are covered with deep cracks and holes " +
        "where stone has crumbled away or even fallen out " +
        "of them.\n");
    add_item(({"rubble"}),
        "A large pile of rubble covers the path further " +
        "east, it looks like that way might be a dead " +
        "end.\n");

    add_exit(RUIN + "nw_path_3", "east");
    add_exit(RUIN + "nw_path_1", "south");
}
