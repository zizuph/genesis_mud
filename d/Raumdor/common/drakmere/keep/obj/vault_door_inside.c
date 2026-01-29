#include "defs.h"
inherit "/std/door";

void
create_door()
{
    set_door_id(VAULT_ID);
    set_pass_command(({"n", "north"}));
    set_door_name(
      ({"round vault door", "round door", "vault door", "door", "vault"}));
    set_other_room(KEEP_DIR + "keep18");
    set_door_desc(
      "It is a study iron door that secures the vault. The lock mechanism is " +
      "exposed on this side.\n");
    set_lock_name(({"lock", "mechanism", "lock mechanism"}));
    set_lock_desc(
      "It looks like it accepts a key from the other side, but you can " +
      "easily lock or unlock it from here.\n");
    set_open(0);
    set_locked(1);
    set_no_pick();
    set_str(VAULT_STR);
    set_unlock_command("unlock");
}
