inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_cave()
{
  object door;
  
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(5);
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
  
  door = clone_object(CAVE_DIR + "door_lm1c25.c");
  door->move(TO);
  
  
  add_exit(CAVE_DIR + "lm1c26","east",0,1);
  

}
