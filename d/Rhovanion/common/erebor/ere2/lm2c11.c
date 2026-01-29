inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{
  object east_door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("western");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("The corridor ends abruptly in a dead end. "
        + "You can see some marks on the wall though.\n");

  add_exit(CAVE_DIR + "lm2c13","south",0,1);
 
  add_item("marks","The marks read:\nOin was here\n");
 
 
}
