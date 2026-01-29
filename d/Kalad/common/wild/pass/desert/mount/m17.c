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
   set_long("An apparently endless sea of slate-grey rocks surrounds "+
      "you from every direction, making the world seem composed solely of this "+
      "rocky wasteland. A rocky path heads to the northwest and southeast, "+
      "while the ever-present rays of the Kaladian sun strike you from "+
      "above, seeming to suck the life from you. A harsh and dry wind blows "+
      "around this area, adding to the scene of desolation.\n");
   add_item(({"slate-grey rocks","rocks","rock"}),"Large, featureless "+
      "stones that have fallen from the mountains.\n");
   add_item(({"rocky path","path"}),"A rugged trail that winds its "+
      "way through this rocky terrain.\n");
   add_item(({"base","mountains","mountain"}),"The dark, grey peaks "+
      "rise high above you, daunting in their size.\n");
   add_item(({"kaladian sun","sun"}),"Its fierce rays nearly blind you!\n");
   add_item(({"edge","steep cliff","cliff"}),"A rocky precipice "+
      "overlooking the rugged terrain around you.\n");
   add_exit(CPASS(desert/mount/m16),"northwest",0,4);
   add_exit(CPASS(desert/mount/m18),"southeast",0,4);
}
