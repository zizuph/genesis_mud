/*     Created by:      Sarr
 *     Location:        
 *     Modified:        
 */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"


object obj;
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
    "well kept. A small side street heads off to the east to a "+
    "rather large looking estate. Market street continues to the "+
    "southeast.\n");
    add_item("estate","You can't see very well from here, but you "+
    "think you see a couple of black flags posted around the "+
    "entrance.\n");
    hear_bell = 2;
    add_item("street","It is very wall taken care of.\n");
    add_item("merchants","They wander about tending to their wares.\n");
    add_item("estates","Grand houses and gardens of such "+
    "beauty that you are amazed.\n");
    add_exit(NOBLE(market/s4),"northwest",0,0,-1);
    add_exit(NOBLE(road/r13),"east",0,0,-1);
    add_exit(NOBLE(market/s2),"southeast",0,0,-1);
    reset_room();
}

void
reset_room()
{
    if(!obj)
    {
        obj = clone_object(NOBLE(npc/street_sweeper));
        obj->arm_me();
        obj->move_living("xxx",TO);
    }
}

