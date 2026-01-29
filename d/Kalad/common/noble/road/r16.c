inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a small road");
    set_long("You are now on a small, white-stoned paved road. The "+
    "road heads northeast to the very busy intersection of "+
    "High street and Wayfarer's Boulevard in the Caravan "+
    "district, while west, it goes a short distance. Directly "+
    "to the south, you see a large hedge that surrounds the "+
    "park. There is an opening here, and you can enter the "+
    "park by going south.\n");
    add_item("hedge","It surrounds the great park.\n");
    add_item("road","A very nice white-stoned road that is clean "+
    "and well-kept.\n");
    add_item("park","The hedge blocks your view, but you can "+
    "see the entrance off to your south.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(park/p1),"south",0,0,-1);
    add_exit(CVAN(high-wayfar),"northeast",0,0,-1);
    add_exit(NOBLE(road/r15),"west",0,0,-1);
}

