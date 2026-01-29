#include "../local.h"
#include <stdproperties.h>

inherit SPARKLE_SEA + "sparkle_sea-k";

#define SPARKLE_LINK "/d/Genesis/start/human/town/jetty1"

public void
create_sea_room()
{
    ::create_sea_room();

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(HIGH_SEAS_DIFFICULTY);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The open waters of the high seas are highly " +
        "dangerous, with only master navigators capable of sailing!\n");
    set_sailing_difficulty_message("\n\nYou navigate skillfully " +
        "into the toroid's high seas!\n\n\n");

    set_short("the vast Toroid high seas");
    set_long("@@long_descr");

    add_item(({"high sea","ocean","sea","high seas of genesis","seas",
        "water","toroid","toroid high seas"}),
        "Around you stretches the high seas of Genesis, a vast body of water " +
        "that extends across the great toroid to many large continents " +
        "and a number of smaller landmasses as well.\n");
    add_item(({"continents","landmasses"}),
        "You are far from any continent or landmass, and can only see the " +
        "high seas of Genesis all around you.\n");

    add_row_exit(KRYNN_LINK, "south", 0, 1);

    add_std_exits();

}

