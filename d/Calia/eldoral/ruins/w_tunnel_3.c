#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("a darkened tunnel beneath "+CASTLE_NAME);
    set_long("You are in a long, dark tunnel which " +
        "seems to be cut through solid stone itself. " +
        "The walls are perfectly polished smooth, " +
        "however, and the floor appears to have " +
        "been carefully surfaced beneath the layers " +
        "of dust which now blanket it. Upon the " +
        "cold walls are mounted several iron sconces. " +
        "The passage extends southwards into darkness, " + 
        "but to the north, it appears that it emerges " +
        "back into the daylight.\n\n");

    add_item(({"ceiling", "roof"}),
        "The dark, squared-off ceiling appears to have " +
        "been cut out of the surrounding stone through " +
        "which this tunnel passes.\n");
    add_item(({"floor","ground"}),
        "The ground here is made simply from hard-packed " +
        "earth, now pounded by falling rubble from " +
        "the ceiling and walls.\n");
    add_item(({"walls", "wall"}),
        "The smoothly cut walls here look to have been " +
        "cut from the surrounding stone, and the only " +
        "things which break up it's clean surface are " +
        "jagged holes where pieces of stone have fallen " +
        "away, and rusted iron sconces.\n");
    add_item(({"sconces","sconce", "rusty sconces", "iron sconces"}),
        "Heavy iron rings form torch sconces high up on " +
        "the walls.\n");

    DARK;
    INSIDE;

    add_exit(RUIN + "nw_path_1", "north");
    add_exit(RUIN + "w_tunnel_2", "south");
}
