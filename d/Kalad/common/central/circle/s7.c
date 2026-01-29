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
      "bricks of stone. A small house is on the western side "+
      "of the road. The street continues to the north and "+
      "southwest.\n");
   
   add_item(({"brick","bricks"}),"Most of the bricks are hole, but some "+
      "are craced up, leaving smaller pieces that you might be able to "+
      "pry loose.\n");

   add_item("house","Its a small home of some of the "+
      "citizens of Kabal.\n");
   
   add_exit(CENTRAL(circle/s8),"southwest",0,1);
   add_exit(CENTRAL(circle/s6),"north",0,1);
   add_exit(CENTRAL(circle/house4),"in",0,-1,-1);
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

