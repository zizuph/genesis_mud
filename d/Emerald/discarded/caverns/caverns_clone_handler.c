/*
 * CLONE_HANDLER for the Caverns
 * -Alaron
 */

inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/defs.h"
#include "defs.h"

void create_clone_handler()
{
  set_default_area(CAVERNS_DIR);
  add_clone(CAVERNS_DIR + "npc/prisoner3", 1, 1, CAVERNS_DIR + "4jail");
  add_clone(CAVERNS_DIR + "npc/prisoner1", 2, 1, CAVERNS_DIR + "1jail");
  add_clone(CAVERNS_DIR + "npc/pguard", 3, 3, CAVERNS_DIR + "2guardrm");
  add_clone(CAVERNS_DIR + "npc/pguard", 4, 3, CAVERNS_DIR + "1guardrm");
  add_clone(CAVERNS_DIR + "npc/pguard2", 5, 1, CAVERNS_DIR + "6jail");
  add_clone(CAVERNS_DIR + "npc/prisoner2", 6, 1, CAVERNS_DIR + "8jail");
  add_clone(CAVERNS_DIR + "npc/pguard", 7, 1, CAVERNS_DIR + "9jail");
  add_clone(CAVERNS_DIR + "npc/chef", 8, 1, CAVERNS_DIR + "kitchen");
  set_clone_handler_id("Mountain Caverns Clone Handler");
}
