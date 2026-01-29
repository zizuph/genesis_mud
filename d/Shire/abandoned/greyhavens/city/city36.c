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

    add_exit(CITY_DIR +  "city35.c", "south");
    add_exit(CITY_DIR +  "city61.c", "east");
    add_exit(CITY_DIR +  "city37.c", "northwest");
    add_exit(CITY_DIR +  "city43.c", "north");

}
