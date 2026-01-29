/*
 * tissue.c
 *
 * Used in npc/spirit.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "std/object";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

#define SPIRIT_PROP "_roke_got_tissue"

void
remove_object()
{
    tell_room(ENV(TO), "The tissue dissolves magically.\n");
    ::remove_object();
}

void
leave_env(object a, object b)
{
    ::leave_env(a, b);

    if (living(b))
        return;

    set_alarm(2.0, 0.0, remove_object);
}

void
add_prop(string prop, int value)
{
    ::add_prop(prop, value);

    if (query_prop("_roke_i_polished_globe_1") &&
        query_prop("_roke_i_polished_globe_2") &&
        query_prop("_roke_i_polished_globe_3") &&
        query_prop("_roke_i_polished_globe_4"))
    {
        write("You have managed to polish all globes. The tissue " +
              "dissolves in a bright flash.\n");

        if (!QDONE(ROKEGROUP, SPIRITQUEST))
        {
            write("You feel a divine power making you more experienced.\n");
            QLOG("Polish quest", SPIRITQUESTXP);
            QSET(ROKEGROUP, SPIRITQUEST);
            TP->add_exp_quest(SPIRITQUESTXP);
        }
        TP->remove_prop(SPIRIT_PROP);
        remove_object();
    }
}

void
create_object()
{
    set_name("tissue");

    set_short("paper tissue");
    set_adj("paper");
    set_long("A light blue paper tissue.\n");
    seteuid(getuid());
}

int
blow(string s)
{
    if (s != "nose")
        return 0;

    this_player()->catch_msg("You blow your nose with the tissue.\n");
    say(QCTNAME(this_player()) + " blows " +
        this_player()->query_possessive() +
        " nose with a paper tissue.\n");

    return 1;
}

void
init()
{
    ::init();

    add_action(blow, "blow");
}
