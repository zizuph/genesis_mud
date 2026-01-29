#include "local.h"
#include <stdproperties.h>

inherit ROOM_BASE;

public void
create_sea_room()
{
    ::create_sea_room();

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(NORMAL_DIFFICULTY);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The open waters of the Pen Sea are not " +
        "suitable for unskilled sailors!\n");
    set_sailing_difficulty_message("You navigate across the calm " +
        "waters of the Pen Sea!\n");

    set_short("near the docks of Sparkle");
    set_long("You are near the harbour docks of the port town of Sparkle " +
        "- a bustling hub for merchants, sailors and adventurers. To " + 
        "your east extends the open waters of the Pen Sea.\n");

    add_item(({"sparkle","town","port town","port town of sparkle", 
        "harbour", "docks"}),
        "to your west are the docks of the port town of Sparkle.\n");

    add_item(({"water", "sea", "ocean","pen sea", "pensea" }), 
        "The blue-gray waters of the Pen Sea are relatively calm, " +
        "and considered kind to novice sailors. A gentle current runs " +
        "from north to south along the coastline bordering Sparkle.\n");

    add_std_exits();
}

