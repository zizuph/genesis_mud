/*
 *  Filename:       armdoor2.c
 *  Description:    This is a door for a wagon.
 *
 *  Copyright (c) Sep. 2003 by Peter Bech Lund, aka. Vencar of Krynn
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
        str = "Its an open strong steel door, without any traces " +
              "of ways to handle it, a big blank steel plate that have " +
              "no features whatsoever.\n";
    else
        str = "Its a closed strong steel door, without any traces " +
              "of ways to handle it, a big blank steel plate that have " +
              "no features whatsoever.\n";
    return str;
}

create_door()
{
   ::create_door();
   set_door_id("armdoor");
   set_pass_command("wagon");
   set_door_name(({"strong steel door","door", "steel", "strong"}));
   set_door_desc("@@door_desc");
   set_lock_desc("You see no lock.\n");
   set_open_desc("There is an open heavily armoured door in the left side " +
                 "of the wagon.\n");
   set_closed_desc("There is a closed heavily armoured door in the left side " +
                 "of the wagon.\n");

   set_pick(75);
   set_open(0);
   set_locked(1);
   set_key(ARM_KEY);
}

public void
make_connection(string obj, object door)
{
    set_other_room(obj);
}

int
close_door(string arg)
{
    tell_object( TP, "You look for a handle on " + TO->short() +
                     " but can't find one.\n");

    return 1;
}

int
open_door(string arg)
{
    tell_object( TP, "You look for a handle on " + TO->short() +
                     " but can't find one.\n");

    return 1;
}
