/*
 * transformer.c
 *
 * Used in wild/monk_lib.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Given a title by Gorboth, Oct 2009.
 */

// MUPP, add a timeout that cleans data

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"
#include <ss_types.h>
#include <macros.h>

#define H_NAM(x) (what->id(x))

#define ORCBABY 1
#define ROKEBEER 2
#define IRONPOT 4
#define GRIMOIRE 8
#define BUTTERCUPS 16
#define LOGS 32
#define ALLOFIT 63
#define SAVEFILE ROKEDIR + "npc/transob"

void createwand(object who);
void clona(object who);

string *gubbar;
int *bitm;
static int has_introduced = 0;

void
create_monster()
{
    gubbar = ({});
    bitm = ({});
    seteuid(getuid(TO));
    restore_object(SAVEFILE);

    set_title("the Old, Former Brother of Kaheda and Caretaker of the"
      + " Monastery");
    set_name("drelkhorn");
    add_name("brother");
    set_race_name("human");
    add_name("hermit");
    set_short("old hermit");
    set_adj("old");
    add_adj("wise");

    set_long("The hermit is old, really old. You suspect that he even " +
             "might be old enough to have been around when this " +
             "monastery was still a place full of life.\n");

    default_config_npc(35);
    set_base_stat(0, 60);
    set_alignment(200);
    set_exp_factor(50);

    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_HEIGHT, 187);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_skill(SS_UNARM_COMBAT, 100);
}

int
query_knight_prestige()
{
    return -2;
}

void
do_intro()
{
    command("introduce me");
}

void
clear_intro()
{
    has_introduced = 0;
}

void
add_introduced(string who)
{
    if (!has_introduced)
    {
        has_introduced = 1;
        set_alarm(2.0, 0.0, &do_intro());
        set_alarm(15.0, 0.0, &clear_intro());
    }
}

void
thank_chat(object from, object what)
{
    int index;
    int temp;

    if (!objectp(what))
        return;

    if (function_exists("create_object", what) == "/std/food")
    {
        command("say Gee! Thanks! I *love* food!");
        command("eat all");
        return;
    }

    if (H_NAM("ha-ha-given-by-mayor"))
    {
        command("ponder");
        set_alarm(2.0, 0.0, &command("say I guess that you want to have " +
                                     "it transformed into a wand..."));
        set_alarm(5.0, 0.0, &command("say You should fetch me a few " +
                                     "other objects too."));
        set_alarm(7.0, 0.0, &command("say I need Refnas' grimoire from " +
                                     "the castle..."));
        set_alarm(10.0, 0.0, &command("say ...a lovely buttercup..."));
        set_alarm(13.0, 0.0, &command("say ...a corpse of an orc " +
                                      "baby..."));
        set_alarm(15.0, 0.0, &command("say ...a Cadu beer, an iron " +
                                      "pot, and a log to build a fire."));
        set_alarm(20.0, 0.0, &command("say Gather those things, return" +
                                      " here and give them to me."));

        if (member_array(from->query_real_name(), gubbar) < 0)
        {
            gubbar += ({from->query_real_name()});
            bitm += ({0});
        }
        what->remove_object();

        save_object(SAVEFILE);
        return;
    }

    index = member_array(from->query_real_name(), gubbar);

    if (index < 0)
    {
        command("say I don't want this!!! Are you sure that you shouldn't");
        command("say give me something else first???");
        command("drop all");
        return;
    }

    temp = bitm[index];

    if (H_NAM("corpse of orc baby"))
        bitm[index] = bitm[index] | ORCBABY;
    if (H_NAM("cadubeer"))
        bitm[index] = bitm[index] | ROKEBEER;
    if (H_NAM("ironpot"))
        bitm[index] = bitm[index] | IRONPOT;
    if (H_NAM("refnasgrim"))
        bitm[index] = bitm[index] | GRIMOIRE;
    if (H_NAM("buttercups"))
        bitm[index] = bitm[index] | BUTTERCUPS;
    if (H_NAM("log") || H_NAM("wood"))
        bitm[index] = bitm[index] | LOGS;

    if (bitm[index] == temp)
    {
        command("say I don't want this!");
        command("drop all");
        return;
    }

    if (bitm[index] == ALLOFIT)
        set_alarm(1.0, 0.0, &createwand(from));

    command("say Thanks! I will keep it for you!");

    what->remove_object();
    save_object(SAVEFILE);
}

void
createwand(object who)
{
    set_alarm(5.0, 0.0, &command("emote creates a strange hole in the " +
                                 "floor and dumps the stuff in it."));
    set_alarm(10.0, 0.0, &command("emote opens the hole again and " +
                                  "catches something thrown to him.\n"));
    set_alarm(15.0, 0.0, &clona(who));
}

void
clona(object who)
{
    int index;
    object w;

    w = clone_object(ROKEDIR + "obj/questwand");
    w->move(who);
    w->add_prop("_the_transformer", who);

    set_this_player(who);
    command("say Here! Now return the wand to the mayor!");
    who->catch_msg(QCTNAME(this_object()) + " gives you a wand.\n");
    say(QCTNAME(this_object()) + " gives a wand to " + QTNAME(who) +
        ".\n");

    index = member_array(who->query_real_name(), gubbar);

    gubbar = exclude_array(gubbar, index, index);
    bitm = exclude_array(bitm, index, index);

    save_object(SAVEFILE);
}

void
enter_inv(object what, object from)
{
    int ran;

    ::enter_inv(what, from);

    if (!from)                  /* Perhaps it was cloned and moved to me... */
        return;

    set_alarm(itof(1 + random(10)), 0.0, &thank_chat(from, what));
}
