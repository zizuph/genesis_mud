inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("In the mountains");
   set_long("An abundance of slate-grey rocks surrounds you on all sides, "+
      "making the world seem composed solely of mountainous terrain. "+
      "You are travelling on a rocky path that winds its way through the "+
      "mountains, going to the northeast and southwest. "+
      "A dry, mountain wind blows through the mountains, echoing the "+
      "sounds of solitude to your soul. "+
      "The unrelenting rays of the Kaladian sun strike you from above, "+
      "burning the flesh from your bones.\n");
   add_item(({"slate-grey rocks","rocks","rock"}),"Large, featureless "+
      "stones that have fallen from the mountains.\n");
   add_item(({"rocky path","path"}),"A rugged trail that winds its "+
      "way through this rocky terrain.\n");
   add_item(({"base","mountains","mountain"}),"The dark, grey peaks "+
      "rise high above you, daunting in their size.\n");
   add_item(({"kaladian sun","sun"}),"Its fierce rays nearly blind you!\n");
   add_exit(CPASS(desert/mount/m6),"northeast",0,4);
   add_exit(CPASS(desert/mount/m4),"southwest",0,4);
}
