inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("In the mountains");
   set_long("A myriad assortment of slate-grey rocks adorns this "+
      "bleak setting like so much refuse. Winding its way through it is a "+
      "rocky path, which heads off to the east and southwest. High in the "+
      "sky is the Kaladian sun, its presence baking the land beneath it "+
      "mercilessly.\n");
   add_item(({"slate-grey rocks","rocks","rock"}),"Large, featureless "+
      "stones that have fallen from the mountains.\n");
   add_item(({"rocky path","path"}),"A rugged trail that winds its "+
      "way through this rocky terrain.\n");
   add_item(({"base","mountains","mountain"}),"The dark, grey peaks "+
      "rise high above you, daunting in their size.\n");
   add_item(({"kaladian sun","sun"}),"Its fierce rays nearly blind you!\n");
   add_item(({"edge","steep cliff","cliff"}),"A rocky precipice "+
      "overlooking the rugged terrain around you.\n");
   add_item(({"sky"}),"It is the clear blue typical of most deserts.\n");
   add_item(({"land"}),"It is parched and desolate, a setting quite common "+
      "in this part of Kalad.\n");
   add_exit(CPASS(desert/mount/m30),"east",0,4);
   add_exit(CPASS(desert/mount/m32),"southwest",0,4);
}
