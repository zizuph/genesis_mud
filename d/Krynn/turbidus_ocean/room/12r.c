#include "/d/Krynn/common/defs.h"
#include "/d/Calia/sys/water.h"
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

inherit SAIL_ROOM_BASE;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "oceanfloat", }) );

void
reset_sea_room()
{
    set_searched(0);

    return;
}

void
create_sea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");
 
    add_item(({"high sea","ocean","sea","high seas of genesis","seas",
        "water","toroid"}),
        "Around you stretches the high seas of Genesis, a vast body of water " +
        "that extends across the great toroid to many large continents " +
        "and a number of smaller landmasses as well.\n");
    add_item(({"continents","landmasses"}),
        "You are far from any continent or landmass, and can only see the " +
        "high seas of Genesis all around you.\n");

    add_row_exit(ROOM + "11r", "south", 0, 1);
    add_row_exit(ROOM + "12s", "east", 0, 1);
    add_row_exit(ROOM + "13r", "north", 0, 1);
    add_row_exit(ROOM + "12q", "west", 0, 1);


    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(HIGH_SEAS_DIFFICULTY);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The open waters of the high seas are highly " +
        "dangerous, with only master navigators capable of sailing!\n");
    set_sailing_difficulty_message("You navigate skillfully through the dangerous " +
        "open waters of the high seas!\n");

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_sea_room();
}

string
short_descr()
{
    return sea_short();
}
 
string
long_descr()
{
    return sea_desc() + query_sailing_difficulty_desc()+ "\n";
}