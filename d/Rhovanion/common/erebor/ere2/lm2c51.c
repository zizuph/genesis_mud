inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("central");
  set_cave("Erebor");
  set_cave_type(5);
  set_long("This is the resting room for the guards. Placed in a "
        +  "short row are a few messy bed to rest on. There is also a "
        +  "weapon and armour rack at the southern wall, but they are "
        +  "both empty at the moment.\n");

  add_item("rack","The racks are both boring and empty.\n");
  add_item("racks","The racks are both boring and empty.\n");
  add_exit(CAVE_DIR + "lm2c42","northwest",0,1);
}
