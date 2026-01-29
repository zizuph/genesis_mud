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
      "bricks of stone. To the north you see the backside of a low"+
      "building; some pigeons flies up from it, while on the other "+
      "side you only see "+
      "some uninteresting office-buildings. Further east you "+
      "see a crossroad.\n");
   
   add_item(({"brick","bricks"}),"Most of the bricks are hole, but some "+
      "are craced up, leaving smaller pieces that you might be able to "+
      "pry loose.\n");
   add_item("building","It must be a post-office, cause you see letter- "+
      "pigeons fly up from it.\n");
   add_item(({"pigeon","pigeons"}),"Its a...pigeon. Attached to one of its "+
      "legs you see a small cylinder.\n");
   
   add_exit(CENTRAL(high-circle-south),"east",0,1);
   add_exit(CENTRAL(circle/s10),"northwest",0,1);
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

