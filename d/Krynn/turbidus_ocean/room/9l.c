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
 
    add_item(({"turbidus ocean","ocean","sea"}),
        "To your north stretches the Turbidus Ocean - a massive body of water " +
        "that extends from the Courrain Ocean in the east, across northern " +
        "Ansalon to the Sirrion Sea in the west.\n");

    add_row_exit(ROOM + "8l", "south", 0, 1);
    add_row_exit(ROOM + "9m", "east", 0, 1);
    add_row_exit(ROOM + "10l", "north", 0, 1);
    add_row_exit(ROOM + "9k", "west", 0, 1);


    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(ROUGH_SEAS_DIFFICULTY);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The open waters of the Turbidus Ocean are " +
        "rough and beyond your sailing skills to navigate!\n");
    set_sailing_difficulty_message("You navigate skillfully through the rough " +
        "open waters of the Turbidus Ocean!\n");

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_sea_room();
}

string
short_descr()
{
    return turbidus_sea_short();
}
 
string
long_descr()
{
    return turbidus_sea_desc() + query_sailing_difficulty_desc()+ "\n";
}