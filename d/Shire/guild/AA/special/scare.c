/*
 * special/smash.c
 *
 * Port of the AA Smash to the shared combat library
 *
 * Created by Novo, May 2008
 *
 * Modified 10/4/2009 Balance added set_tohit(85) as it was missing. 
 * Modified 06/8/2019 Arman (AoB) revised caid from 70/35 to 75/40
 *                    and increased set_tohit to 95.
 */

#pragma strict_types

#include "../guild.h"

inherit AA_SPECIAL;

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#include "/std/combat/combat.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define VALIDATE        "validate"

// Prototypes
public void             config_ability();
public void             special_did_hit(int aid, string hdesc, int hid, 
                                        int phurt, object enemy, int dt, 
                                        int phit, int dam,object * items);
static int              check_valid_action(object player, mixed * targets, 
                                           string arg, int execute);
static mixed *          check_required_items(object actor, mixed * targets,
                                             string arg, int pretest);

public object *         target_can_scare(object actor, string arg);


/*
 * Function name: config_ability
 * Description  : Main fuction that configures what the special
 *                should look like. Set basic things like combat
 *                aid and the skills to be used for calculating
 *                damage and of course, the name.
 * Arguments    : none
 * Returns      : nothing
 */
public void 
config_ability()
{
    setuid();
    seteuid(getuid());
    
    ::config_ability();
    set_combat_aid(75);
    
    // 10/2/2008 - Replaced Guild Stat with Dis because it takes
    //             greater discipline to intimidate someone.   
    set_stats(({ SKILL_AVG, TS_STR, TS_DIS, SKILL_END }) );
    set_skills(({ SS_SMASH }) );
    //Bypass armour - can be used only one per fight.
    set_dt(MAGIC_DT);
    set_ability_name("scare");
    set_ability_target(target_can_scare);
    set_ability_stationary(1);
    
    // Can scare once every 5 seconds
    set_ability_prep_time(5);
    set_ability_cooldown_time(0);
    set_ability_attack_during_prep(0);

    // 10/4/2009 - Added set_tohit(85) to match guild docs, Petros
    // 06/8/2019 - Revised tohit to 95
    set_tohit(95);
            
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
    
    // Doesnt make sense for this ability to be hastened by dual wield.
    set_ability_dual_wield(0);
}

public int
query_guild_stat_type(object player)
{
    if (IS_LAYMAN(player))
    {
        return SS_LAYMAN;
    }
    else
    {
        return SS_OCCUP;
    }
}

/*
 * Function name: special_did_hit
 * Description  : Mask this function to process when the special
 *                scores. Descriptions seen by everyone are set
 *                here.
 * Arguments    : aid   - attack id
 *                hdesc - hit description
 *                hid   - 
 *                phurt - extent of damage
 *                enemy - person being hit by special
 *                dt    - damage type
 *                phit  - 
 *                dam   - damage amount
 * Returns      : nothing
 */
public void special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt,int phit, 
                int dam,mixed * items)
{


    string wep="arms";
    string * text;

    wep=TP->query_combat_object()->cb_attack_desc(items[0]);
    
    TP->catch_msg("You scream at "+QTNAME(enemy)+
        ", waving your "+wep+" dangerously.\n");
    enemy->catch_msg(QCTNAME(TP)+" screams at you"+
        ", waving "+HIS(TP)+" "+wep+" dangerously.\n");
    TP->tell_watcher(QCTNAME(TP)+" screams at "+QTNAME(enemy)+
        ", waving "+HIS(TP)+" "+wep+" dangerously.\n", enemy);

    if (enemy->query_hp() <= 0)
    {
        text = ({" dies in terror of ",
            " die in terror of  ",
            "!\n" });
    }
    else
    { 
        switch (phurt)
        {
        case -2..0:
            text = ({" laughs at ",
                " laugh at ",
                " without any fear.\n" });
            break;
        case 1..3:
            text = ({" steps back, but otherwise ",
                " step back, but otherwise ",
                " didn't make big impression.\n" });
            break;
        case 4..8:
            text = ({" jumps in fear of ",
                " jump in fear of ",
                ".\n" });
            break;
        case 9..16:
            text = ({" loses "+HIS(enemy)+" breath, looking at ",
                " lose your breath, looking at ",
                " with fear.\n" });
        case 17..32:
            text = ({" staggers in shock, gazing in fear at ",
                " stagger in shock, gazing in fear at ",
                ".\n" });
            break;
        default:
            text = ({" collapses in complete terror of ",
                " collapse in complete terror of ",
                ".\n" });
        }
    }
    TP->catch_msg(QCTNAME(enemy)+text[0]+"you"+text[2]);
    enemy->catch_msg("You"+text[1]+QTNAME(TP)+text[2]);
    TP->tell_watcher(QCTNAME(enemy)+text[0]+QTNAME(TP)+text[2], enemy);


    if (enemy->query_hp() <= 0) enemy->do_die(TP);
    enemy->add_prop("live_i_already_scared", time());
    return 0;

}


/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The player
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object player, mixed * targets, string arg, int execute)
{
    object enemy;

    if (!::check_valid_action(player,targets,arg,execute))
    {
        return 0;
    }
            
    /* 
     * If the player has no skill in shielding and is not practicing, 
     * s/he can't swarm. 
     */ 
    if (!player->query_skill(SS_SMASH)) 
    { 
        player->catch_tell("You are not skilled in scaring others!\n");
        send_debug_message(VALIDATE, 
                           capitalize(player->query_real_name()) 
                         + " is not skilled in scaring.");
        return 0; 
    }

    // If it passes everything, return success
    return 1; 
}


/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure the Calian has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required.
 */
static mixed * 
check_required_items(object actor, mixed * targets,
                     string arg, int pretest)
{
    int max_pen=0;
    int best_aid=-1;
    object cob=actor->query_combat_object();
    
    foreach (int aid : cob->query_attack_id())
    {
        mixed att_loc=cob->query_attack(aid);
        if (!att_loc)
            continue;
        if (att_loc[1][0]>max_pen)
        {
            max_pen=att_loc[1][0];
            best_aid=aid;
        }
    }
    if (best_aid>=0)
    {
        return ({ best_aid });
    }
    //This should never happen
    actor->catch_tell("You have no attacks to scare with!\n");
    return 0;
    
}


static void ability_msg(object actor,mixed * targets,string arg)
{
    actor->catch_msg("You prepare to scare your foe.\n");
}

public object *
target_can_scare(object actor, string arg)
{
    object * results=
        target_one_other_present_living_or_enemy(actor,arg);
    
    if (!sizeof(results))
    {
        return ({ });
    }
    
    foreach (object target : results)
    {
        if ((member_array(target, actor->query_enemy(-1)) != -1) ||
            (member_array(actor, target->query_enemy(-1)) != -1))
        {
            actor->catch_msg(CAP(HE(target))+" pays too much "+
                "attention to you to be scared.\n");
            return ({ });
        }
        if (target->query_prop("live_i_already_scared")+300>time())
        {
            actor->catch_msg(CAP(HE(target))+" is wary of your "+
                "scare tactics.\n");
            return ({ });
        }
    }
    return results;
}





