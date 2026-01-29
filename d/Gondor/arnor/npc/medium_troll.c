/*
 * Troll for Arnor
 * Coded and updated by Tigerlily 
 *    April, 2006 
 */
inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "arnor_defs.h"
#define ATTACKED_TROLL "_attacked_troll_"
/*
#define STUN_OB "/d/Gondor/arnor/obj/stun_ob"
#define MARK "/d/Gondor/arnor/obj/mark"
*/

int aggressive_on();
int descr(object tp);

void
create_monster()
{
    int st = 135 + random(60);
    if (!IS_CLONE)
        return;
    set_name("troll");
    add_name("mountain-troll");
    set_race_name("troll"); 
    set_adj(({"evil", "mountain"}));
    set_long("This is an evil mountain troll that has " +
        "come down from the Misty Mountains to murder and " +
        "pillage. His fists are like two huge boulders.\n");
    set_gender(G_MALE);
    default_config_npc(50);
    set_base_stat(SS_CON, st + 25);
    set_base_stat(SS_STR, st + 50);
    set_base_stat(SS_DEX, st + 10);
    set_base_stat(SS_DIS, st);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_hp(query_max_hp());
    set_act_time(120);
    set_cchat_time(120);
    set_chat_time(120);
    add_act("roar");
    set_aggressive(&aggressive_on());
    add_act("shout Smash 'em! Squash 'em!");
    add_act("shout I'll squash you into jelly, you little maggot!");
    add_cact("roar");
    add_cact("shout Smash 'em! Squash 'em!");
    set_skill(SS_WEP_CLUB, 85);
    set_skill(SS_PARRY, 60);
    set_skill(SS_BLIND_COMBAT, 65);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 65);
    set_skill(SS_AWARENESS, 25);
    add_prop(LIVE_I_SEE_DARK, 95);
    add_prop(CONT_I_WEIGHT, 1467000);
    add_prop(CONT_I_VOLUME, 378000);
    add_prop(CONT_I_HEIGHT, 350);
    set_alignment(-350 - random(100));
}

void
arm_me()
{
    object wep, arm;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    FIX_EUID

    wep = clone_object(WEP_DIR + "trollclub");
    wep->move(TO);
    command("wield club");

    arm = clone_object(ARNOR_ARM + "breechclout");
    arm->move(TO);
    command("wear all");
}

/* Solamnian prestige */
int
query_knight_prestige() 
{
    return (450);
}

int
special_attack(object victim)
{
    int hp, hurt;

    // one round in 10
    if (random(100) < 90)
        return 0;

    hp = victim->query_max_hp() - victim->query_hp();
    if (hp > 100)
        hurt = random(hp)/15;
    else
        hurt = 50;
    
    switch (hurt)
    {
    case 0..5:
        tell_room(environment(), "The evil mountain troll smashes " +
            "his enormous fist onto the " +
            "ground, making the earth shake!\n");
        break;
    case 6..35:
        victim->heal_hp(-hurt);
        victim->catch_msg("The evil mountain troll grazes your head with " +
            "his shovel-like fist! You stagger back from the blow!\n");
        tell_room(environment(), "The evil mountain troll grazes the head of " +
            QTNAME(victim) + " with his shovel-like fist!\n", victim);
        break;
    case 36..55:
        victim->heal_hp(-hurt);
        victim->catch_msg("The evil mountain troll smashes your head with " +
            "his shovel-like fist! You stagger back from the blow!\n");
        tell_room(environment(), "The evil mountain troll smashes " +
            QTNAME(victim) + " with his shovel-like fist! " +
            QCTNAME(victim) + " staggers back from the blow!\n", victim);
        break;
    default:
        victim->heal_hp(-hurt);
        victim->catch_msg("The evil mountain troll smashes you with " +
            "his shovel-like fist! You fall back, head lolling!\n");
        tell_room(environment(), "The evil mountain troll smashes " +
            QTNAME(victim) + " with his shovel-like fist! " +
            QCTNAME(victim) + " falls back, head lolling!\n", victim);
        break;
    }
    return 1;
}

int
aggressive_on()
{
    object tp = this_player();
    object stun;

    setuid(); 
    seteuid(getuid(this_object()));

    if (tp->query_prop(ATTACKED_TROLL))
    {
/*
        stun = clone_object(STUN_OB);
        stun->move(tp);
*/
        set_alarm(1.0, 0.0, &descr(tp));
        return 1;
    }
    return 0;
}

public void
attacked_by(object ob)
{
    object mark;

    setuid(); 
    seteuid(getuid(this_object()));

    ob->add_prop(ATTACKED_TROLL, 1);
/*
    if (!ob->query_prop(ATTACKED_TROLL))
    {
        mark = clone_object(MARK);
        mark->move(ob);
    }
*/
    ::attacked_by(ob);
}

int
descr(object tp)
{
    this_object()->command("emote howls with rage!");
    tp->catch_msg("The evil mountain troll lifts you like a " +
        "rag doll and smashes you to the ground! You are stunned.\n");
    tell_room(environment(), "The evil mountain troll lifts " +
        QTNAME(tp) + " like a rag doll and smashes " +
        tp->query_objective() + "to the ground!\n " +
        QCTNAME(tp) + " flops on the ground like a fish.\n", tp);
    return 1;
}
