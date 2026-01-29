inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A curve in the passage");
   set_long("A curve in the passage.\n"+
      "Black stone as lightless as the depths of the netherworld surrounds "+
      "you from every conceivable direction, trapping you in its cold and "+
      "unyielding embrace, like a musty and forgotten tomb. The sheer "+
      "immensity of rock that lies overhead seems to withdraw the very life "+
      "from you, leaving you a weak and debilitated shell. Here, the passage "+
      "takes a bend, going off to the northeast and south.\n");
   add_item(({"passage"}),
      "A cramped tunnel far beneath the surface of Kalad.\n");
   add_item(({"black stone","stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u5),"northeast",0,2,1);
   add_exit(CPASS(uc/u7),"south",0,2,1);
}
