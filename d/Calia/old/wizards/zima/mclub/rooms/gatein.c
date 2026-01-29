/* MCLUB - Gate to the area, inside
**
** History:
** Date      Coder      Action
** -------- ----------- -------------------------------
** 5/2/95   Zima        Created - found in path4.c
**
*/
inherit "/std/door";
#include "defs.h"
 
void create_door() {
    ::create_door();
    set_other_room(ROOM_DIR+"path3");
    set_door_id(GATE_DOOR_ID);
    set_door_desc("It is a cast iron gate set beneath the stone arch. There "+
                  "is a large lock on it.\n");
    set_door_name("gate");
   set_open(0); /* closed for now */
    set_locked(1); /* locked for now */
    set_no_pick(); /* not pickable */
    set_open_desc("There is an open gate leading west.\n");
    set_pass_command(({"w","west"}));
    set_fail_pass("The iron gate is closed.\n");
    set_open_mess(({"opens the iron gate.\n",
                    "The iron gate swings open to the east.\n"}));
    set_fail_open(({"The iron gate is already opened.\n",
                    "The iron gate is locked.\n"}));
    set_close_mess(({"closes the iron gate.\n",
                     "The iron gate swings shut to the east.\n"}));
    set_fail_close("The iron gate is already closed.\n");
    set_lock_command("lock");
    set_lock_name(({"lock","large lock"}));
    set_lock_desc("It is a large brass lock on the iron gate, cast with "+
                  "simple arcane designs.\n");
    set_lock_mess(({"locks the iron gate with a brass key.\n",
                    "The brass lock on the iron gate clicks.\n"}));
    set_fail_lock(({"The iron gate is already locked.\n",
                    "The iron gate is not closed.\n"}));
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the iron gate with a brass key.\n",
                      "The brass lock on the iron gate clicks.\n"}));
    set_fail_unlock("The iron gate is not locked.");
    set_key(GATE_KEY_NUM);
}
