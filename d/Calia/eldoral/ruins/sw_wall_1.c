#include "defs.h"

inherit STDROOM;

void
create_room()
{
    set_short("atop a wall overlooking the southwest " +
        "courtyard in "+CASTLE_NAME);
    set_long("You have reached what appears to be a " +
        "dead end here atop the east wall of the " +
        "southwest courtyard of "+CASTLE_NAME+". It's " +
        "possible to continue further to the south, " +
        "but the crumbling south wall has left that " +
        "first step being a thirty foot drop to the " +
        "ground below. Beneath the shroud of these walls " +
        "lies the southwest courtyard of the castle, " +
        "a large square area of open space, save for " +
        "the center. The ruins of a building rise on " +
        "your east, offering no clue to its identity. " +
        "\n\n");

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

    add_exit(RUIN + "sw_wall_2", "north");
    add_exit(RUIN + "build1", "east");
}
