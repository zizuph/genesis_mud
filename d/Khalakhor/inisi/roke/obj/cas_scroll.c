/*
 * cas_scroll.c
 *
 * Used in nyreese/cas_t12.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/scroll";

#include "defs.h"

void
create_scroll()
{
    set_name("scroll");
    set_long("An ancient scroll surrounded with an aura of pure magic.\n");
    set_short("ye olde scroll of wisdom");
    set_file(ROKEDIR + "obj/scrollfile");
}

void
init()
{
    ::init();
    add_action("ask", "ask");
}

int
ask(string s)
{
    notify_fail("Ask for what? Reward?\n");
    if ((s != "reward") && (s != "for reward"))
        return 0;

    if (file_name(environment(TP)) != (NYREESEDIR + "cadu_q5"))
    {
        notify_fail("Maybe you should go somewhere else to do that?\n");
        return 0;
    }

    if (!QDONE(ROKEGROUP, SCROLLQUEST))
    {
        seteuid(getuid());
        TP->add_exp_quest(SCROLLQUESTXP);
        QLOG("Scroll quest", SCROLLQUESTXP);
        QSET(ROKEGROUP, SCROLLQUEST);
        //MUPP Add some text from statue
        write("You feel more experienced.\n");
    }
    write("The scroll disappears.\n");
    remove_object();
    return 1;
}
