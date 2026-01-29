/*
 * d5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("the ancient treasure chamber");
    set_long("This is the ancient treasure chamber of the dwarves.\n" +
             "The walls look strong and if the door hadn't been destroyed " +
             "you would most likely not have been able to enter the room.\n");

    add_exit("d3", "north");

    /* do NOT EVER put a reset_room loading treasurechests here!!! /gres */
}

void
load_chest()
{
    object ob = present("chest", TO);
    
    if (!objectp(ob))
    {
        ob = clone_object(ROKEDIR + "obj/treasurechest");
        ob->move(TO);
    }
    ob->fill_chest();
}
