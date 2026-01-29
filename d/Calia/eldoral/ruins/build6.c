#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("in the ruins of a building in " + CASTLE_NAME);
    set_long("You are in the ruins of a building somewhere in " +
        CASTLE_NAME + ". This appears to be the bottom floor of a main " +
        "interior building, as you can see hooks mounted on the north, " +
        "west and south walls where tapestries once hung. Beneath " +
        "these hooks, a number of statues and empty pedestals line " +
        "the bottom of the north and south walls. In the south " +
        "wall, a narrow opening leads down a dark stairway. In the " +
        "north wall, another opening appears to lead down a wide " +
        "hallway, not so grand as this one might once have been, however. " +
        "This hallway strikes off eastwards to places unknown. Also " +
        "against the north wall, you can see a stone staircase leading " +
        "upwards along the wall to an upper floor.\n\n");

    add_item(({"west wall"}),
        "The west wall is " +
        "apparently an outer wall, as the effects of age and weather " +
        "have worn through it in places, probably once windows, leaving " +
        "jagged holes of crumbling stone in their place.\n");
    add_item(({"ceiling", "roof"}),
        "The ceiling of the room appears to be in fairly good " +
        "shape, relatively speaking, made of large, heavy timbers " +
        "supporting blocks of stone.\n");
    add_item(({"timbers"}),
        "The timbers in the ceiling look to be badly decaying, " +
        "but they're so thick, it could be years yet before the " +
        "decay reaches all the way inside.\n");
    add_item(({"walls"}),
        "With the exception of the west wall, the walls here " +
        "are more or less completely intact, with only a handful " +
        "of cracks and missing chunks of stone marring the " +
        "surface.\n");
    add_item(({"floor", "ground"}),
        "The floor is made from large flagstones fitted together, " +
        "but they're starting to crack and crumble, particularly " +
        "near the west wall, where they're more exposed to the " +
        "elements.\n");
    add_item(({"hooks"}),
        "Small iron hooks, now badly rusted, jut out from the " +
        "walls, and probably once sported large tapestries.\n");
    add_item(({"statues"}),
        "Statues depicting what are probably men and women line " +
        "the hall in various stages of decay. The damage to them " +
        "is bad enough to make further identification impossible.\n");
    add_item(({"pedestals"}),
        "Here and there, bare pedestals mark where statues or " +
        "similar objects once stood, but they have crumbled completely " +
        "or been carried away by some earlier visitor.\n");

    INSIDE;

    add_exit(RUIN + "build6-build7_1", "north");
    add_exit(RUIN + "main_hall_1", "east");
    add_exit(RUIN + "catacomb_5", "down");
    add_exit(RUIN + "build_6_u", "up");
}
