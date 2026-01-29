#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_IN;
object wolf1;
object wolf2;

void
reset_flotsam_room()
{
   if(!objectp(wolf1))
      {
      wolf1 = clone_object(TEMP + "living/d_wolf");
      wolf1->move(TO);
   }
   
   if(!objectp(wolf2))
      {
      wolf2 = clone_object(TEMP + "living/d_wolf");
      wolf2->move(TO);
   }
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
   add_item(({"steps","room","torch-lit room"}),
      "A great marble stairway fans down into a large torch-lit " +
      "chamber, the main part of the temple. \n");
   add_item(({"temple","ancient temple","evil temple"}),
      "This ancient temple definitely was crafted well " +
      "before the cataclysm. It is most likely a relic " +
      "of the city-state of Edon, a part of Istar that " +
      "controlled much of what is now Goodlund, but is " +
      "now ruins. \n");
   
   add_exit(TEMP + "t6","west",0);
   add_exit(TEMP + "t4","east",0);
   add_exit(TEMP + "ent","down","@@down_stairs");
   
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
   "To the south, steps lead down into a torch-lit room. The " +
   "sounds of chanting can be heard from down there. " +
   "\n";
}

int
down_stairs()
{
   write("You walk down the marble stairway and " +
      "into the lower parts of the evil temple.\n");
   return 0;
}
