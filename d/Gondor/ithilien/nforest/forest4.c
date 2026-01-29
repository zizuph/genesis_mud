#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object *rabbit = allocate(2 + random(3));

public void
create_area_room()
{
    int     i, s,
	    seed;
    string  name = explode(file_name(TO), "/")[5];

    set_areatype(7);
    set_areadesc("wide glade");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("oak");
    set_extraline("A narrow valley cuts its path through the forest "
      + "south of here, and steep slopes are falling down to the "
      + "valley. Oaks and some ash-trees are standing in scattered "
      + "groups in the glade, getting closer to the north, where "
      + "they change into the forest.");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        "From here the mountains in the east are hidden by many tree tops.\n");
    add_item(({"forest","wood","woodlands","trees"}), BSN(
	"The trees of the forest are large and scattered here, becoming "
      + "denser to the north. Here in the glade are just a few groups "
      + "of oaks and ash trees, with herbs and bushes growing between them."));
    add_item(({"brink", "slope", "slopes", "edge", }), BSN(
	"The edge where the land falls into the great vales runs north "
      + "in a straight line for many miles. To the south, it is interupted "
      + "by the narrow valley coming from the east. The slopes of the valley "
      + "are too steep to climb them."));
    add_item(({"valley", "stream", }), BSN(
	"The valley cuts deep into the land, its steep slopes preventing "
      + "passage to the south. At the bottom of the valley a small stream "
      + "is running down towards the Anduin."));
    add_item(({"anduin", "great vales", "vales", "river", }), BSN(
        "Far west, beyond the vales that stretch from the brink of the "
      + "hills towards to bank of the river, the river Anduin itself can "
      + "be seen, flowing gently southwards, like a broad band of blue "
      + "dividing the green lands on both banks."));
    add_item(({"glade", "herbs", "bushes", }), BSN(
	"Between the trees in the glade lie long launds of green grass "
      + "dappled with celandine and anemones, white and blue; and there "
      + "are acres pupulous with the leaves of woodland hyacinths."));
    add_exit(ITH_DIR + "nforest/forest3", "north",     0, 4);
    add_exit(ITH_DIR + "nforest/forest5", "southeast", 0, 4);

    set_up_herbs(({ ONE_OF_LIST(HERB_MASTER->query_herbs("ithilien")), 
                    ONE_OF_LIST(HERB_MASTER->query_herbs("middle earth")),
                    (HERB_DIR + "alfirin.c"), }),
                  ({ "ground", "field", "flowers", "forest", }), 5);

    reset_room();
}

public void
clone_rabbit()
{
    int     i, s;

    for (i = 0, s = sizeof(rabbit); i < s; i++)
        if (!objectp(rabbit[i]))
        {
            rabbit[i] = clone_object(NPC_DIR + "rabbit");
	    rabbit[i]->set_restrain_path(ITH_DIR + "nforest");
	    rabbit[i]->set_random_move(5);
	    rabbit[i]->move_living("down", TO);
	    set_alarm(30.0 + rnd() * 60.0, 0.0, clone_rabbit);
	    return;
	}
}

public void
reset_room()
{
    object  clock = find_object(CLOCK);

    set_searched(-2);

    if (clock->query_war())
	return;

    set_alarm(30.0 + rnd() * 60.0, 0.0, clone_rabbit);
}

