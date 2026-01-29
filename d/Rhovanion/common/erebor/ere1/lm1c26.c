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
  set_cave_type(1);
  set_long(" "
         + " "
         + " "
         + " "
         + " "
         + " "
         + " "
         + " ");

  add_item("door",BS(
    "It is a normal looking oak door, on which a small sign has been nailed. "
  + "\n"));
  
  add_item("sign",BS(
    "\n"
  + "Beds for hire. "
  + "\n"));
  
  door = clone_object(CAVE_DIR + "door_lm1c26.c");
  door->move(TO);
  
  add_exit(CAVE_DIR + "lm1c22","south",0,1);
  add_exit(CAVE_DIR + "lm1c25","west",0,1);
  add_exit(CAVE_DIR + "lm1c28","north",0,1);

}
