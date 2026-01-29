#pragma strict_types

#include "../../defs.h"

inherit (ROOM + "room");

public nomask void
create_udun_room()
{
    set_short("At the barren plains of Udun."); 

    set_long("The broad paved road stretches southeastwards towards " +
     "the pass Carach Angren and northwestwards towards the pass of " +
     "Cirith Gorgor. This bleak and circular valley between " +
     "Ephel Duath and Ered Lithui seems to be formed by a violent " +
     "volcanic upheaval. The fortress Durthang rests on a " +
     "precarius ledge high above Udun at the mountainrange " +
     "Ephel Duath northwestwards from here.\n");

    add_exit(ROAD + "gor9", "northwest");
    add_exit(ROAD + "gor11", "southeast");
}
