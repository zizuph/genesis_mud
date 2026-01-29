inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A wide passageway");
   set_long("A wide passageway.\n"+
      "Black stone as enduring as the thoughts of fell beings surrounds "+
      "you, seeming to reach out for you with an embrace that promises "+
      "nothing but the frigidness of eternal oblivion. Overhead, countless "+
      "tons of rock lie, their weight seemingly crushing the life from your "+
      "body, leaving it withered and vulnerable. This passage you are in "+
      "travels to the west and east, further into this realm of neverending "+
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
   add_exit(CPASS(uc/u41),"west",0,2,1);
   add_exit(CPASS(uc/u43),"east",0,2,1);
}
