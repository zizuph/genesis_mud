#include "/d/Krynn/common/defs.h"
#include "/d/Calia/sys/water.h"
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

inherit SAIL_ROOM_BASE;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "intertide", }) );

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
 
    add_item(({"rugged coastline","coastline","barren coastline", "peninsula",
       "barren peninsula",
       "northern wastes","wastes","hills","dry rolling hills","rolling hills"}),
       "To your south is the tip of a rugged and barren peninsula, the southwestern " +
       "tip of the Nortern Wastes known as 'Destiny's Hand'. " +
       "Dry rolling hills make up the coastline, populated by little other than " +
       "wild goats and desert eagles.\n");
    add_item(({"turbidus ocean","ocean","sea"}),
        "To your north stretches the Turbidus Ocean - a massive body of water " +
        "that extends from the Courrain Ocean in the east, across northern " +
        "Ansalon to the Sirrion Sea in the west.\n");
    add_item(({"bay"}),
        "To your southeast is a bay full of dangerous shoals and sandbars, beyond " +
        "which you notice a sheltered beach suitable for mooring a ship and making " +
        "landfall.\n");
    add_item(({"sheltered beach","beach","sheltered sandy beach","sandy beach"}),
        "To your southeast you can make out a sheltered sandy beach that would " +
        "be suitable to moor a ship and make landfall.\n");
    add_item(({"dangerous shoals","shoals","sandbars"}),
        "The bay to your southeast is riddled with dangerous shoals and sandbars " +
        "that would require skilled navigation to bypass and get to a sheltered " +
        "sandy beach on the edge of the bay.\n"); 

    add_row_exit(ROOM + "6z", "east", 0, 1);
    add_row_exit(ROOM + "6x", "west", 0, 1);
    add_row_exit(ROOM + "7y", "north", 0, 1);
    add_row_exit(ROOM + "5x", "southwest", 0, 1);
    add_row_exit(ROOM + "5z", "southeast", 0, 1);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_sea_room();
}

string
short_descr()
{
    return "near the tip of a rugged and barren peninsula";
}
 
string
long_descr()
{
    return turbidus_sea_desc() + "To your south is the tip of a rugged and barren " +
        "peninsula, the beginning of a bay to your southeast full of dangerous " +
        "shoals and sandbars that form a natural barrier to a sheltered sandy " +
        "beach suitable for mooring a ship. "+
        query_sailing_difficulty_desc()+ "\n";
}