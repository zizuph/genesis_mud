inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

object ob;
object ob2;
void reset_room();

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
    "is clean. The hot Kaladian sun burns down on you.\n");
    add_exit(NOBLE(gateway/s4),"west",0,0,-1);
    add_exit(NOBLE(gateway/s6),"east",0,0,-1);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/fat_noble));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
    if(!ob2)
    {
        ob2 = clone_object(NOBLE(npc/bodyguard));
        ob2->arm_me();
        ob2->move_living("xxx",TO);
    }
    ob->team_join(ob2);
}

