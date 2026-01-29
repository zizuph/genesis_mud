inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A bend in the passage");
   set_long("A bend in the passage.\n"+
      "Stone of a color so black, it seems as though it was formed from "+
      "the darkness itself, lies in every direction. It whispers to you with "+
      "a promise of an untimely death and an unmarked grave. Lending "+
      "credence to this is the sheer mass of thousands of tons of rock that "+
      "lie above you, a presence that should it decide to collapse in on "+
      "this passage, would lead to your quick death. The passage itself veers "+
      "to the northwest and east. You can almost feel the moisture coming from "+
      "the northwest, its touch caressing your cheek lewdly.\n");
   add_item(({"passage"}),
      "A tunnel located far beneath the sun-lit realm of Kalad.\n");
   add_item(({"black stone","stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u27),"northwest",0,2,1);
   add_exit(CPASS(uc/u36),"east",0,2,1);
}
