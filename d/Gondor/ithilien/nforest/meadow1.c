#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    int     i, s,
	    seed;
    string  name = explode(file_name(TO), "/")[5];

    set_areatype(7);
    set_areadesc("steep bushy slope");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("ash");
    set_extraline("The ground is falling steeply towards the west, "
        + "between higher ground to the north and the south, entering "
        + "one of the great vales of Ithilien. The edge of the forest "
        + "is to the east, following a ridge that runs in a straight "
        + "line from north to south.");
    add_exit(ITH_DIR + "nforest/forest3", "northeast", 0, 4);

    for (i = 0, s = strlen(name); i < s; i++)
	seed += name[i];

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("ithilien"), seed),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("ithilien"), seed),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("middle earth"), seed + 1) }),
                  ({ "ground", "field", "flowers", "forest", }), 3);
}

