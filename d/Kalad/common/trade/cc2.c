inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   hear_bell = 1;
   set_short("A dark alley");
   set_long("You are travelling in a dark, narrow alleyway. All around "+
      "the street is "+
      "trash and other rubbish dumped there by the shady inhabitants of "+
      "the many darkened buildings lining this alley.\n");
   add_item(({"dark alleyway","narrow alleyway","alleyway","alley","street"}),
      "An uncomfortably cramped road that sneaks its way among the dark "+
      "buildings around you.\n");
   add_item(({"trash","rubbish"}),"Nasty things dumped here by the "+
      "unfortunate inhabitants of this district.\n");
   add_item(({"darkened buildings","dark buildings","buildings","building"}),
      "Built from cheap pinewood, the black and decayed buildings seem to "+
      "pervade this area with their rotting presence.\n");
   add_exit(TRADE(cc1),"northeast");
   add_exit(TRADE(cc3),"southwest");
}
