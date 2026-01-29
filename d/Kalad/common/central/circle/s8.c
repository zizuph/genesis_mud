/* Circle road */
/* made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()
{
   ::create_room();
   hear_bell = 3;
   set_short("Circle road");
   set_long("You walk along the circle road, a road paved with large "+
      "bricks of stone. To the north you see the backside of the "+
      "sage's office while on the other side you only see "+
      "some uninteresting office-buildings. Further west you "+
      "see a crossroad.\n");
   
   add_item(({"brick","bricks"}),"Most of the bricks are hole, but some "+
      "are craced up, leaving smaller pieces that you might be able to "+
      "pry loose.\n");
   add_item("prison","A low, simple, solid construction that keeps "+
      "ruffains and drunks imprisoned for some time.\n");
   
   add_exit(CENTRAL(high-circle-south),"west",0,1);
   add_exit(CENTRAL(circle/s7),"northeast",0,1);
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

