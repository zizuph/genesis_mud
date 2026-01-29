/*
 * tsap special for the templars.
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/damage";

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include "/std/combat/combat.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

#include "../local.h"

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

public object *         target_can_tsap(object actor, string arg);


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
    set_combat_aid(2);
    set_skills(({ SS_GUILD_SAP_SKILL }) );
    set_stats(({SKILL_AVG, TS_STR, SKILL_END}));
    set_guild_stat_modifier(SS_LAYMAN, 20, 100);
    
    // When you tsap it takes 5 seconds to execute.
    // We have another timer that limits how often the player can do this one.
    set_ability_prep_time(5);
    set_ability_cooldown_time(SAP_RESET_TIME);

    //Bypass armour - can be used only one per fight.
    set_dt(MAGIC_DT);
    set_ability_name("tsap");
    set_ability_target(target_can_tsap);
    set_ability_stationary(1);
    set_ability_attack_during_prep(0);
    
    // Doesnt make sense for this ability to be hastened by dual wield.
    set_ability_dual_wield(0);
}

public void
hook_special_complete()
{
    write("You feel ready to tsap again.\n");
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
 *                target - person being hit by special
 *                dt    - damage type
 *                phit  - 
 *                dam   - damage amount
 * Returns      : nothing
 */
public void special_did_hit(int aid,
                            string hdesc,
                            int hid, 
                            int phurt,
                            object target,
                            int dt,
                            int phit, 
                            int dam,
                            mixed* items)
{
    string weapon_desc = items[0]->short();
    object attacker = this_player();
    mixed attack_message;
    
    setuid();
    seteuid(getuid());
    
    switch (phurt)
    {
        case 1..30:
            attack_message = ({
            "You quickly swing your "+weapon_desc+" through the air " +
                "and sap "+target->query_the_name(attacker)+
                " with it!\n",
            attacker->query_The_name(target)+ " quickly swings " +
                HIS(attacker) + " " +
                weapon_desc+" through the air, sapping "+
                "you painfully!\n",
            QCTNAME(attacker)+ " quickly swings "+
                HIS(attacker) + " " +
                weapon_desc+ 
                " through the air, sapping " +
                QTNAME(target)+" with it!\n"
            });
            break;
        case 31..75:
            attack_message = ({
            "You swing your "+weapon_desc+" in a vicious arc " +
                "and smack it against "+
                target->query_the_name(attacker)+"!\n",
            attacker->query_The_name(target)+ " swings " +
                HIS(attacker) + " " +
                weapon_desc+" in a vicious arc and smacks it "+
                "against you!\n",
            QCTNAME(attacker)+ " swings "+
                HIS(attacker) + " " +weapon_desc+" in a "+
                "vicious arc and smacks it against " +
                QTNAME(target)+"!\n"
            });
            break;
        case 76..99:
            attack_message = ({
            "With a mighty yell you swing your "+weapon_desc+
                " and smash it into "+
                target->query_the_name(attacker)+"!\n",
            attacker->query_The_name(target)+ " lets out a " +
                "mighty yell and smashes " +
                HIS(attacker) + " " + weapon_desc+
                " into you!\n",
            QCTNAME(attacker)+ " lets out a mighty yell and "+
                "smashes "+
                HIS(attacker) + " " +weapon_desc+" into "+
                QTNAME(target)+"!\n"
            });
            break;
        default:
            if (phurt <= 0)
            {
                attack_message = ({
                "You swing your "+weapon_desc+" wildly through the air "+
                "without hitting anything.\n",
                attacker->query_The_name(target)+ " swings " +
                    HIS(attacker) + " " +
                    weapon_desc+" wildly through the air, apparently "+
                    "in a bad attempt to hit you.\n",
                QCTNAME(attacker)+ " swings " +
                    HIS(attacker) + " " +
                    weapon_desc+" wildly "+
                    "through the air in a bad attempt at hitting "+
                    QTNAME(target)+".\n"
                });
                break;
            }
            
            attack_message = ({
            "With a mighty yell you swing your "+weapon_desc+
                " and smash it into "+
                target->query_the_name(attacker)+"!\n",
            attacker->query_The_name(target)+ " lets out a " +
                "mighty yell and smashes " +
                HIS(attacker) + " " + weapon_desc+
                " into you!\n",
            QCTNAME(attacker)+ " lets out a mighty yell and "+
                "smashes "+
                HIS(attacker) + " " +weapon_desc+" into "+
                QTNAME(target)+"!\n"
            });
    }
    
    /* message to the attacker */
    attacker->catch_tell(attack_message[0]);
    
    /* message to the target */
    target->catch_tell(attack_message[1]);
    
    /* message to onlookers */
    attacker->tell_watcher(attack_message[2], target);
    
    if ( phurt > 0)
    {
        object sapstunob;
        /* Add the stun effect 
         * Note that templars stun 50% of the time, its set in the stun object now.
         * So we haven't changed that part, just moved where the check is done.
         */
        sapstunob = clone_object(SAP_STUN_OB);
        sapstunob->set_effect_caster(attacker);
        sapstunob->set_effect_target(target);
        sapstunob->move(target, 1);
        sapstunob->start();
    }
    
    if (target->query_hp() <= 0)
    {
        target->do_die(attacker);
    }

    // Enemy get immune to another sap for a while.
    target->add_prop(GUILD_SAP_PROP, time());
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
check_valid_action(object player, mixed* targets, string arg, int execute)
{
    object enemy;

    if (!::check_valid_action(player,targets,arg,execute))
    {
        return 0;
    }

    /* 
     * If the player has no skill he cannot sap
     */ 
    if (!player->query_skill(SS_GUILD_SAP_SKILL)) 
    { 
        player->catch_tell("You are not skilled to sap anyone!\n");
        send_debug_message(VALIDATE, 
                           capitalize(player->query_real_name()) 
                         + " is not skilled in sapping.");
        return 0; 
    }

    // If it passes everything, return success
    return 1; 
}


/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure the player has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required.
 */
static mixed* 
check_required_items(object actor,
                     mixed* targets,
                     string str,
                     int pretest)
{
    object ob, weapon, *weapons, *obj, *oblist, sapob, testob;
    string how, weapon_desc;
    object *weaponlist;
    
    if (!strlen(str))
    {
        actor->catch_tell("Sap whom with what?\n");
        return 0;
    }
   
    object * others = 
        FILTER_LIVING_OBJECTS(all_inventory(environment(actor)));
    object * held = all_inventory(actor);
    if (!parse_command(str, others + held, 
            "[the] %l [with] %o", obj, weapon))
    {
        
        if (!parse_command(str, environment(actor),
            "[the] %l", obj))
        {
            actor->catch_tell("Sap whom with what?\n");
            return 0;
        }
        
        if (actor->query_weapon(W_RIGHT)) 
        {
            weapon = actor->query_weapon(W_RIGHT);
        } else if (weapon = actor->query_weapon(W_LEFT))
        {
            weapon = actor->query_weapon(W_LEFT);
        } else if (actor->query_weapon(W_BOTH))
        {
            weapon = actor->query_weapon(W_BOTH);
        } else 
        {
            actor->catch_tell("Sap whom with what?\n");
            return 0;
        }
    }
    
    ob = obj[1];
    /* Make sure we're not trying ourself (like with "attack human")*/
    if (actor == ob && (sizeof(obj) > 2) )
    {
        ob = obj[2];
    }
    else if (actor == ob)
    {
        actor->catch_tell("Sap whom with what?\n");
        return 0;
    }
    
    if (!weapon)
    {
        actor->catch_msg("Sap "+ob->query_the_name(actor)+" with what?\n");
        return 0;
    }
    
    if (!weapon->query_short())
    {
        weapon_desc = weapon->query_name();
    }
    else 
    {
        weapon_desc = weapon->query_short();
    }
    
    if (environment(weapon) != actor)
    {
        actor->catch_msg("You're not holding "+weapon_desc+"!\n");
        return 0;
    }
    
    if (weapon->query_prop(OBJ_I_WEIGHT) < 101)
    {
        actor->catch_msg("The "+weapon_desc+" is too light to use.\n");
        return 0;
    }
    
    if (weapon->query_prop(OBJ_I_VOLUME) < 50)
    {
        actor->catch_msg("The "+weapon_desc+" is too small to use.\n");
        return 0;
    }

    /* We can only sap something that isn't expecting it*/
    if (time() - ob->query_prop(GUILD_SAP_PROP) < SAP_IMMUNE_TIME)
    {
        actor->catch_msg(ob->query_The_name(actor)+" is alert to that sort of attack.\n");
        return 0;
    }
    return ({weapon});
}


static void ability_msg(object actor,mixed * targets,string arg)
{
    actor->catch_msg("You prepare to sap your target.\n");
}

public object*
target_can_tsap(object actor, string arg)
{
    string target, weapon;
    int matches = 0;
    
    if (strlen(arg) > 0)
    {
        matches = sscanf(arg, "%s with %s", target, weapon);
    }
    if (matches != 2)
    {
        target = arg;
    }
    
    object* results=
        target_one_other_present_living_or_enemy(actor, target);
    
    if (!sizeof(results))
    {
        return ({ });
    }

    if(actor->query_attack())
    {
        actor->catch_tell("You can't sap anything while in combat!\n");
        return ({});
    }

    foreach (object target : results)
    {
        if ((member_array(target, actor->query_enemy(-1)) != -1) ||
            (member_array(actor, target->query_enemy(-1)) != -1))
        {
            actor->catch_msg(capitalize(HE(target))+" is alert to that sort of attack.\n");
            return ({ });
        }

        if (target->query_prop(GUILD_SAP_PROP + SAP_IMMUNE_TIME) > time())
        {
            actor->catch_msg(capitalize(HE(target))+" is alert to that sort of attack.\n");
            return ({ });
        }
    }
    return results;
}





