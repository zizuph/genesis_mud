/*
 * spirit.c
 *
 * Used in nyreese/cas_a9.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/act/action";
inherit "/std/act/asking";
inherit "/std/act/domove";

#define BORTPROP "_roke_already_got_spirit_quest"
#define SPIRIT_PROP "_roke_got_tissue"

void mkinv(object ob);

void
default_config_npc(int i)
{
    int j;
    for (j = 0; j < 6; j++)
        set_base_stat(j, i);
}

void
create_creature()
{
    default_config_npc(15);

    set_name("spirit");
    set_race_name("spirit");
    set_short("transparent spirit");
    set_adj("transparent");
    set_gender(1);

    set_long("The spirit haunts the castle, until she has found peace.\n");

    set_alignment(200);

    add_act("emote pokes you in the ribs.\n");
    add_act("say Can you help me?\n");

    add_ask(({"help", "task"}), "@@ask_help", 0);
    set_default_answer("emote looks confused.", 1);

    add_prop(OBJ_M_NO_ATTACK, "You can't attack the transparent spirit.\n");
    set_act_time(4);
}

int
query_knight_prestige()
{
    return -2;
}

void
init_living()
{
    add_action("help", "help");
}

int
help(string s)
{
    NF("Help whom?\n");

    if (s != "spirit")
        return 0;

    NF("The spirit is rather confused. She can't see who wants to help her.\n");
    if (TP->query_invis())
        return 0;

    if (TP->query_prop(BORTPROP))
    {
        TP->catch_msg("Sorry, you can only try this once/login session.\n");
        say("The spirit kicks everyone in the groin.\n");
        return 1;
    }

    TP->add_prop(BORTPROP, 1);

    say("The spirit whispers something to " + QTNAME(TP) + ".\n");
    write("You must help me to polish the shimmering globes " +
        "here in the castle. It is very important that they " +
        "are cleaned properly, or else Cadu will be " +
        "destroyed by the evil forces of the former warlords. " +
        "Unfortunately I can't do it myself, because we spirits " +
        "have some problems holding solid objects.\n\n" +
        "The spirit gives you a tissue.\n");

    set_alarm(1.0, 0.0, &mkinv(TP));

    clone_object(ROKEDIR + "obj/tissue")->move(TP);
    return 1;
}

string
ask_help()
{
    if (TP->query_invis())
        return "The spirit is rather confused. She can't see who wants to help her.\n";
    
    help("spirit");
    return "";
}

void
mkinv(object ob)
{
    if (QDONE(ROKEGROUP, SPIRITQUEST))
        return;

    if (time() - ob->query_prop(SPIRIT_PROP) < 3600)
        return;

    TP->add_prop(SPIRIT_PROP, time());

    ob->catch_msg("The spirit says: I'll make you invisible for a short " +
                  "while so you can pass the guard at the stairs.\n");

    object invis = clone_object(ROKEDIR + "obj/temporary_invis");
    invis->move(ob, 1);
}

