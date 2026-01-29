/*
 * cas_a2.c
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
    set_long("This is a rather peculiar room, with nothing in it but " +
             "a very slippery sliding pole.\n");
    
    add_exit("cas_a1", "west");
    INSIDE;
    add_item("pole", 
             "A slippery pole which extends up to the second " +
             "level and down to the stable.\n"+
             "Pillows lie around the base.\n");

    add_cmd_item(({"down", "down pole", "pole"}), "slide", "@@slide");
    add_cmd_item("pole", "enter", "@@slide");
    add_cmd_item("pole", "climb", "@@climbpole");
}

string
slide()
{
    write("You slide down the pole to the stable!  Wheeeeee...\n");
    set_dircmd("pole");
    TP->move_living("down the pole", NYREESEDIR + "cadu_stable");
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
