inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A wide passageway");
   set_long("A wide passageway.\n"+
      "Black stone as lightless as the depths of the netherworld surrounds "+
      "you, seeming to reach out for you with an embrace that promises "+
      "nothing but the coldness of eternal oblivion. Up above, countless "+
      "tons of rock lie, their weight seemingly crushing the life from your "+
      "body, leaving it withered and vulnerable. This passage you are in "+
      "travels to the north and south, further into this realm of neverending "+
      "stone.\n");
   add_item(({"wide passageway","passageway","passage"}),
      "A relatively cramped tunnel lying far beneath the surface of Kalad.\n");
   add_item(({"black stone","stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u12),"north",0,2,1);
   add_exit(CPASS(uc/u18),"south",0,2,1);
}
