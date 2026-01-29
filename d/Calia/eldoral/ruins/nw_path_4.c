#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("a grassy path in the northwest parts " +
        "of " + CASTLE_NAME);
    set_long("You have reached the end of this " +
        "narrow alley between the outer wall of " +
        "the castle to the north and the foundation " +
        "of the main buildings to the south. " +
        "Actually, the path itself appears to have " +
        "once continued to the east, but a massive " +
        "tower has fallen over from a structure to " +
        "the south, and now its ruins lie across " +
        "the path, projecting through a large hole it smashed " +
        "through the outer wall, and probably " +
        "continues well into the forest outside the " +
        "wall. The grass on the ground here is almost " +
        "completely obliterated by scattered stones " +
        "and fragments of stone. The loosely-piled " +
        "rubble is quite high, " +
        "making climbing it too dangerous to even " +
        "consider. It looks like the only way out is " +
        "to return back down the path to the west.\n\n");

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
    add_item(({"rubble", "tower"}),
        "A large pile of rubble completely covers the path " +
        "here. It appears to be the remains of a large tower " +
        "that has collapsed across the path, and is completely " +
        "impassable.\n");
    add_item(({"hole"}),
        "As the tower collapsed, it crushed away a fair-sized " +
        "hole in the outer wall to the north, but the rubble " +
        "has filled it too thoroughly for you to be able to " +
        "see through it, let alone slip through it.\n");

    add_exit(RUIN + "nw_path_3", "west");
}
