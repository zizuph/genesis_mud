/*
 * cadu_hotel.c
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
    set_short("Small room in the Inn of Cadu");
    set_long("This is the small room used as hotel.\n" +
             "A small sign hangs on the wall.\n");

/*  add_item("sign","The hotel is closed by the Gont board of health.\n");
*/
    add_item("sign", 
             "If you have a ticket you may type 'start here' " +
             "to start here the next time you enter the game.\n");

    add_cmd_item("sign", "read",
                 "If you have a ticket you may type 'start here' " +
                 "to start here the next time you enter the game.\n");

    add_exit("cadu_inn", "down");

    INSIDE;
}

int
start(string s)
{
    object ob;

    NF("start where?\n");
    if (s != "here")
        return 0;

    if (!(ob = present("cadu_inn_ticket", TP)))
    {
        write("You don't have a ticket!\n");
        return 1;
    }

    ob->remove_object();

    TP->set_temp_start_location(NYREESEDIR + "cadu_hotel");

    write("You will start here the next time you enter the game.\n");
    //    TP->command("$quit");
    return 1;
}

void
init()
{
    ::init();

    add_action(start, "start");
}
