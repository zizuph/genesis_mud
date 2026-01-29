/*
 * /d/Faerun/guilds/fire_knives/shadows/fire_combat_msg.c
 *
 * Fire Knive Combat messages.
 *
 * Nerull 2019  
 *
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
    
    weaponob_left = shadow_who->query_weapon(W_LEFT);
    weaponob_right = shadow_who->query_weapon(W_RIGHT);
    
    string weapon_left = weaponob_left->query_short();
    string weapon_right = weaponob_right->query_short();
    

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
    
    if (aid == W_FOOTR)
    {
        return SW->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }
    
    if (aid == W_FOOTL)
    {
        return SW->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }




    // Messages
    switch (phurt)
    {
        
    //////////////////////////////////////////////////////////////////
    case -1:

        if (spcl == 0)
        {
            if (!SW->query_option(OPT_GAG_MISSES))
            {
                shadow_who->catch_msg("You slash twice in quick "
                +"succession at " + QTPNAME(enemy) + " " + hdesc 
                + ", with the "+wpn+", but " 
                + enemy->query_pronoun() + " looks unharmed.\n");
            }

            if (!enemy->query_option(OPT_GAG_MISSES))
            {
                enemy->catch_msg(QCTNAME(shadow_who) 
                + " slashes twice at your " + hdesc 
                + " in quick succession "
                + "with the "+wpn+", but you feel unharmed.\n");
            }

            shadow_who->tell_watcher_miss(QCTNAME(shadow_who) 
            +" slashes twice in quick succession "
            + "at " + QTPNAME(enemy) + " " + hdesc + " with the "
            +wpn+", " 
            + "but " + enemy->query_pronoun() 
            + " looks unharmed.\n", enemy);
            break;
        }


        if (spcl == 1)
        {
            if (!SW->query_option(OPT_GAG_MISSES))
            {
                shadow_who->catch_msg("You turn quickly and slash with your "
                + wpn 
                +" at " + QTPNAME(enemy) 
                + " " + hdesc + ", but fail to break " 
                +"through " + enemy->query_possessive() 
                + " defences.\n");
            }

            if (!enemy->query_option(OPT_GAG_MISSES))
            {
                enemy->catch_msg(QCTNAME(shadow_who) 
                + " turns quickly and slashes with " 
                +SW->query_possessive() + " " + wpn 
                +" at your " + hdesc + ", but " 
                + SW->query_pronoun() 
                +" fails to break through your defences.\n");
            }

            shadow_who->tell_watcher_miss(QCTNAME(shadow_who) 
            + " turns quickly and slashes " 
            +"with " + SW->query_possessive() + " " + wpn + " at " 
            +QTPNAME(enemy) + " " + hdesc + ", " 
            +"but fails to break through " + enemy->query_possessive() 
            +" defences.\n", enemy);
            break;
        }

        if (spcl == 2)
        {
            if (!SW->query_option(OPT_GAG_MISSES))
            {
                shadow_who->catch_msg("You crouch down and leap "
                +"forward, slashing ferociously with "
                +"with the "+wpn+" at " + QTPNAME(enemy) + " " + hdesc + ", but " 
                +enemy->query_pronoun() + " manages "
                +"to dodge your attack.\n");
            }

            if (!enemy->query_option(OPT_GAG_MISSES))
            {
                enemy->catch_msg(QCTNAME(shadow_who) 
                +" crouches down only to suddenly leap forward slashing "
                +"ferociously with the "+wpn
                +" at your " + hdesc + ". Luckily you manage to dodge "
                +SW->query_possessive() + " "
                + "attack.\n");
            }

            shadow_who->tell_watcher_miss(QCTNAME(shadow_who) 
            +" crouches down only to suddenly leap "
            +"forward, slashing ferociously with the "+wpn
            +" at " + QTPNAME(enemy) + " " + hdesc + ". Luckily "
            +QTNAME(enemy) + " "
            +"manages to dodge " + SW->query_possessive() 
            +" attack.\n", enemy);
            break;
        }

        if (spcl == 3)
        {
            if (!SW->query_option(OPT_GAG_MISSES))
            {
                shadow_who->catch_msg("You swipe at " + QTPNAME(enemy) 
                +" " + hdesc + " with your "
                +wpn + ",  missing " + enemy->query_objective() 
                +".\n");
            }

            if (!enemy->query_option(OPT_GAG_MISSES))
            {
                enemy->catch_msg(QCTNAME(shadow_who) + " swipes at your " 
                +hdesc + " with " +SW->query_possessive() + " " 
                + wpn + ", narrowly missing you.\n");
            }

            shadow_who->tell_watcher_miss(QCTNAME(shadow_who) 
            +" swipes at " +QTPNAME(enemy) + " " + hdesc + " with " 
            +SW->query_possessive() + " " + wpn 
            +", narrowly missing " + enemy->query_objective() 
            +".\n", enemy);
            break;
        }
        
        
        
    //////////////////////////////////////////////////////////////////
    case 0..5:

        if (spcl == 0 || spcl == 2)
        {
            shadow_who->catch_msg("You turn quickly and hack with "
            +"your " + wpn +" at " + QTPNAME(enemy) + " " 
            +hdesc + ", delivering " + enemy->query_objective() 
            +" a small wound.\n");

            enemy->catch_msg(QCTNAME(shadow_who) 
            +" turns quickly and hacks with " 
            +SW->query_possessive() + " " + wpn + " at your " 
            +hdesc + ", delivering you a small wound.\n");

            shadow_who->tell_watcher(QCTNAME(shadow_who) 
            +" turns quickly and hacks " 
            +"with " + SW->query_possessive() + " " + wpn + " at " 
            +QTPNAME(enemy) + " " + hdesc + ", " 
            +"delivering " + enemy->query_objective() 
            +" a small wound.\n", enemy);
            break;
        }

        if (spcl == 1 || spcl == 3)
        {
            shadow_who->catch_msg("You lunge at " + QTNAME(enemy) 
            +" and thrust your " + wpn + " into "
            + enemy->query_possessive() + " " + hdesc + ".\n");

            enemy->catch_msg("You feel a pain in your " + hdesc + " as " 
            +QTNAME(shadow_who) + " suddenly " 
            +"thrusts " + SW->query_possessive() + " " + wpn 
            +" into it.\n");

            shadow_who->tell_watcher("With a sudden movement " 
            +QTNAME(shadow_who) +" thrusts into " + QTNAME(enemy) 
            +" " + hdesc + " with " + SW->query_possessive() + " " 
            + wpn + ".\n", enemy);
            break;
        }
        
        
        
    //////////////////////////////////////////////////////////////////
    case 6..15:

        if (spcl == 0)
        {
            shadow_who->catch_msg("Leaping forward quickly you slash "
            +"with your " + wpn +" at " + QTPNAME(enemy) + " " 
            +hdesc + ", delivering " + enemy->query_objective() 
            +" a shallow wound.\n");

            enemy->catch_msg(QCTNAME(shadow_who) 
            +" suddenly leaps forward and slashes with " 
            +SW->query_possessive() + " " + wpn + " at your " 
            +hdesc + ", delivering you a shallow wound.\n");

            shadow_who->tell_watcher(QCTNAME(shadow_who) 
            +" suddenly leaps forward and slashes " 
            +"with " + SW->query_possessive() + " " + wpn + " at " 
            +QTPNAME(enemy) + " " + hdesc + ", " 
            +"delivering " + enemy->query_objective() 
            +" a shallow wound.\n", enemy);
            break;
        }

        if (spcl == 1)
        {
            shadow_who->catch_msg("You leap forward with the "
            +wpn+" and open a shallow wound on " 
            +QTPNAME(enemy) + " " + hdesc + ".\n");

            enemy->catch_msg(QCTNAME(shadow_who) + " leaps forward with " 
            +SW->query_possessive() 
            +" "+wpn+", slicing a wound on your " 
            +hdesc + ".\n");

            shadow_who->tell_watcher(QCTNAME(shadow_who) 
            +" leaps forward in a " 
            +"quick movement, " + SW->query_possessive() + " "
            +wpn+", slicing a " + "wound on " + QTPNAME(enemy) 
            +" " + hdesc + ".\n", enemy);
            break;
        }

        if (spcl == 2)
        {
            shadow_who->catch_msg("Moving suddenly and without warning, you "
            +"rend " + QTNAME(enemy) + " with your "
            +wpn+", deep gouges left on " + QTPNAME(enemy) + " " 
            +hdesc + ".\n");

            enemy->catch_msg("Moving like a blur " + QTNAME(shadow_who) 
            +" leaps past you leaving deep gouges on your " 
            +hdesc + " with the "+wpn+".\n");

            shadow_who->tell_watcher("You barely notice " 
            +QTNAME(shadow_who) + " leaping past " 
            +QTNAME(enemy) + ", leaving deep gouges on "
            +enemy->query_possessive() 
            +" "+hdesc + " with the "+wpn+".\n", enemy);
            break;
        }

        if (spcl == 3)
        {
            shadow_who->catch_msg("Using brute force you bash through " 
            +QTPNAME(enemy) + " defences and rend " 
            +enemy->query_possessive() + " " + hdesc 
            +" with quick slashes with your "+wpn+".\n");

            enemy->catch_msg("With unnatural strength, " 
            +QTNAME(shadow_who) + " breaks through " 
            +"your defences and, with quick gashes to your " 
            +hdesc + " with the "+wpn+", leaving your flesh hanging.\n");

            shadow_who->tell_watcher("With unnatural strength, " 
            +QTNAME(shadow_who) + " breaks through " 
            +QTPNAME(enemy) + " defences and rends " 
            +enemy->query_possessive() + " " + hdesc + " with the "
            +wpn+", cutting deep gashes.\n", enemy);
            break;
        }
        
        
        
    //////////////////////////////////////////////////////////////////
    case 16..40:
 
        if (spcl == 0)
        {
            shadow_who->catch_msg("You make a quick weaving motion "
            +"and slash with your " + wpn 
            +" at " + QTPNAME(enemy) + " " + hdesc + ", injuring " 
            +enemy->query_objective() +".\n");

            enemy->catch_msg(QCTNAME(shadow_who) 
            +" makes a quick weaving motion and slashes with " 
            +SW->query_possessive() + " " + wpn + " at your " 
            +hdesc + ", injuring you.\n");

            shadow_who->tell_watcher(QCTNAME(shadow_who) 
            +" makes a quick weaving motion and slashes " 
            +"with " + SW->query_possessive() + " " + wpn + " at " 
            +QTPNAME(enemy) + " " + hdesc + ", " 
            +"injuring " + enemy->query_objective() + ".\n", enemy);
            break;
        }

        if (spcl == 1)
        {
            shadow_who->catch_msg("You cut deeply into " + QTPNAME(enemy) 
            +" " + hdesc + " with your " + wpn 
            +", leaving four deep gouges.\n");

            enemy->catch_msg(QCTNAME(shadow_who) + " cuts deeply into your " 
            +hdesc + " with " +SW->query_possessive() + " " + wpn 
            +", leaving four deep gouges.\n");

            shadow_who->tell_watcher(QCTNAME(shadow_who) 
            +" cuts deeply into " +QTPNAME(enemy) + " " + hdesc 
            +" with " + SW->query_possessive() + " " + wpn 
            +", leaving four deep gouges.\n", enemy);
            break;
        }

        if (spcl == 2)
        {
            shadow_who->catch_msg("You quickly lunge forward in a blur at " 
            +QTNAME(enemy) + " and cut " +enemy->query_possessive() 
            +" " + hdesc + " with a vicious slice of your " + wpn + ".\n");

            enemy->catch_msg(QCTNAME(shadow_who) 
            +" quickly lunges forward at you " 
            +" and cuts your " + hdesc + " with a vicious slice of " 
            +SW->query_possessive() +" " + wpn + ".\n");

            shadow_who->tell_watcher(QCTNAME(shadow_who) 
            +" quickly lunges forward at "+ QTNAME(enemy) + " and cuts " 
            +enemy->query_possessive() + " " + hdesc + " with a vicious " 
            +"slice of " + SW->query_possessive() + " " + wpn 
            + ".\n", enemy);
            break;
        }

        if (spcl == 3)
        {
            shadow_who->catch_msg("You fake a movement to the left and "
            +"rend open " + QTPNAME(enemy) +" " + hdesc + " with your " 
            + wpn + ".\n");

            enemy->catch_msg(QCTNAME(shadow_who) 
            +" makes a quick move to the right " 
            +" and rends open your " + hdesc + " with " + SW->query_possessive() 
            +" " + wpn + ".\n");

            shadow_who->tell_watcher(QCTNAME(shadow_who) 
            + " makes a quick move to the right and rends open " 
            + QTPNAME(enemy) + " " + hdesc + " with "
            + SW->query_possessive() + " " + wpn + ".\n", enemy);
            break;
        }



    //////////////////////////////////////////////////////////////////
    case 41..79:

        if (spcl == 0)
        {
            shadow_who->catch_msg("You viciously gouge " 
            +QTPNAME(enemy) + " " + hdesc + " with your "
            +wpn+".\n");

            enemy->catch_msg(QCTNAME(shadow_who) 
            +" viciously gouges your " + hdesc + " with the "
            +wpn+".\n");

            shadow_who->tell_watcher(QCTNAME(shadow_who) 
            +" viciously gouges " 
            + QTPNAME(enemy) 
            +" " + hdesc + " with the "+wpn+".\n", enemy);
            break;
        }


        if (spcl == 1)
        {
            shadow_who->catch_msg("You cut a deep wound in " 
            +QTPNAME(enemy) + " " + hdesc + " with your " + wpn 
            +", spreading " + enemy->query_possessive() 
            +" own blood all over " +enemy->query_possessive() 
            +" face.\n");

            enemy->catch_msg(QCTNAME(shadow_who) 
            +" cuts a deep wound in your " + hdesc + " with " 
            +SW->query_possessive() + " " + wpn 
            +", spreading your own blood all over your face!\n");

            shadow_who->tell_watcher(QCTNAME(shadow_who) 
            +" cuts a deep wound in " 
            +QTPNAME(enemy) + " " + hdesc + " with " 
            +SW->query_possessive() + " " + wpn 
            +", spreading " + QTPNAME(enemy) + " own blood all over " 
            +enemy->query_possessive() +" face!\n", enemy);
            break;
        }

        if (spcl == 2)

        {
            shadow_who->catch_msg("You savagely carve " + QTPNAME(enemy) 
            +" " + hdesc + " with the "+wpn+", leaving a gaping wound.\n");

            enemy->catch_msg(QCTNAME(shadow_who) 
            +" carves your " + hdesc + " savagely with " 
            +SW->query_possessive() + " "+wpn
            +"leaving a gaping wound.\n");

            shadow_who->tell_watcher(QCTNAME(shadow_who) + " carves " 
            +QTPNAME(enemy) + " " + hdesc + " savagely with " 
            +SW->query_possessive() + " "+wpn
            +" leaving a gaping wound.\n", enemy);
            break;
        }

        if (spcl == 3)

        {
            shadow_who->catch_msg("You quickly slice " 
            +QTNAME(enemy) +" with your " + wpn 
            +", leaving deep cuts on " + enemy->query_possessive() 
            +" " + hdesc + ".\n");

            enemy->catch_msg(QCTNAME(shadow_who) 
            +" quickly slices you " 
            +"with " + SW->query_possessive() + " " + wpn 
            +", leaving deep cuts on " 
            +"your " + hdesc + ".\n");

            shadow_who->tell_watcher(QCTNAME(shadow_who) 
            +" quickly slices " 
            +QTNAME(enemy) + " with " + SW->query_possessive() + " " 
            +wpn + ", leaving deep cuts on " 
            +enemy->query_possessive() + " " + hdesc + ".\n", enemy);
            break;
        }


    //////////////////////////////////////////////////////////////////
    case 80..99:
                
        if (spcl == 0 || spcl == 1)
        {
            shadow_who->catch_msg("Running at " + QTNAME(enemy) 
            + ", you rend " + enemy->query_possessive() 
            +" " + hdesc + " with your " + wpn + ".\n");

            enemy->catch_msg(QCTNAME(shadow_who) 
            +" sprints at you rending your " + hdesc + " with " 
            +SW->query_possessive() + " " + wpn + ".\n");

            shadow_who->tell_watcher(QCTNAME(shadow_who) 
            +" sprints at " + QTNAME(enemy) 
            +" rending " + enemy->query_possessive() 
            +" " + hdesc + " with " + SW->query_possessive() 
            +" " + wpn + ".\n", enemy);
            break;
        }
         
        if (spcl == 2 || spcl == 3)
        {
            shadow_who->catch_msg("With blinding speed you "
            +"devastatingly slice " + QTNAME(enemy) 
            +" with your "+wpn+".\n");

            enemy->catch_msg("With a flash of speed, " 
            +QTNAME(shadow_who) +" slices you devastatingly "
            +"with the "+wpn+", leaving you helpless and "
            +"whimpering.\n");

            shadow_who->tell_watcher("With a flash of speed, " 
            +QTNAME(shadow_who) +" devastatingly slices " 
            +QTNAME(enemy) + " with the "+wpn+", leaving " 
            +enemy->query_objective() 
            +" helpless and whimpering.\n", enemy);
            break;
        }



    //////////////////////////////////////////////////////////////////
    default:
    
        if (wpn == 0)
        {
             shadow_who->catch_msg("You break the neck of " + QTNAME(enemy) 
            +" with your bare hands!\n");

            enemy->catch_msg(QCTNAME(shadow_who) 
            +" breaks your neck with "
            +SW->query_possessive() + " bare hands!\n");

            shadow_who->tell_watcher(QCTNAME(shadow_who) 
            +" breaks the neck of " + QTNAME(enemy) 
            +" with " + SW->query_possessive() + " bare hands!\n", enemy);
            break;
        }
        
        shadow_who->catch_msg("You lacerate " + QTNAME(enemy) 
        +" with your "+wpn+"!\n");

        enemy->catch_msg(QCTNAME(shadow_who) 
        +" lacerates you with "
        +SW->query_possessive() + " "+wpn+"!\n");

        shadow_who->tell_watcher(QCTNAME(shadow_who) 
        +" lacerates " + QTNAME(enemy) 
        +" to with " + SW->query_possessive() + " "+wpn+"!\n", enemy);
        break;
    }

    return 1;
}


