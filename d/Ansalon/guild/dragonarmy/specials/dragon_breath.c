/*
 * The Dragon Breath Special, executed by a dragonarmy dragon
 *
 * Even though to the player it looks like the dragon is doing the
 * breathing, in actuality, the player is the one executing the special.
 * This ensures that the correct combat aid is being applied based on
 * their specific stats.
 *
 * Created by Petros, January 2009
 */

#pragma strict_types

#include "defs.h"

inherit "/d/Genesis/specials/resist";
inherit "/d/Genesis/specials/std/damage";
inherit "/d/Ansalon/guild/dragonarmy/specials/dragonarmy_utility";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

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

// Defines
#define BDA_BREATH_CAID         15
#define RDA_BREATH_CAID         20

// Prototypes
public void             config_ability();
public void             special_did_hit(int aid, string hdesc, int hid, 
                                        int phurt, object enemy, int dt, 
                                        int phit, int dam, mixed * items,
                                        int result);
static int              check_valid_action(object player, mixed * targets, 
                                           string arg, int execute);
public mixed *          target_dragon_breath(object player, string str);

// Global Variables
private string* elec_hits = ({"unhurt","slightly shocked","somewhat burned",
                             "shocked","charred","electrocuted"});
private string* fire_hits = ({"unhurt","slightly heated","somewhat burned", 
                             "burned","roasted","severely blasted"});

public int
ability_resist_breath(object player, object target, string name)
{
    object dragon;
    
    dragon = query_present_summoned_strike_dragon(player);
    if (!objectp(dragon))
    {
        return 0;
    }

    if (dragon->query_colour() == "red")
    {        
        return spell_resist(player, target, SS_ELEMENT_FIRE, TASK_DIFFICULT);
    }
    
    return spell_resist_electricity(player, target, SS_ELEMENT_FIRE, 
                                    TASK_DIFFICULT);
}

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
    set_combat_aid(BDA_BREATH_CAID);
    set_tohit(95); // 84% chance of hitting
    set_dt(MAGIC_DT);
    set_stats( ({ SKILL_WEIGHT, 41, TS_STR, SKILL_WEIGHT, 41, TS_DEX, 
                  SKILL_WEIGHT, 18, TS_DIS }) );    
    set_skills(({ SS_DRAGONARMY_ATTACK }) );
    set_ability_prep_time(12);
    set_ability_cooldown_time(8);
    set_ability_resist(ability_resist_breath);
    set_ability_target(target_dragon_breath);
    set_ability_name("dragon breath");
    add_ability_restriction(DRAGON_SWOOP_SPECIAL);

    set_guild_stat_modifier(SS_OCCUP, 20, 100);
}

/*
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Arguments    : player - player executing special
 * Returns      : number between 1 and 100
 */
public int query_combat_aid_modifier()
{
    // Combat aid is the maximum provided by a special
    // The modifier is used in situations where the player
    // should not get the maximum combat aid.
    // Value should be between 1 and 100
    object dragon;
    int modifier;
    
    dragon = query_present_summoned_strike_dragon(this_player());
    if (!objectp(dragon))
    {
        return 1;
    }
    
    modifier = query_level_caid_adjustment(this_player());
        
    if (dragon->query_colour() == "red")
    {
        modifier = modifier * RDA_BREATH_CAID / BDA_BREATH_CAID;
        if (sizeof(FILTER_PRESENT(this_player()->query_enemy(-1))) > 1)
        {
            // RDA can also fire at 3 people at once. We do half damage
            // to each in that case.
            modifier /= 2;
        }
    }
    
    return modifier;
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
    object tp = this_player();
    object dragon = query_present_summoned_strike_dragon(tp);
    string player_msg, enemy_msg, watcher_msg;
    
    if (phurt < 0)
    {
        if (dragon->query_colour() == "red") {
            tp->catch_msg(QCTNAME(enemy)+" manages to dodge "+
                "the inferno of dragonfire.\n");
            enemy->catch_msg("The area is bathed in fire, "+
                "but you manage to dodge away from the flames.\n");
            tp->tell_watcher(QCTNAME(enemy)+" manages to dodge "+
                "the inferno of dragonfire.\n", enemy);
        } 
        else 
        {
             tp->catch_msg(QCTNAME(enemy)+" skillfully dodges "+
                "the bolt of lightning.\n");            
             enemy->catch_msg("You skillfully dodge "+
                "the lightning bolt.\n");
             tp->tell_watcher(QCTNAME(enemy)+" skillfully dodges "+
                "the bolt of lightning.\n", enemy);
        }
    }
    else
    {       
        string how_str;
        string * how_hits;
        if (dragon->query_colour() == "red") 
        {
            how_hits = fire_hits;
        } 
        else 
        {
            how_hits = elec_hits;
        }
        switch (phurt)
        {
        case 0:
            how_str = how_hits[0];
            break;
            
        case 1..10:
            how_str = how_hits[1];
            break;
        
        case 11..20:
            how_str = how_hits[2];
            break;
            
        case 21..40:
            how_str = how_hits[3];
            break;
            
        case 41..60:
            how_str = how_hits[4];
            break;
        
        default:
            how_str = how_hits[5];
        }
        
        tp->catch_msg(QCTNAME(enemy) + " is " + how_str + " by the dragon "
            + "breath!\n");            
        enemy->catch_msg("You are "+how_str+" by the dragon breath!\n");
        tp->tell_watcher(QCTNAME(enemy) + " is "+how_str+" by the dragon "+
          "breath!\n", enemy);
    
        /*credit the summoner with the kill*/
        if (enemy->query_hp() <= 0) 
        {
            enemy->do_die(tp);
        }
    }
}

public varargs string
query_restricted_ability_message(string ability, object player)
{
    object dragon;
    string short_desc;
    
    dragon = query_present_summoned_strike_dragon(player);
    if (!objectp(dragon))
    {
        return ::query_restricted_ability_message(ability, player);
    }

    return "You are too busy focusing on guiding " + QTNAME(dragon)
        + " to do that.\n";
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
    
    if (!objectp(query_present_summoned_strike_dragon(player)))
    {
        if (execute)
        {
            player->catch_tell("Expecting to see your dragon dive "
                + "down from the sky, you are a bit dismayed to find "
                + "that you don't see your dragon anywhere in sight!\n");
        }
        else
        {
            player->catch_tell("You don't see a dragon present that can "
                + "be called upon!\n");
        }
        return 0;
    }   
    
    // If it passes everything, return success
    return 1; 
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
 * Function:    hook_special_preparation_complete
 * Description: Called when preparation period is over. Used here
 *              to remove a pending dragon and display the actual
 *              breath attack.
 */
public void
hook_special_preparation_complete()
{
    object dragon;
    
    // We check for the dragon anywhere and remove it.
    dragon = query_summoned_strike_dragon(this_player());
    if (objectp(dragon) && dragon->query_prop(PENDING_DRAGON_SPECIAL))
    {
        send_debug_message("dragon_breath", "Calling remove.");
        set_alarm(0.0, 0.0, &remove_summoned_strike_dragon(this_player()));
    }    
    
    // We check for the dragon only in this room. The player could have
    // moved elsewhere.
    dragon = query_present_summoned_strike_dragon(this_player());
    if (!objectp(dragon))
    {
        return;
    }
    
    if (dragon->query_colour() == "red")
    {
        dragon->tell_watcher(QCTNAME(dragon) + " dives low, "
            + "spewing fire from " + dragon->query_possessive() 
            + " gaping maw!\n", 0);
    }
    else
    {
        dragon->tell_watcher(QCTNAME(dragon) + " dives low, "
            + "blasting lightning from " + dragon->query_possessive() 
            + " gaping maw!\n", 0);
    }    
}

public void
hook_special_in_cooldown()
{   
    object dragon;
    
    dragon = query_present_summoned_strike_dragon(this_player());
    if (!objectp(dragon))
    {
        return;
    }
    this_player()->catch_msg("You see " + QTNAME(dragon) + " still climbing "
        + "back up in the sky and unable to see your signaling.\n");     
}

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    object dragon;
    
    dragon = query_present_summoned_strike_dragon(this_player());
    if (!objectp(dragon))
    {
        return;
    }
    this_player()->catch_msg("\nYou see " + QTNAME(dragon) + " hovering "
        + "high above you, ready to make another attack.\n\n");
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
    object dragon;
    
    dragon = query_present_summoned_strike_dragon(this_player());
    if (!objectp(dragon))
    {
        return;
    }
    this_player()->catch_msg(QCTNAME(dragon) + " swoops down but it seems "
        + "that your foe has slipped away.\n");
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
    object dragon;
    
    dragon = query_present_summoned_strike_dragon(actor);
    if (!objectp(dragon))
    {
        return;
    }
    actor->catch_msg("You signal towards " + QTNAME(dragon) + " in "
        + "the sky above you, and you see " + dragon->query_objective()
        + " begin to make a dive towards you.\n");    
}

public void
hook_already_active(object ability)
{
    object dragon;
    
    dragon = query_present_summoned_strike_dragon(this_player());
    if (!objectp(dragon))
    {
        return;
    }
    this_player()->catch_msg(QCTNAME(dragon) + " is already making "
        + dragon->query_possessive() + " descent.\n");
}

public mixed *
target_dragon_breath(object player, string str)
{
    object dragon;
    object * targets;
    dragon = query_present_summoned_strike_dragon(this_player());
    if (!objectp(dragon))
    {
        player->catch_tell("You don't see a dragon present that can be "
            + "called upon!\n");
        return ({ });
    }
    
    if (dragon->query_colour() == "red")
    {
        targets = (target_present_enemies(player, str));
        // Arrange the targets so that the current target
        // is last.
        targets = targets - ({ player->query_attack() });
        targets = targets[..1] + ({ player->query_attack() });        
    }
    else
    {
        targets = target_one_present_enemy(player, str);
    }
    
    return targets;
}

public void
hook_attack_object(object ob)
{
    // Masking this so that you won't see many attack messages for
    // fire breath when it attacks multiple targets if it's already
    // attacking
    if (IN_ARRAY(ob, this_player()->query_enemy(-1)))
    {
        return;
    }
    
    ::hook_attack_object(ob);
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
    // No fatigue penalty for using a dragon, as it's completely
    // unthematic.
}

