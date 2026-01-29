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

#include "/d/Krynn/common/defs.h"
#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

/* Global variables */
string gMessage, gSender, gCrest;
int gOpen = 0;

/* Prototypes */
public string query_crest();
public void set_crest(string str);

public int
quit_test()
{
    return(query_verb() == "quit");
}

public string
long_desc()
{
    string desc = "This piece of parchment is used for writing missives. ";
    if (gOpen)
    {
        desc += "It is unrolled, and contains a message. "+
	    (query_crest() == "none" ? "" : "At the bottom of "+
	    "the parchment is a crest of "+query_crest())+". ";
    }
    else
    {
        desc += "It has been rolled up and "+
	    (query_crest() == "none" ? "tied shut with a string" :
	    "sealed with a crest of "+ query_crest())+". ";
    }

    desc += "If you wish, you may 'tear' it or 'destroy' it.\n";
    return desc;
}

public void
create_object()
{
    set_name("scroll");
    set_short("scroll");
    set_long(&long_desc());

    add_prop(OBJ_M_NO_DROP, &quit_test());
}

public void
set_crest(string crest)
{
    gCrest = crest;
}

public string
query_crest()
{
    if (!strlen(gCrest))
	return "none";

    return gCrest;
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
            write("You unroll " + LANG_THESHORT(this_object()) + 
		(query_crest() == "none" ? "" : ", breaking the "+
		"seal of "+query_crest()) +".\n");
            say(QCTNAME(TP)+" breaks the seal on "+LANG_THESHORT(TO)+
		" and unrolls it.\n");
            gOpen = 1;
        }

        write(capitalize(LANG_THESHORT(this_object())) + " reads:\n");
        write(gMessage);
        if (query_crest() != "none")
        write("The scroll has been signed by "+query_sender()+", and "+
	    "stamped with the crest of "+query_crest()+".\n");
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
