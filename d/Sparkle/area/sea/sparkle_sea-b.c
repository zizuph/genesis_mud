#include "local.h"
#include <stdproperties.h>

inherit ROOM_BASE;

// Function used in fishing code to allow for area-specific
// fish to be caught.

public string
query_fishing_area()
{
    return "blue_bottom_bay";
}

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
    set_sailing_fail_message("The waters of Blue Bottom Bay are not " +
        "suitable for unskilled sailors!\n");
    set_sailing_difficulty_message("You navigate across the calm " +
        "waters of Blue Bottom Bay!\n");

    set_short("the calm waters of Blue Bottom Bay");
    set_long("You are upon the calm waters of Blue Bottom Bay, a " +
        "body of water the stretches out all around you. " +
        "To your west you can just make out on the horizon " +
        "the coastline, while to your north is the Pen Sea " +
        "that eventually leads to the challenging Toroid High Seas.\n");

    add_item(({"coastline","coast","horizon","west","land"}),
        "To your west you can just make out a thin line of " +
        "land on the horizon.\n");

    add_item(({"bay", "blue bottom bay" }), 
        "Named after the calm blue-gray waters here, Blue Bottom " +
        "Bay is a popular haven for casual fisherman, where schools of " +
        "small fish are common. It is also the only location of the rare " +
        "fortune-changing golden fish!\n");

    add_item(({"water", "sea", "ocean","pen sea", "pensea" }), 
        "The blue-gray waters of the Pen Sea to your north are " +
        "relatively calm, and considered kind to novice sailors.\n");

    add_std_exits();
}

