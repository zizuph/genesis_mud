/*
 *  /d/Emerald/common/guild/aod/special_attacks.c
 *
 *  The special attack code for the Army of Darkness guild in Emerald.
 *
 *  Copyright (c) January 2007, by Cooper Sherry (Gorboth)
 *
 *  Modifications:
 *  - 2018-09-23 (Carnak) Special has been converted to the new system.
 *  - 2021-09-20 (Arman) Fixed typo.
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/damage";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <language.h>
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

#include "/d/Emerald/common/guild/aod/defs.h"

// Prototypes
public void             config_ability();
public void             special_did_hit(int aid, string hdesc, int hid, 
                                        int phurt, object enemy, int dt, 
                                        int phit, int dam, mixed *items,
                                        int result);
static int              check_valid_action(object player, mixed *enemies, 
                                           string arg, int execute);
public object          *query_clubs(object actor);

// Global Variables
static mapping  crush_alarm = ([]),
                kick_alarms = ([]),
                buttkicking = ([]);

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

/*
 * Function name:   hook_buttkick_cooldown
 * Description:     This hook prints a message when the buttkick ability comes
 *                  off cooldown.
 * Arguments:       (object) instigator - The one initiating the buttkick
 * Returns:         Nothing
 */
public void
hook_buttkick_cooldown(object instigator)
{
    if (objectp(instigator))
    {
        instigator->catch_msg("Your foot ... its back in shape! Butts must be "
        + "kicked!\n");
    }
} /* hook_buttkick_cooldown */

/*
 * Function name:   hook_buttkick_expire
 * Description:     This hook prints a message when the buttkick effect expires.
 * Arguments:       (object) instigator - The one initiating the buttkick
 * Returns:         Nothing
 */
public void
hook_buttkick_expire(object instigator)
{
    if (objectp(instigator))
    {
        instigator->catch_tell("Arrgh! Your foot is getting sore. Better let "
        + "it rest for a while. No more buttkicking for now.\n");
        tell_room(environment(instigator), QCTNAME(instigator) + " gives "
        + instigator->query_possessive() + " aching foot a break and brings "
        + "the buttkicking to a halt for now.\n", instigator);
    }
} /* hook_buttkick_expire */

/*
 * Function name: hook_stopped_ability
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_stopped_ability(object ability, object actor)
{
    if (calling_function(-1) != "execute_instant_special")
        actor->catch_msg("You stop preparing your " + ability->short() + ".\n");
} /* hook_stopped_ability */

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
    // Don't display any messages
} /* hook_special_in_cooldown */

/*
 * Function name:   hook_crush_complete
 * Description:     This gets called with a one second delay after the special
 *                  is ready again.
 * Arguments:       (object) actor - The actor of the ability
 * Returns:         Nothing
 */
public void
hook_crush_complete(object actor)
{
    if (query_ability_active(actor))
        return;
    
    actor->catch_tell("Hmmmmmmmmmmm ...It dawns on your tiny brain that you "
    + "could probably try for another crushing blow, if you haven't "
    + "already.\n");
} /* hook_crush_complete */

/*
 * Function name:   hook_special_complete
 * Description:     This gets called whenever the special is ready again.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_complete()
{
    crush_alarm[this_player()] = set_alarm(1.0, 0.0,
        &hook_crush_complete(this_player()));
} /* hook_special_complete */

/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the actor when
 *                the enemies has disappeared during the preparation of the
 *                ability.
 * Returns:       The message to print
 */
public void
hook_targets_gone(object *enemies)
{
    this_player()->catch_msg("You suddenly realize there is no one here to "
    + "crush. They must have slipped away!\n");
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
    this_player()->catch_msg("You are already preparing such an attack.\n");
} /* hook_already_active */

/*
 * Function name:   config_ability
 * Description:     Main fuction that configures what the special should look
 *                  like. Set basic things like combat aid and the skills to be
 *                  used for calculating damage and of course, the name.
 * Arguments:       None
 * Returns:         Nothing
 */
public void 
config_ability()
{
    ::config_ability();
    set_combat_aid(58);
    set_tohit(40); // 39% hit chance
    set_dt(W_BLUDGEON);
    set_stats(({ SKILL_VALUE, 100 })); // Not modified by stats
    set_skills(({ SS_AOD_WALLOP }));
    set_ability_prep_time(20);
    set_ability_cooldown_time(0);
    set_ability_name("crush");
    set_ability_target(target_one_other_present_living_or_enemy);
    
    // Due to balance reasons, it is not affected by dual wield.
    set_ability_dual_wield(0);
} /* config_ability */

/*
 * Function name:   special_did_hit
 * Description:     Mask this function to process when the special scores. 
 *                  Descriptions seen by everyone are set here.
 * Arguments:       (int)       aid     - attack id
 *                  (string)    hdesc   - hit description
 *                  (int)       hid     - 
 *                  (int)       phurt   - extent of damage
 *                  (object)    enemy   - person being hit by special
 *                  (int)       dt      - damage type
 *                  (int)       phit    - 
 *                  (int)       dam     - damage amount
 *                  (mixed *)   items   - 
 *                  (int)       result  - result of cb_tohit
 * Returns:         Nothing
 */
public varargs void
special_did_hit(int aid, string hdesc, int hid, int phurt, object enemy,
                int dt, int phit, int dam, mixed *items, int result)
{
    string  how, how2, how3, *descs;
    int     wielded;
    object  ogre;
    
    ogre = this_player();
    wielded = sizeof(items);
    
    if (wielded)
        descs = map(items, &->short());
    
    /* add fatigue */
    if (ogre->query_fatigue() < 5)
    {
        ogre->heal_hp(-(5 - ogre->query_fatigue()));
        ogre->set_fatigue(0);
        ogre->catch_msg("Ooof! Your ogre limbs are feeling tired and "
        + "drained.\n");
    }
    else
    {
        ogre->add_fatigue(-5);
    }
    
    if (phurt >= 0) 
    {
        /* remove some of the ogre's panic */
        ogre->add_panic(-3 - phurt / 5);

        how = "!\n" + QCTNAME(enemy) + " seems ";
        how2 = "!\nYou feel ";

        /* Give combat descriptions based on the percent damage done.
         * Because players spend such a huge percentage of their time
         * on combat, lets add lots of variety. */
        switch (phurt)
        {
            case 0:
                how += "to have avoided any damage.";
                how2 = "!\nYou seem to have avoided any damage.";
                break;
            case 1:
                how3  = "slightly rattled.";
                how2 += how3;
                how  += how3;
                break;
            case 2:
                how3  = "somewhat rattled.";
                how2 += how3;
                how  += how3;
                break;
            case 3:
                how3  = "slightly battered.";
                how2 += how3;
                how  += how3;
                break;
            case 4:
                how3  = "somewhat battered.";
                how2 += how3;
                how  += how3;
                break;
            case 5:
                how3  = "seriously battered.";
                how2 += how3;
                how  += how3;
                break;
            case 6:
                how3  = "somewhat bashed.";
                how2 += how3;
                how  += how3;
                break;
            case 7:
                how3  = "seriously bashed.";
                how2 += how3;
                how  += how3;
                break;
            case 8:
                how3  = "thoroughly bashed.";
                how2 += how3;
                how  += how3;
                break;
            case 9:
                how3  = "clearly throttled.";
                how2 += how3;
                how  += how3;
                break;
            case 10:
                how3  = "thoroughly throttled.";
                how2 += how3;
                how  += how3;
                break;
            case 11:
                how3  = "absolutely throttled.";
                how2 += how3;
                how  += how3;
                break;
            case 12:
                how3  = "rather pulverized.";
                how2 += how3;
                how  += how3;
                break;
            case 13:
                how3  = "thoroughly pulverized.";
                how2 += how3;
                how  += how3;
                break;
            case 14:
                how3  = "horribly pulverized.";
                how2 += how3;
                how  += how3;
                break;
            case 15..20:
                how3  = "fairly devastated.";
                how2 += how3;
                how  += how3;
                break;
            case 21..33:
                how3  = "seriously devastated.";
                how2 += how3;
                how  += how3;
                break;
            case 34..49:
                how3  = "thoroughly devastated.";
                how2 += how3;
                how  += how3;
                break;
            case 50..99:
                how3  = "completely devastated.";
                how2 += how3;
                how  += how3;
                break;
            default:
                how = " like an avalanche of death and destruction! Ribs"
                    + " crack and bones snap as "
                    + enemy->query_possessive() + " body is mashed"
                    + " into a lifeless pulp!";
                how2 = " like an avalanche of death and destruction! The"
                     + " last thing you remember is the sound of your"
                     + " own spine splintering as hot pain washes over"
                     + " your mind!";
                break;
        }

        switch (wielded)
        {
            default:
            case 0:
                ogre->catch_msg("SLAM!!! You bring your mighty fists"
                  + " down on " + enemy->query_the_name(ogre)
                  + how + "\n");
                enemy->catch_msg("SLAM!!! "
                  + ogre->query_The_name(enemy) + " brings "
                  + ogre->query_possessive() + " mighty fists"
                  + " down on you" + how2 + "\n");
                ogre->tell_watcher("SLAM!!! " + QCTNAME(ogre)
                  + " brings " + ogre->query_possessive()
                  + " mighty fists down on " + QTNAME(enemy)
                  + how + "\n", enemy);
                break;
            case 1:
                ogre->catch_msg("SWAT!!! You swing your "
                  + COMPOSITE_WORDS(descs) + " down into "
                  + enemy->query_the_name(ogre) + how + "\n");
                enemy->catch_msg("SWAT!!! "
                  + ogre->query_The_name(enemy) + " swings "
                  + ogre->query_possessive() + " " + COMPOSITE_WORDS(descs)
                  + " down into you" + how2 + "\n");
                ogre->tell_watcher("SWAT!!! " + QCTNAME(ogre)
                  + " swings " + ogre->query_possessive() + " "
                  + COMPOSITE_WORDS(descs) + " down into " + QTNAME(enemy)
                  + how + "\n", enemy);
                break;
            case 2:
                ogre->catch_msg("BLAM!! BLAM!! One after the other"
                  + " you bring your " + COMPOSITE_WORDS(descs)
                  + " hurtling down" + " on " + enemy->query_the_name(ogre)
                  + how + "\n");
                enemy->catch_msg("BLAM!! BLAM!! One after the other "
                  + ogre->query_The_name(enemy) + " brings "
                  + ogre->query_possessive() + " " + COMPOSITE_WORDS(descs)
                  + " hurtling down on you" + how2 + "\n");
                ogre->tell_watcher("BLAM!! BLAM!! " + QCTNAME(ogre)
                  + " brings " + ogre->query_possessive() + " "
                  + COMPOSITE_WORDS(descs) + " hurtling down on "
                  + QTNAME(enemy) + how + "\n", enemy);
                break;
        }

        if (enemy->query_hp() <= 0)
            enemy->do_die(ogre);
        
        return;
    }
    
    /* We get here if the attack missed */

    switch (wielded)
    {
        default:
        case 0:
            ogre->catch_msg("THUD!!! Your mighty fists smash"
              + " harmlessly into the ground, completely missing "
              + enemy->query_the_name(ogre) + ".\n");
            enemy->catch_msg("THUD!!! " + ogre->query_The_name(enemy)
              + " brings " + ogre->query_possessive() + " mighty fists"
              + " crashing harmlessly into the ground beside you.\n");
            ogre->tell_watcher("THUD!!! " + QCTNAME(ogre)
              + " brings " + ogre->query_possessive() + " mighty fists"
              + " crashing harmlessly into the ground beside "
              + QTNAME(enemy) + ".\n", enemy);
            break;
        case 1:
            ogre->catch_msg("WHOOSH!! Your " + COMPOSITE_WORDS(descs) + " "
              + "sails cleanly over " + enemy->query_the_name(ogre)
              + "'s head, missing " + enemy->query_objective()
              + " entirely.\n");
            enemy->catch_msg("WHOOSH!! " + ogre->query_The_name(enemy)
              + "'s " + COMPOSITE_WORDS(descs) + " sails cleanly over your "
              + "head, missing you entirely.\n");
            ogre->tell_watcher("WHOOSH!! " + QCTNAME(ogre)
              + "'s " + COMPOSITE_WORDS(descs) + " sails cleanly over "
              + QTNAME(enemy) + "'s head, missing "
              + enemy->query_objective() + " entirely.\n", enemy);
            break;
        case 2: 
            ogre->catch_msg("WHUMP!! WHUMP!! Your " + COMPOSITE_WORDS(descs)
              + " plow into the ground on either side of "
              + enemy->query_the_name(ogre) + ", missing "
              + enemy->query_objective() + " completely.\n");
            enemy->catch_msg("WHUMP!! WHUMP!! "
              + ogre->query_The_name(enemy) + "'s " + COMPOSITE_WORDS(descs)
              + " plow into the ground on either side of you, missing"
              + " you completely.\n");
            ogre->tell_watcher("WHUMP!! WHUMP!! " + QCTNAME(ogre)
              + "'s " + COMPOSITE_WORDS(descs) + " plow into the ground on "
              + "either side of " + QTNAME(enemy) + ", missing "
              + enemy->query_objective() + " completely.\n", enemy);
            break;
    }
    
    /* add some panic to the ogre */
    ogre->add_panic(1);
    
} /* special_did_hit */

/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure that the thief has the
 *                necessary weapons.
 * Returns      : items that are required.
 */
static mixed * 
check_required_items(object actor, mixed *enemies, string arg, int pretest)
{
    object *weapon = ({});
    
    if (sizeof(actor->query_weapon(-1)) && !sizeof(weapon = query_clubs(actor)))
    {
        weapon = actor->query_weapon(-1);
        actor->catch_msg("ERRRRR ... ?!? What" + (sizeof(weapon) > 1 ? " "
        + "are these fancy things? " : "'s this fancy thing? ")
        + COMPOSITE_DEAD(weapon) + "?? How is an ogre supposed to crush "
        + "anything using " + (sizeof(weapon) > 1 ? "those" : "that")
        + "? Find a club or use your fists!\n");
        return 0;
    }
    
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
validate_requirements(object actor, mixed enemies)
{
    if (!actor->query_skill(SS_AOD_WALLOP))
    {
        actor->catch_msg("You haven't yet learned how to do any kind of tricky"
        + " attacks. Better visit a trainer.\n");
        return 0;
    }
    
    return 1;
} /* validate_requirements */

/*
 * Function name:   ability_msg
 * Description:     Handles the printing of the ability preparation.
 * Arguments:       None
 * Returns:         Nothing
 */
static void 
ability_msg(object actor, mixed *enemies, string arg)
{
    actor->catch_msg("Your ogre mind starts trying to recall how to manage a "
    + "crushing blow.\n");
} /* ability_msg */

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
    
    return modifier;
} /* query_combat_aid_modifier */

/*
 * Function name:   check_valid_action
 * Description:     Perform ability-specific checks
 * Arguments:       1. (object) The player
 *                  2. (mixed *) The enemies
 *                  3. (string) Arguments passed to the command
 *                  4. (int) Actual spell execution
 * Returns:         (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object actor, mixed *enemies, string arg, int execute)
{
    if (!validate_requirements(actor, enemies))
        return 0;
    
    return 1;
} /* check_valid_action */

/*
 * Function name:   filter_knives
 * Description:     It checks if given object is a weapon and a club.
 * Arguments:       (object) ob - The object to verify if it is a club
 * Returns:         (status) 1 - Item is a club
 *                  (status) 0 - Item is not a club
 */
public status
filter_clubs(object ob)
{
    return (IS_WEAPON_OBJECT(ob) && (ob->query_wt() == W_CLUB));
} /* filter_knives */

/*
 * Function name:   query_clubs
 * Description:     Process the actor for weapons matching the criteria
 * Arguments:       (object) actor - The actor of the special
 * Returns:         (object *) - An array of the wielded clubs
 */
public object *
query_clubs(object actor)
{
    object *weapon;
    
    if (!sizeof(weapon = filter(actor->query_weapon(-1), &filter_clubs())))
        return ({});
    
    return weapon;
} /* query_clubs */

/*
 * Function name:   calc_base_pen
 * Description:     This functions determines the penetration value of the items
 *                  used with the special, it has been masked for the purpose of
 *                  this ogre special. The ogre penetration value is based on
 *                  strength.
 * Arguments:       (object *) items - The items used for the special
 * Returns:         (int) The resulted penetration value
 */
public int
calc_base_pen(mixed *items)
{
    // The pen is capped at 60
    return min(this_player()->query_stat(SS_STR), 300) / 5;
} /* calc_base_pen */


/*
 * Function name:   calc_base_hit
 * Description:     A function used to determine the hit value of the ability
 * Arguments:       (mixed *) items - The items on which we determine hit
 * Returns:         (int) The modified or unmodified hit value
 */
public int
calc_base_hit(mixed *items)
{
    // Lets help the poor unarmed ogres.
    if (!sizeof(this_player()->query_weapon(-1)))
        return calc_base_pen(items);
    
    return ::calc_base_hit(items);
} /* calc_base_hit */

/*
 * Function name:   execute_instant_special
 * Description:     This function is called to execute an instant ogre crush.
 *                  The general of the guild is able to butt-kick members of
 *                  his team.
 * Arguments:       (object) actor - The one being kicked
 * Returns:         (int) 1 - success, 0 - failure
 */
public status
execute_instant_special(object actor)
{
    object *weapon, instigator;
   
    if (!m_sizeof(buttkicking[actor]))
        return 0;
    
    if (!objectp(instigator = buttkicking[actor]["general"]) ||
        (time() - buttkicking[actor]["time"]) > 60)
    {
        buttkicking[actor] = ([]);
        return 0;
    }
    
    if (random(9))
        return 0;
        
    if (member_array(instigator, actor->query_team_others()) < 0)
        return 0;
    
    if (environment(instigator) != environment(actor))
        return 0;
    
    if (sizeof(actor->query_weapon(-1)) && !sizeof(weapon = query_clubs(actor)))
        return 0;
    
    if (!can_execute_ability(actor, ({}), ""))
        return 0;
    
    actor->catch_msg("OOOF!!! That buttkick helped you remember how to "
    + "crush!\n");
    instigator->catch_msg("THUMP!! You kick " 
    + capitalize(actor->query_real_name()) + " right in the butt!\n");
    tell_room(environment(actor), "THUMP!! " + QCTNAME(instigator)
    + " kicks " + QTNAME(actor) + " squarely in the butt!\n",
    ({ instigator, actor }) );
    
    if (execute_ability(actor, ({ actor->query_attack() }), ""))
    {
        stop_ability(actor);
        hook_special_complete();
        return 1;
    }
    
    return 0;
} /* execute_instant_special */

/*
 * Function name:   notify_prep_time
 * Description:     This is a hook that abilities can use to know how long
 *                  the prep time is before execution. A common usage of
 *                  this may be to provide interim messages for long delays.
 * Arguments:       prep_time - the time before preparation and execution
 * Returns:         Nothing
 */
static void
notify_prep_time(float prep_time, object actor, mixed * targets)
{
    if (!pointerp(kick_alarms[actor]))
        kick_alarms[actor] = ([]);
    
    kick_alarms[actor]["prep_time"] = set_alarm((prep_time / 4.0), 0.0,
                                      &execute_instant_special(actor));
} /* notify_prep_time */

/*
 * Function name:   do_ability
 * Description:     The initiating function for the ability, masked to handle
 *                  the buttkicking functionality.
 * Arguments:       (string) arg - The argument used when executing the ability
 * Returns:         Nothing
 */
public int
do_ability(string arg)
{
    object *team_members;
    int     last_kick;
    
    if (query_verb() != "buttkick")
        return ::do_ability(arg);
    
    if (!AOD_GENERAL(this_player()))
    {
        notify_fail("You wish! You aren't the Headhunter General!\n");
        return 0;
    }
    
    if (!strlen(arg) || arg != "team")
    {
        notify_fail("You can <buttkick team> if you want. Is that what"
        + " you want?\n");
        return 0;
    }

    if (!pointerp(kick_alarms[this_player()]))
        buttkicking[this_player()] = ([ "time" : 0 ]);
    
    last_kick = time() - buttkicking[this_player()]["time"];
    
    if (last_kick < 600)
    {
        if (last_kick < 60)
        {
            notify_fail("You are already kicking some serious butt!\n");
            return 0;
        }

        notify_fail("Your kicking foot is still too sore! Better wait"
          + " a while longer.\n");
        return 0;
    }
    
    if (!sizeof(team_members = this_player()->query_team_others()))
    {
        notify_fail("You are not teamed up with anyone! No butts to"
        + " kick!\n");
        return 0;
    }
    
    foreach(object member: team_members)
    {
        if (environment(member) != environment(this_player()) ||
            !IS_OGRE(member))
            team_members -= ({ member });
    }
    
    if (!sizeof(team_members))
    {
        notify_fail("There are no Ogre butts in the area!\n");
        return 0;
    }
    
    write("Butt-kicking time!! You start \"motivating\" your team, Ogre-"
    + "style!\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) + " roars in "
    + "anger and begins kicking everyone forcefully in the butt! LOOK "
    + "OUT!!\n", this_player());
    
    buttkicking[this_player()]["time"] = time();
    
    foreach(object member: team_members)
    {
        buttkicking[member] = ([ "time" : time(), "general" : this_player() ]);
    }
    
    kick_alarms[this_player()] = ([
      "expire" : set_alarm(60.0, 0.0, &hook_buttkick_expire(this_player())),
      "cooldown" : set_alarm(600.0, 0.0, &hook_buttkick_cooldown(this_player()))
    ]);
    
    return 1;
} /* do_ability */