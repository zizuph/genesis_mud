inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a small road");
    set_long("You are now on a small, white-stoned paved road. The "+
      "road splits off to the east through a gate set into " +
      "a large hedge fence. The road leans north further into the "+
      "Noble district, while directly south is the Farmer's way "+
      "and Market Street.\n");
    add_item("road","A very nice white-stoned road that is clean "+
      "and well-kept.\n");
    add_item("hedge","It towers over you, and acts like a fence "+
      "around the park. The entrance is here, to your east.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(road/r2),"north",0,0,-1);
    add_exit(NOBLE(park/p25),"east",0,0,-1);
    add_exit(NOBLE(farmer-market),"south",0,0,-1);
}

