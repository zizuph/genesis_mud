#include "defs.h"

inherit STDROOM;

public int
pass_door()
{
    write("As you travel northwards, you feel a strange chill " +
        "pass over your body, turning around, you notice you appear " +
        "to have stepped through solid stone, as a stone door " +
        "bars the way south!\n");
    return 0;
}

public void
create_room()
{
    set_short("catacombs beneath " + CASTLE_NAME);
    set_long("You are in a narrow passage somewhere in the " +
        "catacombs beneath " + CASTLE_NAME + ". This dark passage appears " +
        "to have been carved out from solid stone rather than " +
        "excavated and built up with blocks. The walls, floor " +
        "and ceiling are perfectly smooth, if not damp and " +
        "covered in a rather slimy mixture of water and dust. It leads " +
        "off to the north, and a narrow, spiral stone stairway " +
        "descends downwards from this point.\n\n");

    add_item(({"ceiling", "roof"}),
        "Carved from the surrounding stone, it slops steeply down " +
        "the curving stairway.\n");
    add_item(({"walls", "wall"}),
        "The flanking walls here are cut from the surrounding " +
        "stone, and spiral downwards towards the stairway's " +
        "destination.\n");
    add_item(({"floor", "ground", "steps"}),
        "The steps have also been cut from solid stone, but " +
        "fortunately they've been left rough, there should be " +
        "little, if any, chance for slipping on them.\n");
    add_item(({"mixture"}),
        "The walls and steps are slicked by a somewhat slimey " +
        "mixture formed of dusty silt and water. It's not pretty, " +
        "but at least it's not dangerous, either.\n");

    DARK;
    INSIDE;

    add_exit(RUIN + "catacomb_6", "north", "@@pass_door");
    add_exit(CAVERNS + "entrance", "down");
}
