#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("atop a wall overlooking the southwest " +
        "courtyard in "+CASTLE_NAME);
    set_long("You are standing atop a crumbling " +
        "wall overlooking the southwest courtyard " +
        "of "+CASTLE_NAME+". " +
        "Further to the north, the heart of " +
        "the castle lies in crumbling ruins, once-grand " + 
        "towers and walls sag and show gaping holes " +
        "in their walls where stones have fallen out. " +
        "Right beside you a massive tower reaches " +
        "skyward, never to reach as high as it once did, as its " +
        "roof and much of its upper west wall have fallen off, " +
        "and now lie in a jagged heap before you, effectively " +
        "blocking any progress to the north.\n\n");

    add_item(({"sky", "mist"}),
        "The sky is shrouded in a thick, white blanket of mist.\n");
    add_item(({"ground", "floor"}),
        "The surface of the walkway is made from hard-packed " +
        "earth. Although fairly rutted in places, it's stable " +
        "enough to walk on.\n");
    add_item(({"building", "tower"}),
        "On your east stands the remains of a large building, " +
        "but the crumbling stone offers little clue as to " +
        "what it might be.\n");
    add_item(({"courtyard"}),
        "Below you to the west spreads the southwest courtyard " +
        "of the ruins. Beyond it, the south and east walls " +
        "mark the edges of the ruins, and beyond them stand " +
        "tall evergreens of the island forest.\n");
    add_item(({"trees", "evergreens", "forest"}),
        "Beyond the courtyard walls, the tall evergreen trees " +
        "of the forest rise upwards into the misty sky, their " +
        "height and depth of the forest obscured by the mist.\n");

    add_exit(RUIN + "sw_wall_2", "south");
}
