#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object drac1;

void
reset_flotsam_room()
{
   if(!objectp(drac1))
      {
      drac1 = clone_object(KNPC + "baaz");
      drac1->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Crowded street in the town of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"crowded street","street"}),"A crowded, well-used " +
      "cobblestone street that runs east and west. \n");
   add_item(({"alley","alleyway"}),"An uninviting alleyway " +
      "opens up to the north. \n");
   add_item("citizens","Although most of the citizens have wisely " +
      "stayed at home, you notice the odd person dart " +
      "from street to street, avoiding draconian patrols.\n");
   add_item("wanderers","You notice the odd person dart from " +
      "street to street avoiding draconian patrols, but you notice " +
      "that most people have wisely stayed at home.\n");
   
   add_invis_exit(FROOM + "street30","north","@@ent_alley",0);
   add_exit(FROOM + "street35","east",0);
   add_exit(FROOM + "street38","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand in a crowded street " +
   "in the southern parts of Flotsam. You notice that " +
   "those who wander the streets are almost exclusively part " +
   "of the occupying dragonarmy. Most of the town's citizens have " +
   "wisely stayed home, as few would walk the streets with " +
   "such dangerous company. The street continues to the east " +
   "and west, while to your north lies an uninviting alleyway. " +
   season_descr() + "\n";
}

int
ent_alley()
{
   write("You step into the darkness of the alley... \n");
   return 0;
}
