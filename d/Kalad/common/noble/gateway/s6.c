inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On Gateway Street");
    set_long("You now travel along the northern most street of Kabal: "+
    "Gateway street. This street heads east all the way into the "+
    "Caravan district, crossing the two gates to outside of the city; "+
    "High gate and Caravan gate. The street here in the noble district "+
    "is clean. Loud noises can be heard from the building to the south "+
    "of you. The hot Kaladian sun burns down on you.\n");
    add_item("building","It looks like the back side of a pub.\n");    
    add_exit(NOBLE(gateway/s5),"west",0,0,-1);
    add_exit(NOBLE(gateway/s7),"east",0,0,-1);
}

