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

    add_exit(CITY_DIR +  "city36.c", "southeast");
    add_exit(CITY_DIR +  "city43.c", "east");
    add_exit(CITY_DIR +  "city38.c", "north");

}
