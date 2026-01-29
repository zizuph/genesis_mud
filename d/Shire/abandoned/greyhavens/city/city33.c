#pragma save_binary
#pragma strict_types

#include "local.h"

inherit GREY_HAVENS;

void
create_gh_room()
{
    area = "heart of";
    areaname = "the City of Mithlond";
    land = "Eriador";
    areatype = 8;
    areadesc = "city";

    extraline = " " +
        "\n";

    add_exit(CITY_DIR +  "city32.c", "south");
    add_exit(CITY_DIR +  "city56.c", "east");
    add_exit(CITY_DIR +  "city34.c", "north");

}
