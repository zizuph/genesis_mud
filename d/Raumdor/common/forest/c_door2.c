/* Sarr */
#include "defs.h"
inherit "/std/door";

void
create_door()
{
   set_door_id("rector");
   set_pass_command(({"n","north"}));
   set_door_name(({"steel door","door"}));
   set_other_room(FOREST_DIR + "crypt1");
   set_door_desc("This is a very large, steel door. On it, you see runes "+
   "engraved on it, but don't know what they mean. There is a heavy "+
   "lock on it.\n");
   set_fail_pass("The vault is closed and sealed with a heavy lock.\n");
   set_open(0);
   set_locked(1);
   set_key(782);
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   set_lock_desc("It is a large lock with and odd shaped key-hole.\n");
}
