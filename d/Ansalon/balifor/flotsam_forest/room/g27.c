#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;
object centaur1,centaur2;

void
reset_flotsam_room()
{
   if(!objectp(centaur1))
      {
      centaur1 = clone_object(FNPC + "centaur2");
      centaur1->arm_me();
      centaur1->move(TO);
   }
   if(!objectp(centaur2))
      {
      centaur2 = clone_object(FNPC + "centaur1");
      centaur2->arm_me();
      centaur2->move(TO);
   }
}

create_flotsam_room()
{
   set_short("A serene glade in an ancient forest");
   set_long("@@long_descr");
   
   add_item(({"serene glade","glade","natural clearing",
            "clearing"}),"@@long_descr");
   add_item(({"ancient forest","forest","trees","thicket",
            "oak trees","oaks",
            "thicket of trees","branches","shadows"}),"Surrounding " +
      "this serene glade is an ancient forest of oak trees. The " +
      "branches of the forest sway gently with the wind as if " +
      "beckoning you, and eerie sounds echo from its shadows.\n");
   add_item(({"lush green grass","green grass","lush grass",
            "grass"}),"Throughout the glade grows lush green grass. " +
      "In some areas it looks like it has been trampled.\n");
   
   add_exit(FROOM + "g25","southeast",0);
   add_exit(FROOM + "g26","west",0);
   add_exit(FROOM + "g21","northeast",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand within a serene glade in an ancient " +
   "forest. Lush grass grows all through this natural clearing, " +
   "ending at a thicket of trees that surround the glade. " +
   tod_descr3() +
   "\n";
}
