inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

object ob;
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
    "well kept. A small road leads to the west that bends up to "+
    "very fancy looking gate, while off to your east, there stands "+
    "a very large silver gate that is open leading to a large "+
    "garden, and behind that, a mansion. There is a sign over the "+
    "gate.\n");
    add_item("mansion","A very large white mansion stands there "+
    "behind the garden. Silver banners and flags adorn the entrance "+
    "of it.\n");
    add_item("sign","A banner: House of Tarquine.\n");
    add_item("road","Its a small side road, but well kept.\n");
    add_item(({"gate","silver gate"}),"All around it fly silver "+
    "flags with the emblem of an eagle.\n");
    add_item("fancy gate","You can't be sure, but you think you "+
    "see red flags flying.\n");
    add_item("garden","A very exotic and beautiful garden.\n");
    add_item("estate","You can't see very well from here, but you "+
    "think you see a couple of black flags posted around the "+
    "entrance.\n");
    hear_bell = 2;
    add_item("street","It is very wall taken care of.\n");
    add_item("merchants","They wander about tending to their wares.\n");
    add_item("estates","Grand houses and gardens of such "+
    "beauty that you are amazed.\n");
    add_exit(NOBLE(market/s3),"northwest",0,0,-1);
    add_exit(NOBLE(tarquine/g1),"east","@@block@@",0,0);
    add_exit(NOBLE(road/r11),"west",0,0,-1);
    add_exit(NOBLE(market/s1),"southeast",0,0,-1);
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

int
block()
{
    write("A guard stops you and says the Lord is not receiving "+
    "visitors yet.\n");
    return 1;
}
