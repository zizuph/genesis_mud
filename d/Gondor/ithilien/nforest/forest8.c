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
    set_areadesc("thicket of brambles");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("oak");
    set_extraline("The land is rising in a long slope to the east. "
      + "The ground is broken, with many clefts and pits cutting "
      + "deep into it. Between the stems of the trees thickets and "
      + "wastes of brambles are growing.");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}), BSN(
        "Beyond the tree tops to the east the dark mountains of Mordor "
      + "loom like a black shadow. That mountain-range is called the "
      + "Ephel Duath, the Shadowy Fence, and it is the outer guard of "
      + "the Black Land."));
    add_item(({"hills", "slopes", "slope", }), BSN(
	"The land between the mountains to the east and the river to the "
      + "west is falling in one long slope down towards the river. "
      + "Here, at the higher end, the slope is covered by trees and "
      + "bushes, and riddled with clefts and pits."));
    add_item(({"ground", "pits", "clefts", "cleft", "pit", }), BSN(
	"The ground is broken here, and the brambles and bushes hide "
      + "many dark pits and deep clefts, and sometimes large "
      + "bush-shrouded hollows cut into the slope. But still the land is "
      + "rising steadily to the east, as if trying to reach up to "
      + "the Ephel Duath."));
    add_item(({"forest","wood","woodlands","trees",}), BSN(
	"The forest gets ever denser as the slope rises towards the "
      + "east. The trees stand closer together here, and between them "
      + "thickets and wastes of brambles grow."));
    add_item(({"thicket", "wastes", "brambles", "bushes", }),
	"Thickets and wastes of brambles grow in the narrows spaces "
      + "between the tree stems.\n");
    add_item(({"anduin", "great vales", "vales", "river", }),
	"The Anduin is hidden by the tops of the trees growing here.\n");

    add_exit(ITH_DIR + "nforest/hogback", "east", 0, 4);
    add_exit(ITH_DIR + "nforest/forest7", "west", 0, 4);

    for (i = 0, s = strlen(name); i < s; i++)
	seed += name[i];

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("ithilien"), seed),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("middle earth"), seed + 1),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("forest"), seed + 2), }),
                  ({ "ground", "field", "flowers", "forest", }), 3);
}

