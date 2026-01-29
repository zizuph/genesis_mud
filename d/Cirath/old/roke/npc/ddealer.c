/*
 * ddealer.c
 *
 * Used in nyreese/red_brewery.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

void
create_monster()
{
    config_default_trade();

    set_name("schlugnur");
    set_race_name("goblin");
    set_adj("stinking");
    set_long("This is a stinkin gobling hanging around in the filthy " +
             "slum district of Cadu.\n");
    set_title("the drug-dealer");

    add_notify_meet_interactive("hiho");

    set_random_move(30);

    set_restrain_path(NYREESEDIR + "red_");
    set_monster_home(NYREESEDIR + "red_brewery");

    default_config_npc(75);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_DEFENCE, 40);

}

int
query_knight_prestige()
{
    return 200;
}

void
makeanoffer(object tp)
{
    if (!tp || E(tp) != E(TO))
        return;

    tp->catch_msg(QCTNAME(TO) +
                  " whispers: Hi there... Wanna buy some grass? Only one gold coin...\n");
    tell_room(E(TO), QCTNAME(TO) + " whispers something to " + QTNAME(tp) +
              ".\n",
              ({tp}));
}

void
hiho()
{
    set_alarm(5.0, 0.0, &makeanoffer(this_player()));
}

void
init_living()
{
    add_action("buy_grass", "buy");
}

int
buy_grass(string s)
{
    int *arr;
    string str;

    notify_fail("Buy what?\n");
    if (s != "grass")
        return 0;

    notify_fail("Get some money before trying to do business!\n");
    if (!can_pay(144, TP))
        return 0;

    arr = pay(144, TP);
    write("You pay " + text(arr) + ".\n");
    arr = exclude_array(arr, 0, 3);
    str = text(arr);
    if (str)
        write("The dealer returns " + str + ".\n");

    write("He gives you some strange brown leaves.\n");
    say(QCTNAME(TP) + " buys something from " + QCTNAME(TO) + ".\n");

    seteuid(getuid());
    clone_object(ROKEDIR + "obj/pot")->move(TP);
    return 1;
}

#if 0
//Disabled until there is a way to detect that the nod is directed
//to the dealer. /Glindor
//FIXA
public void
emote_hook(string emote, object actor, string adverb = 0)
{
    if (emote != "nod")
        return;

    buy_grass("grass");
}

#endif
