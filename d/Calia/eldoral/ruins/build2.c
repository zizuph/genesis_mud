#include "defs.h"

inherit STDROOM;

int
take_the_stairs()
{
    write("You climb the narrow stairway and enter the north corridor.\n");
    say(QCTNAME(TP) + " climbs the narrow stairway.\n");
    return 0;
}

void
create_room()
{
    set_short("inside a ruined tower in " + CASTLE_NAME);
    set_long("You're in the ruins of a tower somewhere in the " +
        "remains of " + CASTLE_NAME + ". The surfaces seem " +
        "to be fairly well preserved and the walls must be " +
        "either very thick or just internal walls. To the " +
        "east, the lower level of this tower extends off in a " +
        "long, arched stone hall. A narrow corridor is cut into the " +
        "southern wall, and a third exit stands in the north wall. " +
        "Unlike the others, however, the north exit is elevated several " +
        "feet from the floor, with a narrow stone stairway leading " +
        "up to it alongside the wall. " +
        "Upon the west wall, a massive carving of strange lion-headed " +
        "creature dominates the room, gazing eastwards down the hall.\n\n");

    add_item(({"ceiling", "roof"}),
        "Looking up, you realize the ceiling is far above your head, and " +
        "that the tower you are in doesn't have different floors, " +
        "but just a walkway around the upper level, though there is " +
        "no apparent way of reaching it from here.\n");
    add_item(({"walls"}),
        "The walls of this room are quite unremarkable in " +
        "structure, built from the same grey stone as the " +
        "rest of the ruins.\n");
    add_item(({"north wall", "staircase", "landing"}),
        "The north wall contains an elevated exit into a " +
        "passage that leads northwards. Raised off the floor " +
        "several feet, a small staircase climbs up the short " +
        "distance to a landing before turning into the corridor.\n");
    add_item(({"south wall"}),
        "A small, arched exit leads southwards into a darkened " +
        "tunnel though the south wall.\n");
    add_item(({"west wall", "carving", "chimera"}),
        "Against the west wall stands a massive carving of " +
        "a strange creature with a lion's head, a goat's body " +
        "and the tail of a serpent.\n");
    add_item(({"floor", "ground", "dust", "debris"}),
        "The ground is quite ordinary, grey stone covered in " +
        "a layer of dust and debris that has fallen from the " +
        "ceiling and walls, over the years.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "build2-build3", "north", "@@take_the_stairs");
    add_exit(RUIN + "build2-build4", "east");
    add_exit(RUIN + "build1-build2", "south");
}
