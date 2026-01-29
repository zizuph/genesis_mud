#pragma save_binary
#pragma strict_types

#include "local.h"

inherit GREY_HAVENS;

void
create_gh_room()
{
    area = "not far from";
    areaname = "the City of Mithlond";
    land = "Eriador";
    areatype = 1;
    areadesc = "woods";
    grass = "dark green";
    extraline = "The ancient forest is quite dense.\n";

    add_exit(GH_HARBOUR_DIR +  "harbour18.c", "south", 0,1,1);
    add_exit(GH_HARBOUR_DIR +  "harbour8.c", "west", 0,1,1);
    add_exit(GH_HARBOUR_DIR +  "harbour17.c", "north", 0,1,1);

}
