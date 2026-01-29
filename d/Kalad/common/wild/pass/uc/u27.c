inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A curve in the passage");
   set_long("A curve in the passage.\n"+
      "Stone as stygion as the intentions of fell and craven beasts surrounds "+
      "you from every direction, trapping you in its cold, unyielding "+
      "embrace. An odor, reminiscent of filth and decay pervades the area, "+
      "causing you to avert your nose in disgust. Above lies only the "+
      "impenetrable barrier of rock that lies between this realm of stone "+
      "and darkness and the realm of life and the sun. The passage you are "+
      "in runs to the west and southeast. From the west the faint sound of "+
      "running water can be heard.\n"+
      "A puddle of filthy water lies here.\n");
   add_item(({"passage"}),
      "A relatively cramped tunnel far beneath the surface.\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_item(({"puddle","filthy water","water"}),
      "A brackish pool of water, filled with unidentified bits of matter.\n");
   add_item(({"matter","unidentified bits","bits","bit"}),
      "It is best not to look at such filthy things.\n");
   add_exit(CPASS(uc/u26),"west",0,2,1);
   add_exit(CPASS(uc/u35),"southeast",0,2,1);
}
