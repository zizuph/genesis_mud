#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Street just west of the city wall");
    set_long("The narrow cobbled street continues"+
        " north-south winding between two-story wooden"+
        " buildings standing very close together. To the"+
        " west a somewhat wider alley leads in between"+
        " two houses. This seems"+
        " to be living quarters for the poorer part of the"+
        " population of Gont Port with narrow alleys between"+
        " the houses filled with litter and refuse that"+
        " no one bothered to take away. The street is fairly"+
        " empty, but now and then people dressed as"+
        " harbour workers or fishermen pass by on their way"+
        " to other areas of the city.\n");
    add_item("buildings","These two-story wooden"+
        " buildings house apartments for the poorer part"+
        " of the population of Gont Port. The sides of"+
        " the houses lean in over the street, making it"+
        " very dark and shadowy.\n");
    add_item("street","The cobbled street is dirty and"+
        " in fairly bad repair, with cobblestones missing"+
        " here and there.\n");
    add_item(({"fishermen","workers"}),"Now and then a"+
        " man dressed as a fishermen or harbour worker walk"+
        " by, on his way to other parts of the city. They"+
        " smile at you as they walk by.\n");
    add_item("alleys","Narrow alleys lead in between"+
        " the houses, filled with heaps of litter and"+
        " refuse. Through the alleys on the east side of"+
        " the street you can catch a glimpse of the city"+
        " wall behind.\n");
    add_item(({"litter","refuse"}),"This seems to be"+
        " household garbage, simply dumped on the alleys"+
        " through the windows of the buildings.\n");
    add_exit("city_road26", "south");
    add_exit("city_road28", "west");
    add_exit("city_road29", "north");
}
