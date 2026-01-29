/* This file is included in the guild shadow.  It contains the code
 * for the guild's special attack.  We keep it in a separate file to
 * keep from cluttering the shadow and for easier debugging.
 *
 * Modified by Blizzard:
 * 25.08.2003 - Changed the chop prepare time (now random)
 * 1.10.2003  - Dis check only if we are not already fighting the target.
 * 
 * 2008 Sept - Louie - Recoded to make use of new specials library.
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>

#include "/d/Ansalon/common/defs.h"
#include "../guild.h"

inherit "/d/Genesis/specials/std/damage.c";

#define AXEWIELDR query_weapon(W_RIGHT)->query_wt() == W_AXE
#define AXEWIELDL query_weapon(W_LEFT)->query_wt() == W_AXE
#define AXEWIELDB query_weapon(W_BOTH)->query_wt() == W_AXE

#define DOOM_CHOP_LOG (GUILD_SPECIALS + "doom_chop")


public object find_best_neidar_weapon(object player);

/*
 * Function:    is_racial_enemy
 * Description: Racial enemies are those enemies that the Neidar is
 *              capable of fighting at a greater ferocity. The list is
 *              in guild.h.
 */
public int
is_racial_enemy(object enemy)
{
    if (!enemy)
    {
        return 0;
    }

    string enemy_race = enemy->query_race();
    string enemy_race_name = enemy->query_race_name();
    foreach (string race : NEIDAR_RACIAL_ENEMIES)
    {
        // We match the enemy's race using wildmatch. This means
        // that any derivation of the race will work.
        // (eg. giant matches frost giant and hill giant)
        if (wildmatch("*" + race, enemy_race)
            || wildmatch ("*" + race, enemy_race_name))
        {
            return 1;
        }
    }
    
    return 0;
}

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
    // Maximum combat aid is in guild.h
    set_combat_aid(CHOP_MAX_AID);
    
    set_tohit(110); // 90% chance of hitting
    
    // Dwarves have bonus on both str and dis    
    set_stats(({ SKILL_AVG, TS_STR, TS_DIS, SKILL_END }) );    
    set_skills( ({ SS_GUILD_SPECIAL_SKILL }) );
    
    // 20 sec per ability, dwarves are strong but slow.
    // So specials a little on the slower side.
    set_ability_prep_time(10);
    set_ability_cooldown_time(10);
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
    set_dt(W_SLASH); //This will change based on weapon

    set_ability_name("chop");
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
 * Returns      : nothing
 */
public void special_did_hit(int aid, string hdesc, int hid, int phurt,
                            object enemy, int dt, int phit, int dam)
{
    object attacker = this_player();
    string weapon, wdtype, watype;
    string *attack_message;
    object wep;
    int wielding_axe;

    //Check what we're wielding
    wep = find_best_neidar_weapon(attacker);

    //Is it even possible we'd lose our weapon between applying damage
    //and displaying these messages?
    if (!wep)
    {
        attacker->catch_msg("You applied damage but don't appear to have "+
        "an axe or club! Please report this.\n");
        return;
    }

    weapon = wep->short();

    if (wep->query_wt() == W_AXE)
    {
        wielding_axe = 1;
    }

    if (phurt < 0)
    {
        /* message to attacker */
        attacker->catch_msg("You swing your " +weapon+ " at "+
        QTNAME(enemy)+ " but miss by a mile.\n");

        if (interactive(enemy))
        {
            /* message to target */
            enemy->catch_msg(QCTNAME(attacker) + " swings at you with "
            +HIS(attacker)+ " " +weapon+ " but misses by a mile.\n");
        }
        /* message to onlookers */
        attacker->tell_watcher(QCTNAME(attacker) + " swings at " +
        QTNAME(enemy)+ " but misses by a mile.\n", enemy);
        return;
    }

    switch (phurt)
    {
        case 0:
        attack_message = ({
            "You curse foully in dwarven as your wild swing " +
            "with your " +weapon+ " at " +enemy->query_the_name(attacker)+
            " just misses.\n",
            attacker->query_The_name(enemy)+ " curses foully in dwarven " +
            "as " +HIS(attacker)+ " wild swing just misses you.\n",
            QCTNAME(attacker)+ " curses foully in dwarven as " +
            HIS(attacker)+ " wild swing at " +QTNAME(enemy) +
            " just misses.\n"
        });
        break;
        case 1..2:
        attack_message = ({
            "You strike out wildly with your " +weapon+ ", just " +
            "grazing " +enemy->query_the_name(attacker)+
            "'s " +hdesc+ ".\n",
            attacker->query_The_name(enemy)+ " strikes out wildly " +
            "at you with " +HIS(attacker)+ " " +weapon+ ", just grazing " +
            "your " +hdesc + ".\n",
            QCTNAME(attacker)+ " strikes out wildly at " +QTNAME(enemy)+
            " with " +HIS(attacker)+ " " +weapon+ ", just grazing " +
            QTNAME(enemy)+ "'s " +hdesc+ ".\n"
        });
        break;
        case 3..5:
        if(wielding_axe)
        {
            wdtype = "slicing a minor flesh wound";
        }
        else
        {
            wdtype = "bruising it moderately";
        }
        attack_message = ({
            "You grin fiercely as you bring your " +weapon+
            " down upon " +enemy->query_the_name(attacker)+ "'s " +
            hdesc+ ", " +wdtype+ ".\n",
            attacker->query_The_name(enemy)+ " grins fiercely as " +HE(attacker)+
            " brings " +HIS(attacker)+ " " +weapon+ " down upon your " +hdesc+
            ", " +wdtype+ ".\n",
            QCTNAME(attacker)+ " grins fiercely as " +HE(attacker)+ " brings " +
            HIS(attacker)+ " " +weapon+ " down upon " +QTNAME(enemy)+ "'s " +hdesc+
            ", " +wdtype+ ".\n"
        });
        break;
        case 6..10:
        attack_message = ({
            "You swing furiously at " +enemy->query_the_name(attacker)+ ", " +
            "slamming the face of your " +weapon+ " into " +
            enemy->query_the_name(attacker)+ "'s " +hdesc+ ".\n",
            attacker->query_The_name(enemy)+ " swings furiously at you, slamming " +
            "the face of " +HIS(attacker)+ " " +weapon+ " into your " +hdesc+ ".\n",
            QCTNAME(attacker)+ " swings furiously at " +QTNAME(enemy)+ ", " +
            "slamming the face of " +HIS(attacker)+ " " +weapon+ " into " +QTNAME(enemy)+ "'s " +
            hdesc + ".\n"
        });
        break;
        case 11..20:
        if(wielding_axe)
        {
            watype = "chop";
            wdtype = "slashing a nasty wound";
        }
        else
        {
            watype = "slam";
            wdtype = "striking a painful blow";
        }
        attack_message = ({
            "You " +watype+ " down mightily upon " +enemy->query_the_name(attacker)+
            "'s " +hdesc+ " with your " +weapon+ ", " +wdtype+ ".\n",
            attacker->query_The_name(enemy)+ " " +watype+ "s down mightily upon " +
            "your " +hdesc+ " with " +HIS(attacker)+ " " +weapon+ ", " +wdtype+ ".\n",
            QCTNAME(attacker)+ " " +watype+ "s down mightily upon " +QTNAME(enemy)+
            "'s " +hdesc+ " with " +HIS(attacker)+ " " +weapon+ ", " +wdtype+ ".\n"
        });
        break;
        case 21..30:
        if(wielding_axe)
        {
            watype = "slice a deep wound upon";
            wdtype = "slices a deep wound upon";
        }
        else
        {
            watype = "smash";
            wdtype = "smashes";
        }
        attack_message = ({
            "You roar gleefully as you " +watype+ " " +
            enemy->query_the_name(attacker)+ "'s " +hdesc+ " with your " +
            weapon + ".\n",
            attacker->query_The_name(enemy)+ " roars gleefully as " +
            HE(attacker)+ " " +wdtype+ " your " +hdesc+ " with " +
            HIS(attacker)+ " " +weapon+ ".\n",
            QCTNAME(attacker)+ " roars gleefully as " +HE(attacker)+ " " +
            wdtype+ " " +QTNAME(enemy)+ "'s " +hdesc+ " with " +
            HIS(attacker)+ " " +weapon+ ".\n"
        });
        break;
        case 31..50:
        if(wielding_axe)
        {
            wdtype = "burying it deeply in";
        }
        else
        {
            wdtype = "smashing it powerfully upon";
        }
        attack_message = ({
            "You swing your " +weapon+ " in a deadly arc, " +
            wdtype+ " " +enemy->query_the_name(attacker)+ "'s " +hdesc+
            ".\n",
            attacker->query_The_name(enemy)+ " swings " +HIS(attacker)+
            " " +weapon+ " in a deadly arc, " +wdtype+ " your " +
            hdesc+ ".\n",
            QCTNAME(attacker)+ " swings " +HIS(attacker)+ " " +weapon+
            " in a deadly arc, " +wdtype+ " " +QTNAME(enemy)+ "'s " +
            hdesc+ ".\n"
        });
        break;
        case 51..75:
        if(wielding_axe)
        {
            wdtype = "tearing a great wound in";
        }
        else
        {
            wdtype = "gleefully pulping";
        }
        attack_message = ({
            "You launch yourself into the air, bringing your " +weapon+
            " down powerfully upon " +enemy->query_the_name(attacker)+
            ", " +wdtype+ " " +HIS(enemy)+ " " +hdesc+ ".\n",
            attacker->query_The_name(enemy)+ " launches " +HIM(attacker)+
            "self into the air, bringing " +HIS(attacker)+ " " +weapon+
            " powerfully down upon you, " +wdtype+ " your " +hdesc+ ".\n",
            QCTNAME(attacker)+ " launches " +HIM(attacker)+ "self into " +
            "the air, bringing " +HIS(attacker)+ " " +weapon+
            " powerfully down upon " +QTNAME(enemy)+ ", " +wdtype+ " " +
            HIS(enemy)+ " " +hdesc+ ".\n"
        });
        break;
        case 76..99:
        if(wielding_axe)
        {
            wdtype = "rips to shreads";
        }
        else
        {
            wdtype = "pulverises";
        }
        attack_message = ({
            "You begin to sing a dwarven warsong of victory, as your blow " +
            "with the " +weapon+ " " +wdtype+ " " +
            enemy->query_the_name(attacker)+ "'s " +hdesc+ ", splattering " +
            "blood everywhere.\n",
            attacker->query_The_name(enemy)+ " begins to sing a dwarven " +
            "warsong of victory, as " +HIS(attacker)+ " blow with the " +
            weapon + " " +wdtype+ " your " +hdesc+ ", splattering blood " +
            "everywhere.\n",
            QCTNAME(attacker)+ " begins to sing a dwarven warsong of victory, " +
            "as " +HIS(attacker)+ " blow with the " +weapon+ " " +wdtype+ " " +
            QTNAME(enemy)+ "'s " +hdesc+ ", splattering blood everywhere.\n"
        });
        break;
        default:
        attack_message = ({
            "You roar in victory as you deal a mortal wound to " +
            enemy->query_the_name(attacker)+ " with your " +weapon+ ".\n",
            attacker->query_The_name(enemy)+ " roars in victory as " +
            HE(attacker)+ " deals you a mortal wound with " +HIS(attacker)+
            " " +weapon+ ".\n",
            QCTNAME(attacker)+ " roars in victory as " +HE(attacker)+
            " deals " +QTNAME(enemy)+ " a mortal wound with " +HIS(attacker)+
            " " +weapon+ ".\n"
        });
        break;
    }

    if (is_racial_enemy(enemy))
    {
        attacker->catch_msg("Your racial hatred of " +QTNAME(enemy)+
        " gives you renewed strength!\n");
        attacker->tell_watcher(QCTNAME(attacker)+ "'s eyes seem to blaze " +
        "with pure hatred!\n");
    }

    //Tell the messages
    attacker->catch_tell(attack_message[0]);
    enemy->catch_tell(attack_message[1]);
    attacker->tell_watcher(attack_message[2], enemy);

    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(attacker);
    }

    if(ADMIN_MANAGER->query_is_doomseeker(attacker))
        send_debug_message("chop", capitalize(attacker->query_real_name())+
            " chop damage: "+ dam + ".", DOOM_CHOP_LOG);
}

/*
 * Filter valid chop weapons
 */
public int
filter_neidar_weapons(object ob)
{
    if (!ob)
    {
        return 0;
    }

    if (!ob->check_weapon())
    {
        return 0;
    }

    int i = ob->query_wt();

    if (i == W_AXE || i == W_CLUB)
    {
        return 1;
    }
    
    return 0;
}

/*
 * Find the best neidar weapon for a player
 */
public object
find_best_neidar_weapon(object player)
{
    object best;
    mixed *weapons = player->query_weapon(-1);

    if (!sizeof(weapons))
    {
        return 0;
    }

    weapons = filter(weapons, filter_neidar_weapons);

    if (!sizeof(weapons))
    {
        return 0;
    }

    foreach (object ob : weapons)
    {
        if (!best)
        {
            best = ob;
            continue;
        }

        if (ob->query_pen() > best->query_pen())
        {
            best = ob;
        }
    }
    return best;
}

/*
 * Function name: check_required_items
 * Description  : Look for an axe or club
 * Returns      : items that are required.
 */
static mixed * 
check_required_items(object actor, mixed * targets,
                     string arg, int pretest)
{
    //Must have a axe/club
    object weapon = find_best_neidar_weapon(actor);
    
    if (weapon)
    {
        return ({ weapon });
    }

    return 0;
}

/*
 * Function name: apply_costs_to_player
 * Description  : By default, a small fatigue cost is applied
 *                for the special. Other costs can be applied
 *                as well by a masked function.
 *                Neidar have no fatigue penalty for using their special.
 * Arguments    : player - player executing the special
 * Returns      : nothing
 */
public void
apply_costs_to_player(object player) 
{
    // Neidar have no fatigue cost
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
    object weapon = find_best_neidar_weapon(player);
    
    if(!sizeof(player->query_weapon(-1)))
    {
    	player->catch_tell("You have no weapon wielded! You can't do "
    	    + "that!\n");
    	return 0;
    }
    
    if (!weapon)
    {
    	player->catch_tell("You don't have the appropriate weapon to do "
    	    + "that.\n");        
        return 0;
    }

    /* Does attacker have the skill? */
    if (!player->query_skill(SS_GUILD_SPECIAL_SKILL))
    {
    	player->catch_tell("First you should learn how.\n");
    	return 0;
    }

    if (BATTLERAGE_ABILITY->is_battleraging_stubbornly(player)
        && BATTLERAGE_ABILITY->query_ability_preparing(player))
    {
        player->catch_tell("You are so focused on defending yourself "
            + "that you cannot focus on anything else!\n");
        return 0;
    }
    
    // Check alignment restrictions
    if(player->query_alignment() < -100)
    {
    	player->catch_tell("You have drifted from the noble path of the "
    	    + "dwarven warrior. You no longer have the fire to use chop "
    	    + "or crush.\n");
    	return 0;
    }
    
    return ::check_valid_action(player, targets, arg, execute);    
}

/*
 * 100 is used for racial enemies.
 * 95 is used for normal.
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Arguments    : player - player executing special
 * Returns      : number between 1 and 100
 */
public int 
query_combat_aid_modifier()
{
    int aid, chop_aid;
    object enemy = TP->query_attack();
    
    chop_aid = CHOP_NORMAL_AID;
    if (BATTLERAGE_ABILITY->is_battleraging_fiercely(TP))
    {
        chop_aid = CHOP_FIERCE_AID;
        send_debug_message("chop", "Adjusting combat aid for fierce "
            + "battlerage at " + chop_aid + "% caid.");
    }
    else if (BATTLERAGE_ABILITY->is_battleraging_aggressively(TP))
    {
        int aggressive_bonus = CHOP_AGGRESSIVE_AID - CHOP_NORMAL_AID;
        int skill = TP->query_skill(BATTLERAGING_SKILL);
        aggressive_bonus = max(1, aggressive_bonus * skill / 100);
        chop_aid += aggressive_bonus;
        send_debug_message("chop", "Adjusting combat aid for aggressive "
            + "battlerage at " + chop_aid + "% caid.");
    }
        
    if (!objectp(enemy) || !is_racial_enemy(enemy))
    {
        // If not a racial enemy, we remove the racial bonus
        chop_aid -= CHOP_RACIAL_BONUS;
        send_debug_message("chop", "Not a racial enemy, reducing total "
            + "aid to " + chop_aid + "%.");
    }

    aid = chop_aid * 100 / CHOP_MAX_AID;    
    send_debug_message("chop", "Combat aid modifier gives caid at "
        + aid + "% of maximum.");
    
    return aid;
}

// HOOKS DEFINED BELOW

/*
 * Function:    hook_special_complete
 * Description: This hook informs the player when they are able to
 *              execute their special again.
 */
public void 
hook_special_complete()
{
    object who = this_player();
    if(who->AXEWIELDR || who->AXEWIELDL || who->AXEWIELDB)
    {
        who->catch_tell("You feel ready to chop again.\n");
    }
    else
    {
        who->catch_tell("You feel ready to crush your foes again.\n");
    }
}

/*
 * Function:    hook_attack_object
 * Description: Called when the Neidar engages someone in battle by
 *              starting with a chop.
 */
public void
hook_attack_object(object ob)
{
    this_player()->catch_msg("You roar an ancient dwarven warcry, and " 
        + "charge into battle against " + QTNAME(ob) + "!\n");
    ob->catch_msg(QCTNAME(this_player()) + " roars an ancient dwarven "
        + "warcry and charges into battle against you!\n");
    tell_room(environment(ob), QCTNAME(this_player()) + " roars an "
        + "ancient dwarven warcry and charges into battle against "
        + QTNAME(ob) + ".\n", ({ this_player(), ob }) );
}

/*
 * Function:    hook_special_in_cooldown
 * Description: When a player tries to execute the special while it is in
 *              cooldown, this hook gets called.
 */
public void
hook_special_in_cooldown()
{
	write("Patience! You have not yet recovered from your last attack!\n");
}

public void
hook_already_active(object ability)
{
    if(this_player()->AXEWIELDR 
       || this_player()->AXEWIELDL 
       || this_player()->AXEWIELDB)
    {
        write("You are already preparing to chop!\n");
    }
    else
    {
        write("You are already preparing to crush your foe!\n");
    }    
}

/*
 * Function name: hook_stun_fail
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_stun_fail(object ability)
{
    if(this_player()->AXEWIELDR 
       || this_player()->AXEWIELDL 
       || this_player()->AXEWIELDB)
    {
        write("You are too stunned to chop!\n");
    }
    else
    {
        write("You are too stunned to crush!\n");
    }        
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
    object * alive;
    
    alive = filter(targets, objectp);
    if (sizeof(alive))
    {
        write("The target of your attack seems to have slipped away.\n");
    }
    else
    {
        write("You relax as you realize your that your target is "
            + "no longer a threat anymore.\n");
    }
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
    actor->catch_msg("You prepare to " + query_verb() + " your "
        + "foe.\n");
}

public int 
do_ability(string arg)
{
    object player;
    object * weapons;
    string attack_verb;
    int wt_types;
    
    player = this_player();
    attack_verb = query_verb();
    weapons = player->query_weapon(-1);
    wt_types = 0;
    foreach (object weapon : weapons)
    {
        wt_types |= weapon->query_wt();
    }
    
    switch (attack_verb)
    {
    case "chop":
        if (!(wt_types & W_AXE))
        {
            break;
        }
        return ::do_ability(arg);
        
    case "crush":
        if (!(wt_types & W_CLUB))
        {
            break;
        }
        return ::do_ability(arg);
    }
    
	notify_fail("You don't have the appropriate weapon to do "
	    + "that.\n");        
    return 0;
}
