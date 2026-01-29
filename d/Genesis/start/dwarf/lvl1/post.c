/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Newbie helper poster added.
 * TAPAKAH, 25/05/2005
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/d/Genesis/lib/post";

#include "../defs.h"

void
create_room()
{
    set_short("The post office of Dwarfheim");
    set_long("You are in the Dwarfheim office of the Genesis Mail System.\n"+
             "It is very silent here, for a post office. In the northern\n"+
             "wall is a counter, with a clerk that waits for your orders.\n"+
             get_std_use());
   
    add_item("counter","The counter is built into the wall.\n");

    add_item("clerk","The clerk is watching you suspiciously.\n");
    add_item("wall", "It is cut from the stone.\n");
    add_exit(LVL1 + "corr3","south");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
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
    ::leave_inv(ob,to);

    post_leave_inv(ob,to);
}

void
mail_message(string new)
{
    write("\nThere is" + new + " mail for you in the post office of Dwarfheim.\n"+
          "(w-s-s-w-w-n from the temple.)\n\n");
}
