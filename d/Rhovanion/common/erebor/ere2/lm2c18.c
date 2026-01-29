inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("eastern");
  set_cave("Erebor");
  set_cave_type(5);
  set_long("This is the guardroom for the royal guard. "
        + "At the moment the room is empty. The guard "
        + "is probably on duty somewhere close by. Stocked "
        + "in racks are different kind of weapons and armours "
        + "in different seizes, but they seem to be hard "
        + "to steal for you as they are well locked behind strong "
        + "chains and bars.\n");

  add_item(({"rack","racks"}),"The racks are filled with quality "
        + "weapons and armours of dwarven kind. Unfortunately "
        + "they are all locked and impossible to open.\n");
 
  add_exit(CAVE_DIR + "lm2c34","south",0,1);
}
