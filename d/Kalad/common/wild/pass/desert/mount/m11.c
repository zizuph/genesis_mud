inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("In the mountains");
   set_long("A myriad number of slate-grey rocks abounds in this area, "+
      "surrounding you on every side. A rocky path stretches out before "+
      "you, heading to the northeast and southwest. A warm wind, laden "+
      "with dust, blows through the area. Above, the malevolent "+
      "rays of the Kaladian sun beat down upon you, impeding your movement.\n");
   add_item(({"slate-grey rocks","rocks","rock"}),"Large, featureless "+
      "stones that have fallen from the mountains.\n");
   add_item(({"rocky path","path"}),"A rugged trail that winds its "+
      "way through this rocky terrain.\n");
   add_item(({"base","mountains","mountain"}),"The dark, grey peaks "+
      "rise high above you, daunting in their size.\n");
   add_item(({"kaladian sun","sun"}),"Its fierce rays nearly blind you!\n");
   add_item(({"edge","steep cliff","cliff"}),"A rocky precipice "+
      "overlooking the rugged terrain around you.\n");
   add_exit(CPASS(desert/mount/m12),"northeast",0,4);
   add_exit(CPASS(desert/mount/m10),"southwest",0,4);
}
