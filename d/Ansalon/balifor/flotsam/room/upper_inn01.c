#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_IN;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("Ordinary Bedroom in the Jetties Inn");
   set_long("@@long_descr");
   
   add_item("shrubbery","A neat little shrub. It grows quietly to itself.\n");
   add_item(({"poor painting","painting"}),
      "This is a painting of a ship in a terrible storm on the " +
      "Blood Sea of Istar. It is a rather crude piece of artwork.\n");
   
   add_exit(FROOM + "inn01","down","@@down",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand in a pretty ordinary bedroom. If you " +
   "have paid for a room you can start here " +
   "when you next decide to return to these realms. " +
   "On the wall is a poor painting of the Blood Sea " +
   "of Istar, and a shrubbery sits quietly in the " +
   "corner.\n";
}

int
down()
{
   write("You climb down the sagging stairway...\n");
   return 0;
}
