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
    "are clean. You can smell fresh baked goods coming from the "+
    "building to your south.\n");
    add_item("building","It is a small white walled building that "+
    "looks like a bakery.\n");
    add_exit(NOBLE(bakery),"south",0,-1,-1);
    add_exit(NOBLE(gateway/s3),"west",0,0,-1);
    add_exit(NOBLE(gateway/s5),"east",0,0,-1);
}

