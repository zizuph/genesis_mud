#pragma strict_types

#include "defs.h"

inherit NECOURTBASE;

public void
create_room()
{
    set_long("You are at the midway point of a narrow " +
        "stone staircase that climbs the side of the " +
        "south wall of a courtyard in the northeastern " +
        "ruins of " + VBFC_ME("castle_name") + ". The stairs slant " +
        "diagonally across the face of the wall, upwards " +
        "to the east and downwards to the west. To " +
        "the north spreads out a wide, square-shaped " +
        "courtyard of ancient construction. " +
        "In the far east end of the north wall, one " +
        "large hole has breached the wall entirely, " + 
        "permitting passage between the courtyard and " +
        "the evergreen forest beyond. In the center " +
        "of the courtyard, twelve black stone pillars " +
        "stand in vigilance over a strange pattern " +
        "embedded in the stones of the courtyard " +
        "floor. In fact, there's a strangely good " +
        "view of the pattern from here.\n\n");

    create_courtyard();

    set_short("midway along a staircase on the south " +
        "wall of a courtyard");

    remove_item("stairs");
    remove_item("stairway");
    remove_item("staircase");
    remove_item("pattern");

    add_item(({"stairs", "stairs", "staircase"}),
        "The staircase is quite narrow, little more " +
        "than blocks of stone that jut out from the " +
        "wall a little further than others. Fortunately, " +
        "it's quite stable.\n");
    add_item(({"pattern"}),
        "Strangely enough, the pattern seems to be quite " +
        "clear from here, as if the pillars are " +
        "positioned to not interfere with it when viewed " +
        "from this position. The seemingly abstract " +
        "swirls, loops and lines of the pattern seem " +
        "to merge together, and almost look like a " +
        "chimera. It's a very odd rendition, and might " +
        "be an interesting souvenir if you could copy " +
        "it somehow.\n");

    add_exit(RUIN + "ne_walk_5", "up");
    add_exit(RUIN + "ne_court_sw", "down");
}

public string
query_pattern()
{
    return "chimera";
}
