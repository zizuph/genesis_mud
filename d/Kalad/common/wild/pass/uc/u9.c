inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A wide passageway");
   set_long("A wide passageway.\n"+
      "Black stone as stygion as the depths of the netherworld surrounds "+
      "you, enfolding you in an embrace that promises only the cold of the "+
      "grave. Overhead lies a monstrous amount of rock, its very presence "+
      "seemingly sucking the vibrancy from your body, leaving it depleted, "+
      "exhausted. This passage runs directly to the northeast and southwest, "+
      "heading further into this realm of neverending stone.\n");
   add_item(({"wide passageway","passageway","passage"}),
      "A relatively cramped tunnel lying far beneath the surface of Kalad.\n");
   add_item(({"black stone","stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u8),"northeast",0,2,1);
   add_exit(CPASS(uc/u11),"southwest",0,2,1);
}
