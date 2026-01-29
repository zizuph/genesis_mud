inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A confined passageway");
   set_long("A confined passageway.\n"+
      "Stone as black as the lightless depths of the netherworld surround "+
      "you, smothering you with its cold embrace. The immensity of rock "+
      "that seems to hang precariously above you seems to squeeze the very "+
      "vitality from your body, leaving you weary beyond belief. The "+
      "passage you are on curves slightly here, heading off to the "+
      "northwest and south, where only darkness rules.\n");
   add_item(({"confined passageway","passageway","passage"}),
      "A cramped tunnel far beneath the surface of Kalad.\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u1),"northwest",0,2,1);
   add_exit(CPASS(uc/u4),"south",0,2,1);
}
