inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A bend in the passage");
   set_long("A bend in the passage.\n"+
      "Black stone, as unnervingly lightless as the depths of oblivion, "+
      "surrounds you, reaching out to you with an embrace filled with "+
      "the coldness of death. Above, countless tons of rock hang silently, "+
      "their presence seems to siphon off your energy, leaving you depleted and "+
      "most frightening of all, vulnerable. The passage bends here, curving to the "+
      "northwest and east. Beyond lies more of this realm of stone and rock.\n");
   add_item(({"passage"}),
      "A tunnel located far beneath the sun-lit realm of Kalad.\n");
   add_item(({"black stone","stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u17),"northwest",0,2,1);
   add_exit(CPASS(uc/u23),"east",0,2,1);
}
