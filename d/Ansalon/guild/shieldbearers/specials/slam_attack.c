/*
 * Port of the Shieldbearer Slam to the new Genesis Specials System
 *
 * Created by Petros, August 2008
 *
 * Modifications:
 *  - Changing from tell_room to tell_watcher to reduce spam when testing.
 *    Petros, May 2009
 * 
 *  - Last change
 *    ?, 2010/10/06
 *  - Fixed cooldown message to not spam lplog
 *    Lavellan, 2011/03/25
 *  - Added calls to manager for new implemented code.
 *    Carnak, 2017/01/25
 */ 

#pragma strict_types

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

#include "/std/combat/combat.h"
#include "guild.h"

#define SLAM_LOG        (GUILD_DIR+"slam_damage")
#define OPT_SHORT_SLAM  "short_slam"
#define OPT_POWER_STUN  "power_stun"
#define OPTIONS_MGR     (GUILD_DIR+"options_manager")
#define SLAM_CAID       50
#define SLAM_TIME       34
#define SHORT_SLAM_TIME 23
#define LIVE_O_ACTION_SLAM_TIME "_live_o_action_slam_time"

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
    set_combat_aid(SLAM_CAID);
    set_tohit(80); // 75% chance of hitting
    set_dt(W_BLUDGEON);
    // Extra damage taken from Strength and Guild Stat
    set_stats(({ SKILL_AVG, TS_STR, TS_CON, SKILL_END }) );
    // Can slam once every 34 seconds on average
    set_ability_time(SLAM_TIME);
    set_ability_name("slam");
    set_ability_attack_during_prep(0);
    
    set_guild_stat_modifier(SS_LAYMAN, 20, 100);
}

/*
 * Function:    get_best_shield
 * Description: Gets the shield with the best AC that's worn
 * Arguments:   actor - person to check
 * Returns:     Returns the best shield or 0, if none worn
 */
public object
get_best_shield(object actor)
{
    object right_shield, left_shield;
    if ( actor->query_armour(W_RIGHT)->query_at() == A_SHIELD )
    {
        right_shield = actor->query_armour(W_RIGHT);
    }
    
    if ( actor->query_armour(W_LEFT)->query_at() == A_SHIELD )
    {
        left_shield = actor->query_armour(W_LEFT);
    }
    
    if (objectp(right_shield) && !objectp(left_shield))
    {
        return right_shield;
    }
    else if (!objectp(right_shield) && objectp(left_shield))
    {
        return left_shield;
    }
    else if (objectp(right_shield) && objectp(left_shield))
    {
        if (right_shield->query_ac() < left_shield->query_ac())
        {
            return left_shield;
        }
        else
        {
            return right_shield;
        }
    }
    
    return 0;
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
    object  player, slam;
    string  shield_short;
    string  attacker_desc,
            defender_desc,
            watcher_desc;
    int     percentage;
    
    player = this_player();
    shield_short = items[0]->short();
    
    OPTIONS_MGR->add_talent(player, OFFENSIVE_TALENT);
    percentage = OPTIONS_MGR->query_control_level(player);
    
    if (phurt >= 0)
    {
        if ((player->query_race() == "hobbit") ||
            (player->query_race_name() == "gnome") )
        {
            attacker_desc = "With a shriek, you run into " + QTNAME(enemy)
            + ", slamming " + HIM(enemy) + " with your " + shield_short + ".\n";
            defender_desc = "With a shriek, " + QTNAME(player) + " runs "
            + "into you, slamming you with " + HIS(player) + " " + shield_short
            + ".\n";
    	    watcher_desc = "With a shriek, " + QTNAME(player) + " runs into "
            + QTNAME(enemy)+ ", slamming " + HIM(enemy) + " with " + HIS(player)
            + " " + shield_short + ".\n";
        }
        else
        {
      	    attacker_desc = "With a roar, you charge into " + QTNAME(enemy)
            + ", slamming " + HIM(enemy) + " with your " + shield_short + ".\n";
    	    defender_desc = "With a roar, " + QTNAME(player) + " charges "
            + "into you, slamming you with " + HIS(player) + " " + shield_short
            + ".\n";
    	    watcher_desc = "With a roar, " + QTNAME(player) + " charges into "
            + QTNAME(enemy)+ ", slamming " + HIM(enemy) + " with " + HIS(player)
            + " " + shield_short + ".\n";
        }
        
        int in_cooldown = enemy->query_in_cooldown();

        switch (phurt)
    	{
        case 0:
            if (in_cooldown)
            {
                attacker_desc += QCTNAME(enemy) + " looks " + "unaffected, "
                + "shrugging off the attack effortlessly.\n";
                defender_desc += "You are unaffected by " + HIS(player)
                + " attack.\n";
                watcher_desc += QCTNAME(enemy) + " looks unaffected, shrugging "
                + "off the attack effortlessly.\n";
            }
            else
            {
                attacker_desc += QCTNAME(enemy) + " stumbles, knocked slightly "
                + "off balance by the attack.\n";
           	    defender_desc += "You stumble, knocked slightly off balance by "
                + "the attack.\n";
        	    watcher_desc += QCTNAME(enemy) + " stumbles, knocked slightly "
                + "off balance by the attack.\n";
        	}
    	    break;

        case 1..6:
            if (in_cooldown)
            {
                attacker_desc += "Your " + shield_short + " crashes into "
                + QTNAME(enemy) + " and bruises " + HIM(enemy) + " deeply.\n";
                defender_desc += QCTNAME(player) + " crashes into you with "
                + HIS(player) + " " + shield_short + " and bruises you deeply"
                + ".\n";
                watcher_desc += QCTNAME(player) + " crashes into "
                + QTNAME(enemy) + " with " + HIS(player) + " " + shield_short
                + " and bruises " + HIM(enemy) + " deeply.\n";
            }
            else
            {
                attacker_desc += QCTNAME(enemy) + " stumbles, knocked slightly "
                + "off balance by the attack.\n";
           	    defender_desc += "You stumble, knocked slightly off balance by "
                + "the attack.\n";
        	    watcher_desc += QCTNAME(enemy) + " stumbles, knocked slightly "
                + "off balance by the attack.\n";
        	}
            break;

        case 7..18:
            if (in_cooldown)
            {
                attacker_desc += "Your momentum propels your " + shield_short
                + " into the side of " + QTNAME(enemy) + " and the impact "
                + "causes " + HIM(enemy) + " to trickle blood.\n";                    
                defender_desc += QCTNAME(player) + " forces " + HIS(player)
                + " " + shield_short + " into you and smashes your sides so "
                + "hard you start to bleed.\n";
                watcher_desc += QCTNAME(player) + " forces " + HIS(player) + " "
                + shield_short + " into " + QTNAME(enemy) + " and smashes "
                + HIS(enemy) + " sides so hard that " + QTNAME(enemy)
                + " begins to trickle blood.\n";
            }
            else
            {
        	    attacker_desc += QCTNAME(enemy) + " struggles to keep "
                + HIS(enemy) + " footing.\n";
        	    defender_desc += "You struggle to keep your feet after the "
                + "mighty attack.\n";
        	    watcher_desc += QCTNAME(enemy) + " struggles to keep "
                + HIS(enemy) + " footing.\n";
        	}
            break;
        case 19..36:
            if (in_cooldown)
            {
                attacker_desc += "You hold your " + shield_short + " tightly "
                + "as you crash forcefully into " + QTNAME(enemy) + " crushing "
                + HIS(enemy) + " bones.\n"; 
                defender_desc += QCTNAME(player) + " crashes into you, forcing "
                + HIS(player) + shield_short + " into your body so hard it you "
                + "hear your bones crack.\n";
                watcher_desc += QCTNAME(player) + " crashes into "
                + QTNAME(enemy) + ", forcing " + HIS(player) + " "
                + shield_short + " into " + QTNAME(enemy) + "'s body so hard "
                + "you hear bones crack.\n";
            }
            else
            {        
                if ( enemy->query_humanoid() )
        	    {
        	        attacker_desc += QCTNAME(enemy) + " retreats backwards "
                    + "fearfully after such a mighty hit!\n";
        	        defender_desc += "Your knees buckle and you fall "
                    + "backwards, unable to keep your footing.\n";
        	        watcher_desc += QCTNAME(enemy)+ "'s knees buckle, forcing "
                    + HIM(enemy) + " backwards onto the ground.\n";
        	    }
        	    else
        	    {
        	        attacker_desc += QCTNAME(enemy) + " retreats backwards "
                    + "fearfully after such a mighty hit!\n";
        	        defender_desc += "You retreat backwards fearfully after "
                    + "such a hard hit!\n";
        	        watcher_desc += QCTNAME(enemy) + " retreats backwards "
                    + "fearfully after such a mighty hit!\n";
        	    }
        	}
            break;
        default:
            if (in_cooldown)
            {
                attacker_desc += "You pull your " + shield_short + " up at "
                + "just the right moment and hit " + HIM(enemy) + " squarely "
                + "in the head causing " + HIM(enemy) + " to spew blood.\n";
                defender_desc += QCTNAME(player) + " brings up " + HIS(player)
                + " " + shield_short + " at just the right moment. The blow "
                + "hits you with great force and causes you to spew blood.\n";
                watcher_desc += QCTNAME(player) + " brings up " + HIS(player)
                + " " + shield_short + " at just the right moment. The blow "
                + "hits " + QTNAME(enemy) + " with great force and causes "
                + HIM(enemy) + " to spew blood.\n";
            }
            else
            {        
        	    attacker_desc += QCTNAME(enemy)+ " collapses to the ground, "
                + "dazed and totally unaware of " + HIS(enemy)
                + " surroundings.\n";
        	    defender_desc += "You feel dizzy... Is that the ground coming "
                + "up to meet you?\n";
        	    watcher_desc += QCTNAME(enemy)+ " collapses to the ground, "
                + "dazed and totally unaware of " + HIS(enemy)
                + " surroundings.\n";
        	}
            break;
    	}
        
        player->catch_msg(attacker_desc);
        enemy->catch_msg(defender_desc);
        player->tell_watcher(watcher_desc, enemy, ({ player, enemy }));
                  
        if ( enemy->query_hp() <= 0 )
        {
            enemy->do_die(player);
    	    return;
        }

        if (!in_cooldown && percentage > 0)
        {
            int stun_cycle = player->query_prop(LIVE_O_ACTION_SLAM_TIME);
            
            if (!stun_cycle)
                stun_cycle = query_ability_time();
            
            seteuid(getuid(TO));
            
            /* We apply a stun to the opponent. */
            slam = clone_object(SLAM_STUN_OBJ);
            slam->set_stun_cycle_time(stun_cycle);
            slam->set_effect_caster(player);
            slam->set_effect_target(enemy);
            slam->config_stun_effect()
            slam->set_phurt_value(phurt);
            slam->move(enemy, 1);
            if (slam->start())
            {
                /* If the start call succeeds, then we check for power stuns */
                send_debug_message("slam", "Stunning enemy for a " + stun_time
                + " seconds stun cycle.");                
    
                if (OPTIONS_MGR->query_option(OPT_POWER_STUN,
                    player->query_real_name()))
                {
                    int sb_avg, target_avg;
                
                    sb_avg = player->query_average_stat();
                    target_avg = enemy->query_average_stat();
                    float size_adj = min(1.0, itof(sb_avg) / itof(target_avg));
                    stun_time = ftoi(itof(stun_time) * size_adj);
                    if (size_adj < 1.0)
                    {
                        send_debug_message("slam", "Power slam time adjusted "
                        + "downwards to " + stun_time + " because of size "
                        + "differences.");
                    }
                
                    /*
                     * If player has specified to execute a power stun, then
                     * both the attacker and the target will be stunned.
                     */
                    slam = clone_object(SLAM_STUN_POWER);
                    slam->set_stun_cycle_time(stun_time);
                    slam->set_effect_caster(player);
                    slam->set_effect_target(enemy);
                    slam->set_phurt_value(phurt);
                    slam->move(enemy, 1);
                    slam->start();    
                
                    slam = clone_object(SLAM_STUN_POWER);
                    slam->set_stun_cycle_time(stun_time);
                    slam->set_effect_caster(player);
                    slam->set_effect_target(player);
                    slam->move(player, 10);
                    slam->start();
                
                    player->catch_msg("You swing your " + shield_short + " "
                    + "around, place your head inside it and force your "
                    + "entire body weight towards " + QTNAME(enemy) + "! "
                    + "The force of the blow causes you to become dazed "
                    + "as well.\n");
                    
                    enemy->catch_msg(QCTNAME(player) + " swings " + HIS(player)
                    + " " + shield_short + " around, places " + HIS(player)
                    + " head inside and forces " + HIS(player) + " whole "
                    + "body into you. You become quite dazed by the force "
                    + "of the impact.\n");
                    
                    player->tell_watcher(QCTNAME(player) + " swings "
                    + HIS(player) + " " + shield_short + " around, places "
                    + HIS(player) + " head inside and forces " + HIS(player)
                    + " whole body into " + QTNAME(enemy) + "! Both are dazed "
                    + "by the force of the impact.\n", enemy, 
                    ({ enemy, player }));                
                }
            }
        }                
    }
    else
    {
        // Missed the slam
        if ((player->query_race() == "hobbit") ||
            (player->query_race_name() == "gnome") )
        {
            player->catch_msg("With a shriek, you run past " + QTNAME(enemy)
            + ", missing " + HIM(enemy) + " with your " + shield_short + ".\n");
            enemy->catch_msg("With a shriek, " + QTNAME(player) + " runs "
            + "past you, missing you with " + HIS(player) + " " + shield_short
            + ".\n");
            player->tell_watcher("With a shriek, " + QTNAME(player) + " runs "
            + "past " + QTNAME(enemy) + ", missing " + HIM(enemy) + " with "
            + HIS(player) + " " + shield_short + ".\n", enemy);
        }
        else
        {
     	    player->catch_msg("With a roar, you charge past " + QTNAME(enemy)
            + ", missing " + HIM(enemy) + " with your " + shield_short + ".\n");
    	    enemy->catch_msg("With a roar, " + QTNAME(player) + " charges "
            + "past you, missing you with " + HIS(player) + " " + shield_short
            + ".\n");
    	    player->tell_watcher("With a roar, " + QTNAME(player) + " charges "
            + "past " + QTNAME(enemy) + ", missing " + HIM(enemy) + " with "
            + HIS(player) + " " + shield_short + ".\n", enemy);
        }
    }

    player->remove_prop(LIVE_O_ACTION_SLAM_TIME);
            
    return;
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
    
    /* Does attacker have the skill? */
    if (!(player->query_skill(SHIELDSLAM_SPECIAL)))
    {
        player->catch_tell("First you should learn how to slam.\n");
        return 0;
    }
    
    if ( member_array(A_SHIELD, player->query_armour(-1)->query_at()) < 0 )
    {
    	player->catch_tell("You cannot slam without a shield!\n");
    	return 0;
    }    

    if (IS_PLAYER_OBJECT(player)
        && !player->query_guild_member(NEIDAR_CLAN)
        && !player->test_bit("Ansalon", 3, 13))
    {
        player->catch_tell("You are not considered a friend of the Neidar "
            + "Clan, and thus cannot use your Shieldbearer abilities!\n");
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

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    if (!objectp(this_player()))
        return;
    write("You feel like you could slam someone again!\n");
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
    write("Your target seems to have escaped!\n");
}

void
slam_message(object who, mixed * targets)
{
    object target;
    
    if (objectp(who->query_attack()))
    {
        // We only show the slam message when someone is starting
        // a fight with it.
        return;
    }

    foreach (mixed item : targets)
    {
        if (pointerp(item) && sizeof(item) > 0)
        {
            target = item[0];
        }
        else if (objectp(item))
        {
            target = item;
        }
        if (objectp(target))
        {
            break;
        }
    }
    
    if (!objectp(target) || !objectp(who))
    {
        return;
    }
    
    if (environment(target) != environment(who))
    {
        // Have already left the fight.
        return;
    }
    
	if ((who->query_race() == "hobbit") ||
            (who->query_race_name() == "gnome") )
    {
  	    who->catch_msg("Your tiny feet pump swiftly as you run bravely towards "
        + QTNAME(target) + "...\n");
        target->catch_msg(QCTNAME(who) + " puts " + HIS(who) + " head down and "
        + "runs bravely towards you, " + HIS(who) + " tiny feet pumping "
        + "swiftly as " + HE(who) + " approaches...\n");
        who->tell_watcher(QCTNAME(who)+ " puts " + HIS(who) + " head down and "
        + "runs bravely towards " + QTNAME(target) + ", " +HIS(who)+ " tiny "
        + "feet pumping swiftly as " + HE(who) + " approaches...\n", target);
    }
    else
    {
	    who->catch_msg("Your stout legs pump hard as you charge furiously "
        + "towards " + QTNAME(target) + "...\n");
        target->catch_msg(QCTNAME(who) + " puts " + HIS(who) + " head down and "
        + "charges towards you, " + HIS(who) + " stout legs pumping harder and "
        + "harder as " + HE(who) + " approaches...\n");
        who->tell_watcher(QCTNAME(who)+ " puts " + HIS(who) + " head down and "
        + "charges furiously at " + QTNAME(target) + ", " +HIS(who)+ " legs "
        + "pumping harder and harder as " + HE(who) + " approaches...\n",
        target);
	}
}

static void 
ability_msg(object actor,mixed * targets,string arg)
{
    object target;
    
    targets = target_ability(actor, arg);

    if (sizeof(targets) > 0)
    {
        target = targets[0];
        actor->catch_msg("You prepare to slam " + QTNAME(target) + ".\n");
    }    

    // Set the property for the slam time so that they don't try
    // and abuse it.
    actor->add_prop(LIVE_O_ACTION_SLAM_TIME, query_ability_time());
}

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
    float running_time;
    
    running_time = 2.0 + itof(random(ftoi(actor->query_speed(3))));
    set_alarm(prep_time - running_time, 0.0, &slam_message(actor, targets));
    send_debug_message("slam", ftoi(prep_time - running_time) + " is the time "
    + "before running.");
}

/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure the person has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required.
 */
static mixed * 
check_required_items(object actor, mixed * targets, string arg, int pretest)
{
    object shield;
    
    shield = get_best_shield(actor);
    if (objectp(shield))
    {
        return ({ shield });
    }
    
    return 0; // Must have a shield to use ability
}

public int
query_combat_aid_modifier()
{
    int modifier, offensive, result;
    
    /* Get the value of the offensive spec */
    offensive = OPTIONS_MGR->query_offensive_level(this_player());
    /* Modify the spec to reveal the caid */
    offensive = (offensive * 100) / max(1, (offensive + 70));
    /* Use the required skill as a final modifier */
    modifier = this_player()->query_skill(SHIELDSLAM_SPECIAL);
    result = (offensive * modifier) / 100
    
    return result;
}

public int
query_ability_cooldown_time()
{
    return query_ability_time() - query_ability_prep_time();
}

public int
query_ability_prep_time()
{
    return 10;
}

/*
 * Function:    query_ability_time
 * Description: This allows the ability to set the time that the
 *              ability will take during preparation. This is
 *              normally set in the ::config_ability through
 *              set_ability_time. However, abilities can override
 *              this if necessary.
 * Arguments:   none
 * Returns:     the time for each special cycle
 */
public int
query_ability_time()
{
    object player;
    
    setuid();
    seteuid(getuid());
    
    player = this_player();
    if (objectp(player) && OPTIONS_MGR->query_option(OPT_SHORT_SLAM,
        player->query_real_name()))
    {
        // If the Neidar prefers a short slam, we will reduce
        // the amount of time to 23 seconds on average
        return SHORT_SLAM_TIME;
    }
    
    // Otherwise just return the default time
    return SLAM_TIME;
}

public mixed 
query_skills()
{
    // We want to use the Appraise Monster skill, which is maxed out
    // at 60. We want to multiply by 167% in order to get 100. However,
    // we want to cap it at 100 so that the skill isn't ridiculous if
    // someone uses an item to improve their appraise monster skill
    
    object player = this_player();
    
    if (player->query_skill(SS_APPR_MON) > 60)
    {
        return ({ SKILL_VALUE, 100 });
    }

    return ({ SKILL_WEIGHT, 167, SS_APPR_MON });
}

public void
hook_already_active(object ability)
{
	write("You are preparing a shield slam already!\n");
}

public void
hook_special_in_cooldown()
{
	write("Patience! You are not ready to slam your opponent yet!\n");
}
