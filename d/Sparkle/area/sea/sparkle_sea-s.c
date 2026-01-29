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

    set_short("upon the Pen Sea");
    set_long("You are upon the Pen Sea, a body of water the stretches " +
        "out all around you. To your west you can just make out on " +
        "the horizon the coastline, while to your east the Pen Sea " +
        "eventually leads to the challenging Toroid High Seas.\n");

    add_item(({"coastline","coast","horizon","west","land"}),
        "To your west you can just make out a thin line of " +
        "land on the horizon.\n");

    add_item(({"water", "sea", "ocean","pen sea", "pensea" }), 
        "The blue-gray waters of the Pen Sea are relatively calm, " +
        "and considered kind to novice sailors.\n");

    add_std_exits();
}

