inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A curve in the passage");
   set_long("A curve in the passage.\n"+
      "Black stone, as unnaturally dark as the realm of the dead, surrounds you. "+
      "It seems to call to you with promises of a safe place to rest, the "+
      "unending cold of a grave. Overhead lies tons of rock, an impenetrable "+
      "barrier seperating you from the sunlit realms of Kalad. Here the "+
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
   add_exit(CPASS(uc/u17),"east",0,2,1);
   add_exit(CPASS(uc/u21),"southwest",0,2,1);
}
