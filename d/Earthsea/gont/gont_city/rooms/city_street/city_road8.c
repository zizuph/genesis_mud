#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

#define TRAV_HALL "/d/Earthsea/travellers/room/hall"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Three way crossing outside a large garden");
    set_long("The narrow street continues along the"+
        " edge of wide grass lawns stretching out towards the"+
        " west, secluded with an iron fence. Just to the"+
        " northwest you can see two high towers, of black stone"+
        " rising up above the rest of the buildings. Looking"+
        " west is another beautiful house, almost a palace,"+
        " embedded among groves of birch and oak trees. There"+
        " is an avenue leading up to the entrance of that house"+
        ". Looking southeast, you"+
        " can catch a glimpse of the water beyond some lower"+
        " structures. To the southwest the road continues"+
        " toward a greener area of the city.\n");
    add_item("lawns","The grass lawns are part of the large"+
        " garden surrounding the house west of here.\n");
    add_item("street","The cobbled street is very clean"+
        " and fairly empty, without much traffic. It leads"+
        " northeast towards the two towers, and southeast"+
        " to the harbour and the sea.\n");
    add_item(({"house","palace"}),"This large stone"+
        " building is almost embedded among several groves of"+
        " oaks and birches. An alley below high oak trees"+
        " leads up to the front door through a gate in the"+
        " iron fence.\n");
    add_item("fence","The iron fence has a gate here, where"+
        " you can walk through to the west.\n");
    add_item("water","Beyond the lower structures to the"+
        " southeast you can catch a glimpse of the grey sea"+
        " and the harbour of Gont City.\n");
    add_item("avenue","A gravel path leading towards the front"+
        " entrance of the large palace, under the thick crowns"+
        " of old oak trees.\n");
    add_item("towers","Just to the northwest you can see"+
        " two high towers made of black stone, rising up above the"+
        " rest of the city.\n");
    add_exit("city_road12", "southwest");
    add_exit("city_road9", "southeast");
    add_exit("city_road7", "northwest");
    add_exit(TRAV_HALL, "west");
}
