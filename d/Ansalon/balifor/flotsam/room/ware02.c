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
   set_short("Empty warehouse");
   set_long("@@long_descr");
   
   add_item("walls","The great wooden walls rise up " +
      "into the darkness of the ceiling. \n");
   add_item("ceiling","Far above, shrouded in darkness is the " +
      "wooden roof to this warehouse.\n");
   
   add_exit(FROOM + "street40","out","@@ware_out",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand within the great wooden walls " +
   "of one of Flotsams warehouses. This high-vaulted stone " +
   "based structure faces the full fury of the winter " +
   "sea storms that come in from the docks, so it leans " +
   "slightly towards the inner parts of town. At present " +
   "this warehouse is empty, although it is likely to be " +
   "filled soon with provisions for the Dragonarmies. \n";
}

int
ware_out()
{
   write("You leave the warehouse... \n");
   return 0;
}
