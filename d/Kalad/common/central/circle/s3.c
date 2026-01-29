/* Circle road */
/* made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_room()
{
   ::create_room();
   hear_bell = 3;
   set_short("Circle road");
   set_long("You walk along the circle road, a road paved with large "+
      "bricks of stone. To the west you see the backside of the "+
      "building of the Council of the Lords, while on the other side you "+
      " only see "+
      "a small house. The road continues to "+
      "the south and to the northwest.\n");
   
   add_item(({"brick","bricks"}),"Most of the bricks are hole, but some "+
      "are craced up, leaving smaller pieces that you might be able to "+
      "pry loose.\n");
   
   add_item("building","The backside of the Council of the Lords - building is "+
      "fairly plain. Only some windows and some cracks in the wall "+
      "are visible except the usual graffitti.\n");
   
   add_item(({"window","windows"}),"You see four of them, but you can "+
      "only reach the two lowest ones. All of them are closed.\n");
   
   add_item(({"cracks","crack"}),"The cracks criss-crosses the wall. "+
      "A few of them are fairly wide...this building is really in "+
      "need of major repairs.\n");

   add_item("house","Its a small building that some "+
      "citizens of Kabal lives in.\n");
   
   add_exit(CENTRAL(circle/s2),"northwest",0,1);
   add_exit(CENTRAL(circle/s4),"south",0,1);
   add_exit(CENTRAL(circle/house3),"in",0,-1,-1);
}

void
init()
{
   ::init();
   add_action("try_climb","climb");
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

int
try_climb(string str)
{
   notify_fail("Climb what?\n");
   
   if (!str)
      return 0;
   if (str != "crack" && str!= "cracks")
      return 0;
   
   if (TP->query_skill(SS_CLIMB) <=20)
      {
      write("You start to climb the cracks but slip and fall down. "+
         "Ouch! That hurts...\n");
      say(QCTNAME(TP) + " starts to climb up the cracks but slips "+
         "and fall down, hurting himself on the bricks.\n");
      TP->heal_hp(-50);
      if (TP->query_hp() <1) TP->do_die(TO);
      return 1;
   }
   write("You start to climb up the cracks, trying to follow the "+
      "easy way upwards. Finally you come to a window...a closed window. "+
      "After a while you decide to climb down again.\n");
   say(QCTNAME(TP) + " starts to climb up the cracks. After a while "+
      "he comes climbing down again.\n");
   return 1;
}

