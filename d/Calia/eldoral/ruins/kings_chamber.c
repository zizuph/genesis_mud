#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("in a spacious chamber high in the " +
        "ruins of " + CASTLE_NAME);
    set_long("You've entered a large, spacious " +
        "chamber located high in the ruins of " +
        CASTLE_NAME + ". High above you, several holes " +
        "stand open in the raftered ceiling, making " +
        "the large windows in the walls rather " +
        "redundant. In the center of the rubble-" +
        "strewn floor, you notice a particularly " +
        "large and regularly shaped heap of decayed " +
        "wood and fabric. A similar, though smaller, " +
        "heap, lies against the east wall beneath " +
        "a window. A single archway in the south " +
        "wall provides the only means of exit from " +
        "this room.\n\n");

    add_item(({"ceiling", "roof"}),
        "Above your head, the high ceiling appears to be " +
        "constructed from heavy stone slates laid across " +
        "thick wooden rafters. Many of the rafters have " +
        "rotted away completely, bringing their stone burden " +
        "down with them. As a result, the ceiling contains " +
        "almost as many holes as it does stone tiles.\n");
    add_item(({"rafters", "wooden rafters"}),
        "The rafters in the ceiling here are quite large, but " +
        "age and decay has claimed most of their strength, " +
        "causing the destruction of most of them. Those that " +
        "have fallen have left large holes in the ceiling " +
        "as a reminder of their presence.\n");
    add_item(({"tiles", "stone tiles"}),
        "Spread across the rafters, the stone tiles once made " +
        "a rather elegant-looking roof to this chamber. However, " +
        "with the collapse of several of the supporting rafters, " +
        "around half of the tiles now lie in shattered piles of " +
        "rubble on the floor.\n");
    add_item(({"holes"}),
        "The ceiling is now covered in holes where tiles once " +
        "lay, exposing the room to the mist-filled sky beyond.\n");
    add_item(({"sky", "mist"}),
        "Through the holes in the ceiling and the windows, you " +
        "can see nothing of the sky due to the thick, billowing " +
        "white mist which pervades this entire valley, from what " +
        "you've seen.\n");
    add_item(({"walls"}),
        "The walls of the room are unspectacular. They've been " +
        "constructed simply from large blocks of grey stone, " +
        "but time has claimed most of their strength, and they " +
        "now bear the marks of the passage of time in weblike " +
        "cracks and crumbling faces.\n");
    add_item(({"windows"}),
        "High in the walls, the windows allow natural light to " +
        "to filter down into the room. However, this is somewhat " +
        "redundant, given that far more light seeps down through " +
        "the large number of holes now evident in the ceiling.\n");
    add_item(({"floor", "ground"}),
        "The floor of the chamber is littered with rubble and " +
        "remains, mostly rotted wood and stone which has " +
        "fallen from the ceiling above.\n");
    add_item(({"heap", "heaps"}),
        "Dominating the rubble, two heaps of hopelessly rotted " +
        "wood and fabric stand in the center of the room and " +
        "beneath one of the windows. Their size and shape are " +
        "quite regular, is if they were once pieces of furniture, " +
        "but crumbled to splinters where they stood.\n");

    INSIDE;

    add_exit(RUIN + "sitting_room", "south");
}
