#include "local.h"
inherit ROOM_BASE;

public void
create_sea_room()
{
    ::create_sea_room();

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("the southern coastline of Goodlund");

    add_item(({"coastline", "peninsula", "goodlund peninsula",
        "goodlund", "wendle woods", "beast's run", 
        "beasts run", "woods"}),
        "To your north you make out the coastline of Goodlund, " +
        "a land of lush forests - the Wendle Woods, home to " +
        "tribes of centaur, and Beast's Run where Kagonesti elves " +
        "are known to call home.\n");

    add_item(({"water", "sea", "ocean", "courrain", 
        "south courrain ocean" }), 
        "The blue-gray waters of the South Courrain Ocean is rough and " +
        "white-capped, with strong currents running counter-clockwise from " +
        "east to west along the coastline of the continent of Ansalon.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "oceanfloat", }) );
}

