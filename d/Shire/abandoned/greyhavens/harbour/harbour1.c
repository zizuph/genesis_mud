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
    areatype = 8;
    areadesc = "grassy area";
    grass = "dark green";

    extraline = "The Grey Havens Road leads from the harbour area " +
        "to the city of Grey Havens, or Mithlond, itself. To the southwest " +
	"lie the docks for passenger vessels. Far to the northeast rise the " +
	"city walls.\n";

    add_item("road", "The road is ancient but well-kept.\n");

    add_exit(GH_HARBOUR_DIR +  "harbour2", "northeast");
    add_exit("/d/Shire/common/greyhaven/path3", "southwest");

}
