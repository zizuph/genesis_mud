#include "defs.h"

inherit STDROOM;

void
create_room()
{
    set_short("atop a wall overlooking the southwest " +
        "courtyard in "+CASTLE_NAME);
    set_long("You stand atop a tall wall marking the " +
        "eastern edge of the southwest courtyard of " +
        CASTLE_NAME+". Below you stretches " +
        "the southwest courtyard outwards towards " +
        "the west wall. Towards the north, the " +
        "crumbling ruins of towers, walkways " +
        "and more walls rise into the sky, wrapping " +
        "around the courtyard and passing to your " +
        "immediate east. At your feet, you see a " +
        "stone stairway climbing down the side of " +
        "the wall towards the south, the only visible " +
        "means of getting to the courtyard from here " +
        "without jumping.\n\n");

    add_item(({"sky", "mist"}),
        "The sky is shrouded in a thick, white blanket of mist.\n");
    add_item(({"ground", "floor"}),
        "The surface of the walkway is made from hard-packed " +
        "earth. Although fairly rutted in places, it's stable " +
        "enough to walk on.\n");
    add_item(({"building"}),
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
    add_item(({"stairs", "stairway"}),
        "A narrow stone stairway descends here down to " +
        "the courtyard.\n");

    add_exit(RUIN + "sw_wall_3", "north");
    add_exit(RUIN + "sw_wall_1", "south");
    add_exit(RUIN + "sw_court_stairs", "down");
}
