inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(2);
  set_long("You are standing in the middle of the Great Hall. "
         + "Here the sceneary is dominated by the big black hole "
         + "sorrounded by a shiny brass fence. There is small sign "
         + "attached to the fence. Emanating from the hole you can "
         + "hear the faint sound of running water. The enormous hall "
         + "continues in all directions.");

  add_item("hole","Looking down into the darkness of the hole you can "
         + "see black water emerging from the depths below. It flows "
         + "in a slow steady pace, unstoppable, almost like the time "
         + "itself.\n");

  add_item("fence","A sturdy fence high enough to keep dwarves from "
         + "falling into the hole.\n");

  add_item("sign","The sign reads:\n\nThe source of Running.\n");

  add_exit(ERE_DIR + "lm1c11","west",0,1);
  add_exit(ERE_DIR + "lm1c16","north",0,1);
  add_exit(ERE_DIR + "lm1c18","east",0,1);  
  add_exit(ERE_DIR + "lm1c14","south",0,1);
}
