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
  set_cave_type(2);
  set_long("You are standing in the Great Hall just along the "
         + "south wall. The gigantic hall seems to go on forever "
         + "expanding to your north and west. There seems to be "
         + "some sort of establishment to your south. Through the "
         + "doorway you can hear the sound of laughing people. "
         + "Outside there is a small red sign.");

  add_item("sign","The sign reads:\n\nThe Red Lantern.\n");

  add_exit(CAVE_DIR + "lm1c14","west",0,1);
  add_exit(CAVE_DIR + "lm1c18","north",0,1);
  add_exit(CAVE_DIR + "lm1c20","northeast",0,1);  
  add_exit(CAVE_DIR + "lm1c84","south",0,1);
}
