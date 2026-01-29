#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("in a narrow corridor");
    set_long("You are inside the eastern end of a passage " +
        "that at one time cut east and west beneath the " +
        "ruins of Castle Chimera. However, at some point " +
        "in the past, all that came to an end. The ceiling, " +
        "floor and walls here were all built from blocks " +
        "of some sort of grey stone, painstakingly placed " +
        "together. Not carefully enough to avoid the ravages " +
        "of the years, unfortunately. The passage only " +
        "comes in a few feet, then dead-ends where the " +
        "ceiling and walls have collapsed in to form an " +
        "impenetrable obstacle to progress to the west. " +
        "The once carefully placed stones on the floor " +
        "have heaved up atop clods of earth where the " +
        "floor was compressed by the weight of the roof " +
        "and whatever was above it. There's nothing " +
        "to do here but turn around.\n\n");

    add_item(({"ceiling", "roof"}),
        "Made from long slabs of cut stone laid across the " +
        "tops of the walls, the ceiling of this room apparently " +
        "isn't as strong as it might have been, as it has " +
        "collapsed entirely just a few feet into the passage.\n");
    add_item(({"walls"}),
        "The walls are made from large blocks of cut grey " +
        "stone that have crumbled away a few feet into the " +
        "the passage and collapsed.\n");
    add_item(({"floor", "ground"}),
        "The stone tiles on the floor have been heaved up out " +
        "of place by earth pushing up from beneath when the " +
        "ceiling collapsed.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "ne_court_nw", "east");
}
