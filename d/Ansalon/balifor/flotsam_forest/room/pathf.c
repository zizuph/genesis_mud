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
   set_short("Before a well-maintained farmhouse");
   set_long("@@long_descr");
   
   add_item(({"path","rough path","rough stone path","stone path"}),
      "A rough path of broken cobblestone and rocks heads northwest " +
      "from the farmhouse through fields of wheat.\n");
   add_item(({"house","farmhouse","well-maintained farmhouse"}),
      "Before you stands a well-maintained farmhouse. Its door stands " +
      "open allowing easy access.\n");
   add_item(({"entrance","door"}),"The door to the farmhouse stands " +
      "open. You could enter it if you have no problems with tresspassing.\n");
   add_item("stable","A small wooden stable stands at the side of the " +
      "farmhouse.\n");
   add_item(({"fields","fields of wheat","wheat"}),"Fields of wheat " +
      "stand on either side of the path.\n");
   
   add_exit(FROOM + "patha","northwest",0);
   
   add_cmd_item(({"farmhouse","door","house","farm"}),"enter","@@enter_farm");
   add_cmd_item("stable","enter","@@enter_stable");
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + "You stand upon a rough stone path before a " +
   "well-maintained farmhouse. Its entrance stands open before you, " +
   "while to the side is a stable. The stone path leads northwest " +
   "through fields of wheat.\n";
}

string
enter_farm()
{
   write("You step inside the well-maintained farmhouse.\n");
   TP->move_living("into the farmhouse",FROOM + "farm2",1,0);
   return "";
}

string
enter_stable()
{
   write("You step inside the stable.\n");
   TP->move_living("into the stable",FROOM + "stable",1,0);
   return "";
}
