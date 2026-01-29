/* Sarr */
#include "defs.h"
inherit "/std/door";

void
create_door()
{
   set_door_id(VAULT_ID);
   set_pass_command(({"s","south"}));
   set_door_name(
     ({"round vault door", "round door", "vault door", "door", "vault"}));
   set_other_room(KEEP_DIR + "keep19");
   set_door_desc("It is a sturdy iron door attached to a large vault. It is " +
     "flat except for a gold-rimmed keyhole.\n");
   set_lock_name(({"lock", "keyhole", "gold-rimmed keyhole"}));
   set_lock_desc("The keyhole looks typical, except it is gilded around the rim.\n");
   set_open(0);
   set_locked(1);
   set_key(VAULT_KEY);
   set_lock_command("lock");
   set_unlock_command("unlock");
}

