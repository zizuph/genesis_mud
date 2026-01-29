#include "local.h"
inherit ROOM_BASE;

public void
create_sea_room()
{
    ::create_sea_room();

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("the southern coastline of the Dairly Plains");

    add_item(({"dairly plains", "plains", "north", "grasslands",
        "scrublands", "grasses", "copses", "woods", "coastline", 
        "laughing lands" }),
        "To your north is the southern coastline of the " +
        "Dairly Plains - rolling grasslands " +
        "of verdant grasses broken by spare copses of woods and " +
        "scrublands - and the Laughing Lands, so named due to " +
        "the sound of the cackling, nomadic, hyena-type gnolls " +
        "that dwell in these endless dry grass plains.\n");

    add_item(({"water", "sea", "ocean", "courrain", 
        "south courrain ocean" }), 
        "The blue-gray waters of the South Courrain Ocean are rough and " +
        "white-capped, with strong currents running counter-clockwise from " +
        "east to west along the coastline of the continent of Ansalon.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "oceanfloat", }) );
}

