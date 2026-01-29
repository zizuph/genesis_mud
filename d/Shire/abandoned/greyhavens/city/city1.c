#pragma save_binary
#pragma strict_types

#include "local.h"

inherit GREY_HAVENS_CITY_ROOM;


void
create_gh_room()
{
    area = "boardwalk";
    areaname = "the City of Mithlond";
    land = "Eriador";
    areatype = 8; // boardwalk
    areadesc = "city";

    extraline = " " +
        "\n";

    add_exit(CITY_DIR +  "city2.c", "northwest");
    add_exit(CITY_DIR +  "city29.c", "north");
    add_exit(CITY_DIR +  "city5.c", "northeast");

}
