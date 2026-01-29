#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_IN;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("Center of the temple");
   set_long("@@long_descr");
   
   add_item(({"center","forsaken temple","temple"}),"@@long_descr");
   add_item(({"great dome","dome","crystal","ceiling",
            "rose crystal"}),
      "Above you is the great dome of the temple. Made of some " +
      "sort of rose crystal, you notice some signs that it was " +
      "once decorated with various legends of the god whose " +
      "temple this place was dedicated to. Now these patterns " +
      "have faded away or are covered with grime, totally " +
      "unrecognizable.\n");
   add_item(({"signs","patterns"}),
      "They are now unrecognizable, being covered with grime " +
      "or having faded with time.\n");
   add_item("cracks","The dome above you is riddled with a " +
      "myriad of cracks.\n");
   add_item("grime","Grime covers much of the dome above you.\n");
   add_item(({"walls","grey marble walls","marble walls"}),
      "These grey marble walls once were decorated with " +
      "patterns, but these have long faded with time.\n");
   add_item(({"passages","passageways"}),
      "Passageways lead off in all the cardinal directions.\n");
   
   
   add_exit(CROOM + "temp4","north",0);
   add_exit(CROOM + "temp5","south",0);
   add_exit(CROOM + "temp6","east",0);
   add_exit(CROOM + "temp2","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand in the center of a forsaken temple. " +
   "Above you is a great dome of some sort of rose crystal. " +
   "In its time it probably would have focused the light " +
   "of the sun or moons into an elaborate pattern on the " +
   "walls and ceiling, but it is now covered with grime, " +
   "and the only light filters through the cracks in it. " +
   "Passageways lead off in all the cardinal directions.\n";
}
