inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("In the mountains");
   set_long("An abundance of slate-grey rocks surrounds you on all sides, "+
      "making the world seem composed solely of mountainous terrain. "+
      "The rocky path stretches out before you, travelling to the "+
      "northeast and south. Partially hidden by the bulk of the mountains "+
      "around you is a dark opening in the west. "+
      "A dirt-choked wind rattles around the area, bringing with it the "+
      "smell of burnt meat. "+
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
   add_exit(CPASS(desert/mount/m11),"northeast",0,4);
   add_exit(CPASS(desert/mount/o1),"west");
   add_exit(CPASS(desert/mount/m9),"south",0,4);
}
