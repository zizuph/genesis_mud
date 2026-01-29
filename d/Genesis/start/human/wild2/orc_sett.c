/* 	orc_sett.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "wild.h"

void reset_room();

void
create_room()
{
    set_short("Orc settlement");
    set_long("You are standing in the middle of a small orc settlement. The"
      + " settlement is tiny and seldom used. Only a few orcs seem to"
      + " inhabit this place. The road from the south appears to end"
      + " as it heads north toward some kind of fortification.\n");

    add_exit(THIS_DIR + "orc_fort","north");
    add_exit(THIS_DIR + "orc_vall1","south");
    add_exit(THIS_DIR + "orcfort/orc_house","east");

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
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

    reset_room();
}

void
reset_room()
{
    object orc;
    
    if (!present("orc")) {
        orc = clone_object(OBJ_DIR + "orc");
        orc->arm_me();
        orc->move_living("apa", TO);
    }
}
