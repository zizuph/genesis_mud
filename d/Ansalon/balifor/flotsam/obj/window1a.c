/*
Door from corridor into cell, ground level.

cell_door1a.c
-------------

Coded ........: 95/01/28
By ...........: Jeremiah

latest update : 95/05/21
By ...........: Jeremiah

*/

#include "/d/Ansalon/balifor/flotsam/local.h"
inherit STDDOOR;

create_door()
{
   ::create_door();
   set_door_id("window1");
   set_pass_command("window");
   set_door_name(({"shuttered window","window"}));
   set_other_room(FROOM + "inn_room1");
   set_door_desc("This is a shuttered window. A simple " +
      "latch is used to keep it closed. It is so dirty you " +
      "can see nothing of what is on the other side. \n");
   set_lock_command("lock");
   set_lock_mess(({"locks the shuttered window.\n","You hear the " +
            "latch fall into place with a soft 'click'.\n"}));
   set_fail_lock(({"The window is already locked.\n","Lock an open " +
            "window?\n"}));
   set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the shuttered window.\n", "The latch " +
            "pops out with a soft 'click'.\n"}));
   set_fail_unlock("The window is already unlocked.\n");
   set_pick(19);
   set_open(0);
   set_locked(1);
   set_key(BOGUS_KEY);
}

