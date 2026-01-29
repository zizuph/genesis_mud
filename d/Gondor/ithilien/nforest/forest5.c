#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  deer;

public void
create_area_room()
{
    int     i, s,
	    seed;
    string  name = explode(file_name(TO), "/")[5];

    set_areatype(7);
    set_areadesc("open woodland");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("ilex");
    set_extraline("The forest is wide open here, with scattered groups "
      + "of large trees and wide glades between them. A steep cliff drops "
      + "down to the south, at its foot a small stream running quickly "
      + "westwards.");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        "From here the mountains in the east are hidden by many tree tops.\n");
    add_item(({"forest","wood","woodlands","trees","glades"}), BSN(
        "Great ilexes of huge girth stand dark and solemn in wide glades "
      + "with here and there among them hoary ash-trees, and giant oaks. "
      + "In the glades grow many herbs and flowers, giving off sweet "
      + "and pungent smells that fill the air."));
    add_item(({"cliff", "stream", "valley", }), BSN(
	"The cliff is the northern wall of a valley that cuts through the "
      + "land here. Down at its bottom, the swift stream is hurrying "
      + "towards the Anduin, murmuring loudly over the many rocks and "
      + "stones in its bed."));
    add_item(({"anduin", "great vales", "vales", "river", }), BSN(
        "Far west, beyond the vales that stretch from the brink of the "
      + "hills towards to bank of the river, the river Anduin itself can "
      + "be seen, flowing gently southwards, like a broad band of blue "
      + "dividing the green lands on both banks."));
    add_exit(ITH_DIR + "nforest/forest4", "northwest", 0, 4);
    add_exit(ITH_DIR + "nforest/forest6", "southeast", 0, 4);
    set_up_herbs(({ ONE_OF_LIST(HERB_MASTER->query_herbs("ithilien")), 
                    ONE_OF_LIST(HERB_MASTER->query_herbs("middle earth")),
                    (HERB_DIR + "seregon.c"), }),
                  ({ "ground", "field", "flowers", "forest", }), 5);

    reset_room();
}

string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}

public void
reset_room()
{
    object  clock = find_object(CLOCK);

    set_searched(-2);

    if (clock->query_war())
	return;

    if (objectp(deer))
	return;

    deer = clone_object(NPC_DIR + "deer");
    deer->set_restrain_path(ITH_DIR + "nforest/");
    deer->set_random_move(5);
    deer->set_whimpy(50);
    deer->move_living("down", TO);

}

