/*
 * The Dragon Swoop Special, executed by a dragonarmy dragon
 *
 * Even though to the player it looks like the dragon is doing the
 * swooping, in actuality, the player is the one executing the special.
 * This ensures that the correct combat aid is being applied based on
 * their specific stats.
 *
 * Created by Petros, January 2009
 * Updated by Zhar, April 2015
 *    - updated code formatting
 *    - changed tab characters to spaces
 *    - changed hit descriptions to remove the silly "almost literally" thing
 */

#pragma strict_types

#include "defs.h"

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

// Prototypes
public void config_ability();
public void special_did_hit(int aid, string hdesc, int hid, int phurt,
                            object enemy, int dt, int phit, int dam,
                            mixed * items, int result);
static int check_valid_action(object player, mixed * targets, string arg,
                              int execute);

// Defines
#define BDA_SWOOP_CAID  15
#define RDA_SWOOP_CAID  10


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
    set_combat_aid(BDA_SWOOP_CAID);
    set_tohit(95); // 84% chance of hitting
    set_dt(W_SLASH); 
    set_stats( ({ SKILL_WEIGHT, 41, TS_STR, SKILL_WEIGHT, 41, TS_DEX, 
                  SKILL_WEIGHT, 18, TS_DIS }) );    
    set_skills(({ SS_DRAGONARMY_ATTACK }) );
    set_ability_prep_time(12);
    set_ability_cooldown_time(8);
    set_ability_name("dragon swoop");
    add_ability_restriction(DRAGON_BREATH_SPECIAL);
    
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
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
        modifier = modifier * RDA_SWOOP_CAID / BDA_SWOOP_CAID;
    }

    return modifier;
}

/*
 * Function:    check_required_items
 * Description: Returns the weapon that will be used in the attack
 */
static mixed * 
check_required_items(object actor,mixed * targets,
                     string arg,int pretest)
{
    object weapon;

    // Dragon Swoop will automatically use the pen of the best
    // weapon. It won't use the weapon if it's less than 40, and
    // just default to 40.

    if (!objectp(weapon = query_best_wielded_weapon(actor))
        || weapon->query_pen() < 40)
    {
        // If the weapon is worse than 40 or not available,
        // we go ahead and just use 40.
        return ({ });
    }

    return ({ weapon });
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

    enemy_msg = QCTNAME(dragon) + " swoops down with enormous speed "
        + "towards you with both claws extended and ";
    watcher_msg = QCTNAME(dragon) + " swoops down with enormous speed "
        + "towards " + QTNAME(enemy) + " with both claws extended and ";

    if (phurt >= 0)
    {
        switch(phurt)
        {
            case 0:
                enemy_msg += "just barely scratches you as ";
                watcher_msg += "just barely scratches "
                    + QTNAME(enemy) 
                    + " as ";
                break;
            case 1..2:
                enemy_msg += "grazes your "
                    + hdesc
                    + " as ";
                watcher_msg += "grazes "
                    + enemy->query_possessive()
                    + " "
                    + hdesc
                    + " as ";
                break;
            case 3..5:
                enemy_msg += "inflicts painful wounds upon you with quick "
                    + "double swipes as ";
                watcher_msg += "inflicts painful wounds upon "
                    + QTNAME(enemy)
                    + " with quick double swipes as ";
                break;
            case 6..10:
                enemy_msg += "digs them deeply into your "
                    + hdesc
                    + " and "
                    + "tears out a large chunk of flesh as ";
                watcher_msg += "digs them deeply into "
                    + enemy->query_possessive()
                    + " "
                    + hdesc
                    + " and tears out a large chunk of "
                    + "flesh as ";
                break;
            case 11..20:
                enemy_msg += "slashes you on the "
                    + hdesc
                    + " with such "
                    + "momentum that you are lifted off the ground slightly "
                    + "as ";
                watcher_msg += "slashes "
                    + QTNAME(enemy)
                    + " on the "
                    + hdesc
                    + " with such momentum that "
                    + enemy->query_pronoun()
                    + " is lifted off the groundly slightly as ";
                break;
            case 21..30:
                enemy_msg += "attacks you with great ferocity and tears into "
                    + "your "
                    + hdesc
                    + " with both claws and bite as ";
                watcher_msg += "attacks "
                    + QTNAME(enemy)
                    + " with great "
                    + "ferocity and tears into "
                    + enemy->query_possessive()
                    + " "
                    + hdesc
                    + " with both claws and bite as ";
                break;
            case 31..50:
                enemy_msg += "knocks you backwards with tremendous force "
                    + "while heavily wounding your "
                    + hdesc
                    + " as ";
                watcher_msg += "knocks "
                    + QTNAME(enemy)
                    + " backwards with "
                    + "tremendous force while heavily wounding "
                    + enemy->query_possessive()
                    + " "
                    + hdesc
                    + " as ";
                break;
            case 51..75:
                enemy_msg += "almost breaks you in half as the two "
                    + "claws pierce deeply into your "
                    + hdesc
                    + " as ";
                watcher_msg += "almost breaks "
                    + QTNAME(enemy)
                    + " in half as the two claws pierce deeply into "
                    + enemy->query_possessive()
                    + " "
                    + hdesc
                    + " as ";
                break;
            case 76..99:
                enemy_msg += "lacerates your "
                    + hdesc
                    + " causing profuse "
                    + "bleeding as ";
                watcher_msg += "lacerates "
                    + enemy->query_possessive()
                    + " "
                    + hdesc
                    + " causing profuse bleeding as ";
                break;
            default:
                enemy_msg += "rends your "
                    + hdesc
                    + " ripping you "
                    + "to pieces as ";
                watcher_msg += "rends "
                    + enemy->query_possessive()
                    + " "
                    + hdesc
                    + " ripping "
                    + enemy->query_objective()
                    + " to pieces as ";
        }

        watcher_msg += dragon->query_pronoun()
            + " flies by and climbs back "
            + "to the sky again.\n";        
        enemy_msg += dragon->query_pronoun()
            + " flies by and climbs back "
            + "to the sky again.\n";        
    }
    else
    {
        enemy_msg += "badly misses you.\n";
        watcher_msg += "badly misses "
            + QTNAME(enemy)
            + ".\n";        
    }

    tp->catch_msg(watcher_msg);
    enemy->catch_msg(enemy_msg);
    tp->tell_watcher(watcher_msg, enemy, ({ tp, enemy }));
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

    return "You are too busy focusing on guiding "
        + QTNAME(dragon)
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
            player->catch_tell("Expecting to see your dragon swoop "
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

    this_player()->catch_msg("\nYou see "
        + QTNAME(dragon)
        + " hovering "
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

    actor->catch_msg("You signal towards "
        + QTNAME(dragon)
        + " in "
        + "the sky above you, and you see "
        + dragon->query_objective()
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

    this_player()->catch_msg(QCTNAME(dragon)
        + " is already making "
        + dragon->query_possessive()
        + " descent.\n");
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
        set_alarm(0.0, 0.0, &remove_summoned_strike_dragon(this_player()));
    }    
}
