/*
 * ddealer.c
 *
 * Used in nyreese/red_brewery.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

int talking;

void
create_monster()
{
    config_default_trade();

    /*set_name("schlugnur");*/
    NEVERKNOWN;
    set_name("dealer");
    set_race_name("goblin");
    set_adj("stinking");
    set_long("This is a stinkin gobling hanging around in the filthy " +
             "slum district of Cadu.\n");
    set_title("the drug-dealer");

    add_ask("grass", "say It's excellent stuff. Just one gold coin!", 1);
    add_ask(({"help", "task", "job"}), "@@job");

    add_notify_meet_interactive("hiho");

    set_random_move(30);

    set_restrain_path(NYREESEDIR + "red_");
    set_monster_home(NYREESEDIR + "red_brewery");

    default_config_npc(75);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_DEFENCE, 40);

}

void
res_talk()
{
    talking = 0;
}

string
job()
{
    if (talking) return "";
    talking = 1;
    command("say I'd like you to do the following:");
    set_alarm(1.0, 0.0, &command("say Go three steps west."));
    set_alarm(4.0, 0.0, &command("say Pound your head against the wall."));
    set_alarm(6.0, 0.0, &command("say Stand on one leg and say 'cuckoo'."));
    set_alarm(8.0, 0.0, &command("say And then ponder if you are really up to any task."));
    set_alarm(9.0, 0.0, &res_talk());

    return "";
}
int
query_knight_prestige()
{
    return 200;
}

void
makeanoffer(object tp)
{
    if (!tp || ENV(tp) != ENV(TO))
        return;
    if (talking) return;

    tp->catch_msg(QCTNAME(TO) +
                  " whispers: Hi there... Wanna buy some grass? Only one gold coin...\n");
    tell_room(ENV(TO), QCTNAME(TO) + " whispers something to " + QTNAME(tp) +
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

    write("He gives you some strange brown grass.\n");
    say(QCTNAME(TP) + " buys something from " + QCTNAME(TO) + ".\n");

    seteuid(getuid());
    clone_object(ROKEDIR + "obj/pot")->move(TP);
    return 1;
}

public void
emote_hook(string emote, object actor, string adverb,
           object *oblist, int cmd_attr, int target)
{
    if (!target || emote != "nod")
        return;

    buy_grass("grass");
}
