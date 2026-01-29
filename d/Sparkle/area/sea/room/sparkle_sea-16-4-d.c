#include "../local.h"
#include <stdproperties.h>

inherit SPARKLE_SEA + "sparkle_sea-d";

#define SPARKLE_LINK "/d/Genesis/start/human/town/jetty1"

public void
create_sea_room()
{
    ::create_sea_room();

    set_long("You are upon the seas near the port hub " +
        "town of Sparkle. To your west private ships " +
        "may dock, while to your east stretches the body " +
        "of water known as the Pen Sea that eventually " +
        "leads to the Toroid High Seas.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(NORMAL_DIFFICULTY);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The open waters of the seas are not " +
        "suitable for unskilled sailors!\n");
    set_sailing_difficulty_message("You navigate across the calm " +
        " waters of the Pen Sea!\n");

    set_sink_path(ROOM + "sink_room");

    reset_sea_room();

    add_row_exit(SPARKLE_LINK, "west", 0, 1);

}

