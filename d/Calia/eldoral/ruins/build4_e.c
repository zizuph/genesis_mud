#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("the ruins of a long hall in " + CASTLE_NAME);
    set_long("You are in the east end of a long room " +
        "resembling a hall of some sort. Whatever it " +
        "once was, its functional days are long gone. " +
        "Above you, a thick white mist churns in the " +
        "sky, visible through the gaping hole where " +
        "a ceiling once stood. In fact, it's not so " +
        "much a hole as a complete absence of a " +
        "ceiling over the walls. What was the ceiling " +
        "now lies in piles of broken stone on the " +
        "floor, choking off further passage to the " +
        "east and burying anything that might once " +
        "have been here. The hall continues towards " +
        "the west, however, and a narrow archway in " +
        "the south wall leads off in that direction.\n\n");

    add_item(({"ceiling", "roof"}),
        "Where a ceiling used to be is now nothing but a " +
        "gaping hole above the walls, exposing the room " +
        "to the mist-filled sky above.\n");
    add_item(({"sky", "mist"}),
        "Thick white mist churns in the sky above you, " +
        "completely blocking your view of it.\n");
    add_item(({"piles", "pile", "stone", "broken stone"}),
        "The floor is choked with the broken stone remains " +
        "of what used to be the ceiling.\n");
    add_item(({"walls"}),
        "The walls are common enough, grey stone blocks cut " +
        "and fit into place. They're holding up fairly well " +
        "to the passage of time, but are covered in a fine " +
        "spiderweb of small cracks.\n");
    add_item(({"floor", "ground"}),
        "The floor is comprised of flagstones carefully set " +
        "into place, though several have started lifting and " +
        "cracking.\n");

    add_exit(RUIN + "build4_w", "west");
    add_exit(RUIN + "cath-build4", "south");
}
