inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

object ob;
object ob2;
object ob3;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("On End Street");
    set_long("You are travelling along End street in the Noble "+
    "district. The street here is very well taken care of, and "+
    "there is hardly any trash or refuse around. Off to your "+
    "east you can see the grand estates of the various rich "+
    "nobles of Kabal. You are nearing the intersection of "+
    "End and Gateway, which is a little ways north.\n");
    hear_bell = 2;
    add_item("street","It is very wall taken care of.\n");
    add_item("estates","Grand houses and gardens of such "+
    "beauty that you are amazed.\n");
    add_exit(NOBLE(end/s6),"north",0,0,-1);
    add_exit(NOBLE(end/s4),"south",0,0,-1);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/old_noble));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
    if(!ob2)
    {
        ob2 = clone_object(NOBLE(npc/bodyguard));
        ob2->arm_me();
        ob2->move_living("xxx",TO);
    }
    if(!ob3)
    {
        ob3 = clone_object(NOBLE(npc/bodyguard));
        ob3->arm_me();
        ob3->move_living("xxx",TO);
    }
    ob->team_join(ob2);
    ob->team_join(ob3);
}

