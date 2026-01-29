inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/defs.h"
#include "default.h"

void create_clone_handler()
{
  set_default_area(TELBERIN_DIR);
  add_clone(NPC_DIR + "curan", -1);
  add_clone(NPC_DIR + "wanderguard", 4);
  set_clone_handler_id("Telberin clone handler");
}
