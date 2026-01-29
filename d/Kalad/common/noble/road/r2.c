inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a small road");
    set_long("You are now on a small, white-stoned paved road. Large "+
    "estates with beautiful mansions lie to your north, while "+
    "a hedge towers over you to the southeast, running the "+
    "length of the park to the east.\n");
    add_item("estates","They are large and look very well kept.\n");
    add_item("mansion","Beautiful architecture, only the very elite "+
    "could afford such mansions.\n");
    add_item("road","A very nice white-stoned road that is clean "+
    "and well-kept.\n");
    add_item("hedge","It towers over you, and acts like a fence "+
    "around the park. The entrance is here, to your east.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(road/r3),"northeast",0,0,-1);
    add_exit(NOBLE(road/r1),"south",0,0,-1);
}

