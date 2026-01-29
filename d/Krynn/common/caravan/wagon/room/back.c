/*
 *  Filename:       front.c
 *  Description:    This is the front room of all wagons, it will only be
 *                  the leader in the caravan who has a front room.
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
    remove_exit("left");
    remove_exit("right");

    add_exit( myWagon->query_room(R_LEFT, M_OBJECT), "left", 0, MOVE_FORWARD_FAT );
    add_exit( myWagon->query_room(R_RIGHT, M_OBJECT), "right", 0, MOVE_FORWARD_FAT );
}

public string
long_desc(string longdesc)
{
    string str, desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    if (!myWagon->i_am_burned_down())
        desc =  "You are behind a long caravan, right in front of you is " +
                LANG_ART(myWagon->short()) + " " + myWagon->short() + "." +
                "You are sure you are able to catch up with the wagon in " +
                "front, only question is if you want run up on the 'left' or " +
                "or 'right' hand side of the caravan.\n";
    else
        desc =  "You are behind a wagon, right in front of you is " +
                LANG_ADDART(myWagon->short()) + "." +
                "You can go back around the wagon, " +
                "only question is if you want to walk up on the 'left' or " +
                "or 'right' hand side of the wagon.\n";

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
        desc = "Behind a caravan, with " +
             LANG_ADDART(myWagon->short()) + " right in front";
    else
        desc = "At the rear of the remains of a wagon";

    return desc;
}

void
create_wagon_room()
{

    set_long(long_desc);

    set_short(shorter_desc);
}


