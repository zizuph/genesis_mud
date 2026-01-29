/*
 *  Filename:       wr_conestoga.c
 *  Description:    This is the room on top of the passenger wagon
 *                  w_conestoga.
 *
 *  Copyright (c) Okt. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 */

#pragma strict_types
#include "/sys/language.h"
#include "wagon.h"


inherit WAGON_ROOM_INDOOR;


public string
short_desc(string shortdesc)
{
    string desc;
    desc = "Inside the generic boring wagon";
    return desc;
}
public string
long_desc(string longdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =  "You are inside the cubic steel cage of " +
            LANG_ADDART(myWagon->short()) +  ", there is not much room " +
            "here. The floor are also made out of steel bars, making it " +
            "very uncomfortable to travel in this wagon. In the front of " +
            "the cage, there is a grid forming a door.\n";


    return desc;
}

void
init()
{
    ::init();
}


void
create_wagon_room()
{

}


