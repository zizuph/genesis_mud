/* Circle road */
/* made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;

create_room()
{
   ::create_room();
   hear_bell = 3;
   set_short("Circle road");
   set_long("You walk along the circle road, a road paved with large "+
      "bricks of stone. To the east you see the plaza opens up, "+
      "while the circle street continues to the northwest and to the "+
      "south. You notice some pigeons flying up from a building "+
"southeast from you. A post office must be in that direction. "+
      "A small house lies next to the road.\n");
   
   add_item(({"pigeon","pigeons"}),"They look like...pigeons. Except "+
      "that you notice a small cylinder attached to one of their legs.\n");
   
   add_item(({"brick","bricks"}),"Most of the bricks are hole, but some "+
      "are craced up, leaving smaller pieces that you might be able to "+
      "pry loose.\n");
   add_item("plaza","Eastwards you see the plaza; the center for the "+
      "administration of the city of Kabal.\n");
   add_item("house","Its a small home for some of the citizens of Kabal.\n");
   
   add_exit(CENTRAL(circle/s10),"south",0,1);
   add_exit(CENTRAL(circle/s12),"northwest",0,1);
   add_exit(CENTRAL(plaza/sq_st_sw),"east",0,1);
   add_exit(CENTRAL(circle/house2),"in",0,-1,-1);
   set_alarm(0.0,0.0,"reset_room");
}

void
init()
{
   ::init();
   add_action("pry_loose","pry");
}

int
pry_loose(string str)
{
   notify_fail("Pry what loose?\n");
   
   if (!str)
      return 0;
   if (str != "stones" && str!= "stone")
      return 0;
   write ("You try to pry one of the stones loose, but its too stuck.\n");
   say(QCTNAME(TP)+" tried to pry one of the stones loose, but failed.\n");
   return 1;
}

reset_room()
{
   if(!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/cmilitia");
      ob1 -> arm_me();
      ob1 -> move_living("xxx", TO);
   }
}

