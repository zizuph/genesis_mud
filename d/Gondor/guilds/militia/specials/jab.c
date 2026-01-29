/*
 * Port of the Thornlin Militia Jab attack to the new Genesis Specials 
 * System
 *
 * Created by Petros, August 2008
 *
 * Modified caid from 42 to 40 following global layman guild review.
 * -Arman (AoB) 6 August 2019
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

#define JAB_LOG         (MILITIA_DIR+"jab_damage")

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
    set_combat_aid(40);
    set_tohit(110);
    set_dt(W_IMPALE);
    set_stats( ({ SKILL_AVG, TS_STR, TS_DEX, TS_INT, SKILL_END }) );    
    set_skills(({ SKILL_WEIGHT, 200, SS_MILITIA }) );
    // Can jab once every 14 seconds on average
    set_ability_prep_time(6);
    set_ability_cooldown_time(8);
    set_ability_name("jab");

    // Jab cannot be used at the same time as Evade
    add_ability_restriction(EVADE_ABILITY);    
    
    set_guild_stat_modifier(SS_LAYMAN, 20, 100);
}

public int
query_guild_stat_type(object player)
{
    if (!player->query_occ_militia())
    {
        send_debug_message("jab", "Using lay militia guild stat.");
        return SS_LAYMAN;
    }
    else
    {
        send_debug_message("jab", "Using occ militia guild stat.");    
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
    string it_them, msg1, msg2, msg3, wdesc;
    
    player = this_player();
    weapon = find_wep(player, 1);
    wdesc = weapon->short();
    
	if (enemy->query_hp() <= 0)
	{
        if (!(random(255) % 4))
        {
            player->catch_tell("With a look of grim determination, you throw " +
                "all your weight into a strike on " + 
                enemy->query_the_possessive_name(player) + " " + hdesc + 
                ", causing bones to snap and blood to spray.\n");
            enemy->catch_tell("With a look of grim determination, " + 
                player->query_the_name(enemy) + " throws all " + 
                player->query_possessive() + " weight into a strike on your " + 
                hdesc + ". As you struggle to stay conscious, you hear your " +
                "bones breaking and are nearly blinded with your own " +
                "spraying blood.\n");
            player->tell_watcher("With a look of grim determination, " + 
                QTNAME(player) + " throws all " + player->query_possessive() + 
                " weight into a " + "strike on " + QTPNAME(enemy) + " " + 
                hdesc + ". " + QCTNAME(enemy) + " turns pale as " + 
                enemy->query_possessive() + " bones break and blood " +
                "sprays.\n", enemy);
        }
        else
        {
            player->catch_tell(enemy->query_The_name(player) + " screams in " +
                "agony as you drive your " + wdesc + " through " + 
                enemy->query_possessive() + " " + hdesc + ". You withdraw " +
                "it quickly, allowing " + enemy->query_possessive() + 
                " body to fall.\n");
            enemy->catch_tell("You scream in agony as " + 
                player->query_the_name(enemy) + " drives " +
                player->query_possessive() + " " + wdesc + " through your " +
                hdesc + ".  As " + player->query_pronoun() + " withdraws it, " +
                "all goes dark.\n");
            player->tell_watcher(QCTNAME(enemy) + " screams in agony as " +
                QTNAME(player) + " drives " + player->query_possessive() + " " +
                wdesc + " completely through " + QTPNAME(enemy) + " " +
                hdesc + ".  As " + QTNAME(player) + " withdraws it, " +
                QTNAME(enemy) + " slumps to the ground, dead.\n", enemy);
        }

        enemy->do_die(player);
    }
    else
    {
        switch (phurt)
    	{
        case -2..0:
            msg1 = "You thrust your " + wdesc + " towards " + 
                enemy->query_the_name(player) + ", just barely missing " +
                enemy->query_possessive() + " " + hdesc + ".\n";
            msg2 = player->query_The_name(enemy) + " thrusts " +
                player->query_possessive() + " " + wdesc + " towards you, just " +
                "barely missing your " + hdesc + ".\n";
            msg3 = QCTNAME(player) + " thrusts " + player->query_possessive() + " " +
                wdesc + " towards " + QTNAME(enemy) + ", just barely missing " +
                enemy->query_possessive() + " " + hdesc + ".\n";
            break;
    
        case 1..4:
            msg1 = "You jab " + enemy->query_the_name(player) + " lightly " +
                "with your " + wdesc + ", nicking " + enemy->query_possessive() +
                " " + hdesc + ".\n";
            msg2 = player->query_The_name(enemy) + " jabs you lightly with " +
                player->query_possessive() + " " + wdesc + ", nicking your " + hdesc +
                ".\n";
            msg3 = QCTNAME(player) + " jabs " + QTNAME(enemy) + " lightly with " +
                player->query_possessive() + " " + wdesc + ", nicking " +
                enemy->query_possessive() + " " + hdesc + ".\n";
            break;
    
        case 5..8:
            msg1 = "You jab at " + enemy->query_the_possessive_name(player) +
                " " + hdesc + ", but deliver only a glancing blow.\n";
            msg2 = player->query_The_name(enemy) + " jabs at your " + hdesc +
                ", wounding you slightly.\n";
            msg3 = QCTNAME(player) + " jabs at " + QTPNAME(enemy) + " " + hdesc +
                ", causing a bit of damage.\n";
            break;
    
        case 9..14:
            msg1 = enemy->query_The_name(player) + " grimaces in pain as you jab " +
                "your " + wdesc + " into " + enemy->query_possessive() + " " +
                hdesc + ".\n";
            msg2 = "You grimace in pain as " + player->query_the_name(enemy) +
                " drives " + player->query_possessive() + " " + wdesc + " deeply " +
                "into your " + hdesc + ".\n";
            msg3 = QCTNAME(enemy) + " grimaces in pain as " + QTNAME(player) +
                " drives " + player->query_possessive() + " " + wdesc + " deep " +
                "into " + QTPNAME(enemy) + " " + hdesc + ".\n";
            break;
    
        case 15..20:
            msg1 = "Seeing " + enemy->query_the_name(player) + " off-guard, " +
                "you bring the butt of your " + wdesc + " whipping around, " +
                "battering " + enemy->query_objective() + " painfully in the " +
                hdesc + ".\n";
            msg2 = "Seeing you off-guard, " + player->query_the_name(enemy) +
                " brings the butt of " + player->query_possessive() + " " + wdesc +
                " whipping around, battering you painfully in the " + hdesc + ".\n";
            msg3 = "Seeing " + QTNAME(enemy) + " off-guard, " + QTNAME(player) + 
                " brings the butt of " + player->query_possessive() + " " + wdesc +
                " whipping around, battering " + QTNAME(enemy) + " painfully in " +
                "the " + hdesc + ".\n";
            break;
    
        case 21..25:
            msg1 = "You smile in grim satisfaction as you deal " +
                enemy->query_the_name(player) + " a serious wound to the " + hdesc +
                ".\n";
            msg2 = player->query_The_name(enemy) + " smiles in grim satisfaction " +
                "as " + player->query_pronoun() + " badly injures your " + hdesc + 
                ".\n";
            msg3 = QCTNAME(player) + " smiles in grim satisfaction as " +
                player->query_pronoun() + " deals a major wound to " + 
                QTPNAME(enemy) + " " + hdesc + ".\n";
            break;
    
        case 26..30:
            msg1 = "In one fluid motion, you thrust aside a clumsy blow and " +
                "lunge forward, nearly knocking " + enemy->query_the_name(player) +
                " down with your blow to " + enemy->query_possessive() + " " +
                hdesc + ".\n";
            msg2 = "In one fluid motion, " + player->query_the_name(enemy) +
                " thrusts aside your clumsy attack and lunges forward with " +
                player->query_possessive() + " " + wdesc + ", nearly knocking you " +
                "over with an excruciating blow to the " + hdesc + ".\n";
            msg3 = "In one fluid motion, " + QTNAME(player) + " thrusts aside " +
                QTPNAME(enemy) + " clumsy blow and lunges forward, nearly " +
                "knocking " + enemy->query_objective() + " down with a blow " +
                "to the " + hdesc + ".\n";
            break;
    
        case 31..35:
            msg1 = enemy->query_The_name(player) + " turns pale as your " + wdesc +
                " slams into " + enemy->query_possessive() + " " + hdesc + ".\n";
            msg2 = "You feel the blood drain from your face as " +
                player->query_the_possessive_name(enemy) + " " + wdesc + " slams " +
                "into your " + hdesc + ".\n";
            msg3 = QCTNAME(enemy) + " turns pale as " + QTPNAME(player) + " " +
                wdesc + " slams into " + enemy->query_possessive() + " " + hdesc + 
                ".\n";
            break;
    
        case 36..40:
            msg1 = "You feel more confident as your " + wdesc + " badly wounds " +
                enemy->query_the_name(player) + " in the " + hdesc + ".\n";
            msg2 = player->query_The_name(enemy) + " looks increasingly confident " +
                "as " + player->query_possessive() + " " + wdesc + " gravely " +
                "injures your " + hdesc + ".\n";
            msg3 = QCTNAME(player) + " looks more confident as " + 
                player->query_pronoun() + " gravely injures " + QTPNAME(enemy) +
                " " + hdesc + ".\n";
            break;
    
        case 41..45:
            msg1 = enemy->query_The_name(player) + " loses " + 
                enemy->query_possessive() + " concentration for a split " +
                "second, and you thrust your " + wdesc + " nearly through " +
                enemy->query_possessive() + " " + hdesc + ".\n";
            msg2 = "You lose your concentration for a split second, only to " +
                "receive an excruciating jab. You realize too late that " +
                player->query_the_possessive_name(enemy) + " " + wdesc + 
                " has horribly wounded your " + hdesc + ".\n";
            msg3 = QCTNAME(enemy) + " appears distracted for a split second, " +
                "only to find " + enemy->query_possessive() + " " + hdesc +
                " gruesomely impaled on " + QTPNAME(player) + " " + wdesc + ".\n";
            break;
    
        case 46..50:
            it_them = (hdesc == "legs" ? "them" : "it");
            msg1 = "Turning your back on " + enemy->query_the_name(player) + " for " +
                "a moment, you quickly spin, whipping your " + wdesc + " into " +
                enemy->query_possessive() + " " + hdesc +  ", nearly crushing " +
                it_them + ".\n";
            msg2 = player->query_The_name(enemy) + " turns " + 
                enemy->query_possessive() + " back on you for a moment, and " +
                "you close to strike. " + player->query_The_name(enemy) + 
                " suddenly spins, whipping " + player->query_possessive() +
                wdesc + " into your " + hdesc + " nearly crushing " + it_them +
                ".\n";
            msg3 = QCTNAME(player) + " turns " + player->query_possessive() + 
                " back on " + enemy->query_the_name(player) + " for a moment, " +
                "tricking " + enemy->query_objective() + " into advancing. " +
                QCTNAME(player) + " spins suddenly, whipping " +
                player->query_possessive() + " " + wdesc + " into " + 
                QTPNAME(enemy) + " " + hdesc + ", nearly crushing " +
                it_them + ".\n";
            break;
    
        case 51..65:
            msg1 = "You wonder what keeps " + enemy->query_the_name(player) +
                " fighting as you bring your " + wdesc + " crashing into " +
                "the side of " + enemy->query_possessive() + " " + hdesc + ".\n";
            msg2 = "You wonder what you are doing here, as " + 
                player->query_the_name(enemy) + " brings " + 
                player->query_possessive() + " " + wdesc + " crashing into the " +
                "side of your " + hdesc + ".\n";
            msg3 = "You begin to wonder why " + QTNAME(enemy) + " doesn't run " +
                "as you watch " + QTPNAME(player) + " " + wdesc + " come " +
                "crashing into the side of " + player->query_possessive() + " " +
                hdesc + ".\n";
            break;
    
        case 66..85:
            msg1 = "You look away briefly as you see the gruesome results " +
                "of your blow to " + enemy->query_the_possessive_name(player) +
                " " + hdesc + ".\n";
            msg2 = "You nearly lose consciousness as " + 
                player->query_the_possessive_name(enemy) + " " + wdesc + 
                "gruesomely mangles your " + hdesc + ".  You feel an urge to " +
                "run, but fear you are too weak.\n";
            msg3 = QCTNAME(enemy) + " nearly loses consciousness as " + 
                QTNAME(player) + " delivers a gaping wound to " + QTPNAME(enemy) + 
                " " + hdesc + ".\n";
            break;
    
        default:
            msg1 = "With a look of grim determination, you throw all your weight " +
                "into a strike on " + enemy->query_the_possessive_name(player) +
                " " + hdesc + ", causing bones to snap and blood to spray.\n";
            msg2 = "With a look of grim determination, " + 
                player->query_the_name(enemy) + " throws all " + 
                player->query_possessive() + " weight into a strike on your " + hdesc +
                ". As you struggle to stay conscious, you hear your bones " +
                "breaking and are nearly blinded with your own spraying blood.\n";
            msg3 = "With a look of grim determination, " + QTNAME(player) +
                " throws all " + player->query_possessive() + " weight into a " +
                "strike on " + QTPNAME(enemy) + " " + hdesc + ". " + 
                QCTNAME(enemy) + " turns pale as " + enemy->query_possessive() +
                " bones break and blood sprays.\n";
            break;
    	}

        player->catch_tell(msg1);
        enemy->catch_tell(msg2);
        player->tell_watcher(msg3, enemy);
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
    
    if (player->query_skill(SS_MILITIA) < 1)
    {
        player->catch_msg("You don't have the first clue how to "
          + "accomplish that technique. Perhaps you should seek "
          + "training.\n");
        return 0;
    }

    if (!objectp(find_wep(player, 1)))
    {
        player->catch_msg("You can't seem to accomplish that without a " 
          + "proper weapon.\n");
        return 0;
    }

    return 1;
}


public varargs string
query_restricted_ability_message(string ability, object player)
{
    string short_desc;
    
    short_desc = ability->short();
    if (!strlen(short_desc))
    {
        if (query_ability_preparing(player))
        {
            return "You are busy looking for a hole in your enemy's "
                + "defences.\n";
        }
        else if (query_ability_in_cooldown(player))
        {
            return "You are still recovering from looking for holes "
                + "in your enemy's defences.\n";
        }
    }
    
    if (query_ability_preparing(player))
    {        
        return "You are too busy looking for a hole in your " 
          + "enemy's defences to " + short_desc + ".\n";
    }
    else if (query_ability_in_cooldown(player))
    {
        return "You are still recovering from looking for "
             + "holes in your enemy's defence and cannot yet "
             + short_desc + ".\n";
    }
            
    return ::query_restricted_ability_message(ability);
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

    send_debug_message("jab", 
                    name + " jabs with Pen of " + pen + ", "
                    + "Damage of " + damage,
                       JAB_LOG);
}

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    write("\nYou feel able to jab again.\n\n");
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
    write("There are no enemies for you to jab.\n");
}

static void 
ability_msg(object actor,mixed * targets,string arg)
{
    object target;
    
    if (sizeof(targets) > 0)
    {        
        target = targets[0];
        actor->catch_msg("You look for an opening in " + QTPNAME(target)
                       + " defences.\n");
    }
}
