/* /d/Faerun/mere/npcs/quest_assassin/
 * 
 *
 * Nerull 2019
 */
 
inherit "std/monster.c";
inherit "/std/combat/unarmed";   /* Get standard unarmed routines */

#include "/d/Faerun/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <options.h>
#include <filter_funs.h>
#include "defs.h"

void arm_me();

/*
* Function name: create_monster()
* Description  : Constructor. Edit this to change monster.
*/
nomask void create_monster()
{
    seteuid(getuid());

    set_race_name("human");
    set_name("_quest_assassin_");
    add_name("alfredo");
    add_name("assassin");

    add_adj("dark");
    add_adj("clad");

    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    
    set_short("dark clad male human");
    
    set_long("This individual is clad in all dark "
    +"and masked so only his brown eyes are visible. His boots "
    +"are equipped with a sharp spike. Judging "
    +"by his behaviour he seems desperate or crazed, as if "
    +"he has been hiding out from someone hunting him for "
    +"a long period of time.\n");

    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 190);

    set_stats(({ 150, 140, 160,
                 143, 120, 180 }));

    set_hitloc_unarmed(A_HEAD, 45, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 45, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 45, 10, "left arm");
    set_hitloc_unarmed(A_BODY, 45, 45, "body");
    set_hitloc_unarmed(A_LEGS, 45, 20, "legs");

    set_attack_unarmed(W_LEFT,  25, 25, W_BLUDGEON,
    80, "left fist");

    set_attack_unarmed(W_RIGHT,  25, 25, W_BLUDGEON,
    80, "right fist");
    
    set_attack_unarmed(W_FOOTR, 25, 25, W_BLUDGEON,
    0, "left foot");

    set_attack_unarmed(W_FOOTL, 25, 25, W_BLUDGEON,
    0, "right foot");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_WEP_KNIFE,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_AWARENESS,60);
    set_skill(SS_2H_COMBAT, 100);
    
    set_act_time(5);
    set_cact_time(5);
    add_act("emote looks around suspiciously.");
    add_act("emote eats some dried chicken.");
    add_act("emote sharpen his blades.");
    
    set_cchat_time(5);
    add_cchat("Die, agent of the Brotherhood!");
    add_cchat("You will regret this!");
    add_cchat("You think you can kill me? Hah!");
    add_cchat("I'm not impressed with your skills "
    +"in combat!");
    
    set_aggressive(1);
    
    arm_me();
}


mixed 
query_option(int opt) 
{
    return (opt == OPT_UNARMED_OFF); 
}


void
arm_me()
{
    object wep;

    wep = clone_object(WEP_DIR + "assassin_dagger");
    wep -> move(TO);
    
    wep = clone_object(WEP_DIR + "assassin_dagger");
    wep -> move(TO);
    
    command("wield weapons");
}


/*
* Function name: special_attack()
* Description  : The special attack vs player teams.
*/
int
special_attack(object enemy)
{
    object me = this_object();

    mixed *hitresult;
    
    string how;
    string ohow;
    string tar;

    int     n = -1;

    if (random(5))
    {
        return 0;  /* Continue with the normal attacks */
    }

    // The special.
    hitresult = enemy->hit_me(200
        + random(200), W_SLASH, me, -1);

    how = " doing neglible damage";
    ohow = " doing neglible damage";

    if (hitresult[0] >= 0)

    {
        how = " puncturing ";
        ohow = " puncturing ";
        tar = " chest";
    }

    if (hitresult[0] > 10)
    {
        how = " stabs ";
        ohow = " stabs ";
        tar = " chest";
    }

    if (hitresult[0] > 20)
    {
        how = " and pierces ";
        ohow = " and pierces ";
        tar = " body, spraying blood everywhere";
    }

    if (hitresult[0] == -1)
    {
        me->catch_msg("You kick " + QCTNAME(enemy)
            + " with your spiked boot," + how + ".\n");
            
        enemy->catch_msg(QCTNAME(me)
            + " kicks you with his spiked boot," + how + ".\n");
 
        tell_watcher(QCTNAME(me) + " kicks "+ QCTNAME(enemy) 
            + " with his spiked boot," + how + ".\n");

        return 1;
    }

    if (hitresult[0] >= 0)
    {
        me->catch_msg("You kick " + QCTNAME(enemy)
            + " with your spiked boot," +
            how + enemy->query_possessive() + tar + ".\n");
            
        enemy->catch_msg(QCTNAME(me)
            + " kicks you with his spiked boot," +
            ohow + "your" + tar + ".\n");
 
        tell_watcher(QCTNAME(me) + " kicks "+ QCTNAME(enemy) 
            + " with his spiked boot," +
            ohow + enemy->query_possessive() + tar + ".\n", enemy);
            
            

        if (enemy->query_hp() <= 0);
        enemy->do_die(me);

        return 1;
    }

    return 1; /*  Important! Should not have two attacks in a round. */
}

