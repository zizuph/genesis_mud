#include "local.h"
inherit ROOM_BASE;

public void
create_sea_room()
{
    ::create_sea_room();

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("the coastline of Silvanesti");

    add_item(({ "coastline", "silvanesti", "forest" }),
        "To your southwest is the coastline of Silvanesti, the " +
        "great forest kingdom of the high elves. Suspicious of " +
        "outsiders, the Silvanesti elves are likely the most " +
        "isolationist nation on the continent.\n");

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

