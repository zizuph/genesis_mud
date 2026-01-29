inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("In the mountains");
   set_long("An apparently endless sea of slate-grey rocks surrounds "+
      "you from every direction, making the world seem composed solely of this "+
      "rocky waste. A rocky path travels to the northwest, and back down to the "+
      "southwest. A hot, dry wind races among the mountains, its sound "+
      "somehow threatening in this environment. The fierce rays of the "+
      "Kaladian sun strike you from above, "+
      "causing you no end in misery.\n");
   add_item(({"slate-grey rocks","rocks","rock"}),"Large, featureless "+
      "stones that have fallen from the mountains.\n");
   add_item(({"rocky path","path"}),"A rugged trail that winds its "+
      "way through this rocky terrain.\n");
   add_item(({"base","mountains","mountain"}),"The dark, grey peaks "+
      "rise high above you, daunting in their size.\n");
   add_item(({"kaladian sun","sun"}),"Its fierce rays nearly blind you!\n");
   add_item(({"edge","steep cliff","cliff"}),"A rocky precipice "+
      "overlooking the rugged terrain around you.\n");
   add_exit(CPASS(desert/mount/m17),"northwest",0,4);
   add_exit(CPASS(desert/mount/m19),"southwest",0,4);
}
