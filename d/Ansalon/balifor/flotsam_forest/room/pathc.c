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
   set_short("Before a rundown farmhouse");
   set_long("@@long_descr");
   
   add_item(({"path","stone path","rough path","rough stone path"}),
      "A rough path of broken cobblestone and rocks heads southwest " +
      "from the farmhouse through fields of wheat.\n");
   add_item(({"fields","fields of wheat","wheat"}),"Fields of "+
      "wheat grow on either side of the path.\n");
   add_item(({"farmhouse","small farmhouse","rundown farmhouse","small rundown farmhouse"}),
      "Before you is a small rundown farmhouse. Its door is ajar, allowing " +
      "you easy entrance. Smoke billows from the chimney stack, so you presume it is occupied.\n");
   add_item("door","The door to the rundown farmhouse is ajar. You can " +
      "enter it if you wish.\n");
   add_item(({"chimney","chimney stack","smoke"}),"Smoke billows from " +
      "a wobbly chimney stack.\n");
   
   add_exit(FROOM + "pathb","southwest",0);
   
   add_cmd_item(({"farmhouse","door","house"}),"enter","@@enter_house");
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + "You stand upon a rough stone path before a small " +
   "rundown farmhouse. You notice smoke billowing from its chimney stack, so you presume it is occupied. The stone " +
   "path heads to the southwest through fields of wheat.\n";
}

string
enter_house()
{
   write("You step inside the rundown farmhouse.\n");
   TP->move_living("into the farmhouse",FROOM + "farm1",1,0);
   return "";
}
