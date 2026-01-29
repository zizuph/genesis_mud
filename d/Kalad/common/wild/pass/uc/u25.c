inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A sewer passage");
   set_long("A sewer passage.\n"+
      "Stone as black as the thoughts of otherworldly demons surrounds "+
      "you from all directions, holding you in its cold, unyielding "+
      "embrace. An odor, reminiscent of filth and decay pervades the area, "+
      "causing you to avert your nose in disgust. Above lies only the "+
      "impenetrable barrier of rock that lies between this realm of stone "+
      "and darkness and the realm of life and light. The passage you are "+
      "inside of runs directly west and east. A small stream of filthy water "+
      "runs along the center of the passage, also heading west and east.\n");
   add_item(({"sewer passage","passage"}),
      "A sewer tunnel located beneath the streets of the city-state of Kabal.\n");
   add_item(({"passage"}),
      "Which passage?\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_item(({"walls"}),
      "You cannot examine all the walls at once.\n");
   add_item(({"wall"}),
      "Which wall?\n");
   add_item(({"southern wall","south wall"}),
      "The wall of the passage in the south, while composed of the same "+
      "unusually black stone as the rest of the passage, possesses one distinguishing "+
      "quality, it is riddled with cracks.\n");
   add_item(({"cracks","crack"}),
      "A closer inspection of the rifts within the wall reveals a hole, "+
      "just barely large enough for a human to enter.\n");
   add_item(({"hole"}),
      "A hole just large enough for a human to fit inside of.\n");
   add_item(({"small stream","stream","filthy water","water"}),
      "Disgusting, brackish water, filled with unidentified bits of matter.\n");
   add_item(({"matter","unidentified bits","bits","bit"}),
      "It is best not to look at such filthy things.\n");
   add_exit(CPASS(uc/sewer_connection),"west","@@block",2,1);
   add_exit(CPASS(uc/u26),"east",0,2,1);
}
void
init()
{
   ::init();
   AA(enter,enter);
}
enter(string str)
{
   if(!str || str != "hole")
      {
      NF("You can't enter '" + str + "'.\n");
      return 0;
   }
   write("You duck your head and enter the hole in the southern wall.\n");
   set_alarm(1.0,0.0,"do_enter");
   return 1;
}
void
do_enter()
{
   TP->move_living("into the hole in the southern wall","/d/Kalad/common/caravan/lot/ur2");
   return;
}
block()
{
   write("You continue west for a bit, but are soon forced to turn back due to "+
      "an unusually large pile of filth and debris blocking the way to the "+
      "west.\n");
   say(QCTNAME(TP) + " continues west for a bit, but is soon forced to "+
      "turn back due to an unusually large pile of filth and debris blocking the "+
      "way to the west.\n");
   return 1;
}
