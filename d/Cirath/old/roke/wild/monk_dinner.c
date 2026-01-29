/*
 * monk_dinner.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Ged */
/* Milan added list of members 19.10.93 */
/* Food added by Glindor May-94 */

/* last edition made by Fysix, october 1996
 * involving the addition of the guild member list
 * I left the old dinner list function (list_of_members())
 * in this room, in case it's needed again in the future
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room.c";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

int win;

void
create_room()
{
    set_short("diningroom");

    set_long("You are in a nice diningroom. The members of the guild " +
             "use to have nice dinners here. There are windows to the " +
             "south and west, giving you a very nice view of Gont. " +
             "In the middle of the room there is a large dinner-table " +
             "and there are also some chairs to sit on when you want " +
             "to eat. In the corner you can see a list.\n");

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item(({"chair", "chairs"}), "These chairs look very comfortable.\n");

    add_item("table", "This is a sturdy oak table. Looks perfect when you " +
             "want to eat a meal after a training pass.\n");

    add_item(({"window", "windows"}), "@@window");

    INSIDE;

    add_exit("monk_h1", "east");

    //    room_add_object(MONKS + "servers/member_poster");
}

void
init()
{
    ::init();
    add_action("goherb", "enter");
    add_action("close", "close");
    add_action("open", "open");
    add_action("sit", "sit");
}

int
sit()
{
    TP->catch_msg("You sit down on one of the chairs, but you decide to " +
                  "stand up again immediately.\n");

    say(QCTNAME(TP) + " sits on one of the chairs for a short moment.\n");
    return 1;
}

string
window()
{
    if (win == 1)
    {
        return
            "The windows are made of the highest quality glass you can find.\n" +
            "One of them seems to be open and below you can see a herbgarden.\n";
    }
    else
    {
        return
            "The windows are made of the highest quality glass you can find.\n" +
            "It looks like you could open one of them.\n";
    }
}

int
goherb(string apa)
{
    if (apa == "window" && win == 1)
    {
        write("You leave through the open window.\n");
        say(QCTNAME(TP) + " leaves through the open window.\n");
        TP->move_living("M", WILDDIR+ "monk_herbg_sw");
        return 1;
    }
    else
    {
        if (apa != "window")
        {
            TP->catch_msg("Enter what ? The window?\n");
            return 1;
        }
        else
        {
            TP->catch_msg("Are you kidding? Enter the closed window!\n");
            return 1;
        }
    }
}

int
open(string s)
{
    if (!s || s != "window")
    {
        NF("Open what?\n");
        return 0;
    }

    if (win == 0)
    {
        write("You open the window easily.\n");
        say(QCTNAME(TP) + " opens one of the windows.\n");
        win = 1;
    }
    else
        write("The window is already open.\n");
    return 1;
}

int
close(string s)
{
    if (!s || s != "window")
    {
        NF("Close what?\n");
        return 0;
    }

    if (win == 0)
    {
        TP->catch_msg("Its very hard to close a closed window !\n");
        return 1;
    }
    else
    {
        TP->catch_msg("You close the open window.\n");
        say(QCTNAME(TP) + " closes the open window.\n");
        win = 0;
        return 1;
    }
}
