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
   
   add_exit(FROOM + "g42","northeast",0);
   add_exit(FROOM + "f13","southwest","@@enter_forest");
   
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

int
enter_forest()
{
   write("You step into the shadows of the ancient forest...\n");
   return 0;
}
