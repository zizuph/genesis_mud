#pragma save_binary
#pragma strict_types

#include "local.h"

inherit GREY_HAVENS;

void
create_gh_room()
{
    string light_status = "";

    area = "not far from";
    areaname = "the City of Mithlond";
    land = "Eriador";
    areatype = 11;
    areadesc = "rocky shore";

    extraline = "The Mithlond Lighthouse stands on a natural " +
        "jetty protuding into the Bay of Lune.\n";

    if (CLOCK->query_am_pm() == "pm")
      light_status = " The glass room atop the lighthouse is brightly lit.";

    add_item("lighthouse", "The Mithlond Lighthouse rises from the " +
	"Jetty formed of enormous boulders. It is a brilliant white." +
        light_status + "\n");
    
    add_exit(GH_HARBOUR_DIR +  "harbour20.c", "east");

}
