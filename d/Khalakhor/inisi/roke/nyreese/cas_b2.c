/*
 * cas_b2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("This room is dominated by a large hole " +
             "in the middle of the room. There is a sliding pole here " +
             "which is secured in the ceiling, leading down through a " +
             "quite wide hole in the floor.\n");

    add_exit("cas_b3", "east");
    add_exit("cas_b1", "west");
    add_item("pole",
             "A slippery pole which extends all the way down to the stable.\n" +
             "Pillows lie around the base.\n");
    add_cmd_item(({"down", "down pole", "pole"}), "slide", "@@slide");
    add_cmd_item("pole", "enter", "@@slide");
    add_cmd_item("pole", "climb", "@@climbpole");
    INSIDE;
}

string
slide()
{
    write("You slide down the pole to the ground floor!  Wheeeeee...\n");
    set_dircmd("pole");
    TP->move_living("down the pole", NYREESEDIR + "cas_a2");
    return "You stand up and dust yourself off...\n";
}

string
climbpole()
{
    say(QCTNAME(TP) +
        " tries to climb up the pole but fails and slides down.\n");

    write("You try to climb up the pole but slip and" +
          " slide all the way down!\n");
    set_dircmd("pole");
    TP->move_living("down the pole", NYREESEDIR + "cadu_stable");
    return "You stand up and dust yourself off...\n";
}
