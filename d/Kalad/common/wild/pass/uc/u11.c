inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A crossroads of passages");
   set_long("A crossroads of passages.\n"+
      "Stone as black as the lightless depths of the netherworld surrounds "+
      "you, reaching for you with an embrace that promises only the cold of "+
      "eternal death. Above lies incalculable tons of rock, its weight "+
      "seeming to crush the vitality from your body, leaving it weary and "+
      "vulnerable. Here the passage splits, heading to the northeast, "+
      "south and southwest.\n");
   add_item(({"crossroads","crossroad","passages","passage"}),
      "A relatively cramped tunnel lying far beneath the surface of Kalad.\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u9),"northeast",0,2,1);
   add_exit(CPASS(uc/u13),"south",0,2,1);
   add_exit(CPASS(uc/u12),"southwest",0,2,1);
}
