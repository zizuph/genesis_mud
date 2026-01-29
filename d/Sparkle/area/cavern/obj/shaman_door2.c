
/* 
 * Modified for goblin start area by Quis, 17 May 92 
 * An example door made by Nick, 1991-12-19 
 */

#include "../goblins.h"

#pragma save_binary

inherit "/std/door";

create_door() 
{
  ::create_door();

  set_door_id("goblinshamandoor");
  set_pass_command(({"e","east"}));
  set_door_name(({"massive oak door","oak door","massive door","door"}));
  set_other_room(GOBLIN_CAVERN_DIR + "altar");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(1);
}