/* 	orc_fort.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "wild.h"

void reset_room();

void
create_room()
{
    set_short("Orc fortress");
    set_long("\n"+
             "This is the orc fortress.\n"+
             "A low barricade has been built to prevent any intruders from breaching\n"+
             "the defenses. However, it is a barricade built by orcs...\n"+
             "There is also a low building with a passage leading north.\n"+
             "");

    add_exit(THIS_DIR + "orc_sett","south");
    add_exit(THIS_DIR + "orcfort/r2", "north");

    add_item(({"passage" }),
             "It leads past the barricade and into the building.\n");
    add_item(({"building" }),
             "It seems to be a temple of some kind.\n"+
             "");
    add_item(({"temple" }),
             "The temple is probably some kind of holy place for the orcs.\n"+
             "Perhaps it holds treasures. Orc treasures...\n"+
             "");
    add_item(({"fortress" }),
             "The fortress consists of a inner temple with an open square\n"+
             "surrounded by a weak barricade\n"+
             "");
    add_item(({"square" }),
             "This is where these orcs do their combat training. What a laugh.\n"+
             "");
    add_item(({"barricade" }),
             "Not much to look at. It might stop a few stampeding dwarves but\n"+
             "that's about it. Pathetic.\n"+
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "orc_temple.txt");


    reset_room();
}

void
make_orcs(int n)
{
    object ob;

    for (; n > 0; n--) {
        if (random(10))
            ob = clone_object(OBJ_DIR + "orc");
        else
            ob = clone_object(OBJ_DIR + "urukhai");
        ob->arm_me();
        ob->move_living("apa", TO, 1, 1);
    }
}

void
reset_room()
{
    int i;
    object orc;
    
    if (!present("orc") && !present("urukhai")) {
        make_orcs(3);
        set_alarm(5.0, 0.0, &make_orcs(3));
        set_alarm(10.0, 0.0, &make_orcs(3));
    }
}
