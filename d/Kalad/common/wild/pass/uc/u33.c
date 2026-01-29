inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A crossroads of passages");
   set_long("A crossroads of passages.\n"+
      "Stone as black as the soulless undead surrounds you from every angle, "+
      "its lightless embrace promising the only certainty in mortal life, death. "+
      "Overhead lies an unthinkable amount of rock, a massive volume of which "+
      "seperates you from the sun-lit realms up above. The rock's burdening "+
      "presence seems to absorb your energy, leaving you weakened and weary. "+
      "Three passages are open to you here, one leading to the east, "+
      "another to the south and a third one to the southwest.\n");
   add_item(({"crossroads","crossroad","passages","passage"}),
      "A relatively cramped tunnel lying far beneath the surface of Kalad.\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u34),"east",0,2,1);
   add_exit(CPASS(uc/u40),"south",0,2,1);
   add_exit(CPASS(uc/u39),"southwest",0,2,1);
}
