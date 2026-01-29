#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
    set_area ("the foot of the Last Bridge on");
    set_areaname ("the Great East Road");
    set_land ("Rhudaur");
    set_areatype (AREATYPE_ROAD);
    set_areadesc ("riverbank at");
    set_grass ("sparse, sickly");
    set_treetype ("pine");

    set_extraline ("The Hoarwell river's stentorian passage around the " +
    "footings of Last Bridge's three arches dominate the ears.  Shadows " +
    "from the hills of Trollshaw cover the road to the south.  To the " +
    "northwest are the dry downs of the Lone-lands.  " +
    "The road continues to the northwest and southeast from here. ");

add_item (({"great east road", "road", "mud"}),
"The Great East Road is an ancient passageway for travellers with need " +
"to follow its winding and rolling ways.  Due to recent rains, mud " +
"covers the entire breadth of the road, revealing nothing about other " +
"travellers to the casual observer. \n");
add_item (({"hoarwell", "river", "hoarwell river"}),
"Rushing and foaming in its hurry towards southern lands, the mighty " +
"Hoarwell loudly protests the Last Bridge's existence, which has forced " +
"the waters around the footings and through the bridge's three arches. \n");
add_item (({"bridge", "last bridge"}),
"Three grand arches of massive, smooth granite support a span over " +
"the river Hoarwell, wide enough for two passing wagons.  The " +
"condition of the granite blocks easily lends itself towards a sense " +
"of timelessness and strength. \n");
add_item (({"trees", "pine trees", "pines"}),
"Growing far apart at this distance from the hills of Trollshaw has " +
"allowed them to reach tremendous heights.\n");

    add_exit (ER_DIR + "erb38", "northwest", 0, 1);
    add_exit (ER_DIR + "erb40", "southeast", 0, 1);
}
