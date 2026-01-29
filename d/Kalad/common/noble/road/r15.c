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
    set_long("You are now on a small, white-stoned paved road. The "+
    "road leads east to an intersection, and north back to "+
    "Wayfarer's Boulevard. You can see the park to the south.\n");
    add_item("road","A very nice white-stoned road that is clean "+
    "and well-kept.\n");
    add_item("park","The hedge blocks your view, but you can "+
    "see the entrance off to your southeast.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(wayfarer/s10),"north",0,0,-1);
    add_exit(NOBLE(road/r16),"east",0,0,-1);
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

