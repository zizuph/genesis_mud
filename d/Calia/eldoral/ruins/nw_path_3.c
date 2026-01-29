#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("a narrow path in the northwest of " +
        CASTLE_NAME);
    set_long("You are in a very narrow path, almost " +
        "like an alley, in the northwest parts of " +
        CASTLE_NAME+", between the outer wall to " +
        "the north and the foundation of the main " +
        "buildings to the south. Between " +
        "the two walls stretches a green strip of " +
        "thick, deep grass. In fact it's quite a " +
        "nice walk except for having to sidestep the " +
        "small to medium chunks of stone which " +
        "litter the ground, remains of the walls' " +
        "eroded battlements. The path extends " +
        "westwards where it corners southwards, " +
        "and eastwards a short way. It appears from " +
        "here that the way is blocked by rubble.\n\n");

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

    add_exit(RUIN + "nw_path_4", "east");
    add_exit(RUIN + "nw_path_2", "west");
}
