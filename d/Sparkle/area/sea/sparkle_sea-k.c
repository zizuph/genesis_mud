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

int
no_go()
{
    write("Strong currents frustrate any progress you make trying to sail north.\n");
    return 1;
}

string
long_descr()
{
    return "You find yourself upon the vast waters of the Toroid High Seas, " +
        "the great ocean that surrounds Genesis and links the main continents " +
        "and domains that make up this world. " + query_sailing_difficulty_desc()+ "\n";
}