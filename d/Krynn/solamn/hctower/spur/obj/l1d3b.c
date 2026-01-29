// cell door in guardrm.c
// grace aug 1994

inherit "/std/door";
#include "../local.h"

void auto_close_door();

void
create_door()
{
    set_door_id("_level1_door3_");
   set_pass_command(({"e","east","go through","out","exit"}));         
   set_fail_pass("Walking through a door is a skill you haven't " +
      "mastered yet. Try opening it first.\n");
   set_door_name(({"flat iron grill","grill", "grille","iron grill",
       "prison cell door", "cell door"}));
   set_door_desc("A flat iron grill set into a stone wall. "+
      "There is a lock on it.\n");
   set_other_room(ROOM + "guardrm.c");
     set_open(0);
   set_locked(1);
   //   set_open_desc();
   //  set_closed_desc();
   set_open_command(({"open","open grill","turn","push"}));
   set_open_mess(({"pushes the grill open.\n", "The flat iron grill " +
            "slowly opens wide.\n "}));
   set_fail_open(({"The grill is already open!\n",
            "You must unlock the grill before it can be opened!\n"}));
   set_close_command(({"close","pull", "pull closed", "close grill"}));
   set_close_mess(({"pulls the grill closed.\n", "The flat iron grill " +
            "slowly slides closed.\n"}));
   set_fail_close("The flat iron grill is already closed.\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It is a small lock made of iron. The key that fits " +
      "this keyhole should be quite small.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"turns a key in the lock of the flat iron grill.\n",
            "You hear a click from the lock of the flat iron grill.\n"}));
   set_fail_lock(({"The cell door is already locked.\n",
            "You feel silly trying to lock and open door!\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"turns a key in the keyhole, unlocking the grill.\n",
            "You hear a click from the lock on the cell door, perhaps " +
            "it is unlocked now.\n"}));
   set_fail_unlock("That doesn't seem possible...\n");
   set_key(CELL);
   set_pick(40);
} 

auto_close_door()
{
   if (!other_door) 
      load_other_door();
   
   do_close_door("");
   do_lock_door("");
   other_door->do_close_door("");
   other_door->do_lock_door("");
}

