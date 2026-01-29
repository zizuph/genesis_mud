/*
 * beggar.c
 *
 * Used in nyreese/cadu_q2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <stdproperties.h>

void
create_monster()
{
    set_name("ovurnurf");
    add_name("beggar");
    set_title("the beggar");
    set_adj("old");
    set_short("old beggar");
    set_long("He looks very hungry.\n");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_act_time(5);
    add_act("say Please! Give me something to eat...");
    set_alignment(50);

    default_config_npc(20);

    add_leftover(ROKEDIR + "obj/skin", "skin", 1, "", 1, 1);

    add_ask("dragon", "The beggar says: The dragon lives in a cave.\n");
    add_ask("wand", "The beggar says: Wands are usually zapped.\n");

    ::create_monster();
}

int query_knight_prestige(){return -3;}

void
thanx(object tp)
{
    set_this_player(tp);

    if (!present("ppapp", tp))
    {
        tp->catch_msg("Here! Take this as a reward for your help.\n");
        tp->catch_msg("The beggar gives you an old piece of paper.\n");
        clone_object(ROKEDIR + "obj/ppapp")->move(tp);
    }
    if (!QDONE(ROKEGROUP,BEGGARQUEST))
    {
        tp->catch_msg("You feel more experienced!\n");
        tp->add_exp(BEGGARQUESTXP);
        QSET(ROKEGROUP, BEGGARQUEST);
        QLOG("feed beggar");
    }

}

void
enter_inv(object a, object b)
{
    ::enter_inv(a,b);
  
    if (function_exists("set_amount", a) == "/std/food")
        set_alarm(5.0, 0.0, &thanx(TP));
  
    set_alarm(2.0, 0.0, &command("say thank you!"));
    set_alarm(3.0, 0.0, &command("eat all"));
}
