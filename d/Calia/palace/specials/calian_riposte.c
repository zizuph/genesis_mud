/*

    This shadow contains the code for the Calian special Riposte. To be used 
    for testing and making sure everything works before inheriting it in the
    guild shadow.

    Bishop of Calia, June 2005.

 */

#pragma strict_types
#pragma save_binary

#include "defs.h"

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <options.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include CALIAN_HEADER

//Prop for making sure riposte doesn't happen more than 1 in 5 secs:
#define CALIAN_I_LAST_RIPOSTE "_calian_i_last_riposte"


object
query_calian_riposte_shadow()
{
    return this_object();
}

void
remove_riposte_shadow()
{
    remove_shadow();
}

/*
   Returns the weapon wielded that's the most suitable for riposte, or
   zero if no weapon is wielded.

 */
object
find_calian_weapon(object calian)
{
    int i, wep1_type, wep2_type;
    object best_weapon;
    object *weapons = calian->query_weapon(-1);

    for (i = 0 ; i < sizeof(weapons) ; i++)
    {
        if (!objectp(best_weapon))
        {
            best_weapon = weapons[i];
        }
        else
        {
            wep1_type = best_weapon->query_wt();
            wep2_type = weapons[i]->query_wt();
        
            if (wep1_type == wep2_type)
            {
                // Same type? Choose highest pen.
                if (best_weapon->query_pen() < weapons[i]->query_pen())
                {
                    best_weapon = weapons[i];
                }
            }
            else
            if ((wep2_type == W_SWORD))
            {
                //This weapon is a sword, so the last one wasn't. Choose this.
                best_weapon = weapons[i];
            }
            else
            if ((wep2_type == W_POLEARM) &&
                (wep1_type != W_SWORD))
            {
                //The first weapon isn't a polearm or a sword, choose this
                //polearm.
                best_weapon = weapons[i];
            }
            
            //If we get here the weapon wasn't a suitable weapon, so might
            //as well keep the previous best_weapon.    
        }
    }
    
    return best_weapon;    
}

void
print_failed_riposte_msg()
{
    shadow_who->catch_msg("You attempt a riposte maneuver, but fail to" + 
        " position yourself properly.\n");
}

void
print_riposte_attack(object enemy, object enemy_wep, object cal_wep, 
    mixed *hitresult)
{
    string temp, player, victim, onlooker;
    
    if (objectp(enemy_wep))
    {
        switch(random(4))
        {
            case 0:
                player = capitalize(enemy->query_The_name(shadow_who)) + 
                    " strikes at you with " + enemy->query_possessive() +
                    " " + enemy_wep->short() + ", but you see it coming and" +
                    " deflect the blow fluidly. ";
                victim = "You strike at " + shadow_who->query_the_name(enemy) +
                    " with your " + enemy_wep->short() + ", but " + 
                    shadow_who->query_pronoun() + " deflects the blow" +
                    " fluidly. ";
                onlooker = QCTNAME(enemy) + " strikes at " + QTNAME(shadow_who)
                    + " with " + enemy->query_possessive() + " " + 
                    enemy_wep->short() + ", but the blow is deflected" +
                    " fluidly. ";
                break;
            case 1: 
                player = capitalize(enemy->query_The_name(shadow_who)) + 
                    " brings " + enemy->query_possessive() + " " +
                    enemy_wep->short() + " around to attack you, but " +
                    enemy->query_pronoun() + " is too slow and you easily" +
                    " strike the blow aside. ";
                victim = "You bring your " + enemy_wep->short() + " around" +
                    " to attack " + shadow_who->query_the_name(enemy) + "," +
                    " but you are too slow and the the blow is easily struck" +
                    " aside. ";
                onlooker = QCTNAME(enemy) + " brings " + 
                    enemy->query_possessive() + " " + enemy_wep->short() + 
                    " around to attack " + QTNAME(shadow_who) + ", but the" +
                    " attack is too slow and is easily struck aside. ";
                break;
            case 2:
                player = capitalize(enemy->query_The_name(shadow_who)) + 
                    " feints and swings " + enemy->query_possessive() +
                    " " + enemy_wep->short() + " in low against you, but" +
                    " you are prepared for the attack and parry with little" +
                    " difficulty. ";
                victim = "You feint and swing your " + enemy_wep->short() + 
                    " in low against " + shadow_who->query_the_name(enemy) + 
                    ", but " + shadow_who->query_pronoun() + " parries your" +
                    " attack with little difficulty. ";
                onlooker = QCTNAME(enemy) + " feints and swings " + 
                    enemy->query_possessive() + " " + enemy_wep->short() +
                    " in low against " + QTNAME(shadow_who) + ", but the" +
                    " attack is parried with little difficulty. ";
                break;
            default:
                player = capitalize(enemy->query_The_name(shadow_who)) + 
                    " twirls " + enemy->query_possessive() + " " + 
                    enemy_wep->short() + " around quickly, but you are" +
                    " watching " + enemy->query_possessive() + " hands and" +
                    " effortlessly turn the attack aside when " +
                    enemy->query_pronoun() + " lashes out. ";
                victim = "You twirl your " + enemy_wep->short() + " around" +
                    " quickly in an attempt to trick " 
                    + shadow_who->query_the_name(enemy) + ", but " + 
                    shadow_who->query_pronoun() + " effortlessly turns your" +
                    " attack aside when you finally lash out. ";
                onlooker = QCTNAME(enemy) + " twirls " +
                    enemy->query_possessive() + " " + enemy_wep->short() +
                    " quickly, then suddenly lashes out against " + 
                    QTNAME(shadow_who) + ", but the attack is effortlessly" +
                    " turned aside. ";
        }
    }
    else 
    {
        switch (random(4))
        {
            case 0:
                player = capitalize(enemy->query_The_name(shadow_who)) + 
                    " attacks you, but you sidestep the blow. ";
                victim = "You attack " + shadow_who->query_the_name(enemy) +
                    ", but " + shadow_who->query_pronoun() + " sidesteps the" +
                    " blow. ";
                onlooker = QCTNAME(enemy) + " attacks " + QTNAME(shadow_who) +
                    ", but " + shadow_who->query_pronoun() + " sidesteps the" +
                    " blow. ";
                   
                break;
            case 1: 
                player = capitalize(enemy->query_The_name(shadow_who)) + 
                    " attacks you, but you duck just in time to avoid being" +
                    " hit.";
                victim = "You attack " + shadow_who->query_the_name(enemy) +
                    ", but " + shadow_who->query_pronoun() + " ducks just in" +
                    " time to avoid being hit. ";
                onlooker = QCTNAME(enemy) + " attacks " + QTNAME(shadow_who) +
                    ", but " + shadow_who->query_pronoun() + " ducks just in" +
                    " time to avoid being hit. ";
                break;
            case 2:
                player = capitalize(enemy->query_The_name(shadow_who)) + 
                    " attacks you, but you step back quickly and all you feel"+
                    " is a rush of air. ";
                victim = "You attack " + shadow_who->query_the_name(enemy) +
                    ", but " + shadow_who->query_pronoun() + " steps back" +
                    " quickly and your blow falls short. ";
                onlooker = QCTNAME(enemy) + " attacks " + QTNAME(shadow_who) +
                    ", but " + shadow_who->query_pronoun() + " steps back" +
                    " quickly and the blow falls short. ";
                break;
            default:
                player = capitalize(enemy->query_The_name(shadow_who)) + 
                    " attacks you, but you avoid the strike with a timely" +
                    " jump. ";
                victim = "You attack " + shadow_who->query_the_name(enemy) +
                    ", but " + shadow_who->query_pronoun() + " avoids the" +
                    " strike with a timely jump. ";
                onlooker = QCTNAME(enemy) + " attacks " + QTNAME(shadow_who) +
                    ", but " + shadow_who->query_pronoun() + " avoids the" +
                    " strike with a timely jump. ";
        }
    }
    
    player += "With your opponent out of balance, you ";
    victim += "As you are out of balance, " + 
        shadow_who->query_the_name(enemy) + " ";
    onlooker += "With " + shadow_who->query_possessive() + " opponent out of" +
        " balance, " + QTNAME(shadow_who) + " ";
    
    if (!hitresult)
    {
        switch (random(2))
        {
            case 0:
                player += "prepare for a counterattack, but " + 
                    enemy->query_pronoun() + " recovers " +
                    enemy->query_possessive() + " poise before you can act. ";
                victim += "appears to plan a counterattack, but you recover" +
                    " your poise before " + shadow_who->query_pronoun() + " can" +
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
                    shadow_who->query_possessive() + " " + cal_wep->short() +
                    ", but the attack fails to connect. ";
                onlooker += temp + "s at " + QTNAME(enemy) + " with " +
                    shadow_who->query_possessive() + " " + cal_wep->short() +
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
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ", but the attack is ill-timed and glances off" +
                        " harmlessly.";
                    onlooker += "stabs at " + enemy->query_objective() + 
                        " with " + shadow_who->query_possessive() + " " +
                        cal_wep->short() + ", but the attack is ill-timed" +
                        " and glances off harmlessly.";
                    break;
                case 1..5:
                    player += "jab " + enemy->query_objective() + " with" +
                        " your " + cal_wep->short() + ", but only cause a" +
                        " surface wound.";
                    victim += "jabs at you with " + 
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ", but only causes a surface wound.";
                    onlooker += "jabs " + enemy->query_objective() + " with " +
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ", but only causes a surface wound.";                    
                    break;                
                case 6..10:
                    player += "slide your " + cal_wep->short() + " past " +
                        enemy->query_possessive() + " guard and open up" +
                        " painful wound.";
                    victim += "slides " + shadow_who->query_possessive() + " "
                        + cal_wep->short() + " past your guard and opens up" +
                        " a painful wound.";
                    onlooker += "slides " + shadow_who->query_possessive() + 
                        " "+ cal_wep->short() + " past " + 
                        LANG_POSS(QTNAME(enemy)) + " guard and opens up" +
                        " a painful wound.";
                    break;                
                case 11..20:
                    player += "thrust savagely at " + enemy->query_objective() 
                        + " with your " + cal_wep->short() + ", causing a" +
                        " deep wound.";
                    victim += "thrusts savagely at you with " + 
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ", causing a deep wound.";
                    onlooker += "thrusts savagely at " + 
                        enemy->query_objective() + " with " + 
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ", causing a deep wound.";
                    break;                
                case 21..40:
                    player += "skewer " + enemy->query_objective() + " with" +
                        " your " + cal_wep->short() + ", leaving a grievous" +
                        " wound.";
                    victim += "skewers you with " + 
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ", leaving a grievous wound.";
                    onlooker += "skewers " + enemy->query_objective() + 
                        " with " + shadow_who->query_possessive() + " " + 
                        cal_wep->short() + ", leaving a grievous wound.";
                    break;                
                default:
                    player += "poke a hole in " + enemy->query_objective() +
                        " with your " + cal_wep->short() + ".";
                    victim += "pokes a hole in you with " + 
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ".";
                    onlooker += "pokes a hole in " + enemy->query_objective() +
                        " with " + shadow_who->query_possessive() + " " +
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
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ", but only manages to hit you with the flat side" +
                        " and the blow glances off.";
                    onlooker += "lashes out at " + enemy->query_objective() +
                        " with " + shadow_who->query_objective() + " " +
                        cal_wep->short() + ", but only manages to hit with" +
                        " the flat side and the blow glances off.";
                    break;
                case 1..5:
                    player += "cut " + enemy->query_objective() + " with" +
                        " your " + cal_wep->short() + ", but " + 
                        enemy->query_pronoun() + " moves away from the blow" +
                        " and only receives a shallow wound.";
                    victim += " cuts you with " + 
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ", but you move away from the blow and only" +
                        " receive a shallow wound.";
                    onlooker += " cuts " + enemy->query_objective() + " with "+
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ", but " + QTNAME(enemy) + " moves away from the" +
                        " blow and receives only a shallow wound.";
                    break;                
                case 6..10:
                    player += "slice into " + enemy->query_objective() + 
                        " with your " + cal_wep->short() + ", opening up a" +
                        " painful wound.";
                    victim += "slices into you with " + 
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ", opening up a painful wound.";
                    onlooker += "slices into " + enemy->query_objective() + 
                        " with " + shadow_who->query_possessive() + " " +
                        cal_wep->short() + ", opening up a painful wound.";
                    break;                
                case 11..20:
                    player += "deeply wound " + enemy->query_objective() +
                        " with a quick sideswipe of your " + cal_wep->short()
                        + ".";
                    victim += "deeply wounds you with a quick sideswipe of " +
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ".";
                    onlooker += "deeply wounds " + enemy->query_objective() +
                        " with a quick sideswipe of " + 
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ".";
                    break;                
                case 21..40:
                    player += "rend " + enemy->query_objective() + 
                        " brutally with your " + cal_wep->short() + "," +
                        " creating a long and deep gash.";
                    victim += "rends you brutally with " + 
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ", creating a long and deep gash.";
                    onlooker += "rends " + enemy->query_objective() +
                        " brutally with " + shadow_who->query_possessive() + 
                        " " + cal_wep->short() + ", creating a long and deep" +
                        " gash.";
                    break;                
                default:
                    player += "cleave " + enemy->query_objective() + " nearly"+
                        " in two with your " + cal_wep->short() + ".";
                    victim += "cleaves you nearly in two with " + 
                        shadow_who->query_possessive() + " " + cal_wep->short()
                        + ".";
                    onlooker += "cleaves " + enemy->query_objective() + 
                        " nearly in two with " + shadow_who->query_possessive()
                        + " " + cal_wep->short() + ".";            
            }
        } 
    }
    
    shadow_who->catch_msg(player + "\n");
    enemy->catch_msg(victim + "\n");
    shadow_who->tell_watcher(onlooker + "\n", ({shadow_who, enemy}));
}   


/*
 * Function   : query_not_attack_me()
 * Arguments  : who: the attacker, aid: the attack ID
 * Description: Determines whether an attack is successful
 * Returns    : true if the attack fails, false if the attack succeeds
 */
int 
query_not_attack_me(object who, int aid)
{
     int temp = 0;
     int riposte_diff = TASK_ROUTINE;
     int attacker_skill;
     mixed hitresult;
     object opp_wep = who->query_weapon(aid); 
     object calian_riposte_weapon = find_calian_weapon(shadow_who);
     
          
     if (random(100) >= 20)
     {
         //No riposte.
         return shadow_who->query_not_attack_me(who, aid);
     }
     else
     {
         //Checks:
         
         if (who != shadow_who->query_attack())
         {
             //Only intercept blows from the people you're fighting.
             return shadow_who->query_not_attack_me(who, aid);
         }
         
         if (time() - shadow_who->query_prop(CALIAN_I_LAST_RIPOSTE) <= 5)
         {
             //Sanity check: No riposte if last riposte was 5 seconds ago or
             //later.
             if (shadow_who->query_wiz_level())
             {
                 shadow_who->catch_msg("Missed riposte due to sanity" +
                     " check.\n");
             }
             
             return shadow_who->query_not_attack_me(who, aid);
         } 
         
         if (shadow_who->query_prop(LIVE_I_STUNNED)
             || shadow_who->query_prop(LIVE_I_ATTACK_DELAY))
         {
             return shadow_who->query_not_attack_me(who, aid);
         }
         
         if (!objectp(calian_riposte_weapon))
         {
             //No weapon wielded by Calian.
             return shadow_who->query_not_attack_me(who, aid);
         }
         
         if (!CAN_SEE(shadow_who, who))
         {
             //Can't see who we're fighting: no riposte.
             return shadow_who->query_not_attack_me(who, aid);
         }
         
         if (!((calian_riposte_weapon->query_wt() == W_SWORD )
             || (calian_riposte_weapon->query_wt() == W_POLEARM)))
         {
             //Not wielding a sword or polearm.
             return shadow_who->query_not_attack_me(who, aid);
         }
         
         if (calian_riposte_weapon->query_dt() == W_BLUDGEON)
         {
             //No bludgeoning swords/polearms, if they even exist.
             return shadow_who->query_not_attack_me(who, aid);
         }
            

         //End checks.
     
         // Task modifiers:
         
         if (!objectp(opp_wep))
         { 
             //Unarmed opponent:
             riposte_diff += 100;
         }
         
         if (calian_riposte_weapon->query_wt() != W_SWORD)
         {
             //Not using a sword.
             riposte_diff += 100;
         }
     
         if (3 * shadow_who->query_prop(OBJ_I_WEIGHT) < 
             who->query_prop(OBJ_I_WEIGHT))
         {
             //Opponent more than three times as massive.
             riposte_diff += 100;
         }
         
         if (3 * calian_riposte_weapon->query_prop(OBJ_I_WEIGHT) < 
             opp_wep->query_prop(OBJ_I_WEIGHT))
         {
             //Opponent's weapon more than three times as massive.
             riposte_diff += 100;
         }
         
         // End task modifiers.
         
         if (!objectp(opp_wep))
         {
             attacker_skill = SS_UNARM_COMBAT;
         }
         else
         {
             attacker_skill = SS_WEP_FIRST + (int)opp_wep->query_wt()
                 - W_FIRST;
         }
         
    
         if (shadow_who->resolve_task(riposte_diff, ({SS_CALIAN_RIPOSTE_SKILL,
             SS_PARRY, TS_DEX}), who, ({SKILL_WEIGHT, 200, attacker_skill, 
             TS_INT})) <= 0 )
         {
             //Failure!
             print_failed_riposte_msg();
             return shadow_who->query_not_attack_me(who, aid);
         }
         else
         {
             //Success! Figure out how much damage this attack should do.
             
             temp = MAX(25, (shadow_who->query_stat(SS_DEX))/10 + 
                 shadow_who->query_stat(SS_OCCUP)/10 + 
                 calian_riposte_weapon->query_pen()/2);
             
             temp = F_PENMOD(temp, 
                 shadow_who->query_skill(SS_CALIAN_RIPOSTE_SKILL));
                 
             if ((who->query_not_attack_me(shadow_who, 
                 calian_riposte_weapon->query_attack_id()) != 1) && 
                 (shadow_who->query_combat_object()->cb_tohit(-1, 70, who)>=0))
             {
                 hitresult = who->hit_me(temp, 
                     calian_riposte_weapon->query_dt(), shadow_who, -1);
             }

             print_riposte_attack(who, opp_wep, calian_riposte_weapon, 
                 hitresult);
             
             if (hitresult && shadow_who->query_wiz_level())
             {
                 shadow_who->catch_msg("Pen for this attack was: " + temp + 
                     ".\n");
             }

             if (who->query_hp() <= 0)
             {
                 who->do_die(shadow_who);
             }
                          
             shadow_who->add_prop(CALIAN_I_LAST_RIPOSTE, time());
             
             return 1;
         }         
        
     }
}