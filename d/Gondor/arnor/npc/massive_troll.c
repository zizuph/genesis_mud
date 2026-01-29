/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 * Palmer 9 June 2006 - Removed see invisibility ability. Hes just a troll.
 * Zizuph   Feb 2022  - removed magic resistance, which is now provided through AC.
 *
 */

inherit "/std/monster";
inherit "/lib/unique";
inherit "/d/Genesis/lib/intro";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <language.h>

#include "/d/Gondor/private/gondor_admin.h"
#include "/d/Gondor/defs.h"
#include "arnor_defs.h"

void kill_victim(object victim);

object arm;
int aggressive_on();

void
create_monster()
{
    int st = 340 + random(25);
    if (!IS_CLONE)
        return;
    set_name("barash-gund");
    set_living_name("barash-gund");
    set_title("the Invincible Stonecrusher of Angmar");
    set_race_name("troll"); 
    set_adj(({"massive", "mountain"}));
    set_long("This is a massive mountain troll that has " +
        "come down from the Misty Mountains to murder and " +
        "pillage. His fists are like enormous shovels that he uses " +
        "to escavate the rock underground.\nHis forehead " +
        "is tattooed with the crest of Angmar.\n");
    set_gender(G_MALE);
    set_aggressive(&aggressive_on());
    default_config_npc(175);
    set_base_stat(SS_CON, st + 120);
    set_base_stat(SS_STR, st + 50);
    set_base_stat(SS_DEX, st + 10);
    set_base_stat(SS_WIS, 175);
    set_base_stat(SS_INT, 200);
    set_base_stat(SS_DIS, st);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_hp(query_max_hp());
    set_act_time(120);
    add_prop(LIVE_I_QUICKNESS, 100);
    set_cchat_time(120);
    set_chat_time(120);
    add_act("roar");
    add_act("shout Smash 'em! Squash 'em!");
    add_cact("roar");
    add_cact("shout Smash 'em! Squash 'em!");
    add_cact("emote drools slime on the ground.");
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_PARRY, 95);
    set_skill(SS_BLIND_COMBAT, 95);
    set_skill(SS_UNARM_COMBAT, 95);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 95);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(CONT_I_WEIGHT, 1467000);
    add_prop(CONT_I_VOLUME, 378000);
    add_prop(CONT_I_HEIGHT, 350);
    set_alignment(-600);
    set_exp_factor(150);
    add_prop("_live_m_no_drain", 
        "The tough hide of the massive mountain troll wards " +
        "off your attack!\n");

    TELL_ADMIN("Barash-gund cloned at " + ctime(time()));


}

void
arm_me()
{
    object wep, clout, mail;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    FIX_EUID
    wep = clone_unique((ARNOR_WEP + "skull_club.c"), MAX_UNIQUE_ITEMS, 
        ({ (ARNOR_WEP + "common_axe.c"), 
           (ARNOR_WEP + "common_club.c"), }), 1, 25 );
    wep->move(TO);
    command("wield all");

    clout = clone_object(ARNOR_ARM + "breechclout");
    clout->move(TO);

    arm = clone_unique((ARNOR_ARM + "targa"), 7, 
        ({ (ARNOR_ARM + "iron_shield"), }), 1, 25 );
    arm->move(TO);

    mail = clone_unique((ARNOR_ARM + "mithril_chainmail"), 7,
        ({ (ARNOR_ARM + "ring_mail") }), 1, 25);
    mail->move(TO);
    command("wear all");
    return;
}

/* Solamnian prestige */
int
query_knight_prestige() 
{
    return (500);
}


int
special_attack(object victim)
{
    int hurt, whimp;
    int rate;
    int RAN = 3;
    int troll_str = query_stat(SS_STR);
    int troll_dex = query_stat(SS_DEX);
    object *others = victim->query_team_others();
    object next_victim;
    int i;
    string race, gender;
    string * hitspots = ({"face", "head", "throat", "nose",
                          "chest", "groin", "shoulder", "chin",
                          "ear", "eye", "stomach", "kneecap",
                          "shins", });
    string hitspot = hitspots[random(sizeof(hitspots))];
    string * adjs = ({"pipsqueak", "coward", "girly", "dunghill",
                     "swarmy", "rat-spawn", "jelly-livered",
                     "wimpy", "weakling", });
    string adj = adjs[random(sizeof(adjs))];

    // one round in 5

    if (random(100) < 70)
        return 0;

    rate = RAN;
    hurt = random(troll_str + troll_dex)/rate + 50 + random(150);
    if (hurt >= victim->query_hp())
        hurt = (victim->query_hp())/rate + random(50) ;

    // Shield attack--make harder if he is wearing targa
    if (random(10) < 7)
    {
        if (!arm->id("shield"))
            return 0;
        //extra hard if he wears the targa
        if (arm->id("targa"))
            hurt =  hurt + random(100);

        // occasionally strafe the entire team if there is a team
        if (sizeof(others))
        {
            others += ({ victim });
            for (i = 0; i < sizeof(others); i++)
            {
               // no crits with special and hit enemies only
                if (present(others[i], environment(this_object())))
                {
                    if (hurt >= others[i]->query_hp())
                        hurt = (others[i]->query_hp())/rate + random(75);
                    others[i]->heal_hp(-hurt);
                    others[i]->catch_msg("You are caught off-guard as " +
                        query_the_name(others[i]) + " savagely strafes " +
                        "you, slamming you hard in the " + hitspot + 
                        " with his " + arm->short() + ".\n");
                    whimp = ftoi(itof(others[i]->query_hp()) / 
                        itof(others[i]->query_max_hp()) * 100.0);
                    if (whimp < others[i]->query_whimpy())
                    {
                        others[i]->add_panic(2*hurt);
                        if (present(others[i], environment(this_object())))
                            others[i]->run_away();
                        race = others[i]->query_race_name();
                        if (!stringp(race))
                            race = "rat";
                        command("shout You little " + adj + " " + race + "! " +
                            "Come back here so I can smash you!");
                    }
                    
                    others[i]->attack_object(this_object());
                    this_object()->attack_object(others[i]);
                    kill_victim(others[i]);
                    hurt = random(troll_str + troll_dex)/rate;
                }
            }
            command("roar");
            return 1;
        } // if sizeof others
        // else if player is fighting solo
        victim->heal_hp(-hurt);
        victim->catch_tell("You are caught off-guard as the " +
            "massive mountain troll savagely slams you hard " +
            "in the " + hitspot + " with his " + arm->short() + ".\n");
        kill_victim(victim);
        return 1;
    }

    // no crits with special
    if (hurt > victim->query_hp())
        hurt = (victim->query_hp())/rate + random(100);

    switch (hurt)
    {
    case 0..30:
        command("emote smashes his fist into the ground like an " +
            "earthquake! The shock from it throws you off balance!");
        victim->add_attack_delay(5 + random(5));
        victim->heal_hp(-hurt*3);
        break;
    case 31..150:
        victim->catch_tell(query_The_name(victim) + " clips your head with " +
            "his shovel-like fist! You feel dizzy!\n");
        tell_room(environment(), QCTNAME(this_object()) + " clips " +
            "the head of " +
            QTNAME(victim) + " with his shovel-like fist!\n", victim);
        victim->heal_hp(-hurt);
        victim->add_attack_delay(10 + random(5));
        break;
    case 151..225:
        victim->catch_tell(query_The_name(victim) + " smashes your head with " +
            "his shovel-like fist! You shake your head and hear something " +
            "rattle!\n");
        tell_room(environment(), QCTNAME(this_object()) + " smashes " +
            QTNAME(victim) + " with his shovel-like fist! " +
            QCTNAME(victim) + " shakes " + victim->query_possessive() +
            " head as if stunned!\n", victim);
        victim->heal_hp(-hurt);
        break;
    default:
        victim->catch_tell(query_The_name(victim) + " pulverizes you with " +
            "his shovel-like fist! You fall back, head lolling!\n");
        tell_room(environment(), QCTNAME(this_object()) + " pulverizes " +
            QTNAME(victim) + " with his shovel-like fist! " +
            QCTNAME(victim) + " falls back, head lolling!\n", victim);
        victim->heal_hp(-hurt);
        break;
    }
    kill_victim(victim);
    //occasionally switch randomly to another teammate
    // to keep the team off balance
    if (random(10) > (RAN))
    {
        others += ({ victim });
        next_victim = others[random(sizeof(others))];
        if (present(next_victim, environment(this_object())))
        {
             command("kill " + OB_NAME(next_victim));
             command("grin " + OB_NAME(next_victim));
        }
    }
    return 1;
}

void
do_die(object killer)
{
// log it
    log_file("troll_killers", capitalize(killer->query_real_name()) +
        " killed the massive mountain troll on " + ctime(time())+ ".\n");
    command("emote falls to the ground with a tremendous thud!");
    ::do_die(killer);
}

int
aggressive_on()
{
    object tp = this_player();

    if (member_array(tp, query_enemy(-1)) != -1)
        return 1;
    return 0;
}

/* 
 * Function name:   introduce 
 * Description:     This function makes the npc do an introduction to a 
 *                  player that has not been introed to it earlier. The 
 *                  function may be redefined to create variety. 
 * Arguments:       object who - the living that introduced to me 
 * 
 */
public void 
introduce(object who)
{
    command("introduce myself to " + OB_NAME(who)); 
} 

/* 
 * Function name: greet
 * Description:   This function makes the npc do a greeting to people it
 *                already know and to fellow npc's. It is possible to
 *                redefine, note however that it should never contain an
 *                'introduce myself' command.
 * Arguments:     object who - the living that introduced to me
 *
 */                   
public void
greet(object who)
{
    object *wep = this_object()->query_weapon(-1);

      // He won't greet an enemy! 
    command("shout Out, you little dunghill rat!"); 
    if (sizeof(wep))
    {
        who->catch_tell("The massive mountain troll shakes his " + 
            LANG_SHORT(wep[0]) +
            " in your face, threatening to smash you into pulp!\n");
    } 
} 


void
attacked_by(object ob)
{
    object *arr;

    ::attacked_by(ob);
    TELL_ADMIN("[Barash-gund attacked by " + ob->query_cap_name() + 
        "("+ob->query_average_stat()+") at " + ctime(time()) + "]");
}

void
kill_victim(object victim)
{
    if (victim->query_hp() < 0)
    {
        victim->do_die(this_object());
        //log death
        log_file("troll_deaths", capitalize(victim->query_real_name()) +
            " was killed by the massive mountain troll on " + 
            ctime(time())+ ".\n");
    }
    return;
}

