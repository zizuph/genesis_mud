inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Rolling grassland");
   set_long("A suprisingly lush, rolling grassland spreads out before "+
      "you. The tall grasses bend slightly in the warm desert wind, which "+
      "is continually blowing from the east. Several large boulders lie "+
      "in the northeast, obscuring your view in that direction. From "+
      "above, the heat of the Kaladian sun reminds you clearly of its "+
      "presence.\n");
   add_item(({"lush grassland","rolling grassland","grassland"}),
      "A slightly elevated region here within the Great Kalad Waste, that "+
      "unlike the rest of the region is filled with a relative abundance "+
      "of plant and animal life.\n");
   add_item(({"tall grasses","grasses","tall grass","grass"}),
      "The golden yellow grass grows to a height of nearly four feet, waving "+
      "and undulating as the wind whips among them, creating the appearance "+
      "of a sea of grass.\n");
   add_item(({"kaladian sun","sun"}),"It hangs in the sky, one of the "+
      "constant reminders to you of the oppressive heat of this land.\n");
   add_item(({"sky"}),"Colored the deepest blue, it is completely free "+
      "of clouds.\n");
   add_item(({"large boulders","boulders","large boulder","boulder"}),
      "As large as a good-sized merchant wagon, the huge rocks lie in a "+
      "nearly straight line to the northeast. It does, however, seem "+
      "possible to walk between them, as they are not spaced too near one "+
      "another.\n");
   add_exit(CPASS(desert/d18),"northeast","@@msg");
   add_exit(CPASS(desert/grass/g5),"south");
   add_exit(CPASS(desert/grass/g4),"southwest");
}
msg()
{
   write("Stepping past the boulders you are greeted by swirling dust "+
      "and a lonely expanse of the Great Kalad Waste.\n");
   return 0;
}
