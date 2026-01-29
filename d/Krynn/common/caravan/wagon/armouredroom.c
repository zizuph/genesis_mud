/*
 *  Filename:       armouredroom.c
 *  Description:    This is the room inside the specific wagon armoured.c.
 *
 *  Copyright (c) Aug. 2003 by Peter Bech Lund, aka. Vencar of Krynn
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
    desc = "Inside the treasury wagon";
    return ::short_desc(desc);
}

public string
long_desc(string longdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =  "Inside the "  +
            myWagon->short() + ".\n" +
            "you see two long narrow slits in the left and right wall " +
            "of the wagon. At the front of the wagon you see a huge " +
            "silverplated chest.\n";

    return ::long_desc(desc);
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

