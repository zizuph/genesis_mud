#include "../local.h"

inherit STDDOOR;

void
create_door()
{
   ::create_door();
   set_door_id("vaultdoor");
   set_pass_command(({"s", "south","enter"}));
   set_door_name(({"iron door", "door"}));
   set_other_room(TDIR + "sstorein");
   set_door_desc("This is a solid iron clad door. There is a large " +
                 "keyhole in the middle left side of the door, right " +
                 "under the door handle.\n");
   set_lock_command("lock");
   set_lock_mess(({"locks the iron door.\n", "You hear a loud " +
                   "'click' from the doorlock.\n"}));
   set_fail_lock(({"The door is already locked.\n", "The door is open.\n"}));
   set_unlock_command("unlock");
   set_unlock_mess(({"unlocks the iron door.\n", "You hear a loud " +
                     "'click' from the doorlock.\n"}));
   set_fail_unlock("The door is already unlocked.\n");

   set_pick(51);
   set_str(45);

   set_open(0);
   set_locked(1);

   set_key(VAULT_KEY);
}
