#include "defs.h"

inherit STDROOM;

void
create_room()
{
    set_short("in the west tunnel of "+CASTLE_NAME);
    set_long("You're in a dark tunnel, underneath " +
        "the west side of "+CASTLE_NAME+", judging " +
        "by the courtyard outside to the south. The " +
        "passage seems a bit odd, as the walls and " +
        "ceiling near the south exit are stone " +
        "blocks, but towards the north seem to " +
        "become solid stone. Heavy iron sconces, " +
        "now coated in a thin layer of rust and " +
        "dust, are embedded firmly in the walls. " +
        "The passage continues northwards into " +
        "darkness, and southwards, to what appears " +
        "to be a courtyard of some sort. To the " +
        "east, a narrow doorway leads into a dark " +
        "room.\n\n");

    add_item(({"ceiling", "roof"}),
        "The ceiling is a combination of blocks and " +
        "solid stone here, it seems that this passage " +
        "heads north beneath solid stone.\n");
    add_item(({"floor","ground"}),
        "The ground here is made simply from hard-packed " +
        "earth, now pounded by falling rubble from " +
        "the ceiling and walls.\n");
    add_item(({"walls"}),
        "The walls here are a combination of blocks of " +
        "stone towards the south end of the room, and " +
        "solid stone towards the north.\n");
    add_item(({"sconces"}),
        "Heavy iron rings form torch sconces high up on " +
        "the walls.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "w_tunnel_2", "north");
    add_exit(RUIN + "w_guard", "east");
    add_exit(RUIN + "sw_court_nw", "south");
}

