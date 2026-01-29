#include "defs.h"

inherit SWCOURTBASE;

void
create_room()
{
    set_long("You are approximately halfway up the " +
        "stairs climbing the eastern wall of a " +
        "courtyard in " + VBFC_ME("castle_name") + 
        ". The courtyard itself stretches out below " +
        "you towards the western outer wall. " +
        "Beneath you in the courtyard " +
        "itself, you can see the center of it is " +
        "home of a series of obelisks placed at " +
        "various points along a pattern of black " +
        "stones laid into the grey floor of the " +
        "courtyard. The stairs continue upwards to " + 
        "the north, and down to the courtyard to the " +
        "north.\n\n");

    create_courtyard();

    set_short("on the eastern stairs of the southwest " +
        "courtyard of " + VBFC_ME("castle_name"));

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
        "from this position. Its seemingly abstract " +
        "swirls, loops and lines of the pattern seem " +
        "to merge together, and almost look like a " +
        "warrior. It's a very odd rendition, and might " +
        "be an interesting souvenir if you could copy " +
        "it somehow.\n");

    add_exit(RUIN + "sw_wall_2", "up");
    add_exit(RUIN + "sw_court_se", "down");
}

public string
query_pattern()
{
    return "warrior";
}
