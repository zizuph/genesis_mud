inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

object ob;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("On Gateway Street");
    set_long("You now travel along the northern most street of Kabal: "+
    "Gateway street. This street heads east all the way into the "+
    "Caravan district, crossing the two gates to outside of the city; "+
    "High gate and Caravan gate. The street here in the noble district "+
    "is very well kept and clean. Directly to your west, the street "+
    "intersects with End street.\n");
    add_exit(NOBLE(gateway-end),"west",0,0,-1);
    add_exit(NOBLE(gateway/s2),"east",0,0,-1);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/b_noble_guard_patrol));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
}

