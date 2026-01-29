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

    extraline = "The Mithlond lighthouse lies to the west.\n";

    add_item("path", "A well-worn path descending towards the Mithlond " +
        "lighthouse.\n");
    add_item("lighthouse", "The Mithlond lighthouse rises from " +
	"a jetty on the rocky shoreline.\n");

    add_exit(GH_HARBOUR_DIR +  "harbour3.c", "south");
    add_exit(GH_HARBOUR_DIR +  "harbour20.c", "west");

}
