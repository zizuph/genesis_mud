#pragma save_binary
#pragma strict_types

#include "local.h"

inherit GREY_HAVENS;

void
create_gh_room()
{    area = "not far from";
    areaname = "the City of Mithlond";
    land = "Eriador";
    areatype = 8;
    areadesc = "grassy area";
    grass = "dark green";

    extraline = "Down the gently sloping road to the southwest is " +
	"the harbour area. " +
        "White towers rise above the city walls of Grey Havens to " +
	"the northeast. Waves crash upon the shore in the west. " +
	"Off to the the east is a dense forest.\n";

    add_exit(GH_HARBOUR_DIR +  "harbour4.c", "south");
    add_exit(GH_HARBOUR_DIR +  "harbour14.c", "east");

}
