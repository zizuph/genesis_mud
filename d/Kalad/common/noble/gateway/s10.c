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
    "is clean. A castle rises off to your southeast, while a very "+
    "large and beautiful building is directly to your south.\n");
    add_item("building","The building is a masterpiece of "+
    "architecture. By the looks of it, it must be the famouse "+
    "museum of Kalad.\n");
    add_item("castle","A very nice looking castle, it must belong "+
    "to the high-lord.\n");
    add_exit(NOBLE(gateway/s9),"west",0,0,-1);
    add_exit(NOBLE(gateway/s11),"east",0,0,-1);
}

