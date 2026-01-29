
#include "../goblins.h"

#pragma save_binary

inherit "/std/door";

create_door() {
  ::create_door();
  set_door_id("sinkhole");
  set_pass_command(({"d","down"}));
  set_door_name(({"steel grate","grate"}));
  set_other_room(GOBLIN_CAVERN_DIR + "chamber");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(1);
  set_key(time());
}
