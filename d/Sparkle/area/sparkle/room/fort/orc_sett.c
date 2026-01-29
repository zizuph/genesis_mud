/* 	orc_sett.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void reset_room();

void
create_room()
{
    set_short("Orc settlement");
    set_long("\n"+
             "You are standing in the middle of a small orc settlement.\n"+
             "The settlement is tiny and seldom used. Only a few orcs seem to\n"+
             "inhabit this place. The valley opens up and continues to the west\n"+
             "with the road following the same direction. To the south, the valley\n"+
             "narrows and the road swings in that direction. A little to the north\n"+
             "you can see some kind of fortification.\n"+
             "");

    add_exit ("orc_fort","north");
    add_exit ("orc_vall2","west");
    add_exit ("orc_vall1","south");
    add_exit ("orc_house","east");

    add_item(({"settlement" }),
             "The settlement consists of a number of low houses\n"+
             "");
    add_item(({"houses","house" }),
             "You wouldn't want to live there.\n"+
             "");
    add_item(({"valley","road" }),
             "\n"+
             "");
    add_item(({"fortification" }),
             "Well, it has a low barricade and a small broken gate.\n"+
             "It shouldn't be a problem to enter unless there are Urukhais\n"+
             "inside. Those critters will attack anything...\n"+
             "");
    add_item(({"barricade" }),
             "It's very poorly built.\n"+
             "");
    add_item(({"gate" }),
             "It's broken and beyond repair.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    reset_room();
}

void
reset_room()
{
    object orc;

    if (!present("orc")) {
        orc = clone_object(S_LOCAL_NPC_DIR + "orc");
        orc->arm_me();
        orc->move_living("apa", TO);
    }
}

