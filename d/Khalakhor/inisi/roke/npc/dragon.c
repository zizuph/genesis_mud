/*
 * dragon.c
 *
 * Used in wild/p6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

//MUPP, Maybe a pacifist dragon that only hugs people.

#pragma save_binary
#pragma strict_types

inherit "/std/creature";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

/* fierce drooling dragon protecting us from undead entering the
   building */

#include <wa_types.h>

inherit "/std/combat/unarmed";
inherit "/std/act/action";

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
    set_name("dragon");
    add_name("ddd");
    add_name("kaheda_dragon_quest");
    set_long("He looks a bit lonely, like a lost pet.\n");
    set_race_name("dragon");
    set_adj("cute");
    add_adj("drooling");
    set_alignment(500);
    default_config_npc(162);

    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);

    add_notify_meet_interactive("meet");

    add_leftover(ROKEDIR + "obj/skin", "skin", 1, "", 1, 1);

    set_attack_unarmed(0, 100, 100, W_IMPALE, 50, "jaws");
    set_attack_unarmed(1, 100, 100, W_BLUDGEON, 50, "heavy tail");
    set_hitloc_unarmed(0, ({100}), 10, "head");
    set_hitloc_unarmed(1, ({100}), 80, "body");
    set_hitloc_unarmed(2, ({100}), 10, "tail");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

int
query_knight_prestige()
{
    return -2;
}

void
sigh()
{
    command("sigh");
    command("emote looks very lonely.");
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "hug")
    {
        set_alarm(1.5, 0.0, &command("hug " + OB_NAME(actor)));
        return;
    }

    if (emote == "sigh")
    {
        set_alarm(2.0, 0.0, &sigh());
        return;
    }
}

void
emote_hook_onlooker(string emote, object actor, string adverb, object * targets)
{
    if (emote == "hug")
    {
        set_alarm(1.5, 0.0, &sigh());
        return;
    }
}

void
meet()
{
    if (TP->query_prop(LIVE_I_UNDEAD))
        set_alarm(1.0, 0.0, &command("growl"));
}

void goaway();
void returnme();

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (function_exists("set_amount", ob) == "/std/food")
        if (random(4))
            set_alarm(1.0, 0.0, &command("eat all"));
        else
            set_alarm(1.0, 0.0, goaway);
    else
        set_alarm(2.0, 0.0, &command("drop " + OB_NAME(ob)));
}

void
goaway()
{
    command("emote flies away to eat the food.");
    move_living("M", WILDDIR + "monk_tree");
    command("eat all");

    set_alarm(30.0, 0.0, returnme);
}

void
returnme()
{
    if (MASTER_OB(environment()) == WILDDIR + "monk_tree")
        move_living("home", query_prop(LIVE_O_LAST_ROOM));
}

void
init_living()
{
    ::init_living();
    add_action("north", "in");
}

int
north(string s)
{
    if (s)
        return 0;

    if (TP->query_prop(LIVE_I_UNDEAD))
    {
        write("As you try to enter the building, the dragon grabs you " +
              "and gives you a hard kick, making you fly through the air " +
              "and land in a huge tree.\n");
        say("The drooling dragon grabs " + QTNAME(TP) + " and kicks " +
            TP->query_objective() + " high up in the air.\n");

        TP->move_living("M", WILDDIR + "monk_tree");
        return 1;
    }
    return 0;
}

void
notify_death(object ob)
{
    ::notify_death(ob);
    ob->catch_msg("You somehow feel that you shouldn't have done that. " +
                  "Dragons have parents too, you know.\n");
}
