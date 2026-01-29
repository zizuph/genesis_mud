/*
    castle_knight.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
    Modified by Zignur 2017-09-13 
 
    Cotillion - 2019-04-03
    - Fixed to use global clone_unique
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/special";
inherit "/d/Kalad/lib/assist";
inherit "/lib/unique";

#include "default.h"
#include <money.h>

void
create_kalad_monster()
{
    set_name("knight");
    set_adj("noble");
    set_race_name("human");
    set_short("noble knight of the High-Lord");
    set_long("This is one of the noble knights of the High-Lord. Only "+
        "prestigious nobles of high birth may become a knight of the "+
        "High-Lord's crown. He looks like he has been trained well, and "+
        "is prepared for anything.\n");

    set_alignment(500);
    set_knight_prestige(-300);
    add_speak("Don't cause trouble.\n");
    /* New stats changed by Zignur 2017-09-13 */
    set_stats(({125,130,125,120,120,120}));
    
    /* New skills changed by Zignur 2017-09-13 */
    set_skill(SS_WEP_CLUB,80);
    set_skill(SS_DEFENSE,80);
    set_skill(SS_AWARENESS,60);
    set_skill(SS_PARRY,80);
    set_skill(SS_BLIND_COMBAT,50);

    set_act_time(5);
    add_act("scratch chin");
    add_act("say I am one of the best knights the Lord has.");
    add_act("say None mess with the noble knights.");
    add_act("say Where is my squire?");
    add_act("emote looks down upon you.");
    set_cact_time(3);
    add_cact("swing mace");
    add_cact("say I shall protect my High-Lord!");
    add_cact("shout Fool! You will die now!");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    // We assist Kabal citizens
    add_friend(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    equip(({
        clone_unique(NOBLE + "wep/shimmering_mace", 7, NOBLE + "wep/spiked_mace"), 
        NOBLE + "arm/as_helm",
        NOBLE + "arm/as_breastplate",
        NOBLE + "arm/as_bracers",
        NOBLE + "arm/as_greaves",
        NOBLE + "arm/sl_boots",
        NOBLE + "arm/os_shield",
        }));
        
    command("wield all");         
    command("wear all");

    MONEY_MAKE_SC(random(35))->move(TO);

    // Configure our special attack with random hitlocation
    set_default_special(16, W_BLUDGEON, 90, 300, -1);
    
    /* Added by Zignur 2017-09-13 */
    set_exp_factor(130);
}

// Watch for friends when we enter a new room
void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    watch_friends();
}

void
attack_message(object ob, int hitloc_id)
{
    switch (hitloc_id)
    {
       case A_HEAD:
        switch (random(2))
        {
           case 0:
            ob->catch_msg(QCTNAME(TO) + " backhands you across the " +
                "face with his mailed fist!\n");
            tell_watcher(QCTNAME(TO) + " backhands " + QTNAME(ob) +
                " across the face with his mailed fist!\n", ob);
            break;

           case 1:
            ob->catch_msg(QCTNAME(TO) + " deflects your blow, then " +
                "smashes your face with his elbow!\n");
            tell_watcher(QCTNAME(TO) + " deflects " + QTNAME(ob) + "'s " +
                "blow, then smashes " + HIS(ob) + " face with his elbow!\n", ob);
        }
        break;
        
       case A_BODY:
        ob->catch_msg(QCTNAME(TO) + " slams his knee into your " +
            "stomach!\n");
        tell_watcher(QCTNAME(TO) + " slams his knee into " +
            QTNAME(ob) + "'s stomach!\n", ob);
        break;
    }
}

// Special has random weapon penetration
int
query_special_wcpen()
{
    return 300 + random(300);
}

// Aim for head or body randomly, body with 50% chance
int
query_special_hitloc_id()
{
   return ({A_BODY, A_HEAD})[random(2)];
}

// Give messages
void
special_did_hit(object enemy, string hdesc, int hitloc_id, int phurt,
   int damage_type, int damage)
{
    string msg, other_msg;

    attack_message(enemy, hitloc_id);
    switch (phurt)
    {
       case -100..20:
        msg = "You are merely scratched.\n";
        other_msg = QCTNAME(enemy) + " is merely scratched.\n";
        break;

       case 21..50:
        msg = "You are somewhat bruised by the blow.\n";
        other_msg = QCTNAME(enemy) + " is somewhat bruised by the blow.\n";
        break;

       case 51..70:
        msg = "You flinch in great pain as the blow hits you.\n";
        other_msg = QCTNAME(enemy) + " flinches in great pain.\n";
        break;

       case 71..90:
        msg = "You scream out loud in great pain.\n";
        other_msg = QCTNAME(enemy) + " screams out loud in great pain.\n";
        break;

       default:
        msg = "You scream in agony as the blow smashes you!\n";
        other_msg = QCTNAME(enemy) + " screams in agony as the blow " +
            "smashes " + HIM(enemy) + ".\n";
        break;
    }

    enemy->catch_msg(msg);
    tell_room(ENV(TO), other_msg,enemy);
}

