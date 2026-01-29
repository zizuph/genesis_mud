/*
 * Port of the Minotaur Gore attack to the new Genesis Specials System
 *
 * Created by Petros, August 2008
 *
 * Modified by Mirandus to be part of the New Saurian Racial/Lay guild.
 * It was a simple combat special already part of the new system and
 * thus allowed for easy adaptability.
 *
 * Update Log:
 *   - Mirandus added claw descriptions based on the guild's subloc claws
 *   - Mirandus modified the validate requirements to allow for slashing weapons
 *     and changed the descriptor of claws depending on if unarmed or weapon
 */

#pragma strict_types

#include "lizards.h"

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

#define DISEMBOWEL_LOG        (GUILD_LOG+"disembowel_damage")
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
static string *claw_desc = ({
    "tiny claws",
    "short claws",
    "brittle claws",
    "undeveloped claws",
    "growing claws",
    "curved claws",
    "developing claws",
    "sharp claws",
    "menacing claws",
    "deadly claws",
    "savage claws",
    "vicious claws", 
    "intimidating claws", 
    "knifelike claws",
    "razor-sharp claws",
    "devestating claws",
    "lethal claws",
    });

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
    set_combat_aid(75);
    set_tohit(85); // 78% chance of hitting
    set_dt(W_SLASH);
    // Extra damage taken from Dexterity and Intelligence
    set_stats(({ SKILL_WEIGHT, 40, TS_STR, SKILL_WEIGHT, 40, TS_DEX,
        SKILL_WEIGHT, 20, TS_INT }));
    set_skills(({ SS_GUILD_SPECIAL_SKILL }) );
    // Can disembowel once every 20 seconds on average
    set_ability_prep_time(8);
    set_ability_cooldown_time(12);
    set_ability_name("disembowel");

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
    object *weapons = filter(this_player()->query_weapon(-1), 
        &operator(|)(W_SLASH) @ &->query_wt());
    string * attack_message;
    string claws;
    int claw_level;

    claw_level = min(sizeof(claw_desc) - 1, player->query_stat(SS_LAYMAN) / 10);
    claws = claw_desc[claw_level];
    
    player = this_player();
        
    if (sizeof(weapons) >= 1)
    {
        claws = weapons[0]->query_short();

    }
    
    
    if (phurt >= 0) 
    {
    	/* remove some of the attacker's panic */
    	player->add_panic(-3 - phurt / 5);
    
        switch (phurt)
    	{
    	case 0:
        attack_message = ({
            "You leap at " +enemy->query_the_name(player)+
            ", just missing " +HIM(enemy)+ " with your " +claws+ ".\n",
            player->query_The_name(enemy)+ " leaps past, " +
            HIS(player)+ " " +claws+ " just missing you.\n",
            QCTNAME(player)+ " leaps past " +QTNAME(enemy) +
            "as "+ HE(player)+ " tries to disembowel " +HIM(enemy)+
            " with " +HIS(player)+ " " +claws+ ".\n"
          });
    	    break;
    	case 1..2:
        attack_message = ({
            "You lightly rake your " +claws+ " along " +
            enemy->query_the_name(player)+ "'s " +hdesc+ ", just drawing " +
                "blood.\n",
            player->query_The_name(enemy)+ " lightly rakes " + HIS(player)+
            " " +claws+ " along your " +hdesc + ", just drawing blood.\n",
            QCTNAME(player)+ " lightly rakes " +HIS(player)+ 
                " " +claws+ " along " +QTNAME(enemy)+ "'s " +hdesc+ ", just " +
                "drawing blood.\n"
          });
    	    break;
    	case 3..5:
        attack_message = ({
            "You emit a deep gutteral growl as you just graze " +
            enemy->query_the_name(player)+ "'s " +hdesc+ " with your " +
                claws+ ".\n",
            player->query_The_name(enemy)+ " emits a deep gutteral growl as " +
            HE(player)+ " just grazes your " +hdesc + " with " +HIS(player)+
                " " +claws+ ".\n",
            QCTNAME(player)+ " emits a deep gutteral growl " +HE(player)+ 
                " just grazes " +QTNAME(enemy)+ "'s " +hdesc+ " with " +
                HIS(player)+ " " +claws+ ".\n"
          });               
    	    break;
    	case 6..10:
        attack_message = ({
            "You thrust your " +claws+ " deeply into " +
            enemy->query_the_name(player)+ "'s " +hdesc+ ".\n",
            player->query_The_name(enemy)+ " thrusts " + HIS(player)+
            " " +claws+ " deeply into your " +hdesc + ".\n",
            QCTNAME(player)+ " thrusts " +HIS(player)+ 
                " " +claws+ " deeply into " +QTNAME(enemy)+ "'s " +hdesc+ ".\n"
          });
    	    break;
    	case 11..30:
        attack_message = ({
            "You deeply embed your " +claws+ " into " +
            enemy->query_the_name(player)+ "'s " +hdesc+ ", tearing a " +
                "nasty wound.\n",
            player->query_The_name(enemy)+ " deeply embeds " + HIS(player)+
            " " +claws+ " into your " +hdesc + ", tearing a nasty wound.\n",
            QCTNAME(player)+ " deeply embeds " +HIS(player)+ 
                " " +claws+ " intos " +QTNAME(enemy)+ "'s " +hdesc+ ", tearing " +
                "a nasty wound.\n"
          });
    	    break;
    	case 31..50:
        attack_message = ({
            "You impale " +enemy->query_the_name(player)+ "'s " +hdesc+ 
                " with your " +claws+ ", wounding " +HIM(enemy)+ " badly.\n",
            player->query_The_name(enemy)+ " impales your " +hdesc + 
               " with " +HIS(player)+ " " +claws+ ", wounding you badly.\n",
            QCTNAME(player)+ " impales " +QTNAME(enemy)+ "'s " +hdesc+ 
               " with " +HIS(player)+ " " +claws+ ", wounding " +HIM(enemy)+
               " badly.\n"
          });
    	    break;
    	case 51..75:
        attack_message = ({
            "With a preternatural fury you thrust your " 
            +claws+ " repeatedly into " + enemy->query_the_name(player)+ 
            ", tearing massive wounds in " + HIS(enemy)+ " " +hdesc+ ".\n",
            "With preternatural fury, " +player->query_the_name(enemy)+ 
            " thrusts " + HIS(player)+" " +claws+ " repeatedly into you, "+
            "tearing massive wounds in your " +hdesc + ".\n",
            "With a preternatural fury, " +QTNAME(player)+ " thrusts " 
            +HIS(player)+" " +claws+ " repeatedly into " 
            +QTNAME(enemy)+ ", tearing massive wounds in " +HIS(enemy)+ " " 
            +hdesc+ ".\n"
          });
    	    break;
    	case 76..99:
        attack_message = ({
            "With grim satisfaction you rip into " +
            enemy->query_the_name(player)+ "'s " +hdesc+ " with your " +claws+ 
            ", leaving " +HIM(enemy) +" bloodied and near-death.\n",
            player->query_The_name(enemy)+ " appears grimly satisfied as " 
            + HE(player)+ " rips into you with " +HIS(player)+ " " +claws+
             ", leaving you at deaths door!\n",
            QCTNAME(player)+ " is deeply satisified as" +HE(player)+ 
            " rips into " +QTNAME(enemy)+ "'s " +hdesc+ " with his " 
            +claws+ ", leaving " +HIM(enemy)+" bloodied and near death.\n"
          });
    	    break;
    	default:
        attack_message = ({
            "You thrust your " +claws+ " deeply into " +
            enemy->query_the_name(player)+ "'s stomach , tearing " +HIM(enemy)+ 
                " apart before throwing " +HIS(enemy)+ " disemboweled body " +
                "to the ground!\n",
            player->query_The_name(enemy)+ " thrusts " + HIS(player)+
            " " +claws+ " deeply into your stomach,  tearing you open before " +
                "throwing your disemboweled body to the ground.\n",
            QCTNAME(player)+ " thrusts " +HIS(player)+ 
                " " +claws+ " deeply into " +QTNAME(enemy)+ 
                "'s stcomach, tearing " +HIM(enemy)+ "apart before throwing " 
                +HIS(enemy)+ " disemboweled body ground.\n"
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
                        QTNAME(enemy)+ " easily avoids your " +claws+ ".\n");

    /* message to enemy */
    enemy->catch_msg(QCTNAME(player) + " snarls in frustration as " +
                        "you easily avoid " +HIS(player)+ " " +claws+ ".\n");

    /* message to onlookers */
    player->tell_watcher(QCTNAME(player) + " snarls in frustration as " +
                           QTNAME(enemy)+ " easily avoids " +HIS(player)+
                           " " +claws+ ".\n", enemy);
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
    object *weapons = filter(this_player()->query_weapon(-1), 
        &operator(|)(W_SLASH) @ &->query_wt());
    
    /* Does attacker have the skill? */
    if (!(player->query_skill(SS_GUILD_SPECIAL_SKILL)))
    {
        player->catch_tell("First you should learn how to disembowel.\n");
        return 0;
    }

    if (!sizeof(weapons) && ((player->query_tool(W_BOTH)) || (player->query_tool(W_RIGHT) && 
               player->query_tool(W_LEFT))))
        {
            player->catch_tell("You need to have at least one hand free or "
            +"be using an appropriate weapon.\n");
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

    send_debug_message("disembowel", 
                    name + " disembowels with Pen of " + pen + ", "
                    + "Damage of " + damage,
                       DISEMBOWEL_LOG);
}

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    write("Your preternatural senses feel ready once more!\n");
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
        actor->catch_msg("You prepare to disembowel " + QTNAME(target)+".\n");
    }
}

public void
hook_attack_object(object ob)
{
    object player;
    
    player = this_player();
    if(!player->query_attack())
    {
        write("You leap back onto your haunches prepared to dive, "
            + "forward into battle!\n");
        say(QCTNAME(player)+ " leaps back onto " + player->query_possessive() 
          + " haunches before leaping into battle!\n");
    }
    else
    {
        ::hook_attack_object(ob);
    }    
}
