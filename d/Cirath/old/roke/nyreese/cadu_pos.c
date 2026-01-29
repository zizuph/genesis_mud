/*
 * cadu_pos.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/d/Genesis/lib/post";

#include "defs.h"

void
create_room()
{
    set_short("The post office of Cadu");
    set_long("You are now standing in the post office of Cadu.\n" +
             "It's a rather large room, with yellow walls and a " +
             "wooden floor. In the north wall is a counter with a clerk. " +
             "To the west is a burned down house.\n" + get_std_use());
   
    add_item("clerk", "The clerk is watching you suspiciously.\n");

    add_item(({"wall", "walls"}), "They are yellow.\n");
    add_item("house", "It looks like an old pigeonhouse.\n");
    add_item("counter", 
             "This is the counter that the postmaster works behind.\n");
    add_item("clerk", "He stares at you.\n");
    add_item("floor", "The floor is made of solid oak.\n");

    INSIDE;
    add_exit("cadu_a3" , "south");
    add_exit("cadu_pig", "west");
}

void
init()
{
    ::init();
    post_init();
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}
