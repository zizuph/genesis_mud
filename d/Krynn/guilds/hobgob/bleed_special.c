/*
 * Throtyl Raider's bleed special attack.
 *
 * Port of the old Red Dragonarmy Impale Bleed special.
 *
 * Created by Arman, June 2020
 */

#pragma strict_types

#include "guild.h"

inherit "/d/Genesis/specials/std/damage";
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
#include "/d/Krynn/common/defs.h"

#include "/std/combat/combat.h"

// Prototypes
public void             config_ability();
public void             special_did_hit(int aid, string hdesc, int hid, 
                                        int phurt, object enemy, int dt, 
                                        int phit, int dam, mixed * items,
                                        int result);
static int              check_valid_action(object player, mixed * targets, 
                                           string arg, int execute);
public int              force_fail(object player, mixed * items, 
                                   object enemy, int resist, int result);

// Defines
#define     BLEED_CAID     5
#define     WOUNDING_CAID  40
#define     WOUNDING_OBJ    "/d/Krynn/guilds/hobgob/bleed_wounding_obj"
#define     BLEED_LOG       ("/d/Krynn/guilds/hobgob/log/bleed_damage")

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
    set_combat_aid(BLEED_CAID);
    set_tohit(110); // 90% chance of hitting
    set_dt(W_IMPALE | W_SLASH | W_BLUDGEON);
    set_stats( ({ SKILL_AVG, TS_STR, TS_INT, SKILL_END }) );    
    set_skills(({ SS_GUILD_SPECIAL_SKILL }) );
    set_ability_prep_time(2);
    set_ability_cooldown_time(10);
    set_ability_name("wound");
    
    set_guild_stat_modifier(SS_LAYMAN, 20, 100);
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

    return 100;
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
    string *attack_message;
    object tp = this_player();
    string weapon = items[0]->short();
    int weapon_type = items[0]->query_dt();
    string damage_desc;

    switch(weapon_type)
    {
        case W_BLUDGEON:
            damage_desc = "breaking open";
            break;
        case W_IMPALE:
            damage_desc = "piercing";
            break;
        default:
            damage_desc = "slashing open";
            break;
    }
    
    if (phurt >= 0)
    {
    	switch(phurt)
    	{
    	case 0:
            if (dam > 0)
            {
                attack_message = ({
                    "You strike savagely at " +enemy->query_the_name(tp)+
                    " with your " +weapon+ ", but you are only able "+ 
                    "to cause a minor wound to " +HIS(enemy)+ " " +hdesc+ ".\n",
    
                    tp->query_The_name(enemy)+ " strikes savagely at you with " +
                    HIS(tp)+ " " +weapon+ ", but is only able to cause a minor wound to " +
                    "your " +hdesc+ ".\n",

                    tp->query_The_name(enemy)+ " strikes savagely at " +
                    QTNAME(enemy)+ " with " +HIS(tp)+ " " +weapon+ ", but is " +
                    "only able to cause a minor wound to " +QTPNAME(enemy)+ " " +hdesc+ ".\n"
                });
            }
            else
            {
                attack_message = ({
                    "You strike savagely at " +enemy->query_the_name(tp)+
                    " with your " +weapon+ ", but you are unable to "+ 
                    "cause a wound to " +HIS(enemy)+ " " +hdesc+ ".\n",
    
                    tp->query_The_name(enemy)+ " strikes savagely at you with " +
                    HIS(tp)+ " " +weapon+ ", but is unable to cause a wound to " +
                    "your " +hdesc+ ".\n",

                    tp->query_The_name(enemy)+ " strikes savagely at " +
                    QTNAME(enemy)+ " with " +HIS(tp)+ " " +weapon+ ", but is " +
                    "unable to cause a wound to " +QTPNAME(enemy)+ " " +hdesc+ ".\n"
                });
            }
    	    break;
    	case 1..95:
    	    attack_message = ({
    		"You strike savagely at " +enemy->query_the_name(tp)+
                " with your "+weapon+", " +damage_desc+ " " +HIS(enemy)+ 
                " " +hdesc+ ".\n",
    
    		tp->query_The_name(enemy)+ " strikes savagely at you with " +
    		HIS(tp)+ " " +weapon+ ", " +damage_desc+ " your " +hdesc+ ".\n",

    		tp->query_The_name(enemy)+ " strikes savagely at " +
                QTNAME(enemy)+ " with " +HIS(tp)+ " " +weapon+ ", " +
                damage_desc+ " " +QTPNAME(enemy)+ " " +hdesc+ ".\n"
    	    });
    	    break;
    	default:
    	    attack_message = ({
    		"You strike savagely at " +enemy->query_the_name(tp)+
                " with your "+weapon+", grievously " +damage_desc+ " " +
                HIS(enemy)+ " " + hdesc+ ".\n",
    
    		tp->query_The_name(enemy)+ " strikes savagely at you with " +
    		HIS(tp)+ " " +weapon+ ", grievously " +damage_desc+ " your " +
                hdesc+ ".\n",

    		tp->query_The_name(enemy)+ " strikes savagely at " +
                QTNAME(enemy)+ " with " +HIS(tp)+ " " +weapon+ ", " +
                "grievously " +damage_desc+ " " +QTPNAME(enemy)+ " " +hdesc+ ".\n"
    	    });
    	    break;
    	}
    
    	tp->catch_tell(attack_message[0]);
    	enemy->catch_tell(attack_message[1]);
    	tp->tell_watcher(attack_message[2], enemy);
        
        if (dam > 0)
        {
            // Add a bleeding wound object
            int wound_damage = dam * WOUNDING_CAID / BLEED_CAID;

            object wound_obj = clone_object(WOUNDING_OBJ);
            wound_obj->set_wounding_damage(wound_damage);
            wound_obj->set_wounding_hitloc(hid);
            wound_obj->set_wounding_interval(3);
            wound_obj->set_wounding_time(10); // 9 seconds
            wound_obj->move(enemy, 1);
            wound_obj->start();

            send_debug_message("hobgob", tp->query_The_name(enemy) + " bleeding wound " +
                "total damage is " +wound_damage, BLEED_LOG);
            send_debug_message("hobgob", tp->query_The_name(enemy) + " bleeding wound " +
                "total damage is " +wound_damage);

            // A successful attack generates panic
        	tp->add_panic(-3 - phurt / 5);
        }        
    }
    else
    {
    	tp->catch_tell("You strike out furiously at " +
            enemy->query_the_name(tp)+ ", who deftly avoids your attack.\n");

    	enemy->catch_tell(tp->query_The_name(enemy)+ " strikes furiously at "+
    	  "you, but you deftly avoid "+HIS(tp)+" attack.\n");

    	tp->tell_watcher_miss(QCTNAME(tp)+ " strikes furiously at " +QTNAME(enemy)+ 
          ", who deftly avoids " +HIS(tp)+ " attack.\n", enemy);
    	
    	// a miss emboldens enemies
    	tp->add_panic(1);
    }
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(tp);
    }
}

public object
query_wielded_weapon(object actor)
{
    object * weapons;

    if(!actor->query_weapon(W_RIGHT) && !actor->query_weapon(W_LEFT) && 
       !actor->query_weapon(W_BOTH))
    {
        // Not wielding a weapon
        return 0;
    }
    
    weapons = actor->query_weapon(-1);
    
    return weapons[random(sizeof(weapons))];
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
    
    weapon = query_wielded_weapon(actor);
    if (!weapon)
    {
        return 0;
    }
    
    return ({ weapon });
}

/*
 * Function name: validate_requirements
 * Description  : Function to check all the prerequisites of bleed
 *                These checks are used in both check_valid_action
 *                as well as force fail. (before start, and before
 *                execute)
 * Arguments    : player - person executing the special
 * Returns      : 0/1 - invalid/valid conditions
 */
public int
validate_requirements(object player)
{
    seteuid(getuid()); 
    
    if (player->query_skill(SS_GUILD_SPECIAL_SKILL) < 1)
    {
        player->catch_tell("Maybe you should get some training first!\n");
        return 0;
    }

    // If alignment is agreeable or higher the special won't work

    if (player->query_alignment() > 99)
    {
        player->catch_tell("You feel you are too morally challenged to " +
            "inflict such sadistic wounds!\n");
        return 0;
    }

    if (!objectp(query_wielded_weapon(player)))
    {
        player->catch_tell("You are not wielding an appropriate weapon " +
            "to cause a wound.\n");
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
    
    if (!validate_requirements(player))
    {
        return 0;
    }

    // If it passes everything, return success
    return 1; 
}

/*
 * Function name: force_fail
 * Description:   This function allows the special to force a failure for
 *                whatever reason. Called right before execution at the end
 *                of the delay
 * Arguments:     1. (object)   The player
 *                2. (object) The targets
 *                3. (int *)    Resistance values corresponding to each target
 *                4. (int)      The attempt result as returned by
 *                              query_casting_success()
 * Returns:       1 for failure, 0 for not.
 */
public int 
force_fail(object player, mixed * items, object enemy, 
           int resist, int result)
{
    if (!validate_requirements(player))
    {
        return 1;
    }

    return 0;
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
    write("You are not yet ready to cause a bleeding wound " +
        "on your enemy. Patience!\n");     
}

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    write("You feel ready to cause a bleeding wound again.\n");    
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
	write("The target of your bleeding wound attack "
	    + "seems to have slipped away.\n");    
}

static void 
ability_msg(object actor,mixed * targets,string arg)
{
    write("Your muscles tense eagerly as you prepare to cause a bleeding wound.\n");    
}


