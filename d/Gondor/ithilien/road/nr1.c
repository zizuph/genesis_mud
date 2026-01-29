inherit "/d/Gondor/ithilien/road/road.c";

#include "/d/Gondor/defs.h"
#include <language.h>

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("central");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs north towards Morannon, south it enters a "
      + "ring of trees that surrounds the crossroads where this road meets "
      + "the road from Osgiliath to Minas Morgul. To the east of the road, "
      + "the slopes of the Ephel Duath rise high up into the sky, to the "
      + "west the southern fringes of a great forest can be seen.\n");
    add_tree_ring("south");
    add_forest(1, 0, ({ "forest", "wood", "woods", }) );
    add_mountains(1, "only about half a mile");
    add_road(1);

    add_exit(ITH_DIR + "road/nr2",        "north", test_exit, 3);
    add_exit(ITH_DIR + "road/crossroads", "south", test_exit, 3);
}

