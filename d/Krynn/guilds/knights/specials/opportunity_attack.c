/*
 * Opportunity Attack Ability
 * 
 * This attack ability implements the bases for the opportunity
 * attack. An opportunity attack is when someone tries to attack someone
 * other than the tanker. Since they are busy and receiving attacks from
 * someone who is attacking them, the person whom they're currently
 * fighting gets an opportunity to score a hit. It is called from the
 * opportunity attack shadow.
 *
 * The basic concept is taken from D&D, although it does not implement
 * things like moving away from someone incurring an attack.
 *
 * Created by Petros, June 2008
 * Modified by Petros, December 2013
 */
 
#pragma strict_types

#include "../guild.h"
#include "/d/Genesis/specials/std/defs.h"

inherit DAMAGE_LIB;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

// Prototypes
void print_attack_desc(object player, object enemy, object enemy_wep, 
                       object player_wep, mixed * hitresult);

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
    set_stats( TS_STR );
    set_tohit(75);
    set_ability_prep_time(0);
    set_ability_cooldown_time(10);
    set_ability_name("opportunity_attack");
    set_ability_target(target_one_present_enemy);
    
    // Because opportunity attacks are actually being executed
    // by others, it doesn't make sense to use guildstat to
    // scale it here. Therefore, no call will be made to
    // set_guild_stat_modifier.
}

/*
 * Function name: query_main_weapon
 * Description  : Looks for a weapon that the user is wielding
 * Arguments    : none
 * Returns      : weapon that is wielded, or 0
 */
public object
query_main_weapon()
{
    object weapon, player;
    
    player = this_player();
    
    if (!objectp(weapon = player->query_weapon(W_RIGHT))
        && !objectp(weapon = player->query_weapon(W_LEFT))
        && !objectp(weapon = player->query_weapon(W_BOTH)))
    {
        return 0;
    }
    
    return weapon; 
}

/*
 * Function name: query_skills
 * Description  : Use the weapon skill of the person in determining
 *                extra damage.
 * Arguments    : none
 * Returns      : the skill of the wielded weapon
 */
public mixed 
query_skills()
{
    object weapon;
    
    weapon = query_main_weapon();
    if (!objectp(weapon))
    {
        return SS_UNARM_COMBAT;
    }
    
    switch (weapon->query_wt())
    {
    case W_SWORD:
        return SS_WEP_SWORD;
        
    case W_POLEARM:
        return SS_WEP_POLEARM;

    case W_AXE:
        return SS_WEP_AXE;

    case W_KNIFE:
        return SS_WEP_KNIFE;

    case W_CLUB:
        return SS_WEP_CLUB;
    
    case W_MISSILE:
    case W_JAVELIN:
    default:
        // Throw weapons and default, just use unarmed attack
        return SS_UNARM_COMBAT;
    }
}

/*
 * Function name: print_attack_desc
 * Description  : Based on the hitresult, print out description to
 *                the attacker, the victim, and the onlookers.
 * Arguments    : none
 * Returns      : weapon that is wielded, or 0
 */
public void
print_attack_desc(object player, object enemy, object enemy_wep, 
                  object player_wep, mixed *hitresult)
{
    string temp, player_message, victim, onlooker;
    string wdesc;
    int impale_dt = 0, slash_dt = 0;
    
    if (!objectp(player_wep))
    {
        // THis is an unarmed attack.
        switch (random(5))
        {
        case 0:
            wdesc = "hand";
            break;
        
        case 1:
            wdesc = "elbow";
            break;
        
        case 2:
            wdesc = "foot";
            break;
        
        case 3:
            wdesc = "head";
            break;
        
        case 4:
            wdesc = "knee";
            break;
        }
    }
    else
    {
        wdesc = player_wep->short();
        if (player_wep->query_dt() | W_SLASH)
        {
            slash_dt = 1;
        }
        else if (player_wep->query_dt() | W_IMPALE)
        {
            impale_dt = 1;
        }
    }
    
    if (objectp(enemy_wep))
    {
        player_message = capitalize(enemy->query_The_name(player))
            + " maneuvers around you to charge away, "
            + "and you see an opening in " + player->query_possessive() + " defence. ";
        victim = "You maneuver yourself past  " 
            + player->query_the_name(enemy) + ", but in doing so "
            + "you leave an opening in your defence. ";
        onlooker = QCTNAME(enemy) + " maneuvers past " + QTNAME(player)
            + ", but leaves an opening in " 
            + enemy->query_possessive() + " defence. ";
    }
    else 
    {
        player_message = capitalize(enemy->query_The_name(player))
          + " takes " + enemy->query_possessive() + " attention away "
          + "from you to prepare a mounted charge, and you see an opportunity "
          + "to strike. ";
        victim = "You take your attention from " 
            + player->query_the_name(enemy) + " to prepare a mounted charge, "
            + "but in doing so, leave yourself vulnerable to an attack. ";
        onlooker = QCTNAME(enemy) + " focuses " + enemy->query_possessive()
          + " attention away from " 
          + QTNAME(player) + " to prepare a mounted charge, and in doing so, left "
          + enemy->query_possessive() + " defences with a gaping hole. ";
    }
    
    player_message += "With your opponent focused elsewhere, you ";
    victim += "As you are focused elsewhere, " + 
        player->query_the_name(enemy) + " ";
    onlooker += "With " + player->query_possessive() + " opponent focused " 
              + "elsewhere, " + QTNAME(player) + " ";
    
    if (!hitresult)
    {
        player_message += "strike at " + enemy->query_objective() + 
            " with your " + wdesc + ", but the attack" +
            " fails to connect. ";
        victim += "strikes at you with " + 
            player->query_possessive() + " " + wdesc +
            ", but the attack fails to connect. ";
        onlooker += "strikes at " + QTNAME(enemy) + " with " +
            player->query_possessive() + " " + wdesc +
            ", but the attack fails to connect. ";
    }
    else
    {
        //One set of hit messages for slashing weapons, one for impaling:
        
        if (impale_dt)
        {
            switch (hitresult[0])
            {
            case 0:
                player_message += "stab at " + enemy->query_objective() + " with" +
                    " your " + wdesc + ", but the attack is" +
                    " ill-timed and glances off harmlessly.";
                victim += "stabs at you with " + 
                    player->query_possessive() + " " + wdesc
                    + ", but the attack is ill-timed and glances off" +
                    " harmlessly.";
                onlooker += "stabs at " + enemy->query_objective() + 
                    " with " + player->query_possessive() + " " +
                    wdesc + ", but the attack is ill-timed" +
                    " and glances off harmlessly.";
                break;
            case 1..5:
                player_message += "jab " + enemy->query_objective() + " with" +
                    " your " + wdesc + ", but only cause a" +
                    " surface wound.";
                victim += "jabs at you with " + 
                    player->query_possessive() + " " + wdesc
                    + ", but only causes a surface wound.";
                onlooker += "jabs " + enemy->query_objective() + " with " +
                    player->query_possessive() + " " + wdesc
                    + ", but only causes a surface wound.";                    
                break;                
            case 6..10:
                player_message += "slide your " + wdesc + " past " +
                    enemy->query_possessive() + " guard and open up" +
                    " painful wound.";
                victim += "slides " + player->query_possessive() + " "
                    + wdesc + " past your guard and opens up" +
                    " a painful wound.";
                onlooker += "slides " + player->query_possessive() + 
                    " "+ wdesc + " past " + 
                    LANG_POSS(QTNAME(enemy)) + " guard and opens up" +
                    " a painful wound.";
                break;                
            case 11..20:
                player_message += "thrust savagely at " + enemy->query_objective() 
                    + " with your " + wdesc + ", causing a" +
                    " deep wound.";
                victim += "thrusts savagely at you with " + 
                    player->query_possessive() + " " + wdesc
                    + ", causing a deep wound.";
                onlooker += "thrusts savagely at " + 
                    enemy->query_objective() + " with " + 
                    player->query_possessive() + " " + wdesc
                    + ", causing a deep wound.";
                break;                
            case 21..40:
                player_message += "skewer " + enemy->query_objective() + " with" +
                    " your " + wdesc + ", leaving a grievous" +
                    " wound.";
                victim += "skewers you with " + 
                    player->query_possessive() + " " + wdesc
                    + ", leaving a grievous wound.";
                onlooker += "skewers " + enemy->query_objective() + 
                    " with " + player->query_possessive() + " " + 
                    wdesc + ", leaving a grievous wound.";
                break;                
            default:
                player_message += "poke a hole in " + enemy->query_objective() +
                    " with your " + wdesc + ".";
                victim += "pokes a hole in you with " + 
                    player->query_possessive() + " " + wdesc
                    + ".";
                onlooker += "pokes a hole in " + enemy->query_objective() +
                    " with " + player->query_possessive() + " " +
                    wdesc + ".";               
            }
        }
        else if (slash_dt)
        {
            switch (hitresult[0])
            {
            case 0:
                player_message += "lash out at " + enemy->query_objective() +
                    " with your " + wdesc + ", but only" +
                    " manage to hit with the flat side and the blow" +
                    " glances off.";
                victim += "lashes out at you with " + 
                    player->query_possessive() + " " + wdesc
                    + ", but only manages to hit you with the flat side" +
                    " and the blow glances off.";
                onlooker += "lashes out at " + enemy->query_objective() +
                    " with " + player->query_objective() + " " +
                    wdesc + ", but only manages to hit with" +
                    " the flat side and the blow glances off.";
                break;
            case 1..5:
                player_message += "cut " + enemy->query_objective() + " with" +
                    " your " + wdesc + ", but " + 
                    enemy->query_pronoun() + " moves away from the blow" +
                    " and only receives a shallow wound.";
                victim += " cuts you with " + 
                    player->query_possessive() + " " + wdesc
                    + ", but you move away from the blow and only" +
                    " receive a shallow wound.";
                onlooker += " cuts " + enemy->query_objective() + " with "+
                    player->query_possessive() + " " + wdesc
                    + ", but " + QTNAME(enemy) + " moves away from the" +
                    " blow and receives only a shallow wound.";
                break;                
            case 6..10:
                player_message += "slice into " + enemy->query_objective() + 
                    " with your " + wdesc + ", opening up a" +
                    " painful wound.";
                victim += "slices into you with " + 
                    player->query_possessive() + " " + wdesc
                    + ", opening up a painful wound.";
                onlooker += "slices into " + enemy->query_objective() + 
                    " with " + player->query_possessive() + " " +
                    wdesc + ", opening up a painful wound.";
                break;                
            case 11..20:
                player_message += "deeply wound " + enemy->query_objective() +
                    " with a quick sideswipe of your " + wdesc
                    + ".";
                victim += "deeply wounds you with a quick sideswipe of " +
                    player->query_possessive() + " " + wdesc
                    + ".";
                onlooker += "deeply wounds " + enemy->query_objective() +
                    " with a quick sideswipe of " + 
                    player->query_possessive() + " " + wdesc
                    + ".";
                break;                
            case 21..40:
                player_message += "rend " + enemy->query_objective() + 
                    " brutally with your " + wdesc + "," +
                    " creating a long and deep gash.";
                victim += "rends you brutally with " + 
                    player->query_possessive() + " " + wdesc
                    + ", creating a long and deep gash.";
                onlooker += "rends " + enemy->query_objective() +
                    " brutally with " + player->query_possessive() + 
                    " " + wdesc + ", creating a long and deep" +
                    " gash.";
                break;                
            default:
                player_message += "cleave " + enemy->query_objective() + " nearly"+
                    " in two with your " + wdesc + ".";
                victim += "cleaves you nearly in two with " + 
                    player->query_possessive() + " " + wdesc
                    + ".";
                onlooker += "cleaves " + enemy->query_objective() + 
                    " nearly in two with " + player->query_possessive()
                    + " " + wdesc + ".";            
            }
        } 
        else
        {
            switch (hitresult[0])
            {
            case 0:
                player_message += "lash out at " + enemy->query_objective() +
                    " with your " + wdesc + ", but the blow" +
                    " glances off.";
                victim += "lashes out at you with " + 
                    player->query_possessive() + " " + wdesc
                    + ", but the blow glances off.";
                onlooker += "lashes out at " + enemy->query_objective() +
                    " with " + player->query_objective() + " " +
                    wdesc + ", but the blow glances off.";
                break;
            case 1..5:
                player_message += "hit " + enemy->query_objective() + " with" +
                    " your " + wdesc + ", but " + 
                    enemy->query_pronoun() + " moves away from the blow" +
                    " and only receives a shallow wound.";
                victim += " hits you with " + 
                    player->query_possessive() + " " + wdesc
                    + ", but you move away from the blow and only" +
                    " receive a shallow wound.";
                onlooker += " hits " + enemy->query_objective() + " with "+
                    player->query_possessive() + " " + wdesc
                    + ", but " + QTNAME(enemy) + " moves away from the" +
                    " blow and receives only a shallow wound.";
                break;                
            case 6..10:
                player_message += "strike " + enemy->query_objective() + 
                    " with your " + wdesc + ", opening up a" +
                    " painful wound.";
                victim += "strikes you with " + 
                    player->query_possessive() + " " + wdesc
                    + ", opening up a painful wound.";
                onlooker += "strikes " + enemy->query_objective() + 
                    " with " + player->query_possessive() + " " +
                    wdesc + ", opening up a painful wound.";
                break;                
            case 11..20:
                player_message += "deeply wound " + enemy->query_objective() +
                    " with your " + wdesc + ".";
                victim += "deeply wounds you with " +
                    player->query_possessive() + " " + wdesc
                    + ".";
                onlooker += "deeply wounds " + enemy->query_objective() +
                    " with " + player->query_possessive() + " " 
                    + wdesc + ".";
                break;                
            case 21..40:
                player_message += "rend " + enemy->query_objective() + 
                    " brutally with your " + wdesc + "," +
                    " creating a long and deep wound.";
                victim += "rends you brutally with " + 
                    player->query_possessive() + " " + wdesc
                    + ", creating a long and deep wound.";
                onlooker += "rends " + enemy->query_objective() +
                    " brutally with " + player->query_possessive() + 
                    " " + wdesc + ", creating a long and deep" +
                    " wound.";
                break;                
            default:
                player_message += "cleave " + enemy->query_objective() + " nearly"+
                    " in two with your " + wdesc + ".";
                victim += "cleaves you nearly in two with " + 
                    player->query_possessive() + " " + wdesc
                    + ".";
                onlooker += "cleaves " + enemy->query_objective() + 
                    " nearly in two with " + player->query_possessive()
                    + " " + wdesc + ".";            
            }
        }        
    }
    
    player->catch_msg(player_message + "\n");
    enemy->catch_msg(victim + "\n");
    player->tell_watcher(onlooker + "\n", ({ player, enemy }));
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
 * Description  : Does some validation to make sure the Knight has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required.
 */
static mixed * 
check_required_items(object actor, mixed * targets,
                     string arg, int pretest)
{
    object weapon;
    int hand;
    
    weapon = query_main_weapon();
    if (weapon)
    {
        return ({ weapon });
    }
    
    return ({ });
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
    weapon = query_main_weapon();
    opp_wep = enemy->query_weapon(aid);
    
    print_attack_desc(player, enemy, opp_wep, weapon, hitresult);
    send_debug_message("opp_attack", "Opportunity attack was "
                     + "successful. Damage: " + dam);

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
public void 
hook_special_complete()
{
    // Don't display any messages.
}

public void
hook_special_in_cooldown()
{
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

