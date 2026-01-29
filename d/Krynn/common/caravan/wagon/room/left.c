/*
 *  Filename:       left.c
 *  Description:    This is the room to the left of every caravan wagon.
 *
 *  Copyright (c) Aug. 2003 by Daniel W. Mathiaen, aka. Boron of Krynn
 *
 *  Change log:
 */

#pragma strict_types
#include "/sys/language.h"
#include "../wagon.h"

inherit ROOM_BASE

/*
 *  function:          make_connections
 *  description:       This function connects this room to the neighbour rooms
 *                      so the mortals can move forward, back, left and right
 */
static void
make_connections()
{
    //Clean up
    remove_exit("forward");
    remove_exit("back");

    if (myWagon->i_am_burned_down())
    {
        add_exit(myWagon->query_room(R_BACK, M_OBJECT), "back", 0, MOVE_BACK_FAT);
        add_exit(myWagon->query_room(R_FRONT, M_OBJECT), "forward", 0, MOVE_FORWARD_FAT);
        return;
    }

    if (myWagon->query_rear())
        add_exit(myWagon->query_room(R_BACK, M_OBJECT), "back", 0, MOVE_BACK_FAT);
    else
        add_exit(myWagon->query_back_wagon()->query_room(R_LEFT, M_OBJECT),
                                            "back", 0, MOVE_BACK_FAT);

    if (myWagon->query_leader())
        add_exit(myWagon->query_room(R_FRONT, M_OBJECT), "forward", 0, MOVE_FORWARD_FAT);
    else
        add_exit(myWagon->query_front_wagon()->query_room(R_LEFT, M_OBJECT),
                                        "forward", 0, MOVE_FORWARD_FAT);
}

public string
long_desc(string longdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    if (!myWagon->i_am_burned_down())
        desc =  "You are on the left side of a caravan, next to you you " +
                "see " + LANG_ADDART(myWagon->short()) + "." +
                "It is possible to go 'forward' or fall 'back' through the wagons " +
                "of the caravan.\n";
    else
        desc =  "You are on the left side of a wagon, next to you you " +
                "see " + LANG_ADDART(myWagon->short()) + "." +
                "It is possible to go 'forward' or 'back' around the wagon.\n";


    return ::long_desc(desc);
}

void
init()
{
    ::init();
}

public string
shorter_desc(string shortdesc)
{
    string desc;
    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.";

    if (!myWagon->i_am_burned_down())
        desc = "On the left hand side of a caravan beside " +
             LANG_ADDART(myWagon->short());
    else
        desc = "On the left hand side of the remains of a wagon";

    return desc;
}

void
create_wagon_room()
{

    set_long(long_desc);

    set_short(shorter_desc);
}

