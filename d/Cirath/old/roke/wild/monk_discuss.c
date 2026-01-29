/*
 * monk_discuss.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room.c";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

public void
create_room()
{
    set_short("kaheda newsroom");

    set_long("This is the Kaheda newsroom. Here the guildmembers gather to talk\n" +
             "about the latest gossip in the world. The room is quite large and\n" +
             "there is a very nice atmosphere here, you feel at home. In one of the\n" +
             "corners you can see a small statuette. There is also a large window in the\n"
             +
             "eastern wall. Someone has put a board on the northern wall.\n" +
             "There is a small text on the left side of the board.\n" +
             "Someone has put a brand new faq-board here.\n");

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item("statuette", "Its a small statuette of a mighty wizard." +
             " There is a small sign on it.\n");

    add_item("sign",
             "Rub statuette if you want to go to the common board.\n");
    add_item("faq-board", "@@faq");
    add_cmd_item("faq-board", "read", "@@faq");
    add_cmd_item("sign", "read",
                 "Rub statuette if you want to go to the common board.\n");
    add_item("text", "This board should be used for internal discussions.\n");

    add_cmd_item("text", "read",
                 "This board should be used for internal discussions.\n");

    add_item("window", "You can see a very nice view of Gont from here.\n");

    add_cmd_item(({"window", "through window"}), "look",
                 "You see a beautiful view of Gont. You wish that you were born here.\n");

    INSIDE;

    add_exit("monk_h1", "west");
    add_exit("monk_store", "south");

    clone_object(ROKEDIR + "obj/xmastree")->move(TO);
}

void
init()
{
    ::init();
    add_action("rub", "rub");
}

int
rub(string apa)
{
    if (apa != "statuette")
    {
        notify_fail("Rub what ?\n");
        return 0;
    }
    TP->catch_msg("As you rub the statue it comes to life and you are teleported\n"+             "to the common room.\n");

    say(QCTNAME(TP)+" is integrated by the small statuette.\n");

    TP->move_living("M", WILDDIR + "common");
    return 1;
}
