#pragma strict_types

#include "../defs.h"

inherit (MORDOR_LIB + "room");

public void
create_room()
{
    set_short("At the end of pass Carach Angren."); 

    set_long("The broad paved road stretches southeastwards towards " +
     "the pass Carach Angren and northwestwards towards the pass of " +
     "Cirith Gorgor while paths leading northeastwards and westwards " +
     "from here. This bleak and circular valley between " +
     "Ephel Duath and Ered Lithui seems to be formed by a violent " +
     "volcanic upheaval. The fortress Durthang rests on a " +
     "precarius ledge high above Udun at the mountainrange " +
     "Ephel Duath northwestwards from here.\n");

    add_exit(ROOM + "gor10", "northwest");
    add_exit(ROOM + "gor12", "southeast");
    add_exit(ROOM + "gore1", "northeast");
    add_exit(ROOM + "gorw12", "west");
}
