inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Within the rock plains");
   set_long("You are within a field covered with innumerable rocks, "+
      "many the size of boulders and some as large as small cottages. "+
      "An eerie wind whistles among the rocks, its tone grating in its presence. "+
      "The rugged terrain is devoid of plant life, as the heat from the "+
      "Kaladian sun insures that this place remains barren and desolate.\n");
   add_item(({"field","rugged terrain","terrain"}),
      "A vast expanse of rocks of many shapes and sizes.\n");
   add_item(({"innumerable rocks","rocks","rock","boulders","boulder"}),
      "The many rocks around you appear in nearly every conceivable shape and "+
      "size, created as they were by the combination of heat and wind and "+
      "erosion.\n");
   add_item(({"kaladian sun","sun"}),
      "It hangs in the sky like the bloated carcass of some unfortunate "+
      "animal.\n");
   add_exit(CPASS(desert/rock/p2),"west",0,4);
   add_exit(CPASS(desert/rock/p3),"northwest",0,4);
   add_exit(CPASS(desert/rock/p26),"northeast",0,4);
   add_exit(CPASS(desert/rock/p24),"southwest",0,4);
}
