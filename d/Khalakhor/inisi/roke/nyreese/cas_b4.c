/*
 * cas_b4.c
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
    set_long("You are standing in one of the cornerrooms of the second floor. " +
             "This room is dimly lit by a small blue shimmering globe at the wall. " +
             "The exit to the northeast seems to end up in one of the towers.\n");

    add_item(({"globe", "shimmering globe", "small globe"}),
             "Some ancient magic is used to create light inside the globe.\n" +
             "The globe itself seems to be a part of the wall.\n");
    add_cmd_item("globe", "polish", "@@polish");

    add_exit("cas_t22", "northeast");
    add_exit("cas_b3", "west");
    add_exit("cas_b8", "south");
    INSIDE;
}

int
polish(string s)
{
    object tissue;
    /*
      NF("Polish globe with what?\n");
      if(s!="with tissue")
      return 0;
    */
    NF("But you don't have any tissue!!!\n");
    if (!(tissue = present("tissue", TP)))
        return 0;

    TP->catch_msg("You polish the globe carefully.\n");
    say(QCTNAME(TP) + " polishes the shimmering globe carefully.\n");

    if (!tissue->query_prop("_roke_i_polished_globe_2"))
        TP->catch_msg("The tissue glows for a short moment.\n");

    tissue->add_prop("_roke_i_polished_globe_2", 1);

    return 1;
}
