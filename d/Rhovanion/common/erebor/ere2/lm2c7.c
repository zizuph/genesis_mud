inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(5);

  set_long("The room is badly lit up "
        + "but you can see the few funiture it has. "
        + "A bunk, a table and a chair. There is also a picture "
        + "hanging in a corner, right beside the bunk.\n");

  add_item(({"bed","bunk"}),"The bed is very short. If you "
        + "didnt know better, you would have thought it was "
        + "ment for a child. Beside the bed stands a small chest.\n");
  add_item("table","The table is small and made of granite.\n");
  add_item("chair","As you already suspected, the chair is small. "
        + "You must be small as a dwarf to use it. Else forget "
        + "even to try.\n");
  add_item("picture","Its a pencil drawing of a female dwarf. "
        + "If you look carefully you can see her beard. Or is it a "
        + "shadow on her chin?\n");
 
  add_exit(CAVE_DIR + "lm2c6","west",0,1);
 
 
}
