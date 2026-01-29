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
    areatype = 11;
    areadesc = "rocky shore";

    extraline = "The Mithlond lighthouse sits to the west.\n";

    add_item("path", "A well-worn path descending towards the Mithlond " +
        "lighthouse.\n");

    add_exit(GH_HARBOUR_DIR +  "harbour21.c", "west");
    add_exit(GH_HARBOUR_DIR +  "harbour19.c", "east");

}
