#include "local.h"
inherit ROOM_BASE;

// Function used in fishing code to allow for area-specific
// fish to be caught.

public string
query_fishing_area()
{
    return "balifor";
}

public void
create_sea_room()
{
    ::create_sea_room();

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("the Bay of Balifor");

    add_item(({"bay", "bay of balifor"}),
        "The Bay of Balifor is situated between the Khurman Sea to " +
        "the north and the Southern Courrain Ocean. The Bay is known " +
        "for many storms, with the warmed water from the north colliding " +
        "with the cool air from the south.\n");

    add_item(({"water", "sea", "ocean", "courrain", 
        "south courrain ocean" }), 
        "The blue-gray waters of the South Courrain Ocean is rough and " +
        "white-capped, with strong currents running counter-clockwise from " +
        "east to west along the coastline of the continent of Ansalon.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "oceanfloat", }) );
}

