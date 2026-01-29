#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_IN;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("Red-hued passages of an ancient temple under the town of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"wall","walls","black marble walls","marble walls",
            "passages","passageway",
            "chalcedony","red chalcedony","glowing red chalcedony"}),
      "These black marble walls are streaked with glowing " +
      "chalcedony, that lights up the room a somewhat blood " +
      "red colour.\n");
   add_item(({"temple","evil temple","ancient temple"}),
      "This ancient temple definitely was crafted well " +
      "before the cataclysm. It is most likely a relic " +
      "of the city-state of Edon, a part of Istar that " +
      "controlled much of what is now Goodlund, but is " +
      "now ruins.\n");
   
   add_exit(TEMP + "t3","northeast",0);
   add_exit(TEMP + "t5","west",0);
   
   DARK;
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand within the passages of what can only be " +
   "described as an ancient, and extremely evil, temple. The black " +
   "marble walls are streaked with glowing red chalcedony, which " +
   "pulses like the veins of a dying man. " +
   "\n";
}
