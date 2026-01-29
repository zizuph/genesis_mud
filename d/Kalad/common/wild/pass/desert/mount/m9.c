inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("In the mountains");
   set_long("An abundance of slate-grey rocks surrounds you on all sides, "+
      "making the world seem composed solely of mountainous terrain. "+
      "The rocky path stretches out before you, travelling to the north "+
      "and the southwest. "+
      "A warm wind carresses your skin as it blows about the area. "+
      "The cruel rays of the Kaladian sun strike you from above, searing "+
      "your exposed flesh.\n");
   add_item(({"slate-grey rocks","rocks","rock"}),"Large, featureless "+
      "stones that have fallen from the mountains.\n");
   add_item(({"rocky path","path"}),"A rugged trail that winds its "+
      "way through this rocky terrain.\n");
   add_item(({"base","mountains","mountain"}),"The dark, grey peaks "+
      "rise high above you, daunting in their size.\n");
   add_item(({"kaladian sun","sun"}),"Its fierce rays nearly blind you!\n");
   add_item(({"edge","steep cliff","cliff"}),"A rocky precipice "+
      "overlooking the rugged terrain around you.\n");
   add_exit(CPASS(desert/mount/m10),"north",0,4);
   add_exit(CPASS(desert/mount/m8),"southwest",0,4);
}
