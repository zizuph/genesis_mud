/*
 * Port of the Red Dragonarmy Impale to the new Genesis Combat
 * System.
 *
 * Modifications
 *  - Removed fatigue mask. Used standard 2 fatigue from damage library
 *
 * Created by Petros, September 2008
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
#define     IMPALE_CAID     75
#define     WOUNDING_CAID   50
#define     WOUNDING_OBJ    "/d/Genesis/specials/std/wounding_obj_base"

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
    set_combat_aid(IMPALE_CAID);
    set_tohit(95); // 84% chance of hitting
    set_dt(W_IMPALE);
    set_stats( ({ SKILL_WEIGHT, 41, TS_STR, SKILL_WEIGHT, 41, TS_DEX, 
                  SKILL_WEIGHT, 18, TS_WIS }) );    
    set_skills(({ SS_DRAGONARMY_ATTACK }) );
    set_ability_prep_time(7);
    set_ability_cooldown_time(8);
    set_ability_name("impale");
    
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
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
    int weapon_type = items[0]->query_wt();
    
    if (phurt >= 0)
    {
    	switch(phurt)
    	{
    	case 0:
    	    attack_message = ({
    	      "Crouching low, you set your " +weapon+ " into a " +
    	      "defensive position, keeping "+
    	      enemy->query_the_name(tp)+ " back while you formulate " +
    	      "a plan of attack.\n",
    
    	      "Crouching low, " +tp->query_the_name(enemy)+ " sets "+
    	      HIS(tp)+ " " +weapon+ " into a defensive position, keeping "+
    	      "you back while " +HE(tp)+ " formulates a plan of attack.\n",
    
    	      "Crouching low, "+QTNAME(tp)+ " sets " +HIS(tp)+ " "+
    	      weapon+ " into a defensive position, keeping "+
    	      QTNAME(enemy)+ " back "+
    	      "while " +HE(tp)+ " formulates a plan of attack.\n"
    	    });
    	    break;
    	case 1..2:
    	    attack_message = ({
    	      "You thrust forward at " +enemy->query_the_name(tp)+ " with "+
    	      "your " +weapon+ ", but inflict little more than a graze "+
    	      "on " +HIS(enemy)+ " " +hdesc+ ".\n",
    	      tp->query_The_name(enemy)+ " thrusts forward at you with "+
    	      HIS(tp)+ " " +weapon+ ", but inflicts little more than " +
    	      "a graze upon your " +hdesc+ ".\n",
    	      QCTNAME(tp)+ " thrusts forward at " +QTNAME(enemy)+
    	      " with " +HIS(tp)+ " " +weapon+ ", but inflicts " +
    	      "little more damage than a graze.\n"
    	    });
    	    break;
    	case 3..5:
    	    if(weapon_type == W_SWORD || weapon_type == W_KNIFE)
    		attack_message = ({
    		  "With a wild laugh, you fake a thrust with your " +weapon+
    		  ", and then nonchalantly backhand " +enemy->query_the_name(tp)+
    		  " across " +HIS(enemy)+ " " +hdesc+ " with the " +
    		  "flat of your blade.\n",
    
    		  "With a wild laugh, " +tp->query_the_name(enemy)+ " fakes a thrust with " +
    		  HIS(tp)+ " " +weapon+ ", and then nonchalantly backhands " +
    		  "you across your " +hdesc+ " with the flat of " +
    		  HIS(tp)+ " blade.\n",
    
    		  "With a wild laugh, " +QTNAME(tp)+ " fakes a thrust with " +
    		  HIS(tp)+ " " +weapon+ " at " +QTNAME(enemy)+ ", and then " +
    		  "nonchalantly backhands " +HIM(enemy)+ " across " +
    		  HIS(enemy)+ " " +hdesc+ " with the flat of " +HIS(tp)+ " " +
    		  "blade.\n"
    		});
    	    else
    		attack_message = ({
    		  "You swiftly strike out at " +enemy->query_the_name(tp)+
    		  "'s " +hdesc+ ", but only score a glancing blow with " +
    		  "your " +weapon+ ".\n",
    		  tp->query_The_name(enemy)+ " swiftly strikes out at your "+
    		  hdesc+ ", but only manages to score a glancing blow with "+
    		  HIS(tp)+ " " +weapon+ ".\n",
    		  QCTNAME(tp)+ " swiftly strikes out at "+
    		  QTNAME(enemy)+ "'s " +hdesc+
    		  ", but only scores a glancing blow with " +HIS(tp)+ 
    		  " " +weapon+ ".\n"
    		});
    	    break;
    	case 6..10:
    	    if(weapon_type == W_SWORD || weapon_type == W_KNIFE)
    		attack_message = ({
    		  "Breaking through " +enemy->query_the_name(tp)+ "'s guard, " +
    		  "you bash " +HIM(enemy)+ " with the hilt of your " +weapon+ ".\n",
    
    		  "Breaking through your guard, " +tp->query_the_name(enemy)+ " bashes you " +
    		  "with the hilt of " +HIS(tp) + " " +weapon+ ".\n",
    
    		  "Breaking through " +QTNAME(enemy)+ "'s guard, " +QTNAME(tp)+
    		  " bashes " +HIM(enemy)+ " with the hilt of " +HIS(tp)+
    		  " " +weapon+ ".\n"
    		});
    	    else
    		attack_message = ({
    		  "Reversing your " +weapon+ ", you craftily strike " +enemy->query_the_name(tp)+
    		  " with a solid blow to the " +hdesc+ ".\n",
    
    		  "Reversing " +HIS(tp)+ " " +weapon+ ", " +tp->query_the_name(enemy)+
    		  " craftily strikes you a solid blow to the " +hdesc+ ".\n",
    
    		  "Reversing " +HIS(tp)+ " " +weapon+ ", " +QTNAME(tp)+
    		  " craftily strikes " +QTNAME(enemy)+ " a solid blow " +
    		  "to the " +hdesc+ ".\n"
    		});
    	    break;
    	case 11..20:
    	    attack_message = ({
    	      "You lunge towards " +enemy->query_the_name(tp)+ "'s " +hdesc+
    	      " with your " +weapon+ ", scoring a minor flesh wound.\n",
    
    	      tp->query_The_name(enemy)+ " lunges forward at your " +hdesc+ " with "+
    	      HIS(tp)+ " " +weapon+ ", scoring a minor flesh wound.\n",
    
    	      QCTNAME(tp)+ " lunges forward at " +QTNAME(enemy)+ "'s " +hdesc+
    	      ", scoring a minor flesh wound.\n"
    	    });
    	    break;
    	case 21..30:
    	    attack_message = ({
    	      "You drive forward at " +enemy->query_the_name(tp)+ "'s " +hdesc+
    	      ", piercing a gaping wound with your " +weapon+ ".\n",
    
    	      tp->query_The_name(enemy)+ " drives forward at your " +hdesc+
    	      ", piercing a gaping wound with " +HIS(tp)+ " " +weapon+ ".\n",
    
    	      QCTNAME(tp)+ " drives forward at " +QTNAME(enemy)+ "'s "+
    	      hdesc+ ", piercing a gaping wound with " +HIS(tp)+
    	      " " +weapon+ ".\n"
    	    });
    	    break;
    	case 31..50:
    	    attack_message = ({
    	      "Lunging powerfully with your " +weapon+ ", you "+
    	      "open a crippling wound in " +enemy->query_the_name(tp)+
    	      "'s " +hdesc+ ".\n",
    
    	      "Lunging powerfully at you with " +HIS(tp)+ " " +weapon+
    	      ", " +tp->query_the_name(enemy)+ " opens a crippling wound in your " +
    	      hdesc + ".\n",
    
    	      "Lunging powerfully with " +HIS(tp)+ " " +weapon+ ", "+
    	      QTNAME(tp)+ " opens a crippling wound in " +
    	      QTNAME(enemy)+ "'s " +hdesc+ ".\n"
    	    });
    	    break;
    	case 51..75:
    	    attack_message = ({
    	      "Avoiding a desperate attack by " +enemy->query_the_name(tp)+
    	      ", you thrust your " +weapon+ " down into "+
    	      HIS(enemy)+ " " +hdesc+ " with deadly accuracy.\n",
    
    	      "Avoiding a desperate attack of yours, " +tp->query_the_name(enemy)+
    	      " thrusts " +HIS(tp)+ " " +weapon+ " down into "+
    	      "your " +hdesc+ " with deadly accuracy.\n",
    
    	      "Avoiding a desperate attack by " +QTNAME(enemy)+
    	      ", " +QTNAME(tp)+ " thrusts " +HIS(tp)+ " "+
    	      weapon+ " down into " +QTNAME(enemy)+ "'s "+
    	      hdesc+ " with deadly accuracy.\n"
    	    });
    	    break;
    	case 76..99:
    	    attack_message = ({
    	      "In shock, " +enemy->query_the_name(tp)+ " clutches " +
    	      HIS(enemy)+ " " +hdesc+ " as you deal " +HIM(enemy)+
    	      " a mortal wound. You notice in grim satisfaction the " +
    	      "ammount of blood starting to pool around " +HIM(enemy)+
    	      ".\n",
    
    	      "In shock, you clutch your " +hdesc+ " after " +
    	      tp->query_the_name(enemy)+ " deals you a mortal wound. You notice " +
    	      "in horror a great deal of your lifeblood is starting " +
    	      "to pool around your feet.\n",
    
    	      "In shock, " +QTNAME(enemy)+ " clutches at " +
    	      HIS(enemy)+ " " +hdesc+ " after " +QTNAME(tp)+
    	      " deals " +HIM(enemy)+ " a mortal wound. You notice " +
    	      "in morbid fascination a great deal of blood starting " +
    	      "to pool around " +QTNAME(enemy)+ ".\n"
    	    });
    	default:
    	    attack_message = ({
    	      "In triumph, you raise your " +weapon+ " in a mock " +
    	      "salute, then with a downward lunge you swiftly " +
    	      "impale " +enemy->query_the_name(tp)+ " to the ground, "+
    	      "dealing " +HIM(enemy)+ " a gruesome "+
    	      "death blow.\n",
    
    	      "In triumph, " +tp->query_the_name(enemy)+ " raises " +HIS(tp)+ " " +
    	      weapon+ " in a mock salute to you, then with a savage " +
    	      "downward lunge, " +HE(tp)+ " impales you to the ground, "+
    	      "dealing you a gruesome death blow.\n",
    
    	      "In triumph, " +QTNAME(tp)+ " raises " +HIS(tp)+ " " +
    	      weapon+ " in a mock salute, then with a savage " +
    	      "downward lunge, " +HE(tp)+ " impales " +QTNAME(enemy)+
    	      " to the ground, dealing " +HIM(enemy)+ " a gruesome "+
    	      "death blow.\n"
    	    });
    	    break;
    	}
    
    	tp->catch_tell(attack_message[0]);
    	enemy->catch_tell(attack_message[1]);
    	tp->tell_watcher(attack_message[2], enemy);
        
        if (dam > 0)
        {
            // Add a bleeding wound object
            object wound_obj = clone_object(WOUNDING_OBJ);
            wound_obj->set_wounding_damage(dam * WOUNDING_CAID / IMPALE_CAID);
            wound_obj->set_wounding_hitloc(hid);
            wound_obj->set_wounding_interval(5);
            wound_obj->set_wounding_time(180); // 3 minutes
            wound_obj->move(enemy, 1);
            wound_obj->start();

            // A successful attack generates panic
        	tp->add_panic(-3 - phurt / 5);
        }        
    }
    else
    {
    	tp->catch_tell("You snarl in anger as your well-timed thrust "+
    	  "at " +enemy->query_the_name(tp)+ " is anticipated and " +
    	  "deftly avoided.\n");
    	enemy->catch_tell(tp->query_The_name(enemy)+ " snarls in anger at "+
    	  "you as you anticipate "+HIS(tp)+" attack and deftly avoid it.\n");
    	tp->tell_watcher_miss(QCTNAME(tp)+ " snarls in anger as " +HIS(tp)+
    	  " well-timed thrust at " +QTNAME(enemy)+ " is anticipated and deftly "+
    	  "avoided.\n", enemy);
    	
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
    
    weapons = filter(actor->query_weapon(-1), 
                     &operator(&)(W_IMPALE) @ &->query_dt());
    if (!sizeof(weapons))
    {
        // Not wielding an impaling weapon
        return 0;
    }
    
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
 * Description  : Function to check all the prerequisites of charge
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
    
    if (player->query_skill(SS_DRAGONARMY_ATTACK) < 1)
    {
        player->catch_tell("Maybe you should get some training first!\n");
        send_debug_message("impale", "No training in dragonarmy impale.");
        return 0;
    }

    if (!objectp(query_wielded_weapon(player)))
    {
        player->catch_tell("You are not wielding an appropriate weapon.\n");
        send_debug_message("impale", "Can't impale without a proper weapon.");
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
    write("You are not yet ready to impale. Patience!\n");     
}

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    write("You feel ready to go on the offensive again.\n");    
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
	write("The target for your impale "
	    + "seems to have slipped away.\n");    
}

static void 
ability_msg(object actor,mixed * targets,string arg)
{
    write("Your muscles tense as you prepare to impale.\n");    
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
    int combat_aid_modifier = 1; // if no wounds, we divide by 1, else by 3.

    // We want to reduce the actual damage done by the special if we have wounds on
    // As the wounds will use that combat aid (less).
    if (this_player()->query_prop(RDA_WOUNDS_PROP))
    {
        combat_aid_modifier = 3;        
    }

    // Combat aid is the maximum provided by a special
    // The modifier is used in situations where the player
    // should not get the maximum combat aid.
    // Value should be between 1 and 100
    return query_level_caid_adjustment(this_player()) / combat_aid_modifier;
}
