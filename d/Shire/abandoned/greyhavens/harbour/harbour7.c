#pragma save_binary
#pragma strict_types

#include "local.h"

inherit GREY_HAVENS;

void
create_gh_room()
{
    area = "southeast of";
    areaname = "the City of Mithlond";
    land = "Eriador";
    areatype = 7;
    areadesc = "narrow trail";
    grass = "dark green";
    treetype = "ancient grey oak";
    extraline = "Ancient grey oaks tower above.\n";

    add_exit(GH_HARBOUR_DIR +  "harbour8.c", "south", 0, 1, 1);
    add_exit(GH_HARBOUR_DIR +  "harbour6.c", "west", 0, 1, 1);

}
