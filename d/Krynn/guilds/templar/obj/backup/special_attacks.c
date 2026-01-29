/* 
* Contains the specials of the Templars of Takhisis.
* Louie 2004
*
* Updates:
* Louie Dec 2005 - Changed reset system (same times, different way).
*                  Allow full Templars to tfocus and tattack at same time.
*/

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"


/* Prototypes */
void lay_offensive_special(object tp, object target);
void lay_sap_special(object tp, object target, object weapon);

void reset_offensive_attacking(object who);
void reset_sap_timer(object who);

void combat_attack(object attacker, object target);
void sap_attack(object attacker, object target, object weapon);
mixed cannot_attack_with_lay_special(object who, object target, string attack);

/**
 * Attack Special
 * This special attack is a bludgeon attack that
 * does direct damage to a single target.
 */
void
lay_offensive_special(object tp, object target)
{
    //object who = query_shadow_who();
    object who = tp;

    // Goodies get penalty here!
    if(who->query_alignment()> 0)
    {
        who->catch_tell("You feel too pure to use the skills "+
                        "thought to you in the Dark Queen's service!\n");
        return;
    }
    
    who->catch_msg("You look for an opening to throw an attack.\n");


    /*1-4 second prepare*/
    who->set_offensive_preparing();
    set_alarm(who->query_speed(1 + random(4)), 0.0, &combat_attack(who, target));
    
    /* Initiate battle with the target */
    who->attack_object(target);

    /* reveal the player if he is hiding */
    who->reveal_me(0);
}

/**
 * Sap special
 * This special attack is a bludgeon attack that does
 * direct damage to a single target.  It can only be
 * used at the beginning of combat.
 */
void
lay_sap_special(object tp, object target, object weapon)
{
    // No prepare time
    
    //Attack!!!!!
    tp->attack_object(target);
    
    tp->reveal_me(0);
    
    sap_attack(tp, target, weapon);
    
}


void
reset_offensive_attacking(object who)
{
    who->catch_tell("You feel ready to throw another attack.\n");
    who->reset_offensive_attacking();
}

void
reset_sap_timer(object who)
{
    who->catch_tell("You feel ready to sap again.\n");
    who->reset_sap_timer();
}

/*
* Perform the sap attack.
*/
void
sap_attack(object attacker, object target, object weapon)
{
    mixed hitres;
    int hitsuc, phurt; 
    string why, hdesc;
    string *attack_message;
    string weapon_desc;
    object sapob;
    object sapstunob;

    
    attacker->set_sap_timer();
    
    /* make sure the target is still in the same room as the attacker */
    if (!target || (environment(target) != environment(attacker)))
    {
        attacker->catch_msg("The target of your attack seems to " +
                            "have slipped away.\n");
        return;
    }


    /* Has target become invalid somehow? */
    if (stringp(why = cannot_attack_with_lay_special(attacker, target, "attack")))
    {
        attacker->catch_msg(why);
        return;
    }
    
    attacker->set_sap_timer();
    //120 second reset time
    set_alarm(attacker->query_speed(SAP_RESET_TIME), 0.0, &reset_sap_timer(attacker));
    
    
    /* We can only sap something that isn't expecting it*/
    /*
    if (testob = P(GUILD_SAP_OB_NAME, target)) {
    */
    if (time() - target->query_prop(GUILD_SAP_PROP) < SAP_IMMUNE_TIME)
    {
        write(target->query_The_name(attacker)+" is alert to that sort of attack.\n");
        return;
    }
    
        
    /* Regardless if it hits or not, the target is */
    /* protected from this form of attack for a while*/
    setuid();
    seteuid(getuid());
    target->add_prop(GUILD_SAP_PROP, time());
    
    /* 
     * Try to hit - use cb_hit()
     */
    if ((hitsuc = attacker->query_combat_object()->cb_tohit(-1, 85,
      target)) > 0)
    {
        /* attack successful! */

        hitres = target->hit_me(F_PENMOD(
        ((attacker->query_stat(SS_DEX)/2 + attacker->query_stat(SS_LAYMAN)/2
            + attacker->query_stat(SS_WIS)) / 6),
        attacker->query_skill(SS_GUILD_SAP_SKILL)),
          W_BLUDGEON, attacker, -1);
    }
    else
    {
        /* attack missed. */
        hitres = target->hit_me(hitsuc, 0, attacker, -1);
    }
    
    phurt = hitres[0];
    hdesc = hitres[1];

    /* add fatigue */
    if (attacker->query_fatigue() < 5)
    {
        attacker->heal_hp(-(5 - attacker->query_fatigue()));
        attacker->set_fatigue(0);
        attacker->catch_msg("The strain of the attack drains you.\n");
    }
/*
    else
    {
        attacker->add_fatigue(-5);
    }
*/

    if (!weapon->query_short())
    {   
        weapon_desc = weapon->query_name();
    } else
    {
        weapon_desc = weapon->query_short();
    }
    
    
    if (phurt >= 0) 
    {
        /* remove some of the attacker's panic */
        attacker->add_panic(-3 - phurt / 5);
        

        switch (phurt)
        {
        case 0:
            attack_message = ({
            "You swing your "+weapon_desc+" wildly through the air "+
            "without hitting anything.\n",
            attacker->query_The_name(target)+ " swings " +
                HIS(attacker) + " " +
                weapon_desc+" wildly through the air, apparently "+
                "in a bad attempt to hit you.\n",
            QCTNAME(attacker)+ " swings " +
                HIS(attacker) + " " +
                weapon_desc+" wildly "+
                "through the air in a bad attempt at hitting "+
                QTNAME(target)+".\n"
            });
            break;
        case 1..30:
            attack_message = ({
            "You quickly swing your "+weapon_desc+" through the air " +
                "and sap "+target->query_the_name(attacker)+
                " with it!\n",
            attacker->query_The_name(target)+ " quickly swings " +
                HIS(attacker) + " " +
                weapon_desc+" through the air, sapping "+
                "you painfully!\n",
            QCTNAME(attacker)+ " quickly swings "+
                HIS(attacker) + " " +
                weapon_desc+ 
                " through the air, sapping " +
                QTNAME(target)+" with it!\n"
            });
            break;
        case 31..75:
            attack_message = ({
            "You swing your "+weapon_desc+" in a vicious arc " +
                "and smack it against "+
                target->query_the_name(attacker)+"!\n",
            attacker->query_The_name(target)+ " swings " +
                HIS(attacker) + " " +
                weapon_desc+" in a vicious arc and smacks it "+
                "against you!\n",
            QCTNAME(attacker)+ " swings "+
                HIS(attacker) + " " +weapon_desc+" in a "+
                "vicious arc and smacks it against " +
                QTNAME(target)+"!\n"
            });
            break;
        case 76..99:
            attack_message = ({
            "With a mighty yell you swing your "+weapon_desc+
                " and smash it into "+
                target->query_the_name(attacker)+"!\n",
            attacker->query_The_name(target)+ " lets out a " +
                "mighty yell and smashes " +
                HIS(attacker) + " " + weapon_desc+
                " into you!\n",
            QCTNAME(attacker)+ " lets out a mighty yell and "+
                "smashes "+
                HIS(attacker) + " " +weapon_desc+" into "+
                QTNAME(target)+"!\n"
            });
            break;
        default:
            attack_message = ({
            "With a mighty yell you swing your "+weapon_desc+
                " and smash it into "+
                target->query_the_name(attacker)+"!\n",
            attacker->query_The_name(target)+ " lets out a " +
                "mighty yell and smashes " +
                HIS(attacker) + " " + weapon_desc+
                " into you!\n",
            QCTNAME(attacker)+ " lets out a mighty yell and "+
                "smashes "+
                HIS(attacker) + " " +weapon_desc+" into "+
                QTNAME(target)+"!\n"
            });
            break;
        }


        /* message to the attacker */
        attacker->catch_tell(attack_message[0]);

        /* message to the target */
        target->catch_tell(attack_message[1]);

        /* message to onlookers */
        attacker->tell_watcher(attack_message[2], target);
        
        /* 50% chance of stunning */
        if (( phurt > 0) && random(2))
        {
            /* Add the stun effect */
            sapstunob = clone_object(SAP_STUN_OB);
            sapstunob->move(target);
            attacker->catch_tell(target->query_The_name(attacker) +
                " looks stunned!\n");
            target->catch_tell("You feel stunned!\n");
            attacker->tell_watcher(QCTNAME(target)+
                " looks stunned!\n", target);
        }

        if (target->query_hp() <= 0)
        {
            target->do_die(attacker);
        }

        return;
    }

    /* We get here if the attack missed */

    /* add some panic to the attacker */
    attacker->add_panic(1);
    
    attack_message = ({
            "You swing your "+weapon_desc+" wildly through the air "+
            "without hitting anything.\n",
            attacker->query_The_name(target)+ " swings " +
                HIS(attacker) + " " +
                weapon_desc+" wildly through the air, apparently "+
                "in a bad attempt to hit you.\n",
            QCTNAME(attacker)+ " swings " +
                HIS(attacker) + " " + weapon_desc+" wildly "+
                "through the air in a bad attempt at hitting "+
                QTNAME(target)+".\n"
            });
            
    /* message to attacker */
    attacker->catch_tell(attack_message[0]);

    /* message to target */
    target->catch_tell(attack_message[1]);
 
    /* message to onlookers */
    attacker->tell_watcher(attack_message[2], target);
 
}

/*
* Perform the offensive attack.
*/
void
combat_attack(object attacker, object target)
{
    mixed hitres;
    int hitsuc, phurt; 
    string why, hdesc;
    string *attack_message;

    /* make sure the target is still in the same room as the attacker */
    if (!target || (environment(target) != environment(attacker)))
    {
        attacker->catch_msg("The target of your attack seems to " +
            "have slipped away.\n");
        attacker->reset_offensive_preparing();
        return;
    }


    /* Has target become invalid somehow? */
    if (stringp(why = cannot_attack_with_lay_special(attacker, target, "attack")))
    {
        attacker->catch_msg(why);
        attacker->reset_offensive_preparing();
        return;
    }

    attacker->reset_offensive_preparing();    
    attacker->set_offensive_attacking();

    /*Since we're actually attacking, set reset time*/
    /*10-13 sec reset time*/
    //Update ATTACK_RESET_TIME in local.h if this changes
    set_alarm(attacker->query_speed(10+random(4)), 0.0, &reset_offensive_attacking(attacker));


    /* 
     * Try to hit - use cb_hit()
     */
    if ((hitsuc = attacker->query_combat_object()->cb_tohit(-1, 85,
      target)) > 0)
    {
        /* attack successful! */

        hitres = target->hit_me(F_PENMOD(
        ((attacker->query_stat(SS_DEX)/2 + attacker->query_stat(SS_LAYMAN)/2
            + attacker->query_stat(SS_WIS)) / 6),
        attacker->query_skill(SS_GUILD_ATTACK_SKILL)),
          W_BLUDGEON, attacker, -1);
    }
    else
    {
        /* attack missed. */
        hitres = target->hit_me(hitsuc, 0, attacker, -1);
    }
    phurt = hitres[0];
    hdesc = hitres[1];

    if (attacker->query_fatigue() < 5)
    {
        attacker->heal_hp(-(5 - attacker->query_fatigue()));
        attacker->set_fatigue(0);
        attacker->catch_msg("The strain of the attack drains you.\n");
    }
/*
    else
    {
        attacker->add_fatigue(-5);
    }
*/

    if (phurt >= 0) 
    {
        /* remove some of the attacker's panic */
        attacker->add_panic(-3 - phurt / 5);


        switch (phurt)
        {
            case 0:
                attack_message = ({
                "You step towards "+
                    target->query_the_name(attacker)+
                    " to swing a blow at "+ HIS(target)+
                    " head, but "+HE(target)+" anticipates your "+
                    "attack and hastily moves out of the way"+
                    ".\n",
                capitalize(attacker->query_The_name(target)) +
                    " steps towards you to swing a blow at your head, "+
                    "but you anticipate it and hastily move out "+
                    "of the way.\n",
                QCTNAME(attacker)+" steps towards "+QTNAME(target)+
                    " and swings a blow at "+HIS(target)+" head, but "+
                    HE(target)+" anticipates the attack and hastily "+
                    "moves out of the way.\n"
                });
                break;
            case 1..5:
                attack_message = ({
                "You swing at "+
                    target->query_the_name(attacker)+
                    " with a poorly timed blow, barely "+
                    "nicking "+HIM(target)+".\n",
                attacker->query_The_name(target) +
                    " swings at you with a poorly timed blow, "+
                    "barely nicking you.\n",
                QCTNAME(attacker)+" swings at "+QTNAME(target)+
                    " with a poorly timed blow, barely "+
                    "nicking "+HIM(target)+".\n"
                });
                break;
            case 6..20:
                attack_message = ({
                "You bring your knee up into the midsection of "+
                    target->query_the_name(attacker)+
                    ", grazing "+HIM(target)+".\n",
                attacker->query_The_name(target) +
                    " brings "+HIS(attacker)+" knee up into your midsection, "+
                    "grazing you.\n",
                QCTNAME(attacker)+" brings "+HIS(attacker)+" knee up into "+
                    "the midsection of "+QTNAME(target)+
                    ", grazing "+HIM(target)+".\n"
                });              
                break;
            case 21..35:
                attack_message = ({
                  "You allow "+target->query_the_name(attacker)+
                    " inside your defences and quickly strike "+
                    HIM(target)+
                    " with a painful headbutt.\n",
                attacker->query_The_name(target) +
                    " allows you inside "+HIS(attacker)+" defences "+
                    "and quickly strikes you a painful headbutt.\n",
                QCTNAME(attacker)+" allows "+QTNAME(target)+
                    " inside "+HIS(attacker)+" defences and quickly "+
                    "strikes "+HIM(target)+" with a painful headbutt.\n"
                });
                break;
            case 36..50:
                attack_message = ({
                "You spot an opening in "+
                    target->query_the_name(attacker)+
                    "'s defences and pummel "+
                    HIM(target)+
                    " with a throw "+
                    "of your elbow.\n",
                attacker->query_The_name(target) +
                    " spots an opening in your defence and pummels you "+
                    "with a throw of "+
                    HIS(attacker)+
                    " elbow.\n",
                QCTNAME(attacker)+" spots an opening in "+
                    QTNAME(target)+
                    "'s defences and pummels "+
                    HIM(target)+
                    " with a "+
                    "throw of "+
                    HIS(attacker)+
                    " elbow.\n"
                });
                break;
            case 51..75:
                attack_message = ({
                "You capitalize on a weakness in "
                    +target->query_the_name(attacker)+
                    "'s guard and crush "+HIM(target)+" with a powerful "+
                    "kick.\n",
                attacker->query_The_name(target) +
                    " capitalizes on a weakness in your guard and crushes "+
                    "you with a powerful kick.\n",
                QCTNAME(attacker)+" capitalizes on a weakness in "
                    +QTNAME(target)+
                    "'s guard and crushes "+HIM(target)+" with a powerful kick.\n"
                });
                break;
            case 76..99:
                attack_message = ({
                  target->query_The_name(attacker)+
                    " seems to stand perfectly still as you spin to the side "+
                    "and deliver a devastating blow on "+HIM(target)+".\n",
                  "You attempt to move but cannot dodge out of the way "+
                    "as "+attacker->query_the_name(target)+ " spins to the "+
                    "side and delivers a devastating blow on you.\n",
                  QCTNAME(target)+ " seems to stand perfectly still as "+
                    QTNAME(attacker)+" spins to the side and delivers "+
                    "a devastating blow on "+HIM(target)+".\n"
                });
                break;
            default:
                attack_message = ({
                  target->query_The_name(attacker)+
                    " seems to stand perfectly still as you spin to the side "+
                    "and deliver a devastating blow on "+HIM(target)+".\n",
                  "You attempt to move but cannot dodge out of the way "+
                    "as "+attacker->query_the_name(target)+ " spins to the "+
                    "side and delivers a devastating blow on you.\n",
                  QCTNAME(target)+ " seems to stand perfectly still as "+
                    QTNAME(attacker)+" spins to the side and delivers "+
                    "a devastating blow on "+HIM(target)+".\n"
                });
                break;
        }


        /* message to the attacker */
        attacker->catch_tell(attack_message[0]);

        /* message to the target */
        target->catch_tell(attack_message[1]);

        /* message to onlookers */
        attacker->tell_watcher(attack_message[2], target);
    
        if (target->query_hp() <= 0)
        {
            target->do_die(attacker);
        }
    
        return;
    }

    /* We get here if the attack missed */

    /* add some panic to the attacker */
    attacker->add_panic(1);

    attack_message = ({
        "You step towards "+
            target->query_the_name(attacker)+
            " to swing a blow at "+ HIS(target)+
            " head, but "+HE(target)+" anticipates your "+
            "attack and hastily moves out of the way"+
            ".\n",
        capitalize(attacker->query_The_name(target)) +
            " steps towards you to swing a blow at your head, "+
            "but you anticipate it and hastily move out "+
            "of the way.\n",
        QCTNAME(attacker)+" steps towards "+QTNAME(target)+
            " and swings a blow at "+HIS(target)+" head, but "+
            HE(target)+" anticipates the attack and hastily "+
            "moves out of the way.\n"
        });
    
    /* message to attacker */
    attacker->catch_tell(attack_message[0]);

    /* message to target */
    target->catch_tell(attack_message[1]);
 
    /* message to onlookers */
    attacker->tell_watcher(attack_message[2], target);
}

mixed
cannot_attack_with_lay_special(object who, object target, string attack)
{
    mixed why;
    //object who = query_shadow_who();
    //object who = TP;

    if (!target || !living(target) || !present(target, environment(who)))
    {
        return "Attack whom?\n";
    }

    if (who->query_prop(LIVE_I_ATTACK_DELAY) ||
      who->query_prop(LIVE_I_STUNNED))
    {
        return "You are too stunned to do that.\n";
    }
    
    if (who == target) {
        return "Even YOU are not dumb enough to attack yourself!\n";
    }

    if (stringp(why = target->query_prop(OBJ_M_NO_ATTACK)) ||
      stringp(why = environment(target)->query_prop(ROOM_M_NO_ATTACK)))
    {
        return why;
    }
    else if (why)
    {
        return "You sense a force protecting " + 
        target->query_the_name(who) + ".\n";
    }

    /* Someone might try defining this to block all special attacks */
    if (target->query_not_attack_me(who, -1))
    {
        /* A message should be given by query_not_attack_me(), so
        * no need to specify one here.
        */
        return "";
    }

  /* Check only if not already in combat with this target */
    if ( member_array(target, who->query_enemy(-1)) == -1 )
    {
        if ( (!who->query_npc()) && (who->query_met(target)) &&
            ( who->query_prop(LIVE_O_LAST_KILL) != target))
        {
            who->add_prop(LIVE_O_LAST_KILL, target);
        
        return "Attack " + target->query_the_name(who) + 
            "?!? Please confirm by trying again.\n";
         }

         if ( !F_DARE_ATTACK(who, target) )
         {
         return "You don't dare to attack " + 
             target->query_the_name(who) + ".\n";
         }
    }

    return 0;
}

