/*
 * monk_chapel.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*     The Chapel in the Kaheda Order */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/guild_support";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
/*    string sign =
        "Membership commands:\n" +
        "join occupational\n" +
        "join layman\n" +
        "leave order\n" +
        "update membership\n" +
        "apply for membership\n" +
        "check application\n" +
        "remove application\n\n";
*/

    set_short("small, dark room");
/*
    set_long("You are inside the small chapel of the monastery. It is rather " +
             "dark here; the only source of light is a small window high " +
             "up on one of the walls. There is also a small altar here, " +
             "where you may pray to connect yourself with the gods. " +
             "There is a small sign here, and at the entrance, you see a list.\n");
*/
    set_long("A strange disquiet fills you as you enter this dark room.  " +
             "The only source of light is a small window high up on one of " +
             "the walls. The remains of a stone table, or pedestal are " +
             "centred in the north end of this room.\n");

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");

    add_prop(ROOM_I_INSIDE, 1); /* This is a real room */

    add_exit("monk_board", "south");

    add_item(({"table", "pedestal", "altar"}), 
             "This stone construction appears to be the remains of a large " +
             "table, a pedestal, or perhaps an altar.\n");
    add_item("altar", "The altar is made of stone.\n");
/*
    add_item("list", "@@newlist");
    add_cmd_item("list", "read", "@@newlist");
    add_item("sign", sign);
    add_cmd_item("sign", "read", sign);
*/

    create_guild_support();
}

void
init()
{
    add_action("gs_meditate", "pray");
    add_action("gs_meditate", "meditate");
    ::init();
}

void
leave_inv(object who, object to)
{
    gs_leave_inv(who, to);
    ::leave_inv(who, to);
}

int
gs_hook_already_meditate()
{
    write("You are already praying. If you wish to stop praying " +
          "you can do so by typing 'rise'.\n");
    return 1;
}

void
gs_hook_start_meditate()
{
    write("You kneel in front of the altar and begin to chant a strange " +
          "tune. As you pray to the gods you feel strangely relaxed. " +
          "You find yourself able to <estimate> your different " +
          "preferences and <set> them at your own desire.\n" +
          "Just <rise> when you are done praying.\n");
}

void
gs_hook_rise()
{
    write("Feeling very relaxed, you rise from the altar.\n");
    say(QCTNAME(TP) + " rises from the altar.\n");
}

int
gs_hook_catch_error(string str)
{
    write("You can't do that while praying.\n");
    return 1;
}
