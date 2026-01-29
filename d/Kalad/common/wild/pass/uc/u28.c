inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A curve in the passage");
   set_long("A curve in the passage.\n"+
      "Stone as black as the skin of a drow surrounds you from every side, "+
      "enfolding you in its cold, unyielding embrace. An incalculable "+
      "amount of rock hangs overhead, seeming to absorb the very life from "+
      "your being, leaving you withered and fatigued. Here, the passage "+
      "you are journeying along bends gently, heading to the north and "+
      "southwest where it disappears further into this realm of endless stone.\n");
   add_item(({"passage"}),
      "A tunnel located far beneath the realm of light, the realm of the sun.\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u19),"north",0,2,1);
   add_exit(CPASS(uc/u36),"southwest",0,2,1);
}
