/*
 * Auto-Impale Attack that the RDA has.
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include "defs.h"
#include "/std/combat/combat.h"
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


inherit "/d/Genesis/specials/std/damage";
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public void             config_ability();
public void             special_did_hit(int aid, string hdesc, int hid, 
                                        int phurt, object enemy, int dt, 
                                        int phit, int dam, mixed * items,
                                        int result);
static int              check_valid_action(object player, mixed * targets, 
                                           string arg, int execute);

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
    set_combat_aid(5);
    set_tohit(110);
    set_dt(W_IMPALE);
    set_stats( ({ SKILL_WEIGHT, 40, TS_STR, SKILL_WEIGHT, 60, TS_DEX }));

    set_skills(({ SS_DRAGONARMY_ATTACK }) );
    // This is an instant attack with a cooldown time
    set_ability_prep_time(0);
    set_ability_cooldown_time(240);
    set_ability_name("autoimpale");
    
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
    object player;
    string msg0, msg1, msg2;
    
    player = this_player();
    string weapon = items[0]->short();
    
    if (phurt >= 0)
    {
        switch (dam)
        {
        case 0:
            msg0 = "At the last second, " + QTNAME(enemy) + " manages to "
                + "knock aside your " + weapon + ", avoiding a painful "
                + "injury.\n";
            msg1 = "At the last second, you manage to knock aside "
                + QTNAME(player) + "'s " + weapon + ", narrowly avoiding " 
                + "impaling yourself on it.\n";
            msg2 = "At the last second, " + QTNAME(enemy) + " manages to "
                + "knock aside " + QTNAME(player) + "'s " + weapon 
                + ", narrowly avoiding impaling " + HIM(enemy) 
                + "self on it.\n";
            break;
        case 1..150:
            msg0 = "As " + QTNAME(enemy) + " charges into battle, you "
                + "calmly thrust forward, impaling " + HIS(enemy)+ " " 
                + hdesc + " with your " + weapon + ".\n";
            msg1 = "As you charge into battle, " + QTNAME(player) 
                + " calmly thrusts forward with " + HIS(player)+ " " 
                + weapon + ", impaling your " +hdesc+ "!\n";
            msg2 = "As " + QTNAME(enemy) + " charges into battle, " 
                + QTNAME(player) + " calmly thrusts forward with " 
                + HIS(player)+ " " + weapon + ", impaling " + QTNAME(enemy)
                + "'s " + hdesc+ ". The blow seems to have shocked " 
                + QTNAME(enemy) + " into inaction.\n";
            break;
        case 151..300:
            msg0 = "You inwardly chuckle with dark amusement as " 
                + QTNAME(enemy) + " throws " + HIM(enemy) + "self forward "
                + "into battle, conveniently onto the end of your " + weapon
                + ". " + QCTNAME(enemy) + "'s eyes widen most "
                + "satisfactorily in pain and shock.\n";
            msg1 = "The dark amusement on " + QTNAME(player) + "'s face "
                + "warns you too late of the foolishness of your charge, "
                + "your " + hdesc + " being impaled deeply on " 
                + HIS(player) + " " + weapon + "!\n";
            msg2 = QCTNAME(enemy)+ "'s eyes widen in pain and shock, " 
                + HIS(enemy)+ " " + hdesc+ " impaled deeply on " 
                + QTNAME(player)+ "'s " + weapon + ".\n";
            break;
        default:
            msg0 = "In a blind charge, " + QTNAME(enemy) + " throws " 
                + HIM(enemy) + "self onto the end of your " + weapon + ", "
                + "impaling " + HIM(enemy) + "self badly and effectively "
                + "incapacitating " + HIM(enemy) + "self.\n";
            msg1 = "In a blind charge, you throw yourself upon " 
                + QTNAME(player) + ". Unfortunately for you, the attack "
                + "was anticipated, and you find yourself badly impaled "
                + "on the end of " + HIS(player) + " " + weapon + ".\n";
            msg2 = "In a blind charge, " + QTNAME(enemy) + " throws " 
                + HIM(enemy) + "self onto the end of " + QTNAME(player)
                + "'s " + weapon + ", impaling " + HIM(enemy)+ "self "
                + "badly, and effectively incapacitating " + HIM(enemy)
                + "self.\n";
        }        
    }
    else
    {
        msg0 = QCTNAME(enemy) + " avoids your attempts to impale " 
            + HIM(enemy) + ", entering into close combat with you!\n";
        msg1 = "You avoid " + QTNAME(player) + "'s attempts to impale "
            + "you, and enter into close combat with " + HIM(player)
            + "!\n";
        msg2 = QCTNAME(enemy) + " avoids " + QTNAME(player) + "'s "
            + "attempts to impale " + HIM(enemy)+ ", and the two enter into "
            + "close combat with each other!\n";
    }
    player->catch_msg(msg0);
    enemy->catch_msg(msg1);
    player->tell_watcher(msg2, enemy, ({ player, enemy }));
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_player());
        return;
    }

    // If the person survived and there was damage done, we add the 
    // stun object
    if (dam > 0)
    {
        object stun = clone_object(AUTOIMPALE_STUN);
        stun->move(enemy, 1);
        stun->start();                        
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
    object enemy, weapon;
    object * enemies;
    
    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }

    if (player->query_skill(SS_DRAGONARMY_ATTACK) < 1)
    {
        return 0;
    }

    weapon = query_wielded_weapon(player);
    if (!objectp(weapon))
    {
        return 0;
    }
    
    // If it passes everything, return success
    return 1; 
}

/*
 * Function name: hook_stopped_ability
 * Description:   Return the string that will be printed to the player when
 *                the ability is stopped, such as via spellcasting.
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
ability_msg(object actor, mixed * targets, string arg)
{
    object weapon, target;
    
    weapon = query_wielded_weapon(actor);
    target = targets[0];
    
    actor->catch_msg("You quickly turn the point of your " 
        + weapon->short() + " towards " + QTNAME(target) + ".\n");
    target->catch_msg(QCTNAME(actor) + " quickly turns the point of " 
        + actor->query_possessive() + " " + weapon->short()
        + " towards you.\n");
    actor->tell_watcher(QCTNAME(actor) + " quickly turns the point of " 
        + actor->query_possessive() + " " + weapon->short()
        + " towards " + QTNAME(target) + ".\n", target, 
        ({ actor, target }));
}
