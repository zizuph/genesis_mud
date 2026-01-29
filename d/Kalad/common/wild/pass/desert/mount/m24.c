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
      "rocky barren. A rocky path travels to the north, and back down to the "+
      "south. A dry, choking wind blows around you, threatening in its "+
      "presence. Towards the east, in the side of one of the mountains is "+
      "a large opening, from which smoke is pouring out of. From above, the "+
      "fierce rays of the Kaladian sun strike you, causing you no end in "+
      "misery.\n");
   add_item(({"slate-grey rocks","rocks","rock"}),"Large, featureless "+
      "stones that have fallen from the mountains.\n");
   add_item(({"rocky path","path"}),"A rugged trail that winds its "+
      "way through this rocky terrain.\n");
   add_item(({"base","mountains","mountain"}),"The dark, grey peaks "+
      "rise high above you, daunting in their size.\n");
   add_item(({"kaladian sun","sun"}),"Its fierce rays nearly blind you!\n");
   add_item(({"edge","steep cliff","cliff"}),"A rocky precipice "+
      "overlooking the rugged terrain around you.\n");
   add_item(({"large opening","opening"}),
      "A twenty foot high hole in the side of the mountain.\n");
   add_item(({"smoke"}),
      "It roils thickly out of the opening, rising skyward in a dark grey "+
      "cloud.\n");
   add_exit(CPASS(desert/mount/m23),"north",0,4);
   add_exit(CPASS(desert/mount/g1),"east","@@smoke");
   add_exit(CPASS(desert/mount/m25),"south",0,4);
}
smoke()
{
   TP->catch_msg("You try and prepare yourself for the smoke.\n");
   set_alarm(2.0,0.0,"smoke_effects");
}
smoke_effects()
{
   TP->catch_msg("The smoke proves too much for you.\n");
   TP->command("cough");
   TP->command("choke");
}
