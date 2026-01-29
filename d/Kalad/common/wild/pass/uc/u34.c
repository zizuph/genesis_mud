inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A curve in the passage");
   set_long("A curve in the passage.\n"+
      "Stone as dark as the skin of a decaying corpse surrounds you from all sides, "+
      "encompassing you in its cold, unyielding embrace. An unimaginable "+
      "amount of rock hangs overhead, seeming to absorb the very life from "+
      "your being, leaving you weak and vulnerable. Here, the passage "+
      "you are within curves somewhat, travelling to the west and northeast.\n");
   add_item(({"passage"}),
      "A tunnel located far beneath the realm of light, the realm of the sun.\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u33),"west",0,2,1);
   add_exit(CPASS(uc/u24),"northeast",0,2,1);
}
