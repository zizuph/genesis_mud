#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("central");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs north towards Morannon, south to the crossroads " +
        "where this road meets the road from Osgiliath to Minas Morgul. The " +
        "shadow of the Ephel Duath to the east heavily hangs on the road. To the " +  
        "west, the forests of central Ithilien accompany the road. Sometimes the " +
        "Anduin can be seen through the top of the trees.\n");
    add_mountains(1, "only about a league");
    add_road(2);
    add_forest(1);
    add_exit(ITH_DIR + "road/nr3", "north", test_exit, 3);
    add_exit(ITH_DIR + "road/nr1", "south", test_exit, 3);
}

