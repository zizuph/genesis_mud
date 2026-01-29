/*
 * monk_start.c
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
/*    set_short("starting room");*/
    set_short("small room");

/*
    set_long("This is a small and cosy room. This room is actually very "+
             "small, it is so small that you can't even lie down here."+
             " You can hardly see the small sign on the western wall. "+
             "Back east you can see the training room.\n");
*/
    set_long("This room, (if you can call it that, and not a hole), is so " +
             "small that you can barely stand.  You certainly couldn't lie " +
             "down here.\n");
    add_cmd_item("down", "lie", "No, you can't do that here!\n");

/*
    add_prop(ROOM_M_NO_ATTACK, "You can not do that while on Sacred ground.\n");
    add_item("sign","If you are a member you may type 'start here'\n"+
             "to start here when you enter the game.\n");

    add_cmd_item("sign","read",
                 "If you are a member you may type 'start here'\n"+
                 "to start here when you enter the game.\n");
*/

    add_exit("monk_train","east");

    INSIDE;
}
