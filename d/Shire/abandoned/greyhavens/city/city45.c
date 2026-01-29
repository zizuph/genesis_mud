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

    add_exit(CITY_DIR +  "city46.c", "south");
    add_exit(CITY_DIR +  "city44.c", "west");
    add_exit(CITY_DIR +  "city14.c", "east");
    add_exit(CITY_DIR +  "city15.c", "north");

}
