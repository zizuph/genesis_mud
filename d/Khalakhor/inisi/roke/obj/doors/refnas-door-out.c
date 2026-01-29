/*
 * Door to/from Refnas office to solve the lousy
 * bug which was close to thirty years old.
 * Tapakah, 06/2021
 */

#pragma strict_types

#include "../defs.h"

inherit "/std/door";

void
create_door ()
{
  set_door_id("_refnas_door");
  set_pass_command("west");
  set_door_name(({"oak door", "door"}));
  set_other_room(NYREESEDIR + "cas_c6");

  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(1);
  set_pick(50);
}
