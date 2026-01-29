#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_IN;
object acolyte, skel1, skel2;

void
reset_flotsam_room()
{
   if(!objectp(skel1))
      {
      skel1 = clone_object(TEMP + "living/skel_champ");
      skel1->move(TO);
   }
   
   if(!objectp(skel2))
      {
      skel2 = clone_object(TEMP + "living/skel_champ");
      skel2->move(TO);
   }
   
   if(!objectp(acolyte))
      {
      acolyte = clone_object(TEMP + "living/acolyte");
      acolyte->arm_me();
      acolyte->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Temple to the Lord of Death");
   set_long("@@long_descr");
   
   add_item(({"white ceiling","marble ceiling","ceiling"}),
      "A bone-white marble ceiling, supported by black pillars "+
      "of rock.\n");
   add_item(({"pillars","black pillars","sinister black pillars",
            "sinister black pillars of rock","rock","black rock"}),
      "As black as coal,these pillars seem to have been summoned down " +
      "here by black magic from the Abyss itself.\n");
   add_item(({"walls","wall","pictures"}),"You see pictures " +
      "of creatures dead and dying, their desperate thrashing " +
      "movements as they struggle to live carved in graphic detail " +
      "on the white marble walls of the temple. Alongside " +
      "these you see carvings of legions of undead being lead " +
      "by evil wizards across the lands of Krynn, along with " +
      "many other depictions of death and destruction on Krynn.\n");
   
   add_item("torches","The torches are attached to metal " +
      "sconces and cannot be removed.\n");
   
   add_exit(TEMP + "temp2","north",0);
   add_exit(TEMP + "temp3","northwest",0);
   add_exit(TEMP + "temp6","southwest",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand within the temple of the Lord of Death. " +
   "Sinister black pillars of rock support the bone-white " +
   "marble ceiling. Torches line the wall, casting light " +
   "upon the surrounding walls which are all inscribed with " +
   "graphic pictures of death, decay, and eternal corruption. " +
   "\n";
}
