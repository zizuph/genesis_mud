
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
   set_short("Cliffside road on the edge of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"road","cobblestone road"}),"This cobblestone road " +
      "is not quite so well used as the other roads in Flotsam are. " +
      "Weeds and grasses grow up through the cracks between the " +
      "cobblestones, making the stones loose and treacherous. \n");
   add_item(({"cliff","cliffside","steep cliff"}),"The " +
      "cliff disappears into the darkness below. You can hear the sounds " +
      "of the waves of the Blood Sea crashing upon the rocks below.\n");
   add_item("path","A path carved out of the cliff-face. \n");
   
   add_exit(FROOM + "street17","east",0);
   add_exit(FROOM + "street11","west",0);
   add_exit(FROOM + "street15","south",0);
   add_exit(FROOM + "street22","northeast","@@trail",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on a cobblestone " +
   "road on the edge of a steep cliff. The darkness here seems to " +
   "engulf you, and you can hardly make out any details of your " +
   "surroundings. The road continues east, west, and south, while " +
   "to the northeast you can just make out a path windings down the " +
   "cliffside. " + season_descr() + " \n";
}

int
trail()
{
   write("You make your way down the cliffside trail... \n");
   return 0;
}
