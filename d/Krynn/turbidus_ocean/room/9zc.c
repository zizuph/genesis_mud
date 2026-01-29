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
 
    add_item(({"rugged coastline","coastline","barren coastline",
       "northern wastes","wastes","hills","dry rolling hills","rolling hills"}),
       "To your southeast stretches a rugged and barren coastline, the northern tip " +
       "of the vast Northern Wastes. Dry rolling hills make up the coastline before " +
       "you, with desolate sand dunes extending for leagues inland.\n");
    add_item(({"sand dunes","dunes","desolate sand dunes","inland"}),
       "Beyond the dry rolling hills begin great sand dunes that stretch far inland.\n");
    add_item(({"turbidus ocean","ocean","sea"}),
        "To your north stretches the Turbidus Ocean - a massive body of water " +
        "that extends from the Courrain Ocean in the east, across northern " +
        "Ansalon to the Sirrion Sea in the west.\n");

    add_row_exit(ROOM + "10zc", "north", 0, 1);
    add_row_exit(ROOM + "9zd", "east", 0, 1);
    add_row_exit(ROOM + "9zb", "west", 0, 1);
    add_row_exit(ROOM + "8zb", "southwest", 0, 1);

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
    return "near a rugged coastline in the Turbidus Ocean";
}
 
string
long_descr()
{
    return turbidus_sea_desc() + "To your southeast you can make out a rugged " +
        "coastline of dry, rolling hills. "+
        query_sailing_difficulty_desc()+ "\n";
}