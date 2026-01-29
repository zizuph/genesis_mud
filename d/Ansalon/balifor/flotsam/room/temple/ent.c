
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_IN;
object zomb1, zomb2, skel1, skel2;

void
reset_flotsam_room()
{
   if(!objectp(zomb1))
      {
      zomb1 = clone_object(TEMP + "living/zombie");
      zomb1->move(TO);
   }
   if(!objectp(zomb2))
      {
      zomb2 = clone_object(TEMP + "living/zombie");
      zomb2->move(TO);
   }
   
   if(!objectp(skel1))
      {
      skel1 = clone_object(TEMP + "living/skel_hero");
      skel1->move(TO);
   }
   
   if(!objectp(skel2))
      {
      skel2 = clone_object(TEMP + "living/skel_hero");
      skel2->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Main entrance to the temple of the Lord of Death");
   set_long("@@long_descr");
   
   add_item(({"pillars","rock","black rock"}),"As black as coal, " +
      "these pillars seem to have been summoned down here by " +
      "black magic from the Abyss itself.\n");
   add_item(({"raised altar","altar"}),"You see a raised altar " +
      "to the south.\n");
   add_item(({"great marble stairway","marble stairway","stairway"}),
      "A marble stairway fans down from the passageway above.\n");
   add_item(({"walls","marble","marble walls","bone-white marble"}),
      "The walls of the temple are made of " +
      "bone-white marble.\n");
   add_item(({"passages","red passages","glowing red passages"}),
      "The marble stairway leads upwards to the glowing red " +
      "passages of the upper level of the temple.\n");
   
   
   add_exit(TEMP + "t5","up","@@up_stairs");
   add_exit(TEMP + "temp3","south",0);
   add_exit(TEMP + "temp1","southwest",0);
   add_exit(TEMP + "temp2","southeast",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand at the main entrance to a temple dedicated " +
   "to the Lord of Death. A great marble stairway fans upward " +
   "to glowing red passages. Unlike the passages above, this room is made of bone-white " +
   "marble, with great pillars of black rock holding up the " +
   "ceiling. To the south at the far end of the temple you can " +
   "just make out a raised altar. To the southeast and southwest " +
   "the walls can be followed to the outer parts of the temple. " +
   "\n";
}


int
up_stairs()
{
   write("You climb up the marble stairway.\n");
   return 0;
}
