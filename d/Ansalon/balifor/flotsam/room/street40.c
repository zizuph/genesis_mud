#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("On a street corner outside two warehouses");
   set_long("@@long_descr");
   
   add_item(({"brazier","tall iron brazier","iron brazier"}),"A " +
      "tall iron brazier, its light casting dark shadows on the " +
      "walls of the surrounding buildings. \n");
   add_item("sidewalk","A cobblestone sidewalk. \n");
   add_item(({"corner","street corner"}),"A street corner. " +
      "Nothing unusual with it either.\n");
   add_item("clouds","Overhead loom gloomy clouds that seem to hover " +
      "over Flotsam every minute of the day. \n");
   add_item("warehouses","Two warehouses have entrances on this " +
      "corner. One to the north, the other to the west. \n");
   
   add_exit(FROOM + "ware02","north","@@ware_enter",0);
   add_exit(FROOM + "street39","east",0);
   add_exit(FROOM + "street41","south",0);
   add_exit(FROOM + "ware03","west","@@ware_enter",0);
   
   reset_flotsam_room();
   
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on a street " +
   "corner in the western area of the town of Flotsam. To the " +
   "west and north warehouses stand. A tall iron brazier stands " +
   "off on a sidewalk, relieving little of the gloom brought on " +
   "by the clouds overhead. " + season_descr() + "\n";
}

int
ware_enter()
{
   write("You enter the warehouse... \n");
   return 0;
}
