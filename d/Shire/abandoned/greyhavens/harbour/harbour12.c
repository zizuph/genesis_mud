#pragma save_binary
#pragma strict_types

#include "local.h"

inherit GREY_HAVENS;

void
create_gh_room()
{
    area = "not far from";
    areaname = "the Grey Havens Road";
    land = "Eriador";
    areatype = 15;
    areadesc = "rocky shore";

    extraline = "The rocky shorline on the Gulf of Luhn rises " +
        "gently to the Grey Havens Road.\n";

    add_exit(GH_HARBOUR_DIR +  "harbour3.c", "east");

}
