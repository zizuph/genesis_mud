/* 	giant_conf.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void reset_room();

void
create_room()
{
    set_short("Giant conference");
    set_long("\n"+
             "The giant conference.\n"+
             "This is the place where the giants arrange their annual elf bashing\n"+
             "conference. But since elves are sparse in these regions, humans,\n"+
             "dwarves, hobbits, goblins and gnomes will also do.\n"+
             "");

    add_exit("giant_path","east");

    add_item(({"place","ground" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    reset_room();
}

void
reset_room()
{
    object giant;
    int i;

    if (!present("giant")) {
        for (i = 0; i < 3; i++) {
            giant = clone_object(S_LOCAL_NPC_DIR + "giant");
            giant->arm_me();
            giant->move(TO);
        }
    }
}

