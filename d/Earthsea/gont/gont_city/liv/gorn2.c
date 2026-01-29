/* 
* Standard guard for Gont Port
*
* Coded by Porta, Dec 97
* Modified by Ckrik May 1998 to include a combat special and call for help.
* Modified by Ckrik 7-26-98 Change of long description.
* Modified by Ckrik 7-27-98 Added quest asks.
*/

#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/remember";
inherit "/d/Earthsea/lib/width_height";

#define ASSIST_ME_HP 1000

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <filter_funs.h>
#include <wa_types.h>
#include "assist.h"
#include "defs.h"
#include "/d/Earthsea/quest_handler/quest_handler.h"

#define SPA_DELAY 6
#define MAX_GUARDS_HELP 3
#define BL_AXE "/d/Earthsea/gont/gont_city/wep/bl_battleaxe"
#define PLATEMAIL "/d/Earthsea/gont/gont_city/arm/blue_platemail"
#define CAPE "/d/Earthsea/gont/gont_city/arm/blue_cape"
#define HELMET "/d/Earthsea/gont/gont_city/arm/blue_mask"
#define FEET "/d/Earthsea/gont/gont_city/arm/blue_boots"
#define GUARD "/d/Earthsea/gont/gont_city/liv/guard5"
#define PLAYER_I_GOT_STANDARD_ADV "_i_got_standard_adv"
#define PLAYER_I_GOT_SHIP_QUEST "_i_got_ship_quest"
#define PLAYER_I_BURNED_KARG_SHIPS "_i_burned_karg_ships"
#define TASK_ASK   ({"help", "task", "job",\
"about task", "about job", "quest", "about quest" })
#define KARG_ASK ({"karg", "kargs", "warrior", "warriors", "boat",\
    "boats", "landing", "invasion"})
#define SHIP_QUEST_ASK ({"dangerous mission", "more about the dangerous \
mission", "about mission", "about the mission", "about the dangerous mission", \
"mission"})
#define REWARD_ASK ({"reward"})

private int last_help, guards_sent = 0, special_counter = 4;

public void
create_earthsea_monster()
{
    set_name("gorn");
    set_living_name("_captain_gp_");
    set_adj(({"stern", "grey-haired"}));
    add_name("captain");
    add_name("skahrn");
    add_name("gorn skahrn");
    set_height("very tall");
    set_width("lean");
    set_title("Skahrn of Gont, Hero of the Battle of Torheven");
    set_long("This is the general who serves the Lord of Gont. " +
        "He has saved Gont from occupation by the Kargad Empire " +
        "on more than one occassion. " +
        "Normally, he would be attending land that " +
        "his lord bequeathed to him. But the Lord of Gont asked this " +
        "war hero to aid in the safeguarding of Gont Port " +
        "due to the Karg threat. Many wonder why such an upright " +
        "person would serve an unscrupulous lord, the Lord of " +
        "Gont, who is a well known pirate. He appears very stern.\n");
    set_race_name("human");
    set_stats(({ 190, 210, 190, 115, 120, 170 }));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 95);
    add_chat("If you have no news, then don't waste my time!");
    add_chat("We will eliminate the troublemakers in this town.");
    add_chat("There are rumours of Kargs landing on Gont.");
    add_chat("An invasion from the Kargad Empire seems inevitable.");
    add_chat("East Port was razed by the Kargs.");
    add_act("emote looks very stern.");
    add_act("emote appears worried."); 
    add_chat("We need to strike before the Kargs are ready.");
    add_cchat("You must be working for the Kargs.");
    add_cchat("I will make sure you do not survive this ordeal.");
    (MONEY_MAKE_GC(random(5)))->move(this_object());
    add_equipment(({BL_AXE, FEET, HELMET, CAPE, PLATEMAIL}));
    add_ask(TASK_ASK, VBFC_ME("respond_task_ask"));
    add_ask(KARG_ASK, VBFC_ME("respond_karg_ask"));
    add_ask(SHIP_QUEST_ASK, VBFC("respond_ship_quest_ask"));
    add_ask(REWARD_ASK, VBFC("respond_reward_ask"));
    set_default_answer(QCTNAME(this_object()) + " says: That is not " +
        "of my concern.\n");
    log_my_kills("/d/Earthsea/log/npc_logs/gorn_kill.log");
    log_my_deaths("/d/Earthsea/log/npc_logs/gorn_death.log");
}

/* ***************** Responses ********************* */
public string
respond_reward_ask()
{
    string hero_or_heroine;
    object tp = this_player();

    if(tp->query_gender() == G_FEMALE)
    {
        hero_or_heroine = "heroine";
    } else {
        hero_or_heroine = "hero";
    }

    if(tp->query_prop(PLAYER_I_BURNED_KARG_SHIPS) &&
        tp->query_prop(PLAYER_I_GOT_SHIP_QUEST) && 
        !QH_QUERY_QUEST_COMPLETED(tp, "karg_ship_quest"))
    {
        command("say Good job!");
        command("shake " + tp->query_real_name());
        tp->remove_prop(PLAYER_I_GOT_SHIP_QUEST);
        QH_QUEST_COMPLETED(tp, "karg_standard_adv");
        command("say The people of Gont shall hail you as a " 
            + hero_or_heroine + ".\n");
        command("emote salutes " + QCTNAME(tp) + " in a " +
            "manner reserved only for saluting heroes and heroines.\n");
        tp->catch_tell("You feel much more experienced!\n");
    } else {
        command("say Have you done anything for me? I don't think so.");
    }
  
    return "";
}

public string
respond_ship_quest_ask()
{
    command("say I need someone to destroy the Karg transport ships.");
    command("say Sneak onto the ships and set them on fire.\n");
    command("say It's a long shot, but it would be a blow that the " +
        "Kargs will not recover from.\n");
    this_player()->add_prop(PLAYER_I_GOT_SHIP_QUEST, 1);
    return "";
}

public string 
respond_karg_ask()
{
    command("say The Kargard Empire has decided that they need more slaves. " +
        "So, hordes of Karg warriors have been sent on ships to conquer " +
        "islands neighboring the Kargard Empire.");
    command("sigh");
    command("say It seems that the Kargs have their eyes set on Gont now.");
    return "";
}

public string
respond_task_ask()
{
    object tp = this_player();

    if(tp->query_prop(PLAYER_I_GOT_STANDARD_ADV))
    {
        command("say Have you found the Kargs yet? If so, give the " +
            "evidence to me.\n");
        return "";
    }

    if(tp->query_prop(PLAYER_I_GOT_SHIP_QUEST))
    {
        command("say Has the Karg threat been eliminated? If you think " +
            "this task is too tough for you, perhaps I should " +
            "find another person.");
        command("eyebrow");
        return "";
    }

    if(!QH_QUERY_QUEST_COMPLETED(tp, "karg_standard_adv"))
    {
        command("say As you might know, the Kargard Empire has decided to " +
            "invade Gont. I have been able to keep them at bay " +
            "and force them to hide in the forest for now.");
        command("sigh");
        command("say However, there are rumours that Karg reinforcements " +
            "are landing on a beach somewhere near here.");
        command("say The Karg captain will surely launch an all out " +
            "assault once his reinforcements join him. I need to know " +
            "whether the reinforcements are really coming before " +
            "diverting some forces to eliminate them.");
        command("say Bring me evidence of the existence of the " +
            "Karg reinforcements and I will reward you.\n");
        tp->add_prop(PLAYER_I_GOT_STANDARD_ADV, 1);
        return "";
    }

    if((!QH_QUERY_QUEST_COMPLETED(tp, "karg_ship_quest")))
    {
        command("say It seems that the Kargs have not left their " +
            "ships.");
        command("hmm");
        command("say I have no forces to spare right now. But I have an " +
            "idea. It is EXTREMELY dangerous. If you think you're " +
            "up to the task, ask me more about the dangerous mission");
        return "";
    }

    command("say You've helped me before. Thank you!");

    return "";
}

public void
return_stuff(object ob, object player)
{
    command("drop " + ob->query_name());
    command("say I have no need for this.");
}

public void
reward_standard_adv(object standard, object player)
{
    int request_alarm; 

    player->remove_prop(PLAYER_I_GOT_STANDARD_ADV);
    standard->remove_object();

    if(!QH_QUERY_QUEST_COMPLETED(player, "karg_standard_adv"))
    {
        command("thank "+ lower_case(player->query_name()));
        QH_QUEST_COMPLETED(player, "karg_standard_adv");
        player->catch_msg("You feel a little more experienced!\n");
    }
}

public void
enter_inv(object ob, object from)
{
    if(interactive(from) && (ob->query_karg_standard()) &&
        from->query_prop(PLAYER_I_GOT_STANDARD_ADV))
    {
        set_alarm(2.0, 0.0, &reward_standard_adv(ob, from));
        return;
    }

    if(interactive(from))
        set_alarm(2.0, 0.0, &return_stuff(ob, from));

    return ::enter_inv(ob, from);;
}

/*********************COMBAT SPECIALS*********************/
//Ram special
public void
ram(object enemy)
{
    string damage_lvl;
    mixed damage;
    object to = this_object();

    damage = enemy->hit_me((600 + random(600) - enemy->query_stat(SS_CON)),
        W_BLUDGEON, to, -1);

    if(damage[0] > 75) {
        damage_lvl = "beckoned by the Grim Reaper.";
    } else if(damage[0] > 60) {
        damage_lvl = "severely pummeled from the impact.";
    } else if(damage[0] > 45) {
        damage_lvl = "seriously injured from the impact.";
    } else if(damage[0] > 30) {
        damage_lvl = "quite hurt from the impact.";
    } else if(damage[0] > 15) {
        damage_lvl = "somewhat rattled from the impact.";
    } else if(damage[0] > 0) {
        damage_lvl = "a little shakened from the impact.";
    } else {
        damage_lvl = "not hurt at all from the impact.";
    }

    enemy->catch_msg(QCTNAME(to) + " runs straight at you " +
         "and rams you hard.\nYou are " + damage_lvl + "\n");

    tell_watcher(QCTNAME(to) + " runs straight at " + 
         QCTNAME(enemy) + " and rams "
         + enemy->query_objective() + " hard.\n" +
         QCTNAME(enemy) + " seems to be " + damage_lvl + "\n", enemy);

    if(enemy->query_hp() <= 0)
    {
        enemy->catch_tell("You are flattened and" + 
            " collapse to the ground.\n");
        tell_watcher("\n" + QCTNAME(enemy) + " yells in agony" +
            " as " + enemy->query_pronoun() + " is" +
            " smashed and collapses to the ground.\n", 
            enemy);
        enemy->do_die(this_object());
    }
}

//The guards rush in and help.
public void
help_gorn(object me, object enemy)
{
    object *guards = allocate(5),
        room = environment(me);
    int i;

    setuid();
    seteuid(getuid(me));

    for(i = 0; i < 5; i++)
    {
        guards[i] = clone_object(GUARD);
        team_join(guards[i]);
        guards[i]->move(room);
        guards[i]->command("emote rushes in.\n");
    }

    guards[0]->command("gasp");
    guards[1]->command("shout Help the general!");

    for(i = 0; i < 5; i++)
    {
        guards[i]->command("kill " + enemy->query_real_name());
        guards[i]->command("shout Die scum! You will not escape me.");
    }
}

public int
special_attack(object enemy)
{
    object to = this_object();

    special_counter++;

    //If Gorn has more than 1000 hp, no need for help.
    if(!sizeof(query_team_others()) && query_hp() < 1000 &&
        guards_sent < MAX_GUARDS_HELP &&
        (!last_help || (time() - last_help > 120)))
    {
        command("shout Guards! Come help me out! " +
            "Someone's trying to kill me. " +
            "These bastards are really tough.");
            set_alarm(5.0, 0.0, &help_gorn(to, enemy));
            guards_sent++;
    }

    //The ramming special.
    if(special_counter > SPA_DELAY + random(2))
    {
        ram(enemy);
        special_counter = 0;
        return 1;
    }

    return 0;
}

public void
do_die(object killer)
{
    command("say I have failed the people of Gont, forgive me.");
    command("sigh");
    command("shout Today is a good day to die!");
    ::do_die(killer);
}

//Make sure the guards attack who Gorn is attack *grin*
public void
attack_object(object victim)
{
    object *others = query_team_others();

    if(sizeof(others))
    {
            others[0]->command("say Die scum! You will not escape me.");
            others->command("kill " + victim->query_real_name());
    }

    ::attack_object(victim);
}
