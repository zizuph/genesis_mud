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
  set_long("You are facing an doorway in the northern wall of the "
         + "Great Hall. The air around you is filled with the most "
         + "appetizing smells... Mmmmm... Newly baked bread, roasted "
         + "beef... Yum! This is obviously one of the Montains famous "
         + "taverns. Maybe you should pay it a visit! Behind you the "
         + "Great Hall continues west and south. To your southeast "
         + "there are some stairs leading down. From inside the tavern "
         + "you can hear the sound of people talking. "
         + "Outside there is a sign hanging from the wall.");

  add_item("sign","The sign reads:\n\nThe Golden Stag.\n");

  add_exit(CAVE_DIR + "lm1c16","west",0,1);
  add_exit(CAVE_DIR + "lm1c24","north",0,1);
  add_exit(CAVE_DIR + "lm1c20","southeast",0,1);  
  add_exit(CAVE_DIR + "lm1c18","south",0,1);
}
