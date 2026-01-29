/*
 * blackjack-room
 * Room in the new Cadu Casino with the blackjack table
 */
#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "../defs.h"
#include <stdproperties.h>

object table;

void
reset_room()
{
    if (!table)
    {
        table = clone_object(CASINO + "obj/bjtable");
        table->move(TO);
    }
}

void
create_room()
{
    set_short("Black Jack room");
    set_long("This is the Black Jack room.\n");
    /*
    set_long("This is one of the hot spots of Cadu. " +
             "People come from all over the world to play Black Jack. " +
             "The cosy Black Jack table stands in one corner of the room " +
             "and there are lots of people around it looking at the game. " +
             "To the south you can see the main hall.\n");
    */
   
    add_exit(CASINO + "room/hall", "south");
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
