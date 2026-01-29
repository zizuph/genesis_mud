#include "defs.h"

inherit STDROOM;

void
create_room()
{
    set_short("in the south tunnel of "+CASTLE_NAME);
    set_long("You're in a dark tunnel, underneath " +
        "the south side of "+CASTLE_NAME+", judging " +
        "by the courtyard outside to the west. The " +
        "passage seems a bit odd, as the walls and " +
        "ceiling near the west exit are stone blocks, " +
        "but towards the east seem to become solid " +
        "stone. Heavy iron " +
        "sconces, now coated in a thin layer of rust " +
        "and dust, are embedded firmly in the walls. " +
        "The passage to the east appears to have " +
        "collapsed some time ago, and is now impossible " +
        "to enter.  Westwards, the passage empties " +
        "into what appears to " +
        "be a courtyard of some sort. To the north, " +
        "a narrow doorway leads into a dark room.\n\n");

    add_item(({"ceiling", "roof"}),
        "The ceiling is a combination of blocks and " +
        "solid stone here, it seems that this passage " +
        "heads east beneath solid stone.\n");
    add_item(({"floor","ground"}),
        "The ground here is made simply from hard-packed " +
        "earth, now pounded by falling rubble from " +
        "the ceiling and walls.\n");
    add_item(({"walls"}),
        "The walls here are a combination of blocks of " +
        "stone towards the west end of the room, and " +
        "solid stone towards the east.\n");
    add_item(({"sconces", "sconce"}),
        "Heavy iron rings, mounted at regular intervals " +
        "along the stone walls, serve as torch " +
        "sconces.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "s_guard", "north");
    add_exit(RUIN + "sw_court_se", "west");
}

