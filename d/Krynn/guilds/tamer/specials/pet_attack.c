#pragma strict_types

inherit "/d/Genesis/specials/std/damage";

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

#include "../defs.h"
#include "/std/combat/combat.h"

#define FATIGUE_COST    3

// Prototypes
public void             config_ability();
public void             special_did_hit(int aid, string hdesc, int hid, 
                                        int phurt, object enemy, int dt, 
                                        int phit, int dam, mixed * items,
                                        int result);
static int              check_valid_action(object player, mixed * targets, 
                                           string arg, int execute);
public void             apply_costs_to_player(object player);
public int              force_fail(object player, mixed * items, 
                                   object enemy, int resist, int result);

// Global Variables
static mapping      gPetSpecial = ([]);
                                   
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
    set_combat_aid(50);
    set_tohit(95);
    /* Not affected by the players haste */
    set_ability_hasted(1);
    set_stats(({ SKILL_AVG, TS_STR, TS_DEX, TS_CON,
                            TS_INT, TS_WIS, TS_DIS, SKILL_END }) );
    set_ability_prep_time(2);
    set_ability_cooldown_time(5);
    set_ability_name("pet_attack");
    
    /* This skill is checked in the pet, not the player */
    set_skills(({ SKILL_WEIGHT, 200, SS_MOUNTED_COMBAT }) );
    set_guild_stat_modifier(SS_LAYMAN, 100, 1);        
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
    string name, logfile;
    
    if (interactive(this_player()))
    {
        name = capitalize(this_player()->query_real_name());
    }
    else
    {
        name = MASTER_OB(this_player());
    }
    
    logfile = FILE_PATH(MASTER_OB(this_object()));
    logfile += short() + "_damage";
    logfile = implode(explode(logfile, " "), "");
    
    send_debug_message(short(), name + " hits with Pen of "
        + pen + ", " + "Damage of " + damage, logfile);
} /* report_resolve_ability */

public void
restart_npc_special(object player, string arg)
{
    if (player->query_attack())
        player->command("attack");
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
                int dam, mixed *items, int result)
{
    object  player;
    string  damage, hit_desc, loc_desc, room_desc, enemy_desc, tamer;
    mapping specials;
    int     matur, skill, dam_mod;
    
    dam_mod = (this_player()->query_driver() ? 60 : 100);
    if (query_combat_aid_modifier() < dam_mod && !random(10))
        tell_room(environment(this_player()), QCTPNAME(this_player()) + " "
        + "movement appears limited by injuries.\n", ({ this_player() }),
        this_player());
    
    specials = GENUS->query_special_attack(this_player()->query_genus())[dt];
    hit_desc = one_of_list(m_indexes(specials));
    loc_desc = one_of_list(specials[hit_desc]);
    
    m_delkey(gPetSpecial[this_player()], "type");
    
    switch(enemy->query_max_hp() / max(dam, 1))
    {
        case 0..5:
            damage = one_of_list(([
                W_BLUDGEON : ({
                    "nearly shattering",
                    "crushing down upon"
                }),
                W_SLASH : ({
                    "leaving a gaping wound in",
                    "maiming"
                }),
                W_IMPALE : ({
                    "leaving a gaping wound in",
                    "maiming"
                }),
            ])[dt]);
            break;
        case 6..20:
            damage = one_of_list(([
                W_BLUDGEON : ({
                    "causing a devastating injury on",
                    "leaving a horrific injury in"
                }),
                W_SLASH : ({
                    "causing a devastating injury on",
                    "leaving a horrific injury in"
                }),
                W_IMPALE : ({
                    "causing a devastating injury on",
                    "leaving a horrific injury in"
                }),
            ])[dt]);
            break;
        case 21..50:
            damage = one_of_list(([
                W_BLUDGEON : ({
                    "greatly wounding",
                    "dealing severe bruises to"
                }),
                W_SLASH : ({
                    "greatly wounding",
                    "dealing a severe laceration to"
                }),
                W_IMPALE : ({
                    "greatly wounding",
                    "leaving a gaping wound in"
                }),
            ])[dt]);
            break;
        case 51..100:
            damage = one_of_list(([
                W_BLUDGEON : ({
                    "causing harm to",
                    "leaving painful bruises on"
                }),
                W_SLASH : ({
                    "causing harm to",
                    "leaving deep lacerations on"
                }),
                W_IMPALE : ({
                    "causing harm to",
                    "injuring"
                }),
            ])[dt]);
            break;
        case 101..150:
            damage = one_of_list(([
                W_BLUDGEON : ({
                    "visibly injuring",
                    "inflicting bruises on"
                }),
                W_SLASH : ({
                    "visibly injuring",
                    "visibly lacerating"
                }),
                W_IMPALE : ({
                    "visibly injuring",
                    "inflicting wounds in"
                }),
            ])[dt]);
            break;
        case 151..250:
            damage = one_of_list(([
                W_BLUDGEON : ({
                    "doing some harm to",
                    "inflicting minor bruises on"
                }),
                W_SLASH : ({
                    "doing some harm to",
                    "inflicting minor lacerations"
                }),
                W_IMPALE : ({
                    "doing some harm to",
                    "inflicting minor wounds in"
                }),
            ])[dt]);
            break;
        case 251..400:
            damage = one_of_list(([
                W_BLUDGEON : ({
                    "doing minor damage to",
                    "inflicting minor bruises on"
                }),
                W_SLASH : ({
                    "doing minor damage to",
                    "inflicting minor lacerations on"
                }),
                W_IMPALE : ({
                    "doing minor damage to",
                    "inflicting minor wounds in"
                }),
            ])[dt]);
            break;
        case 401..500:
            damage = one_of_list(([
                W_BLUDGEON : ({
                    "just glancing off",
                    "causing little harm to",
                    "doing little damage to"
                }),
                W_SLASH : ({
                    "just glancing off",
                    "causing little harm to",
                    "doing little damage to"
                }),
                W_IMPALE : ({
                    "just glancing off",
                    "causing little harm to",
                    "doing little damage to"
                }),
            ])[dt]);
            break;
        default:
            damage = one_of_list(([
                W_BLUDGEON : ({ 
                    "leaving without as much as a bruise on",
                    "just glancing off",
                    "causing minor discomfort to"
                }),
                W_SLASH : ({ 
                    "leaving without as much as a nick on",
                    "just glancing off",
                    "causing minor discomfort to"
                }),
                W_IMPALE : ({ 
                    "leaving without as much as a wound on",
                    "just glancing off",
                    "causing minor discomfort to"
                }),
            ])[dt]);
            break;
    }
    
    if (!dam) {
        damage = one_of_list(({
            "doing little to no damage to",
            "not even leaving a mark to",
        }));
        
        /* Chance to increase pet skill on failed attack */
        skill = this_player()->query_skill(SS_MOUNTED_COMBAT);
        matur = this_player()->query_maturity();
        
        if (!random(SUCCESS(skill, matur)))
            this_player()->do_skill_raise(SS_MOUNTED_COMBAT, this_player());
    }
    
    switch(hit_desc)
    {
        case "test":
            break;
            
        default:
        room_desc = QCTNAME(this_player()) + " " + hit_desc + " " +
        QTNAME(enemy) + " with " + this_player()->query_possessive() +
        " " + loc_desc + ", " + damage + " " + enemy->query_possessive() +
        " " + hdesc + ".\n";
        
        enemy_desc = QCTNAME(this_player()) + " " + hit_desc + " you with " +
        this_player()->query_possessive() + " " + loc_desc + ", " + damage +
        " your " + hdesc + ".\n";
            break;
    }
    
    this_player()->tell_watcher(room_desc, enemy, this_player());
    enemy->catch_msg(enemy_desc);
    
    if (enemy->query_hp() < 1)
    {
        if (stringp(tamer = this_player()->query_tamer_name()) &&
            objectp(player = find_player(tamer)) &&
            present(player, environment(this_player())))
            enemy->do_die(player);
        else
            enemy->do_die(this_player());
    }
    
    return;
}


/*
 * Function:    check_required_items
 * Description: Returns the weapon that will be used in the attack
 */
static mixed * 
check_required_items(object actor,mixed * targets,
                     string arg,int pretest)
{
    object weapon, tamer;
    
    // Verify that there is a set tamer.
    if (!objectp(tamer = find_player(actor->query_tamer_name())))
        return ({});
    
    // Prefer the use of pet weapon
    if (!objectp(weapon = MANAGER->query_pet_weapon(tamer)))
        weapon = query_best_wielded_weapon(tamer);
    
    // If the weapon is worse than 40 or not available,
    // we go ahead and just use 40.
    if (!objectp(weapon) || weapon->query_pen() < 40)
        return ({ });
    
    return ({ weapon });
} /* check_required_items */

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
    
    if (player->query_unconscious())
        return 0;
    
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
        return 0;

    // If it passes everything, return success
    return 1; 
} /* check_valid_action */

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
        return 1;

    return 0;
} /* force_fail */

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
} /* hook_stopped_ability */


/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void
hook_special_complete()
{
    write("Time to attack again!\n");
} /* hook_special_complete */

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
    write("The target of your attack seems to have slipped away.\n");    
    hook_special_complete();
} /* hook_targets_gone */


/*
 * Function name: ability_msg
 * Description:   Displays the ability message, pointless to an NPC really.
 */
static void 
ability_msg(object actor, mixed * targets, string arg)
{
    object target;
    
    if (sizeof(targets) > 0)
    {
        target = targets[0];
        actor->catch_msg("You prepare to attack.\n");
    }
} /* ability_msg */

/*
 * Function name: hook_attack_object
 * Description:   Displays the attack hook, pointless to an NPC.
 */
public void
hook_attack_object(object ob)
{
    object player;
    
    player = this_player();
    if(!player->query_attack())
    {
        write("You charge!\n");
    }
    else
    {
        ::hook_attack_object(ob);
    }
} /* hook_attack_object */

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
    int fatigue_cost;
    
    fatigue_cost = max(1, (FATIGUE_COST * player->query_stat(SS_CON)) /
                   player->query_stat(SS_DEX));
    
    if (player->query_fatigue() > fatigue_cost)
    {
        /* Reduce pet fatigue value */
        player->add_fatigue(-fatigue_cost);
        return;
    }
    
    /* Reduce health if fatigue is too low */
    fatigue_cost -= player->query_fatigue();
    player->set_fatigue(0);
    player->heal_hp(-(fatigue_cost * 2));
    player->tell_watcher("The strain of the attack appears draining to "
    + QTNAME(player) + ".\n");
} /* apply_costs_to_player */

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
    int modifier, health, max_health, p_health;
    
    modifier = 100;
    
    this_player()->update_injury();
    
    /* Reduce modifier by 10 for each wound */
    modifier -= (m_sizeof(this_player()->query_injury()) * 10);
    
    if (objectp(this_player()->query_tamer()))
        p_health = this_player()->query_tamer()->query_max_hp();
    else 
        p_health = this_player()->query_max_hp();
    
    health = this_player()->query_hp();
    max_health = this_player()->query_max_hp();
    
    /* Reduce damage done if the pet is damaged, due to it being able to tank */
    if (health < max_health)
        modifier -= (((max_health - health) * 100) / max(1, p_health)) * 2;
    
    return max(1, min(100, modifier));
} /* query_combat_aid_modifier */

/*
 * Function name: query_dt
 * Description  : Checks the weapons and returns the weapon type
 * Arguments    : items - array of required items. Typically only be one
 *                        weapon in the array
 * Returns      : the damage type
 */
public int
query_dt(object * items)
{
    mapping special_dt;
    string  genus = this_player()->query_genus();
    
    if (!mappingp(gPetSpecial[this_player()]))
        gPetSpecial[this_player()] = ([]);
    
    // Set and retains a random damage type
    if (!IN_ARRAY("type", m_indexes(gPetSpecial[this_player()])))
    {
        special_dt = GENUS->query_special_attack(genus);
        gPetSpecial[this_player()]["type"] = one_of_list(m_indexes(special_dt));
    }
    
    return gPetSpecial[this_player()]["type"];
} /* query_dt */