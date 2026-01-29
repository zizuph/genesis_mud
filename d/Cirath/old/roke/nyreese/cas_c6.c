/*
 * cas_c6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

int op_door = 1;
object butler;

void reset_room();

void
fixroom()
{
    write("This room looks like a huge foyer with hangers on the walls.\n" +
          "The walls seem to stretch on forever upwards. It's probably " +
          "some magical illusion. The light from the ceiling is much stronger " +
          "here. You see an exit to the west and a sturdy, wooden door to the " +
          "east.\n");
    if (op_door)
    {
        write("The door is now closed.\n");
    }
    else
    {
        write("The door is now open.\n");
    }
}

string
exadoor()
{
    string s;
    s = "The door is built from a large piece of oak.\n";

    if (op_door)
        return s + "It is closed.\n";
    return s + "It is open.\n";
}

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("@@fixroom");

    add_exit("cas_c5", "west");
    add_exit("cas_c7", "east", "@@block");

    add_cmd_item("door", "open", "@@opendoor");
    add_cmd_item("door", "close", "@@closedoor");
    add_item("door", "@@exadoor");
    reset_room();
}

void
reset_room()
{
    if (!butler)
    {
        butler = clone_object(ROKEDIR + "npc/butler");
        tell_room(TO, "An old, spooky butler arrives.\n");
        butler->move(TO);
    }
}

int
opendoor()
{
    if (op_door == 1)
    {
        write("You open the sturdy, wooden door.\n");
        say(QCTNAME(TP) + " opens the sturdy, wooden door.\n");
        op_door = 0;
    }
    else
    {
        write("The door is already opened. \n");
        say(QCTNAME(TP) + " tries to open the already open door.");
    }
    return 1;
}

int
closedoor()
{
    if (op_door == 0)
    {
        write("You close the sturdy, wooden door.\n");
        say(QCTNAME(TP) + " closes the sturdy, wooden door.\n");
        op_door = 1;
    }
    else
    {
        write("The door is already closed. \n");

    }
    return 1;
}

int
block()
{
    if (op_door)
    {
        write("Sorry, but the door is closed. " +
              "The butler must have closed it.\n");
        return 1;
    }
    else
        return 0;
}
