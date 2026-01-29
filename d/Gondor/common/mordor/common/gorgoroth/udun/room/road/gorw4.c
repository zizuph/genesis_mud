#pragma strict_types

#include "../defs.h"

inherit (MORDOR_LIB + "room");

public void
create_room()
{
    set_short("West hillside of Udun"); 

    set_long("The slightly visible path stretches southwards " +
     "and northeastwards following the steep wall of Ephel Duath's " +
     "foot. This bleak and circular valley between " +
     "Ephel Duath and Ered Lithui seems to be formed by a violent " +
     "volcanic upheaval. The fortress Durthang rests on a " +
     "precarius ledge high above Udun at the top of " +
     "Ephel Duath westwards from here.\n");

    add_exit(ROOM + "gorw3", "northeast");
    add_exit(ROOM + "gorw5", "south");
}
