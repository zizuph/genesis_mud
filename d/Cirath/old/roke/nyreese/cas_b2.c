/*
 * cas_b2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

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
