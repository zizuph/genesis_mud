#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("on a spiraling stone staircase in the " +
        "ruins of " + CASTLE_NAME);
    set_long("You are about halfway down, or so you " +
        "think, a narrow stone staircase that spirals " +
        "down into the depths of " + CASTLE_NAME + "'s " +
        "ruins. The walls here are solid stone, not " +
        "built from blocks but carved from the " +
        "stone on which the castle was built. The " +
        "stone must have had a major fissure in it, " +
        "however. The rest of the staircase beneath " +
        "you has collapsed completely, burying the " +
        "base of the stairs, and probably whatever " +
        "was down there, beneath hundreds of tons " +
        "of stone.\n\n");

    add_item(({"ceiling", "roof"}),
        "Above your head, the ceiling of the stairwell looks " +
        "to have been cut from solid stone, smoothly finished " +
        "to descend uniformly with the steps.\n");
    add_item(({"walls"}),
        "The walls have been cut from the surrounding stone, " +
        "and curve gracefully to follow the spiral of the " +
        "steps.\n");
    add_item(({"steps", "floor", "ground"}),
        "The steps of the stairway are also cut straight out " +
        "of the surrounding stone, and have held up quite well, " +
        "aside from some chipping on their edges.\n");
    
    INSIDE;
    DARK;

    add_exit(RUIN + "main_hall_5", "up");
}
