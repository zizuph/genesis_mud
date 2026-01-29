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
       "To your south stretches a rugged and barren coastline, the southwestern " +
       "tip of the Nortern Wastes known as 'Destiny's Hand'. Dry rolling hills " +
       "make up the coastline, populated by little other than wild goats and " +
       "desert eagles.\n");
    add_item(({"turbidus ocean","ocean","sea"}),
        "To your north stretches the Turbidus Ocean - a massive body of water " +
        "that extends from the Courrain Ocean in the east, across northern " +
        "Ansalon to the Sirrion Sea in the west.\n");
    add_item(({"jetty","pirate jetty","reefcutter's jetty", "jagged rocks",
        "rocks","bay","reefcutters jetty"}),
        "To your east is Reefcutter's Jetty, a dock for pirates and " +
        "corsairs to sell their ill-gotten loot and drink rum! The jetty " +
        "has been cleverly built in a bay crowded with jagged rocks, " +
        "so only a professional navigator would be able to sail to " +
        "the jetty without holing their ship!\n");

    add_row_exit(ROOM + "5u", "northeast", 0, 1);
    add_row_exit(ROOM + "5t", "north", 0, 1);
    add_row_exit(ROOM + "4s", "west", 0, 1);
    add_row_exit(ROOM + "jetty", "east", 0, 1);

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
    return "near a pirate jetty along a rugged coastline";
}
 
string
long_descr()
{
    return turbidus_sea_desc() + "To your south you can make out a rugged " +
        "coastline of dry, rolling hills. To your east is a pirate jetty " +
        "craftily nestled in a bay between jagged rocks. You could " +
        "risk docking there if you had confidence in your sailing skill! "+
        query_sailing_difficulty_desc()+ "\n";
}