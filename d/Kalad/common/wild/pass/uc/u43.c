inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A curve in the passage");
   set_long("A curve in the passage.\n"+
      "Black stone, as obsidian as the depths of the netherworld, surrounds you. "+
      "It seems to call to you with promises of a safe place to rest, the "+
      "eternal cold of a grave. Above you lies tons of rock, a gigantic "+
      "barrier between you and the sunlit realms of Kalad. Here the "+
      "passage you are travelling in curves to the southwest and east.\n");
   add_item(({"passage"}),
      "A tunnel located far beneath the sun-lit realm of Kalad.\n");
   add_item(({"black stone","stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u38),"northeast",0,2,1);
   add_exit(CPASS(uc/u42),"west",0,2,1);
}
