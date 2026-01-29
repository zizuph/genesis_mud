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
   add_item("illusionary wall","To your east is an illusion " +
      "of a cellar wall. You can pass right through it.\n");
   add_item(({"temple","evil temple","ancient temple"}),
      "This ancient temple definitely was crafted well " +
      "before the cataclysm. It is most likely a relic " +
      "of the city-state of Edon, a part of Istar that " +
      "controlled much of what is now Goodlund. Edon was " +
      "particularly advanced in the art of magic, and " +
      "grew in power and pride to such an extent that it " +
      "broke off from Istar to form their own seperate " +
      "realm, as well as breaking away from the Order of " +
      "High Sorcery to form their own society of mages. " +
      "The wrath of those two terrible enemies brought " +
      "about Edons destruction, leaving only scattered " +
      "ruins as its legacy.\n");
   
   add_exit(FROOM + "passage5","east","@@enter_wall");
   add_exit(TEMP + "t7","south",0);
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
   "The passage continues to the south, while you can pass through " +
   "the illusionary wall to the east to take you back to the cellar. " +
   "\n";
}

int
enter_wall()
{
   write("You pass through the illusionary wall " +
      "and into the cellar.\n");
   return 0;
}
