inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A wide passageway");
   set_long("A wide passageway.\n"+
      "Black stone as dark as the thoughts of demons surrounds you from "+
      "all angles, holding you in its cold and unyielding embrace. Above "+
      "lies an unfathomable amount of rock, so much so that its very "+
      "presence seems to suck the life from your body, leaving it frail "+
      "and vulnerable. This passage runs directly to the north and south, "+
      "leading further into this realm of neverending stone and darkness.\n");
   add_item(({"wide passageway","passageway","passage"}),
      "A relatively cramped tunnel lying far beneath the surface of Kalad.\n");
   add_item(({"black stone","stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u6),"north",0,2,1);
   add_exit(CPASS(uc/u8),"south",0,2,1);
}
