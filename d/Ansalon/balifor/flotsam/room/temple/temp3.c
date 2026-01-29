#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_IN;
object skel1, skel2, skel3, skel4;

void
reset_flotsam_room()
{
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
   
   if(!objectp(skel3))
      {
      skel3 = clone_object(TEMP + "living/skel_champ");
      skel3->move(TO);
   }
   
   if(!objectp(skel4))
      {
      skel4 = clone_object(TEMP + "living/skel_champ");
      skel4->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Centre of the temple to the Lord of Death");
   set_long("@@long_descr");
   
   add_item(({"mosaic","yellow skull","skull"}),"This ancient " +
      "mosaic is of a yellow goat skull, the symbol of the God " +
      "of Death, Chemosh. You have a creepy feeling that it is " +
      "leering at you.\n");
   add_item(({"pillars","black pillars","black pillars of rock","rocks"}),
      "Eight black pillars of rock make a ring around the great " +
      "mosaic in the centre of the room. The black pillars are as " +
      "black as coal, and it would not suprise you if they were summoned " +
      "down here from the Abyss itself.\n");
   add_item("altar","You see a raised altar to the south.\n");
   add_item("ceiling","The white marble ceiling is supported " +
      "by eight black pillars. In the centre of the pillars " +
      "is a grotesque mosaic of a goat's skull.\n");
   
   add_exit(TEMP + "ent","north",0);
   add_exit(TEMP + "temp6","south",0);
   add_exit(TEMP + "temp1","northwest",0);
   add_exit(TEMP + "temp2","northeast",0);
   add_exit(TEMP + "temp4","southwest",0);
   add_exit(TEMP + "temp5","southeast",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand in the centre of the temple. Above you a " +
   "mosaic of a great yellow skull has been crafted into the " +
   "marble ceiling. Surrounding it and supporting the ceiling " +
   "are eight black pillars of rock. " +
   "To your south you can make out a raised altar. " +
   "\n";
}
