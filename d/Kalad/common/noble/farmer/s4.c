inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

object ob;
void reset_room();

void
create_room()
{
   ::create_room();
   set_short("On the road of Farmer's Way");
   set_long("You are now on the dusty road known as Farmer's way. "+
      "All around you, many farmers push their carts back and forth "+
      "through here to the market and caravan district. The noise "+
      "from all the comotion is very great, and you feel like a lost "+
      "child in all this chaos. You are now getting closer to the "+
      "intersection of Farmer and Market, and you notice much of the "+
      "noise comes from the market district to the south. "+
      "You notice a large hedge to your "+
      "north that rises about 12 feet tall. You can't be sure, but "+
      "you think the great park of the noble district lies behind "+
      "it. The eternal, blazing Kaladian sun "+
      "beams down on you, making you sweat a little.\n");
   hear_bell = 2;
   add_item("hedge", "It is a monsterous hedge that runs "+
      "all along the road to your west.\n");
   add_item("farmers","They move about you pushing their carts "+
      "along the road.\n");
   add_item("carts","They are wooden carts filled with fruits and "+
      "vegtables off all types.\n");
   add_item("sun","It is making you hot.\n");
   add_item("road","The road is make of stone and dirt and looks "+
      "worn down.\n");
   add_exit(NOBLE(farmer/s5),"west",0,0,0);
   add_exit(NOBLE(farmer/s3),"east",0,0,0);
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

