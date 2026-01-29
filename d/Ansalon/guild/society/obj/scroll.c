/*
 * /d/Ansalon/guild/society/obj/scroll.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * The scroll that the faerie messengers write on.
 *
 * Gwyneth, December 2000
 */
inherit "/std/object";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

/* Global variables */
string gMessage, gSender;
int gOpen = 0;

public int
quit_test()
{
    return(query_verb() == "quit");
}

public string
long_desc()
{
    string desc = "This is a delicate piece of parchment, sized small " +
        "enough to be carried by a faerie, but large enough to " +
        "be useful. ";
    if (gOpen)
    {
        desc += "Tiny faeries and kender have been artfully drawn onto " +
            "the borders, and some words have been written in the center. ";
    }
    else
    {
        desc += "It has been rolled onto a smooth twig. ";
    }

    desc += "If you wish, you may 'tear' it or 'destroy' it.\n";
    return desc;
}

public void
create_object()
{
    set_name("scroll");
    set_short("illuminated scroll");
    set_adj("illuminated");
    set_long(&long_desc());

    add_prop(OBJ_M_NO_DROP, &quit_test());
}

public void
set_message(string message)
{
    gMessage = message;
}

public string
query_message()
{
    return gMessage;
}

public void
set_sender(string sender)
{
    gSender = capitalize(sender);
}

public string
query_sender()
{
    return gSender;
}

public int
read_scroll(string str)
{
    mixed *scroll = FIND_STR_IN_OBJECT(str, this_player());

    if (!sizeof(scroll))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    if (scroll[0] == this_object())
    {
        if (!gOpen)
        {
            write("You unroll " + LANG_THESHORT(this_object()) + ".\n");
            gOpen = 1;
        }

        write(capitalize(LANG_THESHORT(this_object())) + " reads:\n");
        write(gMessage);
        say(QCTNAME(this_player()) + " looks over " + 
        LANG_THESHORT(this_object()) + ".\n");
        return 1;
    }
    else
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
}

private int
tear_scroll(string str)
{
    mixed *scroll = FIND_STR_IN_OBJECT(str, this_player());

    if (!sizeof(scroll))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    if (scroll[0] == this_object())
    {
        if (!gOpen)
        {
            write("Are you sure you wish to tear this scroll without " +
                "reading it first? If so, try again.\n");
            gOpen = 1;
            return 1;
        }

        write("You tear up the " + short() + " and discard it.\n");
        set_alarm(0.1, 0.0, &remove_object());
        return 1;
    }
    else
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
}

public void
init()
{
    ::init();

    add_action(read_scroll, "read");
    add_action(read_scroll, "study");
    add_action(tear_scroll, "tear");
    add_action(tear_scroll, "destroy");
}
