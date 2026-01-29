inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Within the rock plains");
   set_long("You are within a field covered with innumerable rocks, "+
      "a great many of which are as large as boulders and some yet larger, "+
      "being the size of small cottages. "+
      "A dreadful wind blows among the rocks, its eerie tone sending chills "+
      "down your spine and into your soul. "+
      "The rugged terrain lacks any plant life, as all unmoving things "+
      "are insured death by the blistering heat of the Kaladian sun.\n");
   add_item(({"field","rugged terrain","terrain"}),
      "A vast expanse of rocks of many shapes and sizes.\n");
   add_item(({"innumerable rocks","rocks","rock","boulders","boulder"}),
      "The many rocks around you appear in nearly every conceivable shape and "+
      "size, created as they were by the combination of heat and wind and "+
      "erosion.\n");
   add_item(({"kaladian sun","sun"}),
      "It hangs in the sky like the bloated carcass of some unfortunate "+
      "animal.\n");
   add_exit(CPASS(desert/rock/p5),"northwest",0,4);
   add_exit(CPASS(desert/rock/p28),"north",0,4);
   add_exit(CPASS(desert/rock/p34),"northeast",0,4);
   add_exit(CPASS(desert/rock/p33),"east",0,4);
   add_exit(CPASS(desert/rock/p32),"southeast",0,4);
   add_exit(CPASS(desert/rock/p26),"southwest",0,4);
}
