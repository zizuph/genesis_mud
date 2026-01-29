#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("a narrow alley in the ruins of Castle " +
        "Chimera");
    set_long("You are in a narrow alley in the ruins, " +
        "passing between two tall walls of crumbling " +
        "grey stone to your east and west. Towards " +
        "the north, the alley appears to end in an " +
        "open walkway of some sort. Southwards, it " +
        "passes though an archway into a building at " +
        "the end of the rubble-strewn path.\n\n");

    add_item(({"sky", "mist"}),
        "The sky is completely obscured by a thick blanket of " +
        "billowing white mist.\n");
    add_item(({"walls"}),
        "The walls on either side of the alley are made " +
        "of thick grey blocks of stone, but time and the " +
        "weather have eroded much of their integrity, " +
        "and they now appear on the verge of collapse.\n");
    add_item(({"floor", "ground"}),
        "Small, tightly-fitted cobblestones line the ground " +
        "here, providing a moderately firm walking surface.\n");
    add_item(({"archway"}),
        "At one time the archway probably contained a door, " +
        "but now it's little more than a gaping hole in " +
        "the wall.\n");

    add_exit(RUIN + "ne_walk_3", "north");
    add_exit(RUIN + "main_hall_3", "south");
}