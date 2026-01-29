inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A crossroads of passages");
   set_long("A crossroads of passages.\n"+
      "Stone as black as the abyssmal pits of the netherworld surrounds you "+
      "from all sides, enwrapping you in its cold and unyielding embrace. "+
      "Overhead lies an enormous amount of rock, so much so that its "+
      "presence seems to absorb the energy from your form, leaving you weakened "+
      "and weary. The passage splits here, heading off to the north, "+
      "southeast and southwest.\n");
   add_item(({"crossroads","crossroad","passages","passage"}),
      "A relatively cramped tunnel lying far beneath the surface of Kalad.\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u7),"north",0,2,1);
   add_exit(CPASS(uc/u10),"southeast",0,2,1);
   add_exit(CPASS(uc/u9),"southwest",0,2,1);
}
