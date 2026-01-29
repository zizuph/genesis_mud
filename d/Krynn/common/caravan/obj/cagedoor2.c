/*
 *  Filename:       cagedoor2.c
 *  Description:    This is a door for a wagon.
 *
 *  Copyright (c) Aug. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 *
 * based on Door from corridor into cell, ground level. cell_door1a.c
 * done by Jeremiah.
 */


#include "../wagon/wagon.h"
inherit STDDOOR;

public string
door_desc()
{
    string str;
    if (query_open())
        str = "This is an open steel grid, a lock sits on the outside of " +
                  "it.\n";
    else
        str = "This is a closed steel grid, a lock sits on the outside " +
              "of it.\n";
    return str;
}

create_door()
{
   ::create_door();
   set_door_id("cagedoor1");
   set_pass_command("wagon");
   set_door_name(({"steel grid","grid", "door"}));
   set_door_desc("@@door_desc");
   set_open_desc("There is an open steel grid at the front of the " +
                 "wagon here.\n");
   set_closed_desc("There is a closed steel grid at the front of the wagon.\n");
   set_lock_command("lock");
   set_lock_mess(({"locks the steel grid.\n","You hear the " +
            "soft 'click' from the lock..\n"}));
   set_fail_lock(({"The steel grid is already locked.\n","Lock an open " +
            "door?\n"}));
   set_unlock_command("unlock");
   set_unlock_mess(({"unlocks the steel grid.\n", "The lock " +
            "gives a soft 'click'.\n"}));
   set_fail_unlock("The steel grid is already unlocked.\n");
   set_pick(29);
   set_open(0);
   set_locked(1);
   set_key(CAGE_KEY);

}

public void
make_connection(string obj, object door)
{
    set_other_room(obj);
}