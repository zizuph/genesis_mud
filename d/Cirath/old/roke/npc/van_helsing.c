/*
 * van_helsing.c
 *
 * Used in nyreese/cadu_out.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Van Helsing the well known vampire hunter !                 */
/* coded by Calonderiel (With a lot of help from Arren) 930906 */
/*  removed write_file so as not to make log when 
 *  Van Helsing is killed-- Amelia  7/21/97
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";
inherit "/std/act/action";

#include "defs.h"
#include <money.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

int has_introduced = 0;

void
create_monster()
{
    set_name("dr Van Helsing");
    set_living_name("Van Helsing");
    add_name("helsing");
    set_adj("intense");
    add_adj("middle-aged");
    set_race_name("human");

    set_base_stat(SS_CON, 120);
    set_base_stat(SS_DEX, 80);
    set_base_stat(SS_STR, 80);
    set_base_stat(SS_INT, 100);
    set_base_stat(SS_WIS, 100);
    set_base_stat(SS_DIS, 100);

    set_skill(SS_DEFENCE, 60);
    set_skill(SS_WEP_CLUB, 80);
    set_skill(SS_PARRY, 60);
    set_skill(SS_AWARENESS, 70);
    set_alignment(600);

    set_random_move(30);
    set_title("Vampire hunter");
    set_act_time(3);
    add_act("emote looks under the bushes for any skulking vampyres.");
    add_act(({"say I'm looking for my dear friend count Dracul.",
                  "say I've got a gift for him, you see.",
                  "emote shows you a sharpened ash pole!"}));

    set_cact_time(10);
    add_cact("say I'll kill you, minion of darkness!");
    add_cact("emote tries to hit your black heart with a sharpened ash pole!");

    has_introduced = 0;

    set_chat_time(120);
    add_chat("The end of the world is nigh!");
    add_chat("The earthquake made the statues tremble!");

    add_notify_meet_interactive("greet_em");
}

int
emote(string str)
{
    say(QCTNAME(TO) + " " + str + "\n");
    return 1;
}

void
ledsen()
{
    command("sigh");
    command("say Where have all the little vampires gone?");
}

int
leta()
{
    if (!environment(TP)->query_prop(ROOM_I_INSIDE))
        emote("looks under the bushes for any skulking vampyres.");
    else
        emote("looks under the carpet for any hiding vampyres.");
    set_alarm(1.0, 0.0, ledsen);
    return 1;
}

void
tell_vampen()
{
    command("say Where is your master puny one ?");
}

void
greetings()
{
    TP->catch_msg(QCTNAME(TO) + " studies you carefully.\n");
    say(QCTNAME(TO) + " studies " + QCTNAME(TP) + " carefully.\n");
    set_alarm(2.0, 0.0, tell_vampen);
}

void
greet_em()
{
    if (TP->query_guild_name_occ() == "Vampyr guild")
        set_alarm(1.0, 0.0, greetings);
}

void
equip_me()
{
    seteuid(getuid(TO));

    clone_object(ROKEDIR + "arm/h_boots")->move(TO);
    clone_object(ROKEDIR + "arm/h_felt_hat")->move(TO);
    clone_object(ROKEDIR + "arm/h_gloves")->move(TO);
    clone_object(ROKEDIR + "arm/h_kyller")->move(TO);
    clone_object(ROKEDIR + "arm/h_cloak")->move(TO);
    clone_object(ROKEDIR + "arm/h_necklace")->move(TO);
    clone_object(ROKEDIR + "obj/h_crucifix")->move(TO);
    clone_object(ROKEDIR + "wep/h_ashpole")->move(TO);
    clone_object(ROKEDIR + "wep/h_mallet")->move(TO);
    clone_object(ROKEDIR + "wep/h_holy_w_sprinkler")->move(TO);
    
    command("wear all");
    command("wield sprinkler");
}

void
hi()
{
    command("say I've been looking for you !");
    command("grin");
}

void
introduce_me()
{
   command("introduce myself");
   if (TP->query_guild_name_occ() == "Vampyr guild")
      command("cackle");
}

void
remove_int()
{
    has_introduced = 0;
}

void
add_introduced(string name)
{
    if (!has_introduced)
    {
        set_alarm(4.0, 0.0, introduce_me);
        if (TP->query_guild_name_occ() == "Vampyr guild")
        {
            set_alarm(1.0, 0.0, hi);
        }
        has_introduced = 1;
        set_alarm(15.0, 0.0, remove_int);
    }
}

mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    if ((100*query_hp()/query_max_hp()) < 50)
        command("brandish crucifix");
    return (::hit_me(wcpen, dt, attacker, attack_id));
}

/* Solamnian knight prestige */
int query_knight_prestige() {return (-5);}
