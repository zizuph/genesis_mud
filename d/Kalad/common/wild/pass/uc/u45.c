inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A crossroads of passages");
   set_long("A crossroads of passages.\n"+
      "Black stone, as unnervingly lightless as the realm of the undead, "+
      "surrounds you. Its dark embrace seems to whisper to you the fate "+
      "that is yours should you remain here...death. Giving weight to this "+
      "is the presence of the countless tons of rock overhead, a weight that "+
      "should this passage collapse, would easily end your miserable existence. "+
      "The passage itself takes a bend here, heading off to the west, "+
      "northeast and south.\n");
   add_item(({"crossroads","crossroad"}),
      "An intersection of passages.\n");
   add_item(({"passages","passage"}),
      "A tunnel located far beneath the sun-lit realm of Kalad.\n");
   add_item(({"black stone","stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u44),"west",0,2,1);
   add_exit(CPASS(uc/u39),"northeast",0,2,1);
   add_exit(CPASS(uc/u46),"south",0,2,1);
}
