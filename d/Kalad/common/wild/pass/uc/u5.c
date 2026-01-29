inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A curve in the passage");
   set_long("A curve in the passage.\n"+
      "Stone as black as a fetid tar pit surrounds you from all sides, "+
      "enfolding you in its cold, unyielding embrace. An incalculable "+
      "amount of rock hangs overhead, seeming to absorb the very life from "+
      "your being, leaving you withered and fatigued. Here, the passage "+
      "you are journeying along bends gently, heading to the north and "+
      "southwest where it disappears into darkness.\n");
   add_item(({"passage"}),
      "A cramped tunnel far beneath the surface of Kalad.\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u4),"north",0,2,1);
   add_exit(CPASS(uc/u6),"southwest",0,2,1);
}
