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
      "Kaladian sun insures that this place remains barren and desolate. "+
      "To the northwest is a rugged path that winds its way up into the "+
      "Desertrise mountains.\n");
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
   add_item(({"rugged path","path"}),"It twists and turns on its way up into the mountains.\n");
   add_exit(CPASS(desert/mount/m2),"northwest",0,4);
   add_exit(CPASS(desert/rock/p2),"northeast",0,4);
   add_exit(CPASS(desert/rock/p24),"east",0,4);
   add_exit(CPASS(desert/rock/p23),"southeast",0,4);
}
