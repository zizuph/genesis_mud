/*
 * /w/petros/open/ability/examples/swarm.c
 *
 * Port of the Calian Swarm to the new centralized special
 *
 * Created by Petros, May 2008
 * 
 * Modification Log:
 *   9/4/2008
 *   - Fixed runtime error in detecting rogue tankers (Petros)
 *   1/31/2009
 *   - Removed mana as a cost for swarm. Old relic from old times.
 *     melee specials should not drain mana.
 */

#pragma strict_types

#include "defs.h"

inherit DAMAGE_LIB;
inherit SPECIALS_UTILITY;
inherit CALIAN_UTILITY;

#include CALIAN_HEADER
#include COUNCIL_HEADER
#include DEBUGGER_TELL

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#include "/std/combat/combat.h"

// Debug Tags
#define QCA_MOD         "swarm_qca_mod"
#define SWARM_VALIDATE  "swarm_validate"
#define APPLY_COSTS     "swarm_apply_costs"
#define TO_HIT          "swarm_tohit"

#define SWARM_LOG       (CRPALACE_LOGS+"swarm_damage")

// Global Variables
static string *swarm_adverbs = 
        ({ "", " slightly", " stingingly", " adeptly", 
           " precisely", " keenly", " incisively", " deeply", 
           " with deadly accuracy" }); 

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
    ::config_ability();
    // Combat aid defined in calian.h
    set_combat_aid(SWARM_MAX_CAID);
    // Extra damage taken from Strength, Dexterity and Discipline
    set_stats(({ SKILL_AVG, TS_STR, TS_DEX, TS_DIS, SKILL_END }) );
    // Swarm is used in the F_PENMOD calculation for the skill portion
    set_skills(({ SS_SWARM_KNOWLEDGE }) );
    // Can swarm once every 10 seconds.
    set_ability_prep_time(4);
    set_ability_cooldown_time(6);
    set_ability_name("swarm");
    
    set_guild_stat_modifier(SS_OCCUP, 20, 100);    
}

/* 
 * Function:      do_dismember 
 * Description:   When a Calian has killed an enemy with swarm 
 *                it is usually dismembered as a result, this 
 *                function makes this gruesome end possible by 
 *                cloning and moving in all the body parts. 
 * Arguments:     object tp    - the dismemberer 
 *                object enemy - the living to dismember 
 */ 
private void 
do_dismember(object tp, object enemy) 
{ 
    object piece; 
    string enemy_race, hit_piece, *piece_names; 
    int x, *ids; 
    mixed *loc; 

    /* get hitloc strings ready for pieces */ 
    ids = ({ }); 
    ids += (enemy->query_combat_object())->query_hitloc_id(); 
    piece_names = ({ }); 
    for (x = 0; x < sizeof(ids); x++) 
    { 
        loc = (enemy->query_combat_object())->query_hitloc(ids[x]); 
        if (stringp(loc[2])) 
            piece_names += ({ loc[2] }); 
    } 

    enemy->add_prop(LIVE_I_NO_CORPSE, 1); 
    enemy_race = enemy->query_race_name(); 

    enemy->do_die(tp); 
    setuid(); 
    seteuid(getuid(this_object())); 
    for (x = 0; x < sizeof(piece_names); x++) 
    { 
        piece = clone_object(LEFTOVER_OBJECT); 
        piece->leftover_init(piece_names[x], enemy_race); 
        piece->move(environment(tp), 0); 
    } 
} 

/* 
 * Function:      process_do_die
 * Description:   Handles the special messages and the dismembering
 *                for when a Calian kills their enemy using swarm
 * Arguments:     object tp    - the calian
 *                object enemy - the enemy who is about to die
 */ 
public void
process_do_die(object tp, object enemy)
{
    string weapon_desc;
    
    weapon_desc = tp->query_calian_main_weapon()->short();
    
    /* 
     * If the monster should have a corpse and the Calian's 
     * dismember option is set to on, then .. dismember. 
     */ 
    if (!enemy->query_prop(LIVE_I_NO_CORPSE) && 
        (tp->query_skill(CALIAN_OPTIONS) & CALOPT_DISMEMBER)) 
    { 
        tell_object(tp, 
            "You hit " + enemy->query_the_name(tp) + 
            " with a thunderous blow of your " + weapon_desc + 
            ", dismembering " + enemy->query_objective() + "!\n"); 
        if (interactive(enemy)) 
            tell_object(enemy, tp->query_The_name(enemy) + 
                " hits you with a thunderous blow of " + 
                tp->query_possessive() + " " + 
                weapon_desc + ", dismembering you!\n"); 
        special_tell_watcher(tp, QCTNAME(tp) + " hits " + 
            QTNAME(enemy) + " with a thunderous blow of " + 
            tp->query_possessive() + " " + weapon_desc + 
            ", dismembering " + enemy->query_objective() + "!\n", 
            enemy, 0); 
        do_dismember(tp, enemy); 
    } 
    else // otherwise, kill without dismembering. 
    { 
        tell_object(tp, 
            "You hit " + enemy->query_the_name(tp) + 
            " with a thunderous blow of your " + 
            weapon_desc + "!\n"); 
        if (interactive(enemy)) 
            tell_object(enemy, tp->query_The_name(enemy) + 
                " hits you with a thunderous blow of " + 
                tp->query_possessive() + " " + weapon_desc + 
                "!\n"); 
        special_tell_watcher(tp, QCTNAME(tp) + " hits " + 
            QTNAME(enemy) + " with a thunderous blow of " + 
            tp->query_possessive() + " " + weapon_desc + 
            "!\n", enemy, 0); 
        enemy->do_die(tp); 
    } 
    return; 
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
 *                items - 
 *                result - result of cb_tohit
 * Returns      : nothing
 */
public varargs void 
special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt, int phit, 
                int dam, mixed * items, int result)
{
    object player, weapon;
    string current_adverb;
    mixed hit_descr;
    
    player = this_player();
    weapon = player->query_calian_main_weapon();
    current_adverb = player->query_swarm_adverb();
    
    if (result <= 0)
    {
        /* 
         * Damn, missed! 
         */ 
        tell_object(player, "You fail to sneak around " + 
            enemy->query_the_name(player) + "'s defences.\n"); 
        if (interactive(enemy)) 
        {
            tell_object(enemy, 
                player->query_The_name(enemy) + " fails to " + 
                "sneak around your defences.\n"); 
        }
        special_tell_watcher(player, QCTNAME(player) + " fails to sneak " +
            "around " + QTNAME(enemy) + "'s defences.\n", 
            enemy, 0); 
        return;
    }
    
    if (enemy->query_hp() <= 0)
    {
        // Do the death blow message
        process_do_die(player, enemy);
    }    
    else
    {
        // Show the normal swarm messages
        hit_descr = CALIAN_ATTACK_DESC->attack_desc_template_one(player,
                        enemy, dt, phurt, hdesc, 
                        weapon->short(), 
                 ({ " pounce "  + current_adverb + " and ", 
                    " pounces " + current_adverb + " and ", 
                    " pounces " + current_adverb + " and " }), 
                 swarm_adverbs, 1); 
    
        tell_object(player, hit_descr[0]); 
    
        if (interactive(enemy)) 
        {
            tell_object(enemy, hit_descr[1]); 
        }
        
        special_tell_watcher(player, hit_descr[2], enemy, 0);
    }
}

/*
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Arguments    : player - player executing special
 * Returns      : number between 1 and 100
 */
public int 
query_combat_aid_modifier()
{
    int modifier, weapon_modifier;
    object enemy_target, enemy, player, weapon;
    object * team;
    string error_message;
    
    player = this_player();

    modifier = 100;

    if (player->query_prop(CALIAN_MOVE_BEHIND_TARGET_TIME) + 15 > time())
    {
        // If the player has recently (last 15 seconds) been someone that
        // another Calian has moved behind, their combat aid is reduced
        modifier = ftoi((itof(SWARM_MB_TARGET_CAID) / itof(SWARM_MAX_CAID)) 
                         * 100.0);
    }
    else if (!player->query_attack()->query_attack()->has_calian_shadow())
    {
        // If the tanker is not a Calian, we use the non-Calian combat
        // aid number.
        modifier = ftoi((itof(SWARM_NONCALIAN_CAID) / itof(SWARM_MAX_CAID)) 
                         * 100.0);
    }
    
    // Swarm combat aid is modified by weapon skill
    weapon = player->query_calian_main_weapon();
    weapon_modifier = 30; // if unskilled, caid is 30%
    switch (weapon->query_wt())
    {
    case W_SWORD:
        weapon_modifier = player->query_skill(SS_WEP_SWORD);
        break;
        
    case W_POLEARM:
        weapon_modifier = player->query_skill(SS_WEP_POLEARM);
        break;

    case W_AXE:
        weapon_modifier = player->query_skill(SS_WEP_AXE);
        break;

    case W_KNIFE:
        weapon_modifier = player->query_skill(SS_WEP_KNIFE);
        break;

    case W_CLUB:
        weapon_modifier = player->query_skill(SS_WEP_CLUB);
        break;
    }
    modifier = (modifier * weapon_modifier) / 100;
    
    team = player->query_team_others() + ({ player });
    enemy = player->query_attack();
    enemy_target = enemy->query_attack();
    if (objectp(enemy_target)
        && !IN_ARRAY(enemy_target, team))
    {
        /* 
         * Rogue tanker penalty 
         */
        error_message = "You find it hard to coordinate your swarm "
                      + "attack with " 
                      + QTNAME(enemy_target) + ".\n";
        player->catch_msg(error_message);
        send_debug_message(QCA_MOD, error_message);                      
        modifier = modifier / 3;
    }
    
    send_debug_message(QCA_MOD, "combat aid modifier for this swarm is "
                     + modifier);    
    return modifier;
}


/*
 * Function name: query_tohit
 * Description  : Calculates the tohit for the player. Based on
 *                swarm knowledge or wisdom
 * Arguments    : player - player to check
 * Returns      : input to cb_tohit function
 */
public int 
query_tohit()
{
    object weapon, player;
    int tohit;
        
    player = this_player();
    weapon = player->query_calian_main_weapon();
    if (!weapon)
    {
        return 0;
    }
    
    tohit = min(max((player->query_skill(SS_SWARM_KNOWLEDGE) / 2), 
                     player->query_stat(SS_WIS) / 2), 50) 
          + ((25 * weapon->query_hit()) / 13);
    send_debug_message(TO_HIT, capitalize(player->query_real_name())
                     + " has a tohit value of " + tohit,
                       SWARM_LOG);          
    return tohit;
}

/*
 * Function name: query_dt
 * Description  : Checks the weapons and returns the weapon type
 * Arguments    : items - array of required items. Should only be one
 *                        weapon in the array
 * Returns      : the damage type
 */
public int 
query_dt(object * items)
{
    if (!sizeof(items))
    {
        // Return the default damage type
        return ::query_dt(items);
    }

    // Otherwise, just return the damage type of the wielded weapon    
    return items[0]->query_dt();
}

/*
 * Function name: validate_swarm_requirements
 * Description  : Function to check all the prerequisites of swarm.
 *                These checks are used in both check_valid_action
 *                as well as force fail. (before start, and before
 *                execute)
 * Arguments    : player - person executing the special
 * Returns      : 0/1 - invalid/valid conditions
 */
public int
validate_swarm_requirements(object player)
{
    object * team;
    
    /* 
     * Player may have been banned from swarming / mauling by 
     * the Calian Council. 
     */ 
    seteuid(getuid()); 
    if (COUNCIL_CODE->is_swarm_banned(player)) 
    { 
        player->catch_tell("The Calian Council has banned you from " 
                         + "swarming.\n"); 
        send_debug_message(SWARM_VALIDATE, 
                           capitalize(player->query_real_name()) 
                         + " not allowed to swarm.");
        return 0; 
    }    

    if (!player->query_calian_main_weapon())
    {
        // The calian is not wielding a weapon.
        tell_object(player, 
            "You need to be wielding a weapon in order to swarm!\n"); 
        send_debug_message(SWARM_VALIDATE, 
                           capitalize(player->query_real_name()) 
                         + " does not have a weapon wielded.");
        return 0;        
    }
    
    /* 
     * If not teamed, can't swarm. 
     */ 
    if (!sizeof(team = player->query_team_others())) 
    { 
        player->catch_tell("You need to be on a team to swarm!\n");
        send_debug_message(SWARM_VALIDATE, 
                           capitalize(player->query_real_name()) 
                         + " is not on a team.");
        return 0; 
    } 

    /* 
     * If no team members present, can't swarm. 
     */ 
    if (!sizeof(team = FILTER_PRESENT_LIVE(team))) 
    { 
        player->catch_tell("You can't swarm because none of your fellow "
                         + "team members are present!\n"); 
        send_debug_message(SWARM_VALIDATE, 
                           capitalize(player->query_real_name()) 
                         + " has no team members present.");
        return 0; 
    } 

    /* 
     * If no team members are fighting, can't swarm. 
     */ 
    if (!sizeof(filter(map(team, &->query_attack()), objectp))) 
    { 
        player->catch_tell("You can't swarm because none of your present "
                         + "team members are fighting!\n"); 
        send_debug_message(SWARM_VALIDATE, 
                           capitalize(player->query_real_name()) 
                         + " has no teammates fighting.");
        return 0; 
    } 

    return 1;
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
    object * enemies;
    
    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }
    
    if (!validate_swarm_requirements(player))
    {
        return 0;
    }
    
    /* 
     * If the player has no skill in swarming and is not practicing, 
     * s/he can't swarm. 
     */ 
    if (!player->query_skill(SS_SWARM_KNOWLEDGE)) 
    { 
        player->catch_tell("You are not skilled in swarming!\n");
        send_debug_message(SWARM_VALIDATE, 
                           capitalize(player->query_real_name()) 
                         + " is not skilled in swarm.");
        return 0; 
    }
    else
    {
        if (!objectp(enemy = player->try_assist(0)))
        {
            send_debug_message(SWARM_VALIDATE, 
                               capitalize(player->query_real_name()) 
                             + " does not have an enemy to swarm.");            
            return 0;
        }
    } 

    // Calians cannot swarm if they are being attack.
    enemies = filter(all_inventory(environment(player)), 
                     &is_attacking_this_living(,player)); 

    if (player->query_attack()->query_attack() == player) 
    { 
        player->catch_tell("Your enemy is paying too much attention for "
                         + "you to swarm " 
                         + enemy->query_objective() + ".\n"); 
        send_debug_message(SWARM_VALIDATE, 
                           capitalize(player->query_real_name()) 
                         + " can't swarm because enemy is attacking.");                         
        return 0; 
    }
    else if (sizeof(enemies) > 0)
    {
        player->catch_tell("Your enemies are paying too much attention for "
                         + "you to swarm " 
                         + enemy->query_objective() + ".\n"); 
        send_debug_message(SWARM_VALIDATE, 
                           capitalize(player->query_real_name()) 
                         + " can't swarm because he is being attacked.");
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
    object weapon;
    int hand;
    
    weapon = actor->query_calian_main_weapon();
    if (weapon)
    {
        return ({ weapon });
    }
    
    return 0;  // Need to be wielding some sort of weapon
}

/*
 * Function name: apply_costs_to_player
 * Description  : By default, a small fatigue cost is applied
 *                for the special. Other costs can be applied
 *                as well by a masked function.
 * Arguments    : player - player executing the special
 * Returns      : nothing
 */
public void
apply_costs_to_player(object player)
{
    string error_message;
    string tag;
    
    tag = APPLY_COSTS;
    if (player->query_fatigue() < SWARM_FATIGUE) 
    {
        error_message = "Your body hurts as you are so weary in "
            + "your attempts to swarm your enemy.\n";
        player->catch_tell(error_message);
        send_debug_message(tag, error_message);
        player->heal_hp(-10); 
    } 
    player->add_fatigue(-SWARM_FATIGUE); 
}

/*
 * Function name: do_ability
 * Description  : The main entry point for abilities
 * Arguments    : arg - the argument passed in for targeting
 * Returns      : 0/1 - failure/success of the action
 */
public int 
do_ability(string arg)
{
    string adverb;
    
    if (!arg)
    {
        // If there is no argument, just return.
        return ::do_ability(arg);
    }
    
    // Check for an adverb.
    if (strlen(adverb = FULL_ADVERB(arg)))
    {
        arg = "";
        if (this_player()->query_mb_adverb() != adverb)
        {
            this_player()->calian_set_adverb("swarm " + adverb);
        }
    }

    return ::do_ability(arg);
}

/*
 * Function name: hook_stopped_ability
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_stopped_ability(object ability,object player)
{
    // Don't display any messages
}

/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the actor when
 *                the targets has disappeared during the prepartion of the
 *                ability.
 * Returns:       The message to print
 */
public void
hook_targets_gone(object * targets)
{
    write("Your swarm target is not in this room.\n");
}
