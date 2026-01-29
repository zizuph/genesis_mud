#include "local.h"
inherit ROOM_BASE;

public void
create_sea_room()
{
    ::create_sea_room();

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("the coastline of the Dairly Plains");

    add_item(({"dairly plains", "plains", "west", "grasslands",
        "scrublands", "grasses", "copses", "woods", "coastline"}),
        "To your west are the Dairly Plains, rolling grasslands " +
        "of verdant grasses broken by spare copses of woods and " +
        "scrublands.\n");

    add_item(({"water", "sea", "ocean", "courrain", 
        "south courrain ocean" }), 
        "The blue-gray waters of the South Courrain Ocean are rough and " +
        "white-capped, with strong currents running counter-clockwise from " +
        "east to west along the coastline of the continent of Ansalon.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "oceanfloat", }) );
}

