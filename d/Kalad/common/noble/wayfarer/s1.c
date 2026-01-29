inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* By Sarr of Kalad */

object ob;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("Along Wayfarer's Boulevard");
    set_long("You are travelling along Wayfarer's Boulevard in "+
      "the Noble district. The Boulevard here is very well kept and "+
      "clean, as opposed to its condition in the Caravan district. "+
      "The air is fresh and clean, and various beautiful plant life "+
      "surrounds you. Directly to your southeast, you see a gateway. "+
      "A large mansion and garden lies behind it. There is a banner "+
      "over the gateway.\n");
    add_item("banner","A banner that reads: House of Topania.\n");
    add_item("gateway","The gateway is open, and the rest of "+
      "the gate surrounds this beautiful estate.\n");
    add_item("mansion","A very huge and finely decorated house "+
      "with many green-black banners and flags.\n");
    add_item("garden","A very nice garden.\n");
    add_exit(NOBLE(topania/g1),"southeast","@@block@@",0,0);
    add_exit(NOBLE(market/s5),"west",0,0,-1);
    add_exit(NOBLE(wayfarer/s2),"east",0,0,-1);
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
    write("A guard stops you and says that the Lord is not "+
      "receiving visitors yet.\n");
    return 1;
}
