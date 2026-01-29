inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Within the rock plains");
   set_long("You are within a field covered with innumerable rocks, "+
      "a fair number of which are the size of boulders and some as "+
      "massive as a small cottage. "+
      "An eerie-sounding wind whistles among the rocks, producing a tone "+
      "that grates on one's nerves. "+
      "The surrounding terrain is rugged to the extreme and is lacking in "+
      "any plant life, as the heat from the Kaladian sun insures readily.\n");
   add_item(({"field","rugged terrain","terrain"}),
      "A vast expanse of rocks of many shapes and sizes.\n");
   add_item(({"innumerable rocks","rocks","rock","boulders","boulder"}),
      "The many rocks around you appear in nearly every conceivable shape and "+
      "size, created as they were by the combination of heat and wind and "+
      "erosion.\n");
   add_item(({"kaladian sun","sun"}),
      "It hangs in the sky like the bloated carcass of some unfortunate "+
      "animal.\n");
   add_exit(CPASS(desert/rock/p29),"northwest",0,4);
   add_exit(CPASS(desert/rock/p11),"northeast",0,4);
   add_exit(CPASS(desert/rock/p12),"east",0,4);
   add_exit(CPASS(desert/rock/p13),"southeast",0,4);
   add_exit(CPASS(desert/rock/p31),"south",0,4);
   add_exit(CPASS(desert/rock/p33),"southwest",0,4);
   add_exit(CPASS(desert/rock/p34),"west",0,4);
}
