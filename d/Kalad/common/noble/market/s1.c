inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

object ob;
object ob2;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("On Market Street");
    set_long("You are now on the Market Street in the Noble district "+
    "of Kabal. This street is a little noisier than the rest in the "+
    "Noble district becuase of the various merchants travelling along "+
    "here from the Market district. However, the road is clean and "+
    "well kept. You are nearing the intersection of Market and "+
    "Farmer's Way. You can hear the noise from all the farmers "+
    "travelling along the road just to your southeast. West, "+
    "however, a small road leads down along a very peacful and "+
    "quiet way.\n");
    add_item("mansion","A very large white mansion stands there "+
    "behind the garden. Silver banners and flags adorn the entrance "+
    "of it.\n");
    hear_bell = 2;
    add_item("street","It is very wall taken care of.\n");
    add_item("merchants","They wander about tending to their wares.\n");
    add_item("estates","Grand houses and gardens of such "+
    "beauty that you are amazed.\n");
    add_exit(NOBLE(market/s2),"northwest",0,0,-1);
    add_exit(NOBLE(road/r9),"west",0,0,-1);
    add_exit(NOBLE(farmer-market),"southeast",0,0,-1);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/snooty_noble));
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

