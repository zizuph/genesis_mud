inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A curve in the passage");
   set_long("A curve in the passage.\n"+
      "Stone as black as the stygion depths of the realm of the dead encircles you. "+
      "It seems to whisper promises of a safe haven from the darkness, the "+
      "eternal safety of a cold, unmarked grave. Above lies tons of rock, a gigantic "+
      "and uncrossable barrier between you and the sunlit lands of Kalad. Here the "+
      "passage you are travelling in curves to the east from the northwest.\n");
   add_item(({"passage"}),
      "A tunnel located far beneath the sun-lit realm of Kalad.\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u38),"northwest",0,2,1);
   add_exit(CPASS(uc/u45),"east",0,2,1);
}
