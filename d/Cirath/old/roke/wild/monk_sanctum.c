/*
 * monk_sanctum.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room.c";

#include "defs.h"
#include <macros.h>

void
create_room()
{
    set_short("inner sanctum");

    set_long("You are in the holy sanctum of the Kaheda order. There is a large altar\n" +
             "in the center of the room. It is said that the first guildmaster was\n" +
             "buried under the altar. You can feel his soul in this room and when you\n" +
             "close your eyes you can see his deeds in your mind.\n" +
             "To your left side you can see a priest kneeling before the altar.\n");

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item("priest",
             "He is kneeling before the altar and he would probably " +
             "dislike you if you disturbed him.\n");

    add_item("altar", "Its a black altar made of stone.\n");

    add_exit("monk_h2", "south");

    INSIDE;
}

void
init()
{
    ::init();
    add_action("kneel", "kneel");
    add_action("close", "close");
}

int
close(string text)
{
    if (text != "eyes" && text != "my eyes")
    {
        notify_fail("Close what ?\n");
        return 0;
    }

    TP->catch_msg("You close your eyes and you can see your master when he is\n" +
                  "fighting a seven headed hydra with his bare hands.\n");

    say(QCTNAME(TP) + " closes " + TP->query_possessive() +
        " eyes and looks overwhelmed.\n");
    return 1;
}

int
kneel()
{
    TP->catch_msg("You kneel down before the altar and you can feel how the " +
                  "soul\nof the guildmaster is making you stronger.\n");

    say(QCTNAME(TP) + " kneels down before the altar.\n");

    return 1;
}
