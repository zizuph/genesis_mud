#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_IN;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("Farmhouse entrance");
   set_long("@@long_descr");
   
   add_item(({"farmhouse","room"}),"@@long_descr");
   add_item(({"beds","bed"}),"There are two made beds in this room. " +
      "At the bottom of each is a chest.\n");
   add_item(({"chest","chests"}),"A closed and locked chest sits at " +
      "the bottom of each bed. They are probably used to hold clothes " +
      "and private items of the owner.\n");
   
   add_exit(FROOM + "pathf","out",0);
   add_exit(FROOM + "farm_room1","east",0);
   
   add_cmd_item(({"chest","chests"}),({"open","unlock","pick"}),
      "@@open_chest");
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand inside the entrance of the farmhouse. Surprisingly " +
   "you find this room in a very neat and orderly way, quite unlike " +
   "anything you would expect from simple farmers. Two made beds " +
   "are at either side of the room, and a chest sits at the bottom " +
   "of each.\n";
}

string
open_chest()
{
   write("You are unable to open the chest.\n");
   return "";
}
