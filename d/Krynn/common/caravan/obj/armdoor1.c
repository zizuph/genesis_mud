/*
 *  Filename:       armdoor1.c
 *  Description:    This is a magical door for a wagon.
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
        str = "Its an open heavily armoured door with conical steel pads " +
              "pointing away from the door, a lock pulses with " +
              "a strange dark red glow. There are no handle to close " +
              "the door with.\n";
    else
    {
        if (query_locked())
            str = "Its a closed heavily armoured door with conical steel pads " +
                  "pointing away from the door, a lock pulses with " +
                  "a strange dark red glow while humming constantly. There " +
                  "are no handle to open the door with.\n";
        else
            str = "Its a closed heavily armoured door with conical steel pads " +
                  "pointing away from the door, a lock pulses with " +
                  "a strange dark red glow. There " +
                  "are no handle to open the door with.\n";
    }
    return str;
}

public string
lock_desc()
{
    string str;

    if (query_locked())
        str = "The lock is more a kind of an orb, that are humming quietly " +
              "and pulsing in a dark red glow, giving no indications of how " +
              "to be unlocked.\n";
    else
        str = "The lock is more a kind of an orb, which is " +
              "pulsing in a dark red glow, giving no indications of how " +
              "to lock it.\n";
    return str;
}

create_door()
{
   ::create_door();
   set_door_id("armdoor");
   set_pass_command("wagon");
   set_door_name(({"heavily armoured door","door", "armoured"}));
   set_door_desc("@@door_desc");
   set_lock_desc("@@lock_desc");

   set_open_desc("There is an open heavily armoured door on the wagon.\n");
   set_closed_desc("There is a closed heavily armoured door on the wagon.\n");
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
