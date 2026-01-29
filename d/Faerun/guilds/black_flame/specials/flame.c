/* /d/Faerun/guilds/black_flame/specials/flame.c
 *
 * Combat special for the black flames.
 *
 * Nerull 2022
 *
 */

#pragma strict_types
inherit "/d/Genesis/specials/std/damage";

#include "../guild.h"



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

#define POSSESSIVE(x) x->query_possessive()
#define OBJECTIVE(x)  x->query_objective()
#define PRONOUN(x)    x->query_pronoun()
#define HIS(x)        x->query_possessive()
#define HIM(x)        x->query_objective()
#define HE(x)         x->query_pronoun()


public void config_ability()
{
    ::config_ability();
    set_combat_aid(45);
    set_tohit(95);  // 84% chance of hitting

    set_stats( ({ SKILL_WEIGHT, 40, TS_STR, SKILL_WEIGHT, 40, TS_DEX, 
    SKILL_WEIGHT, 20, TS_WIS }) );

    set_skills(({ SS_ANATOMY }) );

    //set_guild_stat_modifier(SS_LAYMAN, 20, 100);
    set_guild_stat_modifier(SS_ANATOMY, 20, 100);

    set_ability_prep_time(7);
    set_ability_cooldown_time(6);
    set_dt(W_SLASH | W_IMPALE);
    set_ability_name("flame");
}


public object
query_wielded_weapon(object actor)
{
    object * weapons;
    
    weapons = filter(actor->query_weapon(-1), 
                     &operator(&)(W_SLASH | W_IMPALE | W_BLUDGEON) @ &->query_dt());

    if (!sizeof(weapons))
    {
        // Not wielding a slashing weapon
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
    
    if (weapon->query_bf_summoned() == 1)
    {
        return ({ weapon });
    }
    
    actor->catch_tell("Weapon requires the black flame.\n");
    return 0;
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
    
    if (!objectp(query_wielded_weapon(player)))
    {
        player->catch_tell("You are not wielding an appropriate weapon.\n");
        
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
    
    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }
    
    if (!validate_requirements(player))
    {
        return 0;
    }
    
    /*if (present("_strangulate_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent strangulation of the "
        +"target, exeecute is not yet ready to be used! Patience!\n");

        return 0;
    }*/
    
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
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    if (!objectp(this_player()))
        return;
    
    write("You are ready to perform flame again.\n");    
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
    string *attack_message;
    object tp = this_player();
    object target = enemy;
    string hitloc = hdesc;
    string weapon = items[0]->short();
    int weapon_type = items[0]->query_wt();
   
    
    if (phurt >= 0)
    {
        switch(phurt)
        {
        case 0:
            attack_message = ({
                  capitalize(target->query_the_name(tp))+ " escapes the swing of your " 
                  +weapon+ " but its black flame slighly burn " +HIS(target)
                  + " " +hitloc+ ".\n",
                  
                 "You escape the swing of " +target->query_the_name(tp)+ "'s " 
                 +weapon+ ", but its black flame manages to slightly burn your " +hitloc
                 + ".\n",
        
                 QCTNAME(target)+ " escapes the swing of " 
                 +QTNAME(tp)+ "'s " +weapon+ ", but its black flame slightly burn " 
                 +HIS(target)+ " " +hitloc+ ".\n"
                });
                
      
                
            
            break;
        case 1..10:
            attack_message = ({
              "You swing your " +weapon+ " in an arch and burn the " 
              +hitloc+ " of " + target->query_the_name(tp)+ " with the black flame.\n",
              
            capitalize(tp->query_the_name(target))+ " swings " 
            +HIS(tp)+ " " +weapon+ " in an arch and burns your " 
            +hitloc+ " with the black flame.\n",
    
            "With a swing of " +HIS(tp)+ " " +weapon+ ", " 
            +QTNAME(tp)+ " burns " +QTNAME(target)+ " 's " +hitloc+ " with "
            +"the black flame.\n"
            });
                       
            
            break;
        
        case 11..30:
            attack_message = ({
              "You thrust your " 
              +weapon+ " with some force, injuring " + target->query_the_name(tp)
              + "'s " +hitloc+ " somewhat while the black flame scorches some flesh.\n",
    
              "As " +tp->query_the_name(target)+ " trusts " +HIS(tp)+ " " 
              +weapon+ " at you, somewhat injuring your " +hitloc+ " while "
              +"its black flame scorches some of your flesh.\n",
    
              "The " +weapon+ " wielded by " +QTNAME(tp)
              + " is trusted with some force at " 
              +QTNAME(target)+ ", injuring their " +hitloc+ " while "
              +"suffering from scorching by the black flame.\n"
            });
            
            
            break;
        case 31..60:
            attack_message = ({
              "With a wild powerful swing, you leave "
              +"a deep scorched wound along " + target->query_the_name(tp)
              + "'s " +hitloc+ " with your " +weapon+ ".\n", 
            
              "With wild brutal force, " +tp->query_the_name(target)+ " swings " 
              +HIS(tp)+ " " +weapon+ " and scores a deep scorched wound "
              +"along your " +hitloc+ ".\n",
    
              "With a wild powerful swing, " 
              +QTNAME(tp)+ " leaves a deep scorched wound along " 
              +QTNAME(target)+ "'s " +hitloc+".\n"
            });

            
            break;
        case 61..80:
            attack_message = ({
              "You drive your "+weapon+" forcefully into " 
              + target->query_the_name(tp)+ "'s "+hitloc+ ", mutilating "
              +"and roasting flesh.\n",
    
             "With great power, " +tp->query_the_name(target)
             + " drives the "+weapon+" into your " 
             +hitloc+", both mutilating and roasting flesh.\n",
    
             capitalize(QTNAME(tp))+ " drives the "+weapon+" with a great "
             +"deal of force into " +QTNAME(target)+ "'s "
             +hitloc+ ", mutilating and roasting flesh.\n" 
            });
            
            
            break;
        case 81..99:
             attack_message = ({
              "Swinging your " +weapon+ " with devastating force into " 
              + target->query_the_name(tp)+ "'s " 
              +hitloc+ ", the black blame consumes a good portion of flesh.\n",
    
              "The " +weapon+ " wielded by " + target->query_the_name(tp)
              + " burrows into your " +hitloc
              + " with devastating force, causing a gruesome wound while "
              +"the black flame consumes a good portion of your flesh.\n",
    
               capitalize(QTNAME(tp))+ " burrows the "+weapon+" with devastating "
             +"force into " +QTNAME(target)+ "'s "
             +hitloc+ "! The black flame consumes a good portion of flesh in "
             +"the process!\n" 
            });
            
  
            break;
        default:              
              attack_message = ({
              "You fatally strike " 
              +target->query_the_name(tp)+ " with your "+weapon+"! The black flame "
              +"suddenly leaps over to "+target->query_possessive()+" body and "
              +"greedily consumes it!\n",
                          
              tp->query_The_name(target)+ " fatally strikes you with the "
              +weapon+"! In an instant, a black flame engulfs your body, and "
              +"you see nothing but darkness! With extreme pain, you are "
              +"completely consumed by it!\n\n",
              
              QCTNAME(tp)+ " fatally strikes " +QTNAME(target)+ " with "
              +weapon+"! The black flame that engulfs "+weapon+" suddenly leaps "
              +"over to "+QTNAME(target)+ "'s body, and greedily consumes "
              +"it!\n"
              });
        }
         
        tp->catch_tell(attack_message[0]);
        target->catch_tell(attack_message[1]);
        tp->tell_watcher(attack_message[2], target);
        
        // A successful attack generates panic
        tp->add_panic(-3 - phurt / 5);      
    }
    else
    {
        tp->catch_tell("You swing clumsily at " 
              +target->query_the_name(tp)+ " with your "
              +weapon+", hitting nothing but air.\n");
          
        target->catch_tell("With a sad excuse of a "
        +"swing, " +tp->query_the_name(target)
              + " misses you entirely with the "+weapon+".\n");
            
        tp->tell_watcher_miss("ith a sad excuse of a "
        +"swing, " +QTNAME(tp)
              + " misses " 
              +QTNAME(target)+ " entirely with the "+weapon+".\n", target);
        
        // A miss emboldens enemies
        tp->add_panic(1);
    }
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(tp);
    }
}


/*
 * Function name:   query_combat_aid_modifier
 * Description:     Calculates the percentage of the maximum combat aid that
 *                  applies to the current situation
 * Arguments:       None
 * Returns:         (int) number between 1 and 100
 */
public int
query_combat_aid_modifier()
{
    int modifier = 45;
    
    // If bf haste effect is present, we reduce caid with 30.
    if (present("_frenzy_object", this_player()))
    {
        modifier -= 30;
    }
    
    return modifier;
} /* query_combat_aid_modifier */



