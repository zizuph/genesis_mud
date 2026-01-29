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
      "are insured death by the blistering heat of the Kaladian sun. "+
      "To the east lies part of the Desertrise mountains.\n");
   add_item(({"field","rugged terrain","terrain"}),
      "A vast expanse of rocks of many shapes and sizes.\n");
   add_item(({"innumerable rocks","rocks","rock","boulders","boulder"}),
      "The many rocks around you appear in nearly every conceivable shape and "+
      "size, created as they were by the combination of heat and wind and "+
      "erosion.\n");
   add_item(({"kaladian sun","sun"}),
      "It hangs in the sky like the bloated carcass of some unfortunate "+
      "animal.\n");
   add_item(({"desertrise mountains","mountains","mountain"}),
      "A lower series of grey-colored mountains that rises above these "+
      "rock-strewn plains.\n");
   add_exit(CPASS(desert/rock/p32),"northwest",0,4);
   add_exit(CPASS(desert/rock/p14),"north",0,4);
   add_exit(CPASS(desert/rock/p16),"southwest",0,4);
}
