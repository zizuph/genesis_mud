/*
 * Backstab
 *
 * This is the new backstab ability using the new special system base. With
 * the recode of the ability, a few changes have naturally occured.
 *
 * The ability can be used when the actor is not seen, or has OBJ_I_HIDE, the
 * ability is also usable in combat if the actor is not being attacked by the
 * present enemies.
 * 
 * The ability is set to 100 caid. If the actor is seen by the target, the 
 * ability caid is lowered ((backstab_skill * 59) / 100). The caid after being
 * lowered by the check_seen modification should be at 59, if the backstab
 * skill is at 100. 
 *
 * The ability prep time is 3 seconds and cooldown is 27, totaling 30 seconds.
 * If the ability is used while already in combat, the prep time of the ability
 * is set to (prep_time * 3) and cooldown is reduced by the same amount,
 * cooldown -= prep_time * 2. This is so as to keep the ability at 30 seconds.
 *
 * The ability has a message displayed 1 second before execution, indicating
 * that the actor is sneaking up on the victim, this is only showed to any
 * present living that can see the actor and manages a difficult resolve_task
 * checking the victims TS_INT and SS_AWARENESS against the actors TS_DEX and
 * SS_SNEAK. If attacked during this inverval, this will interrupt the ability.
 *
 * The ability always attempts to hit the body of the target, masking the hdesc
 * to back. The changing of the hitloc calls the hitloc factor, which has been
 * masked to 100%, as the ability is not targettable and if for some reason the
 * targetting fails, we dont want the ability to scale in caid.
 *
 * To keep the old backstab feature of having a chance of delivering poisons,
 * this ability triggers cb_did_hit on a successful backstab, this also handles
 * the damage description of the ability. This could potentially increase the
 * damage of the special, if the weapon used to backstab with has an added 
 * damage modifier to its did_hit. To balance this the did_hit damage indicator
 * is reduced with the following formula:
 *
 * (dam * min(30, query_combat_aid_modifier) / query_combat_aid_modifier)
 * Which should keep it around a normal hits damage.
 *
 * Created by Carnak at 2017-10-09.
 *
 * In determining how much combat aid benefit should be considered towards a
 * thief guild's combat aid cap, we use the "non-surprise" combat aid applied,
 * which is 59% of set_combat_aid. For a guild with 100 skill in backstab, the
 * combat aid applied towards their cap of 100 would be 59.
 *
 * The backstab special is treated as an occupational thief special, so layman 
 * thief guilds may train up to level 60 (as outlined in 
 * /d/Genesis/doc/rules/wizard/guilds/skills), which equates to 35 combat aid
 * towards their cap of 50 according to the above formula.
 *
 * Balance commentary by Arman at 2017-10-25.
 *
 * 2019-05-24 - Carnak:
 *      Added a relay to allow for masking of this ability, if the player has
 *      another backstab ability this will use that instead. If there are more
 *      than one ability, one will be chosen at random. It only relays if the
 *      ability name matches ("backstab")
 *      The added functions are 'do_ability' and 'query_backstab_abilities'
 *
 * 2019-06-12 - Carnak:
 *      Changed the formula for how damage is passed to the cb_did_hit, it did
 *      more damage than intended with weapons like molten-bladed when the caid
 *      was upped for fire knives guild, also added a log to track it.
 *
 * 2020-06-14 - Carnak:
 *      Made the special MAGIC_DT and added the function query_armour_penetration
 *      to make it ignore shields.
 * 2022-02-23 - Zizuph:
 *      Applied a 4/5 modifier to the damage to account for the dice roll
 *      difference between MAGIC_DT and non-magic hit_mes.
 * 2022-02-27 - Zizuph:
 *      Remove shield AC bypass from all but the first backstab.
 *      
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/damage";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#include <math.h>
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
#include <stdproperties.h>
#include <cmdparse.h>

#include "/std/combat/combat.h"

// Defines
#define ALERT_TO_AMBUSH_ATTACKS     "_alert_to_ambush_attacks"
#define B_TIME_LIMIT                300

// Prototypes
public void             config_ability();
public void             special_did_hit(int aid, string hdesc, int hid, 
                                        int phurt, object enemy, int dt, 
                                        int phit, int dam, mixed *items,
                                        int result);
static int              check_valid_action(object player, mixed *targets, 
                                           string arg, int execute);
public status           actor_was_seen(object actor, object target);
public object          *query_knives(object actor);
public mixed           *target_backstab_loc(object actor, string arg);

public int              query_armour_penetration(int wcpen, int dt,
                        object attacker, object target, int hid, object *items);


// Global Variables
public mapping          specified_knife = ([]),
                        hidden_modifier = ([]);

/*
 * Function name:   report_backstab_damage
 * Description:     Function called from the backstab_did_hit to log the damage
 *                  potentially done by weapon specials.
 * Arguments:       pen    - the pen of the hit
 *                dt     - the damage type of the hit
 *                damage - the amount of damage dealt
 */
public void
report_backstab_damage(object player, object enemy, int pen, int damage,
                       int new_damage)
{
    string  name, logfile;
    
    if (interactive(this_player()))
        name = capitalize(player->query_real_name());
    else
        name = MASTER_OB(player);
    
    logfile = FILE_PATH(MASTER_OB(this_object()));
    logfile += short() + "_weapon_damage";
    logfile = implode(explode(logfile, " "), "");
    
    send_debug_message(short(), name + " hits with Pen of " + pen + ", "
    + "potential Damage of " + new_damage + " when Special damage was "
    + damage, logfile);
} /* report_backstab_damage */


/*
 * Function name: hook_attack_object
 * Description  : Mask the attack description to hide it.
 */
public void
hook_attack_object(object ob)
{
    // Don't display any messages
} /* hook_attack_object */

/*
 * Function name:   hook_special_in_cooldown
 * Description:     This hook prints a message if the ability is in cooldown.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_in_cooldown()
{
    this_player()->catch_msg("You're not ready to backstab again.\n");
} /* hook_special_in_cooldown */

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void
hook_special_complete()
{
    this_player()->catch_msg("You feel ready to perform another backstab.\n");
} /* hook_special_complete */

/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the actor when
 *                the targets has disappeared during the prepartion of the
 *                ability.
 * Returns:       The message to print
 */
public void
hook_targets_gone(object *targets)
{
    this_player()->catch_msg("Your target appears to have slipped away.\n");
} /* hook_targets_gone */

/*
 * Function name:   hook_special_preparation_complete
 * Description:     This is a hook that prints a message if the preparation is
 *                  complete.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_preparation_complete()
{
    // Don't display any messages
} /* hook_special_preparation_complete */

/*
 * Function name:   hook_already_active
 * Description:     This hook prints a message if the ability is already active.
 * Arguments:       (object) ability - The active ability
 * Returns:         Nothing
 */
public void
hook_already_active(object ability)
{
    this_player()->catch_msg("You are already preparing a backstab.\n");
} /* hook_already_active */

/*
 * Function name:   hook_interim_message
 * Description:     This is a hook that prints an interim message.
 * Arguments:       (object) actor - The actor performing the backstab
 * Returns:         Nothing
 */
public void
hook_interim_message(object actor, mixed targets)
{
    object *hidden, *nearby;
    mixed   target;
    nearby = filter(all_inventory(environment(actor)), &living());
    hidden = filter(nearby, &actor_was_seen(actor,));
    
    if (pointerp(target = targets[0]) && !objectp(target = targets[0][0]))
        return;
    
    if (!objectp(target) || environment(actor) != environment(target))
        return;
    
    actor->catch_msg("You "
    + (objectp(actor->query_attack()) ? "circle around" : "sneak up behind")
    + " " + QTNAME(target) + ".\n");
    
    if (!sizeof(hidden -= ({ actor })))
        return;
    
    foreach(object ob: hidden)
    {
        ob->add_prop(ALERT_TO_AMBUSH_ATTACKS, time());
        
        if (ob != target)
        {
            ob->catch_msg(QCTNAME(actor) + " "
            + (objectp(actor->query_attack()) ? "circles around" : "sneaks up "
            + "behind") + " " + QTNAME(target) + ".\n");
            continue;
        }
        
        target->catch_msg("You catch a glimpse of something moving in the "
        + "corner of your eye, noticing " + QTNAME(actor) + " attempting to "
        + (objectp(actor->query_attack()) ? "circle around" : "sneak up behind")
        + " you.\n");
    }
} /* interim_message */

/*
 * Function name: config_ability
 * Description  : Main fuction that configures what the special
 *                should look like. Set basic things like combat
 *                aid and the skills to be used for calculating
 *                damage and of course, the name.
 * Arguments    : None
 * Returns      : Nothing
 */
public void 
config_ability()
{
    ::config_ability();
    set_combat_aid(100);
    set_tohit(110); // 90% hit chance
    set_dt(MAGIC_DT);
    set_stats( ({ SKILL_WEIGHT, 51, TS_DEX, SKILL_WEIGHT, 34, TS_STR, 
                  SKILL_WEIGHT, 15, TS_INT }) );
    set_skills( ({ SS_BACKSTAB }) );
    set_ability_prep_time(3);
    set_ability_cooldown_time(27);
    set_ability_name("backstab");
    set_ability_target(target_backstab_loc);
    set_ability_armour_penetration(query_armour_penetration);
    
    /*
     * The ability does ofcourse not attack during prep or reveal, as it would
     * interrupt the ability.
     */
    set_ability_attack_during_prep(0);
    set_ability_no_reveal(1);
    
    /*
     * The guild_stat_modifier has been set to SS_OCCUP 100, 1 so the ability
     * is always at 100% and not lowered by the modifier.
     */
    set_guild_stat_modifier(SS_OCCUP, 100, 1);
} /* config_ability */

/*
 * Function name:   backstab_did_hit
 * Description:     Mask this function to process when the special scores.
 *                  Descriptions seen by everyone are set here.
 * Arguments:       1. (int) aid   - attack id
 *                  2. (string) hdesc - hit description
 *                  3. (int) hid   - 
 *                  4. (int) phurt - extent of damage
 *                  5. (object) enemy - person being hit by special
 *                  6. (int) dt    - damage type
 *                  7. (int) phit  - 
 *                  8. (int) dam   - damage amount
 *                  9. (mixed *) items - 
 *                  10. (int) result - result of cb_tohit
 * Returns:         Nothing
 */
public varargs void
backstab_did_hit(int aid, string hdesc, int hid, int phurt, object enemy,
                 int dt, int phit, int dam, mixed *items, int result)
{
    object  knife;
    string  stab_desc;
    
    /*
     * Pick the best weapon in the array, or first knife in array if the 
     * best wielded weapon isnt a knife.
     */
    if (!objectp(knife = query_best_wielded_weapon(this_player())) ||
        !IN_ARRAY(knife, items))
        knife = items[0];
    
    /* Miss the attack */
    if (dam < 1)
    {
        this_player()->catch_msg("You lunge at " + QTNAME(enemy) + " with your "
        + knife->short() + ", but miss and reveal your intent!\n");
        this_player()->tell_watcher(QCTNAME(this_player()) + " lunges at "
        + QTNAME(enemy) + " from behind, but misses.\n", enemy);
        enemy->catch_msg(QCTNAME(this_player()) + " lunges at you from behind, "
        + "but misses.\n");
        
        return;
    }

    switch(phurt)
    {
    	case 0..5:
            stab_desc = " weakly";
            break;
        case 6..49:
            stab_desc = "";
            break;
        case 50..75:
            stab_desc = " forcefully";
            break;
        case 76..99:
            stab_desc = " deeply";
            break;
        default:
            stab_desc = " fatally";
    }
    
    this_player()->catch_msg("You move in close behind " + QTNAME(enemy) + " "
    + "and thrust your " + knife->short() +stab_desc+ " into " 
    + enemy->query_possessive() + " back.\n");
    
    this_player()->tell_watcher(QCTNAME(this_player()) + " moves in close "
    + "behind " + QTNAME(enemy) + " and thrusts "
    + LANG_ADDART(knife->short()) +stab_desc+ " into " + enemy->query_possessive()
    + " back.\n", enemy);
    
    enemy->catch_msg("You react too late as " + QTNAME(this_player()) + " "
    + "thrusts " + LANG_ADDART(knife->short()) +stab_desc+ " into your back.\n");

    if (hidden_modifier[this_player()])
        this_player()->catch_msg(QCTNAME(enemy) + " is caught unaware and is "
        + "unable to defend against the surprise assault.\n");
    
    /* If the target dies, we trigger an original message instead of did_hit */
    if(enemy->query_hp() <= 0)
    {
        if(enemy->query_prop(LIVE_I_UNDEAD)) 
        {
            enemy->tell_watcher("The " + knife->short() + " stabs deeply "
            + "into " + QTPNAME(enemy) + " back, unravelling " + enemy->query_possessive() 
            + " undead existence and returning " + enemy->query_objective() + " to being "
            + "truly dead.\n");
            enemy->catch_msg("The " + knife->short() + " stabs deeply into your "
            + "back, unravelling your undead existence and leaving you truly dead.\n");
        }
        else if (enemy->query_humanoid())
        {
            enemy->tell_watcher("The " + knife->short() + " stabs deeply "
            + "into " + QTPNAME(enemy) + " back and into " + enemy->query_possessive() 
            + " heart, killing " + enemy->query_objective() + " instantly.\n");
            enemy->catch_msg("The " + knife->short() + " stabs deeply into your "
            + "back, lodging itself into your heart and killing you instantly.\n");
        }
        else
        {
            enemy->tell_watcher("The " + knife->short() + " stabs deeply "
            + "into " + QTPNAME(enemy) + " back, killing " + enemy->query_objective() 
            + " instantly.\n");
            enemy->catch_msg("The " + knife->short() + " stabs deeply into your "
            + "back, killing you instantly.\n");
        }
    }
} /* backstab_did_hit */

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
public varargs nomask void
special_did_hit(int aid, string hdesc, int hid, int phurt, object enemy,
                int dt, int phit, int dam, mixed *items, int result)
{
    object knife, cmbt;

    /*
     * Pick the best weapon in the array, or first knife in array if the 
     * best wielded weapon isnt a knife.
     */
    if (!objectp(knife = query_best_wielded_weapon(this_player())) ||
        !IN_ARRAY(knife, items))
        knife = items[0];

    cmbt = this_player()->query_combat_object();

    enemy->add_prop(ALERT_TO_AMBUSH_ATTACKS, time());
    
    backstab_did_hit(aid, hdesc, hid, phurt, enemy, dt, phit, dam, items, result);
    
    if (enemy->query_hp() <= 0)
        return enemy->do_die(this_player());
    
    /*
     * Trigger a did_hit message with the weapon, this handles application of
     * poison in poisonous daggers.
     */
    foreach(int id: cmbt->query_attack_id())
    {
        if (!IN_ARRAY(knife, cmbt->query_attack(id)))
            continue;
        
        int max_dmg, prc_dmg, wep_dmg, wep_pen, wep_lev, stat_mod;
        
        /*
         * This damage is calculated from the percentual success of the special
         * and the F_PENMOD on weapons and knife skill. Keep in mind, this does
         * not add damage unless the backstab weapons themselves have a special
         * that is applied in such a way. 
         */
        
        max_dmg = calculate_damage(this_player(), enemy, items, 0, result);
        prc_dmg = dam * 100 / max_dmg;
        wep_pen = calc_base_pen(items);
        wep_lev = this_player()->query_skill(SS_WEP_KNIFE);
        wep_dmg = F_PENMOD(wep_pen, wep_lev) * prc_dmg / 100;
        stat_mod = calc_stat_modifier();
        wep_dmg = wep_dmg * F_STR_FACTOR(stat_mod) / 100;
        
        if (wep_dmg < 1)
            continue;
        
        report_backstab_damage(this_player(), enemy, wep_pen, dam, wep_dmg);
        cmbt->cb_did_hit(id, "back", hid, phurt, enemy, dt, phit, wep_dmg);
    }
} /* special_did_hit */

/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure that the thief has the
 *                necessary weapons.
 * Returns      : items that are required.
 */
static mixed * 
check_required_items(object actor, mixed *targets, string arg, int pretest)
{
    mixed   weapon;
    
    /* Prioritize specified knife */
    if (!(member_array(actor, m_indexes(specified_knife)) > -1 &&
        objectp(weapon = specified_knife[actor])) &&
        !sizeof(weapon = query_knives(actor)))
    {
        actor->catch_msg("You lack the proper weapon to perform a backstab.\n");
        return 0;
    }
    
    if (!pointerp(weapon))
        weapon = ({ weapon });
    
    if (!sizeof(weapon = filter(weapon, &operator(&)(,W_IMPALE) @
        &->query_dt())))
    {
        actor->catch_msg("You require a knife suitable to impale with to "
        + "perform a backstab.\n");
        return 0;
    }
    
    if (sizeof(weapon) > 1)
        weapon = ({ query_best_wielded_weapon(actor) });
    
    return weapon;
} /* check_required_items */

/*
 * Function name: validate_requirements
 * Description  : Function to check all the prerequisites
 *                These checks are used in both check_valid_action
 *                as well as force fail. (before start, and before
 *                execute)
 * Arguments    : actor - person executing the special
 * Returns      : 0/1 - invalid/valid conditions
 */
public int
validate_requirements(object actor, mixed targets)
{
    object *onslaught, tank;
    mixed   enemy;
    
    onslaught = filter(all_inventory(environment(actor)),
                &operator(==)(, actor) @ &->query_attack());
    
    if (actor->query_skill(SS_BACKSTAB) < 1)
    {
        actor->catch_msg("You lack the proper knowledge to backstab "
        + "someone.\n");
        return 0;
    }
    
    if (!pointerp(enemy = targets[0]) || objectp(enemy = enemy[0]))
        tank = enemy->query_attack();
    
    if (!objectp(tank) && (!actor->query_prop(OBJ_I_HIDE) &&
        actor->check_seen(enemy)))
    {
        actor->catch_msg("You must be hidden in order to backstab someone.\n");
        return 0;
    }
    
    /* 
     * Display a different message if the target is attacking you rather than
     * if you are under attack by other enemies.
     */
    if (objectp(tank) && tank == actor)
    {
        actor->catch_msg(QCTNAME(enemy) + " is too focused on you for you to "
        + "be able to perform a backstab.\n");
        return 0;
    }
    
    if (sizeof(onslaught))
    {
        actor->catch_msg("You are too occupied with the onslaught of "
        + COMPOSITE_LIVE(onslaught) + " to perform a backstab.\n");
        return 0;
    }
    
    /* Reset the hidden modifier */
    hidden_modifier[actor] = 0;
    
    /* If the target isnt seen, set hidden_modifier to 1
     *
     * Limited the backstab bonus to once every five minutes on each target.
     */
    if ((time() - enemy->query_prop(ALERT_TO_AMBUSH_ATTACKS) > B_TIME_LIMIT) &&
        (!actor->check_seen(enemy) || (actor->query_prop(OBJ_I_HIDE) > 30)))
        hidden_modifier[actor] = 1;
    
    return 1;
} /* validate_requirements */

/*
 * Function name:   ability_msg
 * Description:     Handles the printing of the ability preparation.
 * Arguments:       None
 * Returns:         Nothing
 */
static void 
ability_msg(object actor, mixed *targets, string arg)
{
    mixed target;
    
    if (pointerp(targets[0]))
        target = targets[0][0];
    
    if (objectp(target) && actor->query_attack())
        actor->catch_msg("You look for an opportunity to backstab "
        + QTNAME(target) + ".\n");
    else
        actor->catch_msg("You prepare yourself to perform a backstab.\n");
} /* ability_msg */

/*
 * Function name:   actor_was_seen
 * Description:     The function determines if the actor was seen by the target.
 * Arguments:       (object) actor - The actor of the backstab
 *                  (object) target - A living object in the surroundings
 * Returns:         (status) 1 - was seen
 *                           0 - not seen
 */
public status
actor_was_seen(object actor, object target)
{
    int     result;
    
    result = target->resolve_task(TASK_DIFFICULT,   ({ SS_AWARENESS, TS_INT }),
                                  actor,            ({ SS_SNEAK,     TS_DEX }));
    
    return (actor->check_seen(target) && result > 0);
} /* actor_was_seen */

/*
 * Function:    notify_prep_time
 * Description: This is a hook that abilities can use to know how long
 *              the prep time is before execution. A common usage of
 *              this may be to provide interim messages for long
 *              delays.
 * Arguments:   prep_time - the time before preparation and execution
 * Returns:     nothing
 */
static void
notify_prep_time(float prep_time, object actor, mixed * targets)
{
    set_alarm(prep_time - 1.0, 0.0, &hook_interim_message(actor, targets));
} /* notify_prep_time */

/*
 * Function name:   query_combat_aid_modifier
 * Description:     Calculates the percentage of the maximum combat aid that
 *                  applies to the current situation
 * Returns:         number between 1 and 100
 */
public int
query_combat_aid_modifier()
{
    // Combat aid is the maximum provided by a special
    // The modifier is used in situations where the player
    // should not get the maximum combat aid.
    // Value should be between 1 and 100
    int modifier = 100;

    /* Lower the caid down to 59 if the target is seen. */
    if (!hidden_modifier[this_player()])
        modifier = 59;

    return modifier;
} /* query_combat_aid_modifier */

/*
 * Function name:   check_valid_action
 * Description:     Perform ability-specific checks
 * Arguments:       1. (object) The player
 *                  2. (mixed *) The targets
 *                  3. (string) Arguments passed to the command
 *                  4. (int) Actual spell execution
 * Returns:         (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object actor, mixed *targets, string arg, int execute)
{
    if (!validate_requirements(actor, targets))
        return 0;
    
    return 1;
} /* check_valid_action */

/*
 * Function name:   filter_knives
 * Description:     It checks if given object is a weapon and a knife.
 * Arguments:       (object) ob - The object to verify if it is a knife
 * Returns:         (status) 1 - Item is a knife
 *                  (status) 0 - Item is not a knife
 */
public status
filter_knives(object ob)
{
    return (IS_WEAPON_OBJECT(ob) && (ob->query_wt() == W_KNIFE));
} /* filter_knives */

/*
 * Function name:   query_knives
 * Description:     Process the actor for weapons matching the criteria
 * Arguments:       (object) actor - The actor of the special
 * Returns:         (object *) - An array of the wielded knives
 */
public object *
query_knives(object actor)
{
    mixed weapon;
    
    if (!pointerp(weapon = filter(actor->query_weapon(-1), &filter_knives())) ||
        !sizeof(weapon))
        return ({});
    
    return weapon;
} /* query_knives */

/*
 * Function name:   get_hitloc_id
 * Description:     Process the target combat object to get the hitloc id that
 *                  matches the specified location.
 * Arguments:       (object) target - The target in which to check for a hitloc
 *                  (string) location - The location for which to check
 * Returns:         (int) - The hitloc id of the specified location
 */
public int
get_hitloc_id(object target, string location)
{
    object   combat_ob;
    int     *hitloc_ids, position; 
    string  *hitloc_descs;
    
    if (!objectp(target))
        return -1;
    
    combat_ob    = target->query_combat_object();
    hitloc_ids   = combat_ob->query_hitloc_id();
    hitloc_descs = map(hitloc_ids, &operator([])(, HIT_DESC) @
                   &combat_ob->query_hitloc());
    position     = member_array(location,hitloc_descs);

    if (position < 0)
        return -1;

    return hitloc_ids[position];
} /* get_hitloc_id */

/*
 * Function name:   process_unspecified_targeting
 * Description:     Performs checks to verify that hitloc_id and enemy object
 *                  are both correct.
 * Returns:         (mixed *) An empty array or an array of arrays containing
 *                            the targets and desired hitloc
 */
private mixed *
process_unspecified_targeting(object actor, object enemy, string loc)
{   
    if (!objectp(enemy))
        return ({ });
    
    int hitloc_id = get_hitloc_id(enemy, loc);
    
    if (hitloc_id == -1)
        return ({ enemy });
    
    return ({ ({ enemy, hitloc_id }) });
} /* process_unspecified_targeting */

/*
 * Function name:   target_backstab_loc
 * Description:     This parses the attack arguments to select the weapon and
 *                  target used in the attack. It also sets the desired hitloc.
 * Returns:         (mixed *) An empty array or an array of arrays containing
 *                            the targets and desired hitloc
 */
public mixed *
target_backstab_loc(object actor, string arg)
{
    object *enemy, *weapons;
    string  target, weapon;
    
    if (strlen(arg) && sscanf(arg, "%s with %s", target, weapon) > 1)
        arg = target;
    
    if (!mappingp(specified_knife))
        specified_knife = ([]);
    
    if (member_array(actor, m_indexes(specified_knife)) > -1)
        m_delkey(specified_knife, actor);
    
    if (strlen(weapon))
    {
        if (!sizeof(weapons = FIND_STR_IN_OBJECT(weapon, this_player())) &&
            sizeof(FIND_STR_IN_OBJECT(weapon, environment(this_player()))))
        {
            actor->catch_msg("You must have the weapon in your possession to "
            + "be able to utilize it for a backstab.\n");
            return ({ });
        }
        
        if (!sizeof(weapons))
        {
            actor->catch_msg("Backstab whom with what?\n");
            return ({ });
        }
        
        if (!sizeof(weapons = filter(weapons, &operator(==)(this_player()) @
            &->query_wielded())))
        {
            actor->catch_msg("You must wield the weapon to be able to stab "
            + "someone in the back with it.\n");
            return ({ });
        }
        
        if (sizeof(weapons))
            specified_knife[actor] = weapons[0];
    }
    
    enemy = target_one_other_present_living_or_enemy(actor, arg);
    
    if (sizeof(enemy))
        return process_unspecified_targeting(actor, enemy[0], "body");
    
    return ({});
} /* target_backstab_loc */

/*
 * Function name:   query_hitloc_factor
 * Description:     This function applies the penalty for targeting a 
 *                  specific hitloc.
 * Returns:         Percentage of damage for targeted attacks
 */
public int
query_hitloc_factor()
{
    /* 
     * Set to 100 and lowered caid, did this to avoid changes in caid if the
     * body targetting fails for some reason. It is also not optional.
     */
    return 100;
} /* query_hitloc_factor */

/*
 * Function name:   query_ability_prep_time
 * Description:     Modifies the prep time based on if the player is in combat
 *                  or not.
 * Returns:         (int) - the new prep time
 */
public int
query_ability_prep_time()
{
    int prep_time = ::query_ability_prep_time();
    
    if (objectp(this_player()->query_attack()))
        prep_time *= 3;
    
    return prep_time;
} /* query_ability_prep_time */

/*
 * Function name:   query_ability_cooldown_time
 * Description:     Modifies the cooldown based on if the player is in combat
 *                  or not.
 * Returns:         (int) - the new cooldown time
 */
public int
query_ability_cooldown_time()
{
    int cooldown = ::query_ability_cooldown_time();
    
    if (objectp(this_player()->query_attack()))
        cooldown -= ::query_ability_prep_time() * 2;
    
    return cooldown;
} /* query_ability_cooldown_time */


/*
 * Function name:   query_backstab_abilities
 * Description:     Returns all masked backstab abilities on the target
 * Arguments:       (object) target - The one to check.
 * Returns:         (mapping) - An array of backstab abilities
 */
public object *
query_backstab_abilities(object target)
{
    object *abilities = ({ });
    
    object temporary_player = this_player();
    set_this_player(target);
    
    foreach (string soul : target->query_cmdsoul_list())
    {
        foreach(string index, string value: soul->query_ability_map())
        {
            string path = MASTER_OB(this_object());
            if (path == value)
                continue;
            
            object ability = find_object(value);
            if (member_array(path + ".c", inherit_list(ability)) > -1 &&
                ability->query_ability_name() == query_ability_name())
                abilities += ({ ability });
        }
    }
    
    set_this_player(temporary_player);
    return abilities;
} /* query_backstab_abilities */

/*
 * Function name:   query_armour_penetration
 * Description:     Alter the weapon class based on armour penetration.
 * Arguments:       (int) wcpen: Weapon class penetration
 *                  (int) dt: Damage type, MAGIC_DT if no ac helps
 *                  (object) attacker: The one who is attacking
 *                  (object) target: The target who is attacked
 *                  (int) hid: The hit location to damage
 *                  (object *) items: The items used to attack
 * Returns:         (int) The altered weapon class penetration
 */
public int
query_armour_penetration(int wcpen, int dt, object attacker, object target,
    int hid = -1, object *items = ({}))
{
    mixed  *hitloc;
    object  combat_obj;
    int     armour_class;
    
    combat_obj = target->query_combat_object();
    
    // Randomize the hitloc if something has gone wrong..
    if (member_array(hid, combat_obj->query_hitloc_id()) < 0)
        hid = one_of_list(combat_obj->query_hitloc_id());
    
    hitloc = combat_obj->query_hitloc(hid);
    
    // Lets go with the proper route to evaluate W_IMPALE array loc
    dt = MATH_FILE->quick_find_exp(W_IMPALE);
    armour_class = hitloc[HIT_AC][dt];
    

    // This benefit should apply to first strike only.    
    if (time() - target->query_prop(ALERT_TO_AMBUSH_ATTACKS) > B_TIME_LIMIT
        && hidden_modifier[attacker])
    {
    
        // Lets remove shields from the equation.
        foreach(object armour: hitloc[HIT_ARMOURS])
        {
            if (armour->query_at() != A_SHIELD)
                continue;
        
        
        
            int shield_ac = armour->query_ac();
        
            // Modify the shield ac to account for the damage type
            if (pointerp(armour->query_am()))
                shield_ac += armour->query_am()[dt];

            armour_class -= shield_ac;
        }
    }
    
    // Normalize the AC.
    armour_class = ftoi(F_AC_MOD(armour_class));
    
    // We are using MAGIC_DT, which has a different dice roll than
    // other weapons.
    // MAGIC_DT = (pen / 4) + random(pen/4) + random(pen/4) + random(pen/4)
    // Normal = random(pen / 4)+random(pen/4)+random(pen/4)+random(pen/4)
    // The average for MAGIC_DT = pen/4 + pen/8 + pen/8 + pen/8 = 5*pen/8.
    // The average for normal = pen/8 + pen/8 + pen/8 + pen/8 = 4*pen/8.
    // We apply a 4/5 factor to account for the dice.
    wcpen = wcpen * 4 / 5;
    
    return max(0, F_NEW_DAMAGE(wcpen, random(100), armour_class));
} /* query_armour_penetration */

/*
 * Function name:   do_ability
 * Description:     The main entry point for abilities, this has been masked to
 *                  allow others to alter this special.
 * Arguments:       (string) arg - the argument passed in for targeting
 * Returns:         (int) 0/1 - failure/success of the action
 */
public int 
do_ability(string arg)
{
    object *alternate = query_backstab_abilities(this_player());
    if (sizeof(alternate))
        return one_of_list(alternate)->do_ability(arg);
    
    return ::do_ability(arg);
}  /* do_ability */
