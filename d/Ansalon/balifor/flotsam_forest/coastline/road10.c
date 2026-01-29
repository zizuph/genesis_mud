#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("A small trail along the edge of a forest");
   set_long("@@long_descr");
   
   add_item(({"small trail","trail"}),
      "This is a small trail, no more than two feet in width, " +
      "probably caused by people walking this way over a long " +
      "space of time. To the north of the trail are low rolling " +
      "hills covered in wild grass. To the south is the border " +
      "of an ancient evergreen forest.\n");
   add_item(({"north","low rolling hills","wild grass"}),
      "To the north are low rolling hills, covered in wild " +
      "grass that sway gently to a soft sea breeze.\n");
   add_item(({"border","ancient evergreen forest"}),
      "To the south of the trail is the outer border of an " +
      "ancient evergreen forest. The sounds of birds and " +
      "insects, as well as the rustle of the leaves as a gentle " +
      "sea breeze blows through its canopy, eminates from " +
      "the forest.\n");
   
   add_exit(CROOM + "road8","northeast",0);
   add_exit(CROOM + "road11","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() +
   "Beneath your feet is a small trail, no more than two " +
   "feet in width, leading westward along the border of an " +
   "ancient evergreen forest, and " +
   "northeastwards " +
   "back towards the main road.\n";
}
