/*
 * Riposte Attack Ability
 * 
 * Calian Riposte is a parry skill that deflects attacks and scores
 * a hit on the attacker. Here are the conditions
 *   a) The effect has base 20% chance of evading one monster
 *   b) It can only happen once every 5 seconds (once a round)
 *   c) It uses to_hit value of 70 (66% chance)
 *   d) The effect is only effective against the person one is
 *      attacking.
 *   e) Can't be stunned or delayed
 *   f) Has to be able to see the attacker
 *   g) sword or polearm must be wielded
 *
 * Adapted by Petros from the original Calian code, June 2008
 */
 
#pragma strict_types

#include "defs.h"

// Riposte Object is both an evade object as well as a damage special
inherit DAMAGE_LIB;
inherit SPECIALS_UTILITY;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>
#include DEBUGGER_TELL
#include CALIAN_HEADER

#define RIPOSTE_LOG       (CRPALACE_LOGS+"riposte_damage")

// Prototypes
void print_riposte_attack(object player, object enemy, object enemy_wep, 
                          object cal_wep, mixed * hitresult, int noattack);

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
    // Set standard combat aid of 25% for a Riposte Attack
    set_combat_aid(RIPOSTE_ATT_MAX_CAID);
    set_stats( TS_DEX );
    set_skills( SS_CALIAN_RIPOSTE_SKILL );
    set_tohit(70);
    // Riposte happens once a round, but its effect from the evade
    // is instant
    set_ability_prep_time(0);
    set_ability_cooldown_time(5);
    set_ability_no_stun(1);
    set_ability_name("riposte");
    set_ability_target(target_one_present_enemy);  
    
    set_guild_stat_modifier(SS_OCCUP, 20, 100);      
}

void
print_riposte_attack(object calian, object enemy, object enemy_wep, 
                     object cal_wep, mixed *hitresult, int noattack)
{
    string temp, player, victim, onlooker;
    
    if (objectp(enemy_wep))
    {
        switch(random(4))
        {
            case 0:
                player = capitalize(enemy->query_The_name(calian)) + 
                    " strikes at you with " + enemy->query_possessive() +
                    " " + enemy_wep->short() + ", but you see it coming and" +
                    " deflect the blow fluidly. ";
                victim = "You strike at " + calian->query_the_name(enemy) +
                    " with your " + enemy_wep->short() + ", but " + 
                    calian->query_pronoun() + " deflects the blow" +
                    " fluidly. ";
                onlooker = QCTNAME(enemy) + " strikes at " + QTNAME(calian)
                    + " with " + enemy->query_possessive() + " " + 
                    enemy_wep->short() + ", but the blow is deflected" +
                    " fluidly. ";
                break;
            case 1: 
                player = capitalize(enemy->query_The_name(calian)) + 
                    " brings " + enemy->query_possessive() + " " +
                    enemy_wep->short() + " around to attack you, but " +
                    enemy->query_pronoun() + " is too slow and you easily" +
                    " strike the blow aside. ";
                victim = "You bring your " + enemy_wep->short() + " around" +
                    " to attack " + calian->query_the_name(enemy) + "," +
                    " but you are too slow and the the blow is easily struck" +
                    " aside. ";
                onlooker = QCTNAME(enemy) + " brings " + 
                    enemy->query_possessive() + " " + enemy_wep->short() + 
                    " around to attack " + QTNAME(calian) + ", but the" +
                    " attack is too slow and is easily struck aside. ";
                break;
            case 2:
                player = capitalize(enemy->query_The_name(calian)) + 
                    " feints and swings " + enemy->query_possessive() +
                    " " + enemy_wep->short() + " in low against you, but" +
                    " you are prepared for the attack and parry with little" +
                    " difficulty. ";
                victim = "You feint and swing your " + enemy_wep->short() + 
                    " in low against " + calian->query_the_name(enemy) + 
                    ", but " + calian->query_pronoun() + " parries your" +
                    " attack with little difficulty. ";
                onlooker = QCTNAME(enemy) + " feints and swings " + 
                    enemy->query_possessive() + " " + enemy_wep->short() +
                    " in low against " + QTNAME(calian) + ", but the" +
                    " attack is parried with little difficulty. ";
                break;
            default:
                player = capitalize(enemy->query_The_name(calian)) + 
                    " twirls " + enemy->query_possessive() + " " + 
                    enemy_wep->short() + " around quickly, but you are" +
                    " watching " + enemy->query_possessive() + " hands and" +
                    " effortlessly turn the attack aside when " +
                    enemy->query_pronoun() + " lashes out. ";
                victim = "You twirl your " + enemy_wep->short() + " around" +
                    " quickly in an attempt to trick " 
                    + calian->query_the_name(enemy) + ", but " + 
                    calian->query_pronoun() + " effortlessly turns your" +
                    " attack aside when you finally lash out. ";
                onlooker = QCTNAME(enemy) + " twirls " +
                    enemy->query_possessive() + " " + enemy_wep->short() +
                    " quickly, then suddenly lashes out against " + 
                    QTNAME(calian) + ", but the attack is effortlessly" +
                    " turned aside. ";
        }
    }
    else 
    {
        switch (random(4))
        {
            case 0:
                player = capitalize(enemy->query_The_name(calian)) + 
                    " attacks you, but you sidestep the blow. ";
                victim = "You attack " + calian->query_the_name(enemy) +
                    ", but " + calian->query_pronoun() + " sidesteps the" +
                    " blow. ";
                onlooker = QCTNAME(enemy) + " attacks " + QTNAME(calian) +
                    ", but " + calian->query_pronoun() + " sidesteps the" +
                    " blow. ";
                   
                break;
            case 1: 
                player = capitalize(enemy->query_The_name(calian)) + 
                    " attacks you, but you duck just in time to avoid being" +
                    " hit. ";
                victim = "You attack " + calian->query_the_name(enemy) +
                    ", but " + calian->query_pronoun() + " ducks just in" +
                    " time to avoid being hit. ";
                onlooker = QCTNAME(enemy) + " attacks " + QTNAME(calian) +
                    ", but " + calian->query_pronoun() + " ducks just in" +
                    " time to avoid being hit. ";
                break;
            case 2:
                player = capitalize(enemy->query_The_name(calian)) + 
                    " attacks you, but you step back quickly and all you feel"+
                    " is a rush of air. ";
                victim = "You attack " + calian->query_the_name(enemy) +
                    ", but " + calian->query_pronoun() + " steps back" +
                    " quickly and your blow falls short. ";
                onlooker = QCTNAME(enemy) + " attacks " + QTNAME(calian) +
                    ", but " + calian->query_pronoun() + " steps back" +
                    " quickly and the blow falls short. ";
                break;
            default:
                player = capitalize(enemy->query_The_name(calian)) + 
                    " attacks you, but you avoid the strike with a timely" +
                    " jump. ";
                victim = "You attack " + calian->query_the_name(enemy) +
                    ", but " + calian->query_pronoun() + " avoids the" +
                    " strike with a timely jump. ";
                onlooker = QCTNAME(enemy) + " attacks " + QTNAME(calian) +
                    ", but " + calian->query_pronoun() + " avoids the" +
                    " strike with a timely jump. ";
        }
    }
    
    if (noattack)
    {    
        // If there is no riposte attack, then we only want to print
        // the first part.
        calian->catch_msg(player + "\n");
        enemy->catch_msg(victim + "\n");
        special_tell_watcher(calian, onlooker + "\n", enemy, 0);        
        return;
    }
    
    player += "With your opponent out of balance, you ";
    victim += "As you are out of balance, " + 
        calian->query_the_name(enemy) + " ";
    onlooker += "With " + calian->query_possessive() + " opponent out of" +
        " balance, " + QTNAME(calian) + " ";
    
    if (!hitresult || hitresult[0] < 0)
    {
        switch (random(2))
        {
            case 0:
                player += "prepare for a counterattack, but " + 
                    enemy->query_pronoun() + " recovers " +
                    enemy->query_possessive() + " poise before you can act. ";
                victim += "appears to plan a counterattack, but you recover" +
                    " your poise before " + calian->query_pronoun() + " can" +
                    " act. ";
                onlooker += "appears to plan a counterattack, but " + 
                    QTNAME(enemy) + " recovers " + 
                    enemy->query_possessive() + " poise too quickly. ";
                break;
            default:
            
                if (cal_wep->query_dt() | W_IMPALE)
                {
                    temp = "thrust"; 
                }
                else
                {
                    temp = "swing";
                }
            
                player += temp + " at " + enemy->query_objective() + 
                    " with your " + cal_wep->short() + ", but the attack" +
                    " fails to connect. ";
                victim += temp + "s at you with " + 
                    calian->query_possessive() + " " + cal_wep->short() +
                    ", but the attack fails to connect. ";
                onlooker += temp + "s at " + QTNAME(enemy) + " with " +
                    calian->query_possessive() + " " + cal_wep->short() +
                    ", but the attack fails to connect. ";
        }
    }
    else
    {
        //One set of hit messages for slashing weapons, one for impaling:
        
        if (cal_wep->query_dt() | W_IMPALE)
        {
            switch (hitresult[0])
            {
                case 0:
                    player += "stab at " + enemy->query_objective() + " with" +
                        " your " + cal_wep->short() + ", but the attack is" +
                        " ill-timed and glances off harmlessly.";
                    victim += "stabs at you with " + 
                        calian->query_possessive() + " " + cal_wep->short()
                        + ", but the attack is ill-timed and glances off" +
                        " harmlessly.";
                    onlooker += "stabs at " + enemy->query_objective() + 
                        " with " + calian->query_possessive() + " " +
                        cal_wep->short() + ", but the attack is ill-timed" +
                        " and glances off harmlessly.";
                    break;
                case 1..5:
                    player += "jab " + enemy->query_objective() + " with" +
                        " your " + cal_wep->short() + ", but only cause a" +
                        " surface wound.";
                    victim += "jabs at you with " + 
                        calian->query_possessive() + " " + cal_wep->short()
                        + ", but only causes a surface wound.";
                    onlooker += "jabs " + enemy->query_objective() + " with " +
                        calian->query_possessive() + " " + cal_wep->short()
                        + ", but only causes a surface wound.";                    
                    break;                
                case 6..10:
                    player += "slide your " + cal_wep->short() + " past " +
                        enemy->query_possessive() + " guard and open up" +
                        " painful wound.";
                    victim += "slides " + calian->query_possessive() + " "
                        + cal_wep->short() + " past your guard and opens up" +
                        " a painful wound.";
                    onlooker += "slides " + calian->query_possessive() + 
                        " "+ cal_wep->short() + " past " + 
                        LANG_POSS(QTNAME(enemy)) + " guard and opens up" +
                        " a painful wound.";
                    break;                
                case 11..20:
                    player += "thrust savagely at " + enemy->query_objective() 
                        + " with your " + cal_wep->short() + ", causing a" +
                        " deep wound.";
                    victim += "thrusts savagely at you with " + 
                        calian->query_possessive() + " " + cal_wep->short()
                        + ", causing a deep wound.";
                    onlooker += "thrusts savagely at " + 
                        enemy->query_objective() + " with " + 
                        calian->query_possessive() + " " + cal_wep->short()
                        + ", causing a deep wound.";
                    break;                
                case 21..40:
                    player += "skewer " + enemy->query_objective() + " with" +
                        " your " + cal_wep->short() + ", leaving a grievous" +
                        " wound.";
                    victim += "skewers you with " + 
                        calian->query_possessive() + " " + cal_wep->short()
                        + ", leaving a grievous wound.";
                    onlooker += "skewers " + enemy->query_objective() + 
                        " with " + calian->query_possessive() + " " + 
                        cal_wep->short() + ", leaving a grievous wound.";
                    break;                
                default:
                    player += "poke a hole in " + enemy->query_objective() +
                        " with your " + cal_wep->short() + ".";
                    victim += "pokes a hole in you with " + 
                        calian->query_possessive() + " " + cal_wep->short()
                        + ".";
                    onlooker += "pokes a hole in " + enemy->query_objective() +
                        " with " + calian->query_possessive() + " " +
                        cal_wep->short() + ".";               
            }
        }
        else
        {
            switch (hitresult[0])
            {
                case 0:
                    player += "lash out at " + enemy->query_objective() +
                        " with your " + cal_wep->short() + ", but only" +
                        " manage to hit with the flat side and the blow" +
                        " glances off.";
                    victim += "lashes out at you with " + 
                        calian->query_possessive() + " " + cal_wep->short()
                        + ", but only manages to hit you with the flat side" +
                        " and the blow glances off.";
                    onlooker += "lashes out at " + enemy->query_objective() +
                        " with " + calian->query_objective() + " " +
                        cal_wep->short() + ", but only manages to hit with" +
                        " the flat side and the blow glances off.";
                    break;
                case 1..5:
                    player += "cut " + enemy->query_objective() + " with" +
                        " your " + cal_wep->short() + ", but " + 
                        enemy->query_pronoun() + " moves away from the blow" +
                        " and only receives a shallow wound.";
                    victim += " cuts you with " + 
                        calian->query_possessive() + " " + cal_wep->short()
                        + ", but you move away from the blow and only" +
                        " receive a shallow wound.";
                    onlooker += " cuts " + enemy->query_objective() + " with "+
                        calian->query_possessive() + " " + cal_wep->short()
                        + ", but " + QTNAME(enemy) + " moves away from the" +
                        " blow and receives only a shallow wound.";
                    break;                
                case 6..10:
                    player += "slice into " + enemy->query_objective() + 
                        " with your " + cal_wep->short() + ", opening up a" +
                        " painful wound.";
                    victim += "slices into you with " + 
                        calian->query_possessive() + " " + cal_wep->short()
                        + ", opening up a painful wound.";
                    onlooker += "slices into " + enemy->query_objective() + 
                        " with " + calian->query_possessive() + " " +
                        cal_wep->short() + ", opening up a painful wound.";
                    break;                
                case 11..20:
                    player += "deeply wound " + enemy->query_objective() +
                        " with a quick sideswipe of your " + cal_wep->short()
                        + ".";
                    victim += "deeply wounds you with a quick sideswipe of " +
                        calian->query_possessive() + " " + cal_wep->short()
                        + ".";
                    onlooker += "deeply wounds " + enemy->query_objective() +
                        " with a quick sideswipe of " + 
                        calian->query_possessive() + " " + cal_wep->short()
                        + ".";
                    break;                
                case 21..40:
                    player += "rend " + enemy->query_objective() + 
                        " brutally with your " + cal_wep->short() + "," +
                        " creating a long and deep gash.";
                    victim += "rends you brutally with " + 
                        calian->query_possessive() + " " + cal_wep->short()
                        + ", creating a long and deep gash.";
                    onlooker += "rends " + enemy->query_objective() +
                        " brutally with " + calian->query_possessive() + 
                        " " + cal_wep->short() + ", creating a long and deep" +
                        " gash.";
                    break;                
                default:
                    player += "cleave " + enemy->query_objective() + " nearly"+
                        " in two with your " + cal_wep->short() + ".";
                    victim += "cleaves you nearly in two with " + 
                        calian->query_possessive() + " " + cal_wep->short()
                        + ".";
                    onlooker += "cleaves " + enemy->query_objective() + 
                        " nearly in two with " + calian->query_possessive()
                        + " " + cal_wep->short() + ".";            
            }
        } 
    }
    
    calian->catch_msg(player + "\n");
    enemy->catch_msg(victim + "\n");
    special_tell_watcher(calian, onlooker + "\n", enemy, 0);
}  
 
// Riposte Attack Section


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
    int modifier;
    object * team, * calians;
    object player;
        
    player = this_player();
    // Start out with modifier 100
    modifier = 100;
    
    team = player->query_team_others();
    team = FILTER_PRESENT_LIVE(team);
    calians = filter(team, &->has_calian_shadow());
    
    if (sizeof(calians) == 0)
    {
        modifier = RIPOSTE_ATT_SOLO_CAID;
    }
    
    send_debug_message("riposte_attack", "combat aid modifier for this "
                     + "riposte attack is " + modifier);
    return modifier;
}

/*
 * Function name: query_tohit
 * Description  : Calculates the tohit for the player. Based on
 *                swarm knowledge or wisdom
 * Arguments    : player - player to check
 * Returns      : input to cb_tohit function
 */
public int 
query_tohit()
{
    object weapon, player, attacker;
    int percentage, tohit;
    mixed enemy_weapons;
                
    player = this_player();
    attacker = player->query_attack();
    
    tohit = ::query_tohit(); // by default it's 70
    percentage = 100; // start at 100%    
    weapon = player->query_calian_main_weapon();     
    
    // There are thing sthat will reduce the chance of the riposte. Each
    // condition reduces the effectiveness by 15%
    // 1. Weapon is not a sword or polearm
    // 2. Opponent is unarmed
    // 3. Opponent is at least 3 times more massive
    
    if (weapon->query_wt() != W_SWORD 
        && weapon->query_wt() != W_POLEARM)
    {
        send_debug_message("riposte_attack", "Not using sword or polearm, "
                         + "reducing tohit by 15%");        
        //Not using a sword or polearm
        percentage -= 15;
    }
 
    if (3 * player->query_prop(OBJ_I_WEIGHT) < 
        attacker->query_prop(OBJ_I_WEIGHT))
    {
        send_debug_message("riposte_attack", "Opponent too massive, "
                         + "reducing tohit by 15%");        
        //Opponent more than three times as massive.
        percentage -= 15;
    }
               
    tohit = (tohit * percentage) / 100;
    
    send_debug_message("riposte_attack", "Final tohit value: " + tohit);
    return tohit;
}

/*
 * Function name: query_dt
 * Description  : Checks the weapons and returns the weapon type
 * Arguments    : items - array of required items. Should only be one
 *                        weapon in the array
 * Returns      : the damage type
 */
public int 
query_dt(object * items)
{
    if (!sizeof(items))
    {
        // Return the default damage type
        return ::query_dt(items);
    }

    // Otherwise, just return the damage type of the wielded weapon    
    return items[0]->query_dt();
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
    int hand;
    
    weapon = actor->query_calian_main_weapon();
    if (weapon)
    {
        return ({ weapon });
    }
    
    return 0;  // Need to be wielding some sort of weapon
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
 * Returns      : nothing
 */
public void 
special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt, int phit, 
                int dam, mixed * items)
{
    object player, weapon, opp_wep;
    mixed * hitresult;
    
    hitresult = ({ phurt >= 0 ? phurt : 0, hdesc, phit, dam, hid });
    player = this_player();
    weapon = player->query_calian_main_weapon();
    opp_wep = enemy->query_weapon(aid);
    
    print_riposte_attack(player, enemy, opp_wep, weapon, hitresult, 0);

    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(player);
    }                                                      
}

/*
 * Function name: hook_special_complete
 * Description  : Hook that gets called when a special completes
 *                Use this to display messages and to restart
 *                specials.
 * Arguments    : none. this_player() is valid
 * Returns      : nothing
 */
public void hook_special_complete()
{
    // Don't display any messages.
}

/*
 * Function name: ability_msg
 * Description  : Mask this function so that the prepare messages don't
 *                show up when this ability goes off.
 * Arguments    : actor - person doing the attack
 *                targets - list of targets for the attack
 *                args - arguments passed in to do_ability
 * Returns      : nothing
 */
static void 
ability_msg(object actor, mixed * targets, string arg)
{
    // Don't display any prepare messages
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

    send_debug_message("riposte_attack", 
                    name + " ripostes with Pen of " + pen + ", "
                    + "Damage of " + damage,
                       RIPOSTE_LOG);
}

public void
restart_npc_special(object player, string arg)
{    
    // Riposte Attack is not something that should be
    // restarted after it hits. Otherwise it gives
    // abnormal combat aid during testing of npcs.
}
