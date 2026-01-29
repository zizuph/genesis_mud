/*
 * Port of the Minotaur Gore attack to the new Genesis Specials System
 *
 * Created by Petros, August 2008
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

#define GORE_LOG        (GUILD_DIR+"gore_damage")
#define FATIGUE_COST     3
#define HEALTH_COST      5

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
static string *horn_desc = ({"undeveloped horns",
  "growing horns","horns","sharp horns","long horns",
  "deadly horns", "deadly horns", "deadly horns",
  "impressive horns", "impressive horns", 
  "impressive horns", "regal horns",});

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
    set_combat_aid(45);
    set_tohit(85); // 78% chance of hitting
    set_dt(W_IMPALE);
    // Extra damage taken from Strength and Wisdom
    set_stats(({ SKILL_AVG, TS_STR, TS_WIS, SKILL_END }) );
    set_skills(({ SS_GUILD_SPECIAL_SKILL }) );
    // Can gore once every 20 seconds on average
    set_ability_prep_time(8);
    set_ability_cooldown_time(12);
    set_ability_name("gore");
    
    // Doesnt make sense for this ability to be hastened by dual wield.
    set_ability_dual_wield(0);

    set_guild_stat_modifier(SS_LAYMAN, 20, 100);        
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
    string * attack_message;
    string horns;
    int horn_level;
    
    player = this_player();
    horn_level = MIN(11, player->query_stat(SS_LAYMAN) /10);
    horns = horn_desc[horn_level];
    
    if (phurt >= 0) 
    {
    	/* remove some of the attacker's panic */
    	player->add_panic(-3 - phurt / 5);
    
        switch (phurt)
    	{
    	case 0:
    	    attack_message = ({
    	      "You charge past " +enemy->query_the_name(player)+
    	      ", just missing " +HIM(enemy)+ " with your " +horns+ ".\n",
    	      player->query_The_name(enemy)+ " charges past, " +
    	      HIS(player)+ " " +horns+ " just missing you.\n",
    	      QCTNAME(player)+ " charges past " +QTNAME(enemy) +
    	      " as "+ HE(player)+ " tries to gore " +HIM(enemy)+
    	      " with " +HIS(player)+ " " +horns+ ".\n"
    	    });
    	    break;
    	case 1..2:
    	    attack_message = ({
    	      "You lightly rake your " +horns+ " along " +
    	      enemy->query_the_name(player)+ "'s " +hdesc+ ", just drawing " +
                  "blood.\n",
    	      player->query_The_name(enemy)+ " lightly rakes " + HIS(player)+
    	      " " +horns+ " along your " +hdesc + ", just drawing blood.\n",
    	      QCTNAME(player)+ " lightly rakes " +HIS(player)+ 
                  " " +horns+ " along " +QTNAME(enemy)+ "'s " +hdesc+ ", just " +
                  "drawing blood.\n"
    	    });
    	    break;
    	case 3..5:
    	    attack_message = ({
    	      "You snort in annoyance as you just graze " +
    	      enemy->query_the_name(player)+ "'s " +hdesc+ " with your " +
                  horns+ ".\n",
    	      player->query_The_name(enemy)+ " snorts in annoyance as " +
    	      HE(player)+ " just grazes your " +hdesc + " with " +HIS(player)+
                  " " +horns+ ".\n",
    	      QCTNAME(player)+ " snorts in annoyance as " +HE(player)+ 
                  " just grazes " +QTNAME(enemy)+ "'s " +hdesc+ " with " +
                  HIS(player)+ " " +horns+ ".\n"
    	    });              
    	    break;
    	case 6..10:
    	    attack_message = ({
    	      "You thrust your " +horns+ " deeply into " +
    	      enemy->query_the_name(player)+ "'s " +hdesc+ ".\n",
    	      player->query_The_name(enemy)+ " thrusts " + HIS(player)+
    	      " " +horns+ " deeply into your " +hdesc + ".\n",
    	      QCTNAME(player)+ " thrusts " +HIS(player)+ 
                  " " +horns+ " deeply into " +QTNAME(enemy)+ "'s " +hdesc+ ".\n"
    	    });
    	    break;
    	case 11..30:
    	    attack_message = ({
    	      "You viciously whip your " +horns+ " across " +
    	      enemy->query_the_name(player)+ "'s " +hdesc+ ", tearing a " +
                  "nasty wound.\n",
    	      player->query_The_name(enemy)+ " viciously whips " + HIS(player)+
    	      " " +horns+ " across your " +hdesc + ", tearing a nasty wound.\n",
    	      QCTNAME(player)+ " viciously whips " +HIS(player)+ 
                  " " +horns+ " across " +QTNAME(enemy)+ "'s " +hdesc+ ", tearing " +
                  "a nasty wound.\n"
    	    });
    	    break;
    	case 31..50:
    	    attack_message = ({
    	      "You impale " +enemy->query_the_name(player)+ "'s " +hdesc+ 
                  " with your " +horns+ ", wounding " +HIM(enemy)+ " badly.\n",
    	      player->query_The_name(enemy)+ " impales your " +hdesc + 
                 " with " +HIS(player)+ " " +horns+ ", wounding you badly.\n",
    	      QCTNAME(player)+ " impales " +QTNAME(enemy)+ "'s " +hdesc+ 
                 " with " +HIS(player)+ " " +horns+ ", wounding " +HIM(enemy)+
                 " badly.\n"
    	    });
    	    break;
    	case 51..75:
    	    attack_message = ({
    	      "With a roar, you thrust your " +horns+ " repeatedly into " +
    	      enemy->query_the_name(player)+ ", tearing massive wounds in " +
                  HIS(enemy)+ " " +hdesc+ ".\n",
    	      "With a roar, " +player->query_the_name(enemy)+ " thrusts " + HIS(player)+
    	      " " +horns+ " repeatedly into you, tearing massive wounds in your " +hdesc + ".\n",
    	      "With a roar, " +QTNAME(player)+ " thrusts " +HIS(player)+ 
                  " " +horns+ " repeatedly into " +QTNAME(enemy)+ ", tearing massive wounds in " +
                  HIS(enemy)+ " " +hdesc+ ".\n"
    	    });
    	    break;
    	case 76..99:
    	    attack_message = ({
    	      "You bellow victoriously as you smash " +
    	      enemy->query_the_name(player)+ "'s " +hdesc+ " with your " +horns+ ", leaving " +
                  HIM(enemy) +" at your mercy.\n",
    	      player->query_The_name(enemy)+ " bellows victoriously as " + HE(player)+
    	      " smashes you with " +HIS(player)+ " " +horns+ ", leaving you at deaths door!\n",
    	      QCTNAME(player)+ " bellows victoriously as " +HE(player)+ " smashes " +
                 QTNAME(enemy)+ "'s " +hdesc+ " with his " +horns+ ", leaving " +HIM(enemy)+ 
                 " helpless and at " +HIS(player)+ " mercy.\n"
    	    });
    	    break;
    	default:
    	    attack_message = ({
    	      "You thrust your " +horns+ " deeply into " +
    	      enemy->query_the_name(player)+ "'s " +hdesc+ ", lifting " +HIM(enemy)+ 
                  " into the air and then tossing " +HIS(enemy)+ " mortally wounded body " +
                  "to the ground in victory!\n",
    	      player->query_The_name(enemy)+ " thrusts " + HIS(player)+
    	      " " +horns+ " deeply into your " +hdesc + ", lifting you into the air and tossing " +
                  "your mortally wounded body to the ground like a rag doll.\n",
    	      QCTNAME(player)+ " thrusts " +HIS(player)+ 
                  " " +horns+ " deeply into " +QTNAME(enemy)+ "'s " +hdesc+ ", lifting " +HIM(enemy)+ 
                  " into the air and tossing " +HIS(enemy)+ " mortally wounded body to the " +
                  "ground in victory!\n"
    	    });
    	    break;
    	}


    	/* message to the player */
    	player->catch_tell(attack_message[0]);
    
    	/* message to the enemy */
    	enemy->catch_tell(attack_message[1]);
    
    	/* message to onlookers */
    	player->tell_watcher(attack_message[2], enemy);
    
    	if (enemy->query_hp() <= 0)
    	{
    	    enemy->do_die(player);
    	}
    }
    else
    {
        
        /* We get here if the attack missed */
    
        /* add some panic to the player */
        player->add_panic(1);
    
        /* message to player */
        player->catch_msg("You snarl in frustration as "+
                             QTNAME(enemy)+ " easily avoids your " +horns+ ".\n");
    
        /* message to enemy */
        enemy->catch_msg(QCTNAME(player) + " snarls in frustration as " +
                          "you easily avoid " +HIS(player)+ " " +horns+ ".\n");
    
        /* message to onlookers */
        player->tell_watcher(QCTNAME(player) + " snarls in frustration as " +
                               QTNAME(enemy)+ " easily avoids " +HIS(player)+
                               " " +horns+ ".\n", enemy);
    }
    
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
    if (!(player->query_skill(SS_GUILD_SPECIAL_SKILL)))
    {
        player->catch_tell("First you should learn how to gore.\n");
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
    if (player->query_fatigue() > FATIGUE_COST)
    {
        player->add_fatigue(-FATIGUE_COST);
    }
    else
    {
        player->set_fatigue(0);
    	player->heal_hp(-HEALTH_COST);
    	player->catch_msg("The strain of the attack drains you.\n");        
    }
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

    send_debug_message("gore", 
                    name + " gores with Pen of " + pen + ", "
                    + "Damage of " + damage,
                       GORE_LOG);
}

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    write("You feel ready to gore your foes again!\n");
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
    write("The target of your attack seems to have slipped away.\n");    
    hook_special_complete();
}

static void 
ability_msg(object actor,mixed * targets,string arg)
{
    object target;
    
    if (sizeof(targets) > 0)
    {
        target = targets[0];
        actor->catch_msg("You prepare to gore " + QTNAME(target)
                       + " with your horns.\n");
    }
}

public void
hook_attack_object(object ob)
{
    object player;
    
    player = this_player();
    if(!player->query_attack())
    {
        write("You raise your horned head and roar loudly to the heavens, "
            + "eagerly charging into glorious battle!\n");
        say(QCTNAME(player)+ " raises " + player->query_possessive() 
          + " horned head and roars to the heavens, and charges into "
          + "battle!\n");
    }
    else
    {
        ::hook_attack_object(ob);
    }    
}
