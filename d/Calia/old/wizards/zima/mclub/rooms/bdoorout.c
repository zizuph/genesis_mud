/* MCLUB - Bell Tower Door, Outside
**
** History:
** Date      Coder      Action
** -------- ----------- -------------------------------
** 5/2/95   Zima        Created - found in shvests.c
**
*/
inherit "/std/door";
#include "defs.h"
 
void create_door() {
    ::create_door();
    set_other_room(ROOM_DIR+"shbellt1");
    set_door_id(BELLTOWER_DOOR_ID);
    set_door_desc("It is a heavy oak door with an arched top which leads "+
                  "to the east. There is an iron lock on it.\n");
    set_door_name("door");
    set_open(0);  /* closed initially */
    set_locked(1); /* locked initially */
    set_no_pick(); /* not pickable */
    set_open_desc("The heavy oak door is open leading east.\n");
    set_open_desc("There is an opened door leading east.\n");
    set_pass_command(({"e","east"}));
    set_fail_pass("The heavy oak door is closed.\n");
    set_open_mess(({"opens the heavy oak door.\n",
                    "The heavy oak door swings open to the west.\n"}));
    set_fail_open(({"The heavy oak door is already opened.\n",
                    "The heavy oak door is locked.\n"}));
    set_close_mess(({"closes the heavy oak door.\n",
                     "The heavy oak door swings shut to the west.\n"}));
    set_fail_close("The heavy oak door is already closed.\n");
    set_lock_command("lock");
    set_lock_name(({"lock","iron lock"}));
    set_lock_desc("It is an iron lock on the heavy oak door, cast with "+
                  "simple arcane designs.\n");
    set_lock_mess(({"locks the heavy oak door with a copper key.\n",
                    "The iron lock on the heavy oak door clicks.\n"}));
    set_fail_lock(({"The heavy oak door is already locked.\n",
                    "The heavy oak door is not closed.\n"}));
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the heavy oak door with a copper key.\n",
                      "The iron lock on the heavy oak door clicks.\n"}));
    set_fail_unlock("The heavy oak door is not locked.");
    set_key(BELLTOWER_KEY_NUM);
}
