inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a small road");
    set_long("You are now on a small, white-stoned paved road. The "+
    "road leads northwest to the gate of a nice estate.\n");
    add_item("estate","It is large and look very well kept.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(road/r12),"northwest",0,0,-1);
    add_exit(NOBLE(market/s2),"east",0,0,-1);
}

