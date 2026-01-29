/*
 * cigar.c
 *
 * Used in nyreese/cadu_casino2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/sceduler";

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

void
create_sceduler()
{
    set_name("cigar");
    set_short("fat cigar");
    set_adj("fat");
    set_long("This is a fat cigar from Cadu.\n");
}

int
smoke(string s)
{
    notify_fail("Smoke what?\n");
    if (!id(s))
        return 0;

    notify_fail("It's already lit, stupid!\n");
    if (query_prop("geggegeg"))
        return 0;

    add_prop("geggegeg", 1);
  
    say(QCTNAME(this_player()) + " lights a huge cigar.\n");
    this_player()->catch_msg("You light the cigar.\n");

    enable_random(1);

    set_duration(120);

    set_m_time(15);

    init_sceduling();

    this_player()->add_prop(LIVE_S_SOULEXTRA, "smoking a cigar");

    add_prop(OBJ_I_NO_DROP, "You decide against dropping the burning cigar. It might start a fire.\n");
 
    return 1;
}

void
sceduled_function()
{
    object ob = environment();
    if (living(ob))
        set_this_player(ob);
    else
        return;
    this_player()->catch_msg("You inhale some smoke from the cigar.\n");
    say(QCTNAME(this_player()) +
        " inhales some smoke from a huge cigar.\n");
}

void
remove_function()
{
    string str = "ground";
    object ob = environment();
    if (living(ob))
        set_this_player(ob);
    else
        return;
    
    if (environment(ob)->query_prop(ROOM_I_INSIDE))
        str = "floor";
    this_player()->catch_msg("You drop the consumed cigar on the " + str + ".\n");
    say(QCTNAME(this_player())+" drops a consumed cigar on the " + str + ".\n");
    if (ob->query_prop(LIVE_S_SOULEXTRA) == "smoking a cigar")
        ob->remove_prop(LIVE_S_SOULEXTRA);
}

void
init()
{
    ::init();

    add_action("smoke","smoke");
    add_action("smoke","light");
    add_action("blow","blow");
}

int
blow(string s)
{
    object *obs,who;

    notify_fail("You must light the cigar first.\n");
    if (!query_prop("geggegeg"))
        return 0;

    notify_fail("Blow smoke in whos face?\n");
    if (!s) return 0;
    obs = PARSE_THIS(s, "%l");

    if (!sizeof(obs))
        return 0;
    who = obs[0];

    this_player()->catch_msg("You blow some smoke in " + QTNAME(who) +
                             "'s face.\n");
    who->catch_msg(QCTNAME(this_player()) + 
                   " blows some cigar smoke in your face.\n");
    say(QCTNAME(this_player()) + " blows some smoke in " + QTNAME(who) + 
        "'s face.\n", ({this_player(), who}));

    seteuid(getuid(this_object()));
    clone_object(ROKEDIR + "obj/csmoke")->move(who);

    return 1;
}
