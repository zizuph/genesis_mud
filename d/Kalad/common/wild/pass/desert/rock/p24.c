inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Within the rock plains");
   set_long("You are within the depths of a field covered with innumerable "+
      "rocks, a number of which are as large as boulders and some even greater "+
      "in size, being as massive as a small cottage. "+
      "A dry, wasting wind spirals among the rocks, its movements causing a "+
      "keening that sends chills down your spine. "+
      "The rugged landscape is utterly devoid of plant life, no doubt due "+
      "to the scorching heat of the Kaladian sun.\n");
   add_item(({"field","rugged terrain","terrain"}),
      "A vast expanse of rocks of many shapes and sizes.\n");
   add_item(({"innumerable rocks","rocks","rock","boulders","boulder"}),
      "The many rocks around you appear in nearly every conceivable shape and "+
      "size, created as they were by the combination of heat and wind and "+
      "erosion.\n");
   add_item(({"kaladian sun","sun"}),
      "It hangs in the sky like the bloated carcass of some unfortunate "+
      "animal.\n");
   add_exit(CPASS(desert/rock/p1),"west",0,4);
   add_exit(CPASS(desert/rock/p2),"north",0,4);
   add_exit(CPASS(desert/rock/p25),"northeast",0,4);
   add_exit(CPASS(desert/rock/p23),"south",0,4);
}
