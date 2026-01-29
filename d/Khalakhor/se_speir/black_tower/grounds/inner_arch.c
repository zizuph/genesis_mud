/*
 * inner_arch
 *
 * This room is just inside the archway leading into
 * the grounds of the black tower.
 *
 * Khail - July 7/97
 */
#pragma strict_types

#include "grounds.h"

inherit STDGROUNDS;

public void
create_khalakhor_room()
{
    set_short("inside an ancient archway");
    set_long("You are just within an ancient archway " +
        "that leads out of the grounds around an old " +
        "tower into the forest beyond. The grounds " +
        "are surrounded on all apparent sides by low, " +
        "stony embankments that are covered in a tangle " +
        "of thistles and brambles. To the far west, " +
        "an overgrown graveyard stands beneath the " +
        "skeletal remains of dead oaks which populate " +
        "the clearings. The center of the clearing is " +
        "dominated by the old tower itself, crumbling " +
        "into ruins.\n");

    add_exit(GROUNDS + "grounds_1", "north");
    add_exit(GROUNDS + "outer_arch", "east");
    add_exit(GROUNDS + "grounds_13", "west");
}
