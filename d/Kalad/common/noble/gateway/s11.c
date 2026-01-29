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
    "large and beautiful building is directly to your south, "+
    "and a sign hangs over the entrance.\n");
    add_item("sign","A large and readable one.\n");
    add_cmd_item("sign","read","It reads: The Kabal Museum of Art.\n");
    add_item("building","The building is a masterpiece of "+
    "architecture. By the looks of it, it must be the famouse "+
    "museum of Kalad.\n");
    add_item("castle","A very nice looking castle, it must belong "+
    "to the high-lord.\n");
    add_exit(NOBLE(museum1),"south",0,-1,-1);
    add_exit(NOBLE(gateway/s10),"west",0,0,-1);
    add_exit(CVAN(high-gate),"east",0,0,-1);
}

