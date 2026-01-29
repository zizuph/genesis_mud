inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_cave()
{
  
  object gate;
  
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(1);
  set_long(" "
         + " "
         + " "
         + " "
         + " "
         + " "
         + " "
         + " ");

  add_item("sign",BS(
    "The sign reads:\n"
  + "\n"
  + "Welcome visitor to the broken mug pub, may your visit be ... profitable! "
  + "\n"
  + "\n"));
  
  gate = clone_object(CAVE_DIR + "gate_lm1c77.c");
  gate->move(TO);
  
  
  add_exit(CAVE_DIR + "lm1c78","east",0,1);
  add_exit(CAVE_DIR + "lm1c75","west",0,1);

}
