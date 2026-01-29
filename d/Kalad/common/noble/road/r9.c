inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a small road");
    set_long("You are now on a small, white-stoned paved road. The "+
    "road leads west, and east to Market Street.\n");
    add_item("estates","They are large and look very well kept.\n");
    add_item("mansion","Beautiful architecture, only the very elite "+
    "could afford such mansions.\n");
    add_item("road","A very nice white-stoned road that is clean "+
    "and well-kept.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(road/r8),"west",0,0,-1);
    add_exit(NOBLE(market/s1),"east",0,0,-1);
}

