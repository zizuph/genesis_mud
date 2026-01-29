/*
 * Port of the Thornlin Militia Impale attack to the new Genesis Specials 
 * System
 *
 * Created by Petros, September 2008
 */

#pragma strict_types

#include "defs.h"

inherit DAMAGE_LIB;
#include DEBUGGER_LIB

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
#include "/d/Gondor/guilds/militia/wep_find.c"

// Defines
#define IMPALE_LOG         (MILITIA_DIR+"impale_damage")
#define IMPALE_CAID          3
#define COOLDOWN_TIME      120
#define MILITIA_I_LAST_IMPALE "_militia_i_last_impale"

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

// Global Variables

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
    // The combat aid is 3%, but we will multiply by the number of
    // rounds for the cooldown period.
    set_combat_aid(IMPALE_CAID);
    set_tohit(110);
    set_dt(W_IMPALE);
    set_stats( ({ SKILL_AVG, TS_STR, TS_DEX, TS_INT, SKILL_END }) );    
    set_skills(({ SKILL_WEIGHT, 200, SS_MILITIA_IMPALE }) );
    // This is an instant attack with a cooldown time
    set_ability_prep_time(0);
    set_ability_cooldown_time(COOLDOWN_TIME);
    set_ability_name("impale");
    
    set_guild_stat_modifier(SS_LAYMAN, 20, 100);
}

public int
query_guild_stat_type(object player)
{
    if (!player->query_occ_militia())
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
    string it_them, msg1, msg2, msg3, wdesc, target, mil, wep;
    
    player = this_player();
    weapon = find_wep(player, 1);
    wdesc = weapon->short();
    wep = weapon->short();
    target = enemy->query_the_name(player);
    mil = player->query_the_name(enemy);

    player->add_prop(MILITIA_I_LAST_IMPALE, time());                                                            
    
	if (enemy->query_hp() <= 0)
	{
        msg1 = "Seeing " + target + " running towards you, you plant your " +
            wep + " and aim at " + enemy->query_possessive() + " " + hdesc +
            ". " + capitalize(enemy->query_pronoun()) + " tries to slow down " +
            "but only manages to slip, falling with all " + 
            enemy->query_possessive() + 
            " weight onto the tip. Your weapon jumps in your hand as it " +
            "passes completely through " + enemy->query_objective() + ", and " +
            enemy->query_pronoun() + " struggles in agony for a moment before " +
            "going limp.\n";
        msg2 = "Running towards " + mil + ", you see " + 
            player->query_objective() + " plant " + 
            player->query_possessive() + " " + wep + " in the ground. " +
            "Trying to stop in time, you slip, and your " + hdesc +
            " slams into the tip with all your weight behind it. Trying to " +
            "scream but failing, you struggle with the shaft briefly, but " +
            "everything goes black.\n";
        msg3 = "You see " + target + " run towards " + mil + ", enemy plants " +
            player->query_possessive() + " " + wep + " firmly in the " +
            "ground. As " + target + " tries to stop, " + 
            enemy->query_pronoun() + " slips, falling with all of " +
            enemy->query_possessive() + " weight onto the tip, which is " +
            "completely driven through " + enemy->query_possessive() + " " +
            hdesc + ". " + capitalize(target) + " attempts to scream " +
            "but cannot, and struggles to remove the shaft for a moment " +
            "before collapsing.\n";

        player->catch_tell(msg1);
        enemy->catch_tell(msg2);
        player->tell_watcher(msg3, enemy);
        enemy->do_die(player);
    }
    else
    {
        switch (phurt)
    	{
        case -1..0:
            msg1 = "As " + target + " approaches, you point your " + wep +
                " towards " + enemy->query_possessive() + " " + hdesc +
                ", lower the butt of your " + wep + " to the ground, and " +
                "place your foot on it. " + capitalize(target) + " slows " +
                "down at the last moment, and avoids your blow.\n";
            msg2 = "As you approach " + mil + ", " +
                player->query_pronoun() + " lowers the butt of " +
                player->query_possessive() + " " + wep + " to the " +
                "ground and puts " + player->query_possessive() +
                " foot on it. You slow down at the last moment and avoid " +
                "the blow.\n";
            msg3 = "As " + target + " approaches " + mil + ", " +
                player->query_pronoun() + "lowers the butt of " +
                player->query_possessive() + " " + wep + " to the " +
                "ground and places " + player->query_possessive() +
                " foot on top of it. " + capitalize(target) + " slows " +
                "down at the last moment, and manages to avoid the blow.\n";
            break;
    
        case 1..9:
            msg1 = "As " + target + " approaches, you point your " + wep +
                " towards " + enemy->query_possessive() + " " + hdesc +
                ", lower the butt of your " + wep + " to the ground, and " +
                "place your foot on it. " + capitalize(target) + " slows " +
                "down at the last moment, and is dealt only a glancing " +
                "blow.\n";
            msg2 = "As you approach " + mil + ", " +
                player->query_pronoun() + " lowers the butt of " +
                player->query_possessive() + " " + wep + " to the " +
                "ground and puts " + player->query_possessive() +
                " foot on it. You slow down to avoid running into it, and " +
                "receive only a glancing blow on the " + hdesc + ".\n";
            msg3 = "As " + target + " approaches " + mil + ", " + 
                player->query_pronoun() + " lowers the butt of " + 
                player->query_possessive() + " " + wep + " to the " +
                "ground and places " + player->query_possessive() + 
                " foot on top of it. " + capitalize(target) + " slows " +
                "down at the last moment, and is dealt only a glancing blow " +
                "to the " + hdesc + ".\n";
            break;
    
        default:
            msg1 = "As " + target + " jogs towards you, you plant your " + wep +
                " firmly, and place your foot behind it to anchor it. " +
                "Aiming it straight at " + enemy->query_possessive() + " " + 
                hdesc + ", you feel " + 
                enemy->query_the_possessive_name(player) + " full weight slam " +
                "into the tip, and see that " + enemy->query_pronoun() + " has " +
                "received a deep and crippling wound.\n"; 
            msg2 = "As you jog towards " + mil + ", " + 
                player->query_pronoun() + " plants " + 
                player->query_possessive() + " " + wep + " firmly, places " +
                player->query_possessive() + " foot behind it, and aims it " +
                "straight at your " + hdesc + ". You are unable to stop in " +
                "time, and receive a crippling wound. Colours flash brightly " +
                "before your eyes as you look down and see the blood flowing " +
                "freely from your mangled " + hdesc + ".\n";
            msg3 = "As " + target + " jogs towards " + mil + ", " +
                player->query_pronoun() + " plants " +
                player->query_possessive() + " " + wep + " firmly, places " +
                player->query_possessive() + " foot behind it, and aims it " +
                "straight at " + enemy->query_the_possessive_name() + " " +
                hdesc + ". " + capitalize(target) + " struggles in vain to " +
                "stop in time, and runs " + enemy->query_possessive() + " " + 
                hdesc + " right into the end of the weapon. You " +
                "move back a step to avoid the blood jetting from " + 
                enemy->query_the_possessive_name() + " " + hdesc + ".\n";
            break;
    	}

        player->catch_tell(msg1);
        enemy->catch_tell(msg2);
        player->tell_watcher(msg3, enemy);

        clone_object(MIMPALE_OBJ)->move(enemy);
    }

    return;
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
    
    weapon = find_wep(actor, 1);
    if (objectp(weapon))
    {
        return ({ weapon });
    }
    
    return 0;  // Need to be wielding some sort of weapon
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
    
    if (player->query_skill(SS_MILITIA_IMPALE) < 1)
    {
        send_debug_message("impale", "No training in impale.");
        return 0;
    }

    if (!objectp(find_wep(player, 1)))
    {
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

    if (sizeof(targets) == 1)
    {
        if (objectp(targets[0]))
        {
            enemy = targets[0];
        }
        else if (pointerp(targets[0]))
        {
            enemy = targets[0][0];
        }
        else
        {
            return 0;
        }
    
        if (present("Militia_Impale_Object", enemy))
        {
            // If the impale object is already present in the enemy,
            // we can't impale them again.
            send_debug_message("impale", "Enemy already has impale object "
                             + "and can't impale again.");            
            return 0;
        }
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
    // Don't display any messages
}

/*
 * Function name: report_resolve_ability
 * Description:   Function called when the ability executes to allow
 *                masking and reporting and logging. By default, it
 *                simply sends the info via send_debug_message
 * Arguments:     pen    - the pen of the hit
 *                dt     - the damage type of the hit
 *                damage - the amount of damage dealt
 */
public void
report_resolve_ability(int pen, int dt, int damage)
{
    string name;
    
    if (interactive(this_player()))
    {
        name = capitalize(this_player()->query_real_name());
    }
    else
    {
        name = MASTER_OB(this_player());
    }

    send_debug_message("impale", this_interactive());   
    send_debug_message("impale", 
                    name + " impales with Pen of " + pen + ", "
                    + "Damage of " + damage,
                       IMPALE_LOG);
}

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
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
}

static void 
ability_msg(object actor,mixed * targets,string arg)
{
}
