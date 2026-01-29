/*
 * File Name        : start.c
 * By               : Elmore and Boron
 * Inspiration from : -
 * Date             : March 2001
 * Description      : The Knights of Palanthas' start room.
 *
 */

#pragma strict_types

inherit "/d/Krynn/std/room";

#include "../local.h"

void
create_krynn_room()
{
    set_short("A huge barrack");
    set_long("This is a huge room, the walls are made of white stone, there are "
        + "long rows of beds along the wall, each of them have a small table "
        + "with a golden feather to write with.\n");

    add_item("bed", "You might be able to sleep here if you are a Knight of "
            + "Palanthas.\n");

    add_exit("center_room", "southwest");
}

int
start(string str)
{
    if (str != "here")
    {
        write("Start here?\n");
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("You are not a member of this guild!\n");
        return 1;
    }

    if (this_player()->set_default_start_location(GUILD_STARTLOC))
    {
        write("Ok. You will now start here.\n");
    }
    else
    {
        write("Sorry, some problem prevents you from starting here.\n");
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(start, "start");
}
