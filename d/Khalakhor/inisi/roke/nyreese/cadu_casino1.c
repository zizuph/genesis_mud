/*
 * cadu_casino1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

object table;

void
reset_room()
{
    if (!table)
    {
        table = clone_object(ROKEDIR + "obj/bjtable");
        table->move(TO);
    }
}

void
create_room()
{
    set_short("Black Jack room");
    set_long("This is one of the hot spots of Cadu. " +
             "People come from all over the world to play Black Jack. " +
             "The cosy Black Jack table stands in one corner of the room " +
             "and there are lots of people around it looking at the game. " +
             "To the south you can see the main hall.\n");
   
    add_exit("cadu_casino", "south");
    add_prop(ROOM_M_NO_ATTACK, "No violence in here, please.\n");
   
    reset_room();
}

int
query_won_money()
{
    return table->query_won_money();
}

void
leave_inv(object ob, object to)
{
    if (interactive(ob)) table->leave_room(ob);
    ::leave_inv(ob, to);
}
