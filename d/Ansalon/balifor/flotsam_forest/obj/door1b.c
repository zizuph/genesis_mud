/*

cell_door1a.c
-------------

Coded ........: 95/01/28
By ...........: Jeremiah

latest update : 96/12/16
By ...........: Arman

*/

#include "/d/Ansalon/balifor/flotsam_forest/local.h"
inherit STDDOOR;

create_door()
{
   ::create_door();
   set_door_id("door1");
   set_pass_command("north");
   set_door_name(({"silver gate","gate"}));
   set_other_room(MAZE + "d16");
   set_door_desc("This unadorned door is made completely of " +
      "silver.\n");
   set_lock_command("lock");
   set_lock_mess(({"locks the silver gate.\n","The lock " +
            "'clicks' loudly as you lock the silver gate.\n"}));
   set_fail_lock(({"The silver gate is already locked.\n",
            "No point in locking an open gate.\n"}));
   set_unlock_command("unlock");
   set_unlock_mess(({"unlock the silver gate.\n","The lock " +
            "clicks open as you turn the key.\n"}));
   set_fail_unlock("The gate is already unlocked.\n");
   set_pick(99);
   set_open(0);
   set_locked(1);
   set_key(SILVER_KEY);
}

