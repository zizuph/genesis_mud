/*
 * /d/Faerun/guilds/vampires/shadows/vamp_combat_msg.c
 *
 * Vampires Combat messages.
 *
 * Nerull 2021  
 *
 * 2021-05-03 - Cotillion
 * - Fixed a runtime
 */
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <language.h>
#include <formulas.h>
#include <options.h>
#include "/std/combat/combat.h"
#include "../guild.h"


public string
cr_attack_desc(int aid)
{
    return shadow_who->cr_attack_desc(aid);
}


int cr_did_hit(int aid, string hdesc, int phurt, object enemy, 
int dt, int phit, int dam)
{
    string name;
    string wpn;

    int spcl;
    int hd;

    name = SW->query_name();

    hd = random(3);
    spcl = random(4);

    object weaponob_left;
    object weaponob_right;
    object weaponob_both;
    
    weaponob_left = shadow_who->query_weapon(W_LEFT);
    weaponob_right = shadow_who->query_weapon(W_RIGHT);
    weaponob_both = shadow_who->query_weapon(W_BOTH);
    
    string weapon_left = weaponob_left->query_short();
    string weapon_right = weaponob_right->query_short();
    string weapon_both = weaponob_both->query_short();
    

    if (aid == W_RIGHT)
    {
        wpn = weapon_right;
        
        if (wpn == 0)
        {
            return SW->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
        }
    }

    if (aid == W_LEFT)
    {
        wpn = weapon_left;
        
        if (wpn == 0)
        {
            return SW->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
        }
    }
    
    if (aid == W_BOTH)
    {
        wpn = weapon_both;
        
        if (wpn == 0)
        {
            return SW->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
        }
    }
    
    if (aid == W_FOOTR)
    {
        return SW->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }
    
    if (aid == W_FOOTL)
    {
        return SW->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    /* This is important, don't remove it */
    if (!objectp(enemy))
        return 0;


    // Messages
    switch (phurt)
    {
        // Miss
        case -1:
        if (!SW->query_option(OPT_GAG_MISSES))
        {
            shadow_who->catch_msg("You rush at " 
            + QTPNAME(enemy) + " and jab in multiple directions "
            +"with your "+wpn+" but fail to score a hit.\n");
        }

        if (!enemy->query_option(OPT_GAG_MISSES))
        {
            enemy->catch_msg(QCTNAME(shadow_who) 
            +" rushes at you jabbing "
            +shadow_who->query_possessive()+" "+wpn
            +", but you dodge each thrust.\n");
        }

        shadow_who->tell_watcher_miss(QCTNAME(shadow_who) 
        +" rushes toward " +QTPNAME(enemy)+ " but " 
        +enemy->query_pronoun()+ " manage to dodge the "
        +"attacks.\n", enemy);
        break;
        
        
        
        // Minimal damage / penetration
        case 0..15:     
        shadow_who->catch_msg("You swing your " +wpn
        + " wildly at " + QTNAME(enemy) + " and manage to cut " 
        +enemy->query_possessive()+ " " + hdesc + " superficially.\n");

        enemy->catch_msg(QCTNAME(shadow_who)+" swings wildly at you "
        +"with "+SW->query_possessive() + " " + wpn + ", cutting you "
        +"superficially on the " +hdesc+ ".\n");

        shadow_who->tell_watcher(QCTNAME(shadow_who) +" swings wildly at " 
        + QTNAME(enemy)+ " with " + SW->query_possessive()
        + " " + wpn + ", causing a superficial cut.\n", enemy);
        break;
        
        
        

        // Low damage
        case 16..30:
        shadow_who->catch_msg("Lunging at " + QTNAME(enemy) 
        + ", you manage to slice " +enemy->query_possessive()
        + " " + hdesc + " with your " +wpn+ ".\n");

        enemy->catch_msg(QCTNAME(shadow_who) +" lunges with " 
        +SW->query_possessive() + " " + wpn + ", slicing your " 
        +hdesc+ ".\n");

        shadow_who->tell_watcher(QCTNAME(shadow_who) +" lunges at " 
        + QTNAME(enemy)+ " and slices " + enemy->query_possessive()
        + " " + hdesc + " with " + SW->query_possessive()+ " " 
        + wpn + ".\n", enemy);
        break;
        
        
        
        // Avg damage
        case 31..60:
        shadow_who->catch_msg("You feint, pause, and then "
        +"with rapid succession, viciously slash " 
        + QTNAME(enemy) + " multiple times on the " 
        + hdesc + " with your " +wpn+ ".\n");

        enemy->catch_msg(QCTNAME(shadow_who)+" moves, pauses "
        +"and then viciouslyly slashes your " 
        + hdesc + " with " +SW->query_possessive() 
        + " " + wpn + " multiple times in rapid succession.\n");

        shadow_who->tell_watcher(QCTNAME(shadow_who)+" moves, pauses "
        +"and then viciously slashes " + QTNAME(enemy)
        + " on the " + hdesc + " with " + SW->query_possessive()
        + " " + wpn + " multiple times in rapid succession.\n", enemy);
        break;
        
        
        
        // High damage
        case 61..95:
        shadow_who->catch_msg("Rushing forward you nearly "
        +"eviscerate " + QTNAME(enemy) + " with your " 
        + wpn + " by causing a gruesome wound across " 
        +enemy->query_possessive()+ " belly.\n");

        enemy->catch_msg(QCTNAME(shadow_who)+" rushes forward "
        +"and deals you a gruesome wound across your "
        +"belly with " +SW->query_possessive() + " " 
        + wpn + ", nearly eviscerating you.\n");

        shadow_who->tell_watcher(QCTNAME(shadow_who)+" rushes "
        +"forward and deals " + QTNAME(enemy)
        + " a gruesome wound across " + enemy->query_possessive()
        + " belly.\n", enemy);
        break;
        
        
        
        // Extremely high damage
        case 96..99:               
        shadow_who->catch_msg("Crouching low, you explode with "
        +"unnatural speed and viciously maul " + QTNAME(enemy)
        + ", severely injuring " + enemy->query_possessive()+ " " 
        + hdesc + " with your " + wpn + ".\n");

        enemy->catch_msg(QCTNAME(shadow_who)+" crouches low "
        +"and explodes in a blur of movement to viciously "
        +"maul your " + hdesc + " with " +SW->query_possessive() 
        + " " + wpn + ".\n");

        shadow_who->tell_watcher(QCTNAME(shadow_who)+" crouches "
        +"low and explodes in a blur of movement to viciously "
        +"maul " + enemy->query_possessive()+ " " + hdesc + " with " 
        + SW->query_possessive()+ " " + wpn + ".\n", enemy);
        break;
        
        
        
        // Target dies. We will add blood logic here.
        default:
        /*shadow_who->catch_msg("In a blur of movement and wretched sound, " 
        + enemy->query_the_name(shadow_who)+ " slides from the blade of your " 
        +wpn+ " only to kneel, dead, in a pile of their own viscera.\n");
                  
        enemy->catch_msg("You briefly lose sight of " 
        +QTNAME(shadow_who)+"'s " +wpn+ ". You can feel the blade "
        +"sliding out of your abdomen, leaving no strength in your "
        +"legs as the pain drains away.\n");
      
        shadow_who->tell_watcher("A blur of movement followed by an "
        +"awful squelching sound accompanies the sight of " 
        +QTNAME(enemy)+" sliding limply from " +QTNAME(shadow_who)+ "'s " 
        +wpn+ ", only to slump, kneeling, in an expanding pile of viscera.\n");*/
        
        //int diceroll = random(20);
        
       // if (diceroll == 1)
       // {
           /* if (enemy->query_prop(LIVE_I_UNDEAD))
            { 
                shadow_who->catch_msg("With unnatural speed, you move and grip " 
                + QTNAME(enemy)+ " by the throat and sewers "
                +enemy->query_possessive()+" spine!\n");
                          
                enemy->catch_msg(QCTNAME(shadow_who)+ " suddenly appears before you and grabs "
                +"you by the throat! Before you have a time to react, you feel your spine "
                +"is brutally sewered!\n");
              
                shadow_who->tell_watcher(QCTNAME(shadow_who)
                + " suddenly blinks before " +QTNAME(enemy)+ " and "
                +"grabs "+enemy->query_objective()+" by the throat! Within "
                +"a split second,  "+QTNAME(shadow_who)+" sewers the spine of " 
                +QTNAME(enemy)+ "!\n");   
                break;                
            }
            else
            {
                shadow_who->catch_msg("With unnatural speed, you move and grip " 
                +QTNAME(enemy)+ " by the throat sinking your "
                +"fangs into "+enemy->query_possessive()+" neck! Greedily, "
                +"you drain every last drop of warm blood from "
                +QTNAME(enemy)+ " before the heart stops!\nYou toss the "
                +"lifeless corpse aside!\n");
                              
                enemy->catch_msg(QCTNAME(shadow_who)+ " suddenly appears before you and grabs "
                +"you by the throat! You feel a pair of fangs sink deep into your neck, and "
                +"have the strange sensation of the last of your blood being drained from your "
                +"body! The world fades to black as your heart beats for "
                +"the very last time.\n");
                  
                shadow_who->tell_watcher(QCTNAME(shadow_who)
                + " suddenly blinks before " +QTNAME(enemy)+ " and "
                +"grabs "+enemy->query_objective()+" by the throat before sinking a pair of "
                +"white fangs into the neck! Blood spills from the mouth of "
                +QTNAME(shadow_who)+" when the lifeless corpse of " +QTNAME(enemy)+ " is released "
                +"from the rigid grasp and tossed at the ground!\n", enemy);
                
                int thirstvalue = VAMPIRES_MAPPINGS->query_thirst_gauge(shadow_who->query_name());
                int agevalue = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name());
                
                int thirstvaluecapocc;
                
                switch(agevalue)
                {
                    case 0..24:
                    thirstvaluecapocc = 24;
                    break;
                    
                    case 25..48:
                    thirstvaluecapocc = 48;
                    break;
                    
                    case 49..72:
                    thirstvaluecapocc = 72;
                    break;
                    
                    case 73..100:
                    thirstvaluecapocc = 100;
                    break;
                    
                    case 101..250:
                    thirstvaluecapocc = 150;
                    break;

                    case 251..500:
                    thirstvaluecapocc = 200;
                    break;
                    
                    case 501..1000:
                    thirstvaluecapocc = 250;
                    break;
                    
                    case 1001..1440:
                    thirstvaluecapocc = 300;
                    break;
             
                    case 1441..1450:
                    thirstvaluecapocc = 350;
                    break;
                    
                    case 1451..2000:
                    thirstvaluecapocc = 400;
                    break;
                    
                    case 2001..3000:
                    thirstvaluecapocc = 450;
                    break;
                    
                    case 3001..5000:
                    thirstvaluecapocc = 500;
                    break;
                    
                    case 5001..7000:
                    thirstvaluecapocc = 550;
                    break;
                    
                    case 7001..9000:
                    thirstvaluecapocc = 600;
                    break;
                    
                    case 9001..11000:
                    thirstvaluecapocc = 700;
                    break;
                    
                    case 11001..13000:
                    thirstvaluecapocc = 800;
                    break;
                    
                    case 13001..15000:
                    thirstvaluecapocc = 900;
                    break;
                    
                    case 15001..17529:
                    thirstvaluecapocc = 1000;
                    break;
                    
                    case 17530..999999:
                    thirstvaluecapocc = 1200;
                    break;
                }
                
                int diceroll = random(20);
        
                if (diceroll == 1)
                {
                    if (thirstvaluecapocc > thirstvalue)
                    {
                        thirstvalue = thirstvalue + 1;
                    
                        VAMPIRES_MAPPINGS->set_thirst_gauge(shadow_who->query_name(), thirstvalue);
                            
                        BLOOD_LOG("blood_log",
                        "The Vampire " +shadow_who->query_name() 
                        +" gained 1 bloodpoint (nonspecial).\n");
                    }
                }

                break;
            }*/
            
        shadow_who->catch_msg("Crouching low, you explode with "
        +"unnatural speed and viciously maul " + QTNAME(enemy)
        + ", severely injuring " + enemy->query_possessive()+ " " 
        + hdesc + " with your " + wpn + ".\n");

        enemy->catch_msg(QCTNAME(shadow_who)+" crouches low "
        +"and explodes in a blur of movement to viciously "
        +"maul your " + hdesc + " with " +SW->query_possessive() 
        + " " + wpn + ".\n");

        shadow_who->tell_watcher(QCTNAME(shadow_who)+" crouches "
        +"low and explodes in a blur of movement to viciously "
        +"maul " + enemy->query_possessive()+ " " + hdesc + " with " 
        + SW->query_possessive()+ " " + wpn + ".\n", enemy);
        break;
    }

    return 1;
}


