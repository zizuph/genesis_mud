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
    "is clean. You see a castle rising up to your southeast.\n");
    add_item("castle","A very nice looking castle, it must belong "+
    "to the high-lord.\n");
    add_exit(NOBLE(gateway/s6),"west",0,0,-1);
    add_exit(NOBLE(gateway/s8),"east",0,0,-1);
}

