inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object ob;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("On a small road");
    set_long("You are now on a small, white-stoned paved road. Large "+
    "estates with beautiful mansions lie to your south, while "+
    "the road intersects with Wayfarer's Boulevard just to your north.\n");
    add_item("estates","They are large and look very well kept.\n");
    add_item("mansion","Beautiful architecture, only the very elite "+
    "could afford such mansions.\n");
    add_item("road","A very nice white-stoned road that is clean "+
    "and well-kept.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(wayfarer/s5),"north",0,0,-1);
    add_exit(NOBLE(road/r6),"south",0,0,-1);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/noble_guard_patrol));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
}

