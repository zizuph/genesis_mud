inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A curve in the passage");
   set_long("A curve in the passage.\n"+
      "Black stone as ebony as a fetid tar pit lies in every direction, "+
      "surrounding you with its cold and unyielding embrace. Countless tons "+
      "of rock lie above you, seperating you from the world of light, "+
      "the world of the sun. Here only darkness rules, a lightlessness that "+
      "lies to the northeast and south, where the rest of this passage "+
      "continues.\n");
   add_item(({"passage"}),
      "A cramped tunnel far beneath the surface of Kalad.\n");
   add_item(({"black stone","stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u11),"northeast",0,2,1);
   add_exit(CPASS(uc/u14),"south",0,2,1);
}
