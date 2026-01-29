/* 
* Contains the offensive special of the Pirates of the Bloodsea.
* Navarre June 16th 2006
*
* Adapted from Louie's Templars.
*
* Navarre February 3rd 2007, Fixed typo in attack messages: used "him" instead of HIM(target)
*/

/* Navarre June 24th:
 * Changed HE(attacker) to QTNAME(attacker) for the default message.
 * Navarre june 25th: fixed typo, had there are no one left, changed to is.
 * Navarre July 1st: had misses him, instead of misses HIM(target).
 * Navarre July 4th: Fixed typo, had starts instead of stars 
 * Navarre July 14th: Found that the TO_HIT value was not matching documenation
 * It was 80 but documentation says 75, so i changed it to 75.
 * Navarre July 23th: Removed Alternate_msg, use player prop instead, since all share the soul, doh! :)
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"


#define PREPARE_ATTACK_STR "You start to consider using your bottle for something other than drinking.\n"
#define READY_AGAIN_STR "You feel ready to hit someone with your bottle again.\n"
#define TARGET_GONE_STR "There is no one left to bash with your bottle.\n"
#define SPECIAL_ATTACK -1
#define TO_HIT_VALUE 75
#define BLOOD_OBJ "/d/Ansalon/goodlund/nethosak/city/std/blood"
#define PIRATE_ALT_MSG "_pirate_alt_msg"

/* Prototypes */
void pbash(object tp, object target);

void reset_pbash(object who);

void combat_attack(object attacker, object target);
mixed cannot_attack_with_pbash(object who, object target, string attack);



/**
 * Attack Special
 * This special attack is a bludgeon attack that
 * does direct damage to a single target.
 */
void
pbash(object tp, object target)
{
    //object who = query_shadow_who();
    object who = tp;
    
    who->catch_tell(PREPARE_ATTACK_STR);


    /*1-4 second prepare*/
    who->set_offensive_preparing();
    set_alarm(who->query_speed(1 + random(5)), 0.0, &combat_attack(who, target));
    
    /* Initiate battle with the target */
    who->attack_object(target);

    /* reveal the player if he is hiding */
    who->reveal_me(0);
}


void
reset_pbash(object who)
{
    who->catch_tell(READY_AGAIN_STR);
    who->reset_offensive_attacking(); //Call to shadow.
}

/*
* Perform the offensive attack.
*/
void
combat_attack(object attacker, object target)
{
    mixed hitres;
    int hitsuc, phurt; 
    int str, guild_stat, intox, stagger, damage;
    string default_msg = "";
    string you_msg = "";

    string why, hdesc;
    string *attack_message;
    /* make sure the target is still in the same room as the attacker */
    if (!target || (environment(target) != environment(attacker)))
    {
        attacker->catch_tell(TARGET_GONE_STR);
        attacker->reset_offensive_preparing(); //call to shadow
        return;
    }


    /* Has target become invalid somehow? */
    if (stringp(why = cannot_attack_with_pbash(attacker, target, "attack")))
    {
        attacker->catch_msg(why);
        attacker->reset_offensive_preparing(); //call to shadow
        return;
    }

    attacker->reset_offensive_preparing();   //call to shadow
    attacker->set_offensive_attacking();     //call to shadow

    //Update attack reset time
    //Values here needs to be slightly smaller than 15+random(5)
    //Which is the true value used for resetting the attack special,
    //this is handled in the pirate_shadow file.
    //Otherwise the attack special is slowed to 45 seconds per reset.
    set_alarm(attacker->query_speed(13+random(4)), 0.0, &reset_pbash(attacker));
    /* 
     * Try to hit - use cb_hit()
     */
    if ((hitsuc = attacker->query_combat_object()->cb_tohit(SPECIAL_ATTACK, TO_HIT_VALUE,
         target)) > 0)
    {
        /* attack successful! */
        str = attacker->query_stat(SS_STR);
        guild_stat = attacker->query_stat(SS_LAYMAN);
        intox = attacker->query_intoxicated();
        stagger = attacker->query_skill(SS_SPECIAL_STAGGER);
        damage = F_PENMOD( (str/4 + guild_stat/3 + intox /2)/6, intox/20+(stagger*3)/5 );
        hitres = target->hit_me(damage, W_BLUDGEON, attacker, -1);
        phurt = hitres[3];
    }
    else
    {
        phurt = 0;
    }
    
    if (phurt >= 0) 
    {
        /* remove some of the attacker's panic */
        attacker->add_panic(-3 - phurt / 5);

        if(!target->query_humanoid())
        {
            attack_message = ({"You strike "+QTNAME(target)+" with your bottle.\n",
                                   QCTNAME(attacker)+" strikes you with "+HIS(attacker)+
                                   " bottle.\n",
                                   QCTNAME(attacker)+" strikes "+QTNAME(target)+" with "+
                                   HIS(attacker)+" bottle.\n"
                                   });
        }
        else
        {
            switch (phurt)
            {
                case 0:
                    attack_message = ({
                        "Raising your bottle, you charge straight at "+QTNAME(target)+
                            ", but still bleary from last night's debauchery, you miss "+
                            HIM(target)+" by a mile.\n",
                            QCTNAME(attacker)+" raises "+HIS(attacker)+" bottle as "+
                            HE(attacker)+" charges straight at you. Luckily, in "+
                            HIS(attacker)+" drunken haste "+HE(attacker)+
                            " misses you by a mile.\n",
                            QCTNAME(attacker)+" raises "+HIS(attacker)+" bottle as "+
                            HE(attacker)+" charges straight at "+QTNAME(target)+
                            ". But in "+HIS(attacker)+" drunken haste "+HE(attacker)+
                            " misses by a mile.\n"
                            });
                    break;
                case 1..5:
                    attack_message = ({
                        "Holding your bottle tight, you swing it at "+QTNAME(target)+
                            ", but in your drunken "+"haste, you land only a glancing "+
                            "blow.\n",
                            "Holding "+HIS(attacker)+" bottle tight, "+QTNAME(attacker)+
                            " swings it "+"at you, but deals only a glancing blow.\n",
                            "Holding "+HIS(attacker)+" bottle tight, "+QTNAME(attacker)+
                            " swings it at "+QTNAME(target)+", but deals only a glancing"+
                            " blow.\n"
                            });
                    break;
                case 6..9:
                    attack_message = ({
                        "In an effort to distract "+QTNAME(target)+", you toss your "+
                            "bottle up in the air.\nAs "+ QTNAME(target)+" follows it "+
                            "with "+HIS(target)+" eyes, you knee "+HIM(target)+" in the "+
                            "gut.\n",
                            QCTNAME(attacker)+" tosses "+HIS(attacker)+" bottle up in "+
                            "the air.\nAs you follow it with your eyes, "+HE(attacker)+
                            " knees you in the gut!\n",
                            "In an effort to distract "+QTNAME(target)+", "+
                            QTNAME(attacker)+" tosses "+HIS(attacker)+" bottle up in the "+
                            "air.\nAs "+QTNAME(target)+" follows it with "+HIS(target)+
                            " eyes, "+QTNAME(attacker)+" knees "+HIM(target)+" in the gut!\n"
                            });              
                    break;
                case 10..19:
                    attack_message = ({
                        "As "+QTNAME(target)+" moves in to strike you, you take a "+
                            "swig from your bottle and spit in "+HIS(target)+" face!\n"+
                            QCTNAME(target)+" rubs "+HIS(target)+" eyes, and you strike "+
                            HIM(target)+" soundly on "+HIS(target)+" leg.\n",
                            "As you move in to strike at "+QTNAME(attacker)+", "+
                            HE(attacker)+" takes a swig from "+HIS(attacker)+" bottle and "+
                            "spits in your face!\n"+QCTNAME(attacker)+" strikes you soundly "+
                            "on your leg, as you try to clear your eyes.\n",
                            "As "+QTNAME(target)+" moves in to strike at "+QTNAME(attacker)+
                            ", "+QTNAME(attacker)+" takes a swig from "+HIS(attacker)+
                            " bottle and spits in "+QTPNAME(target)+" face!\n"+
                            QCTNAME(attacker)+" strikes "+QTNAME(target)+" soundly on the "+
                            "leg, as "+HE(target)+" tries to clear his eyes.\n"
                            });
                    break;
                case 20..29:
                    attack_message = ({
                        "Snapping out of your drunken haze, you lunge at "+QTNAME(target)+
                            ", bashing "+HIM(target)+" on the nose with your bottle. Blood "+
                            "spurts everywhere.\n",
                            QCTNAME(attacker)+" snaps out of "+HIS(attacker)+" drunken haze, "+
                            "and lunges at you, bashing you on the nose with "+HIS(attacker)+
                            " bottle. Blood spurts everywhere.\n",
                            QCTNAME(attacker)+" snaps out of "+HIS(attacker)+" drunken haze "+
                            "and lunges at "+QTNAME(target)+", bashing "+HIM(target)+
                            " on the nose with "+HIS(attacker)+" bottle. Blood spurts "+
                            "everywhere.\n"
                            });
                    setuid();
                    seteuid(getuid());
                    clone_object(BLOOD_OBJ)->move(environment(target));
                    break;
                case 30..39:
                    attack_message = ({
                        "Swinging your bottle, you deliver a solid roundhouse punch to "+
                            QTNAME(target)+".\nWhile "+QTNAME(target)+
                            " is left seeing stars, you manage to sneak in another blow!\n",
                            "Swinging "+HIS(attacker)+" bottle, "+QTNAME(attacker)+
                            " delivers you a solid roundhouse punch.\n"+"While you are "+
                            "left seing stars, "+QTNAME(attacker)+" manages to sneak in "+
                            "another blow!\n",
                            "Swinging "+HIS(attacker)+" bottle, "+QTNAME(attacker)+
                            " delivers a solid roundhouse punch to "+QTNAME(target)+
                            ".\nWhile "+QTNAME(target)+" is left seing stars, "+
                            QTNAME(attacker)+" manages to sneak in another blow!\n"
                            });
                    break;
                case 40..99:
                    default_msg = "With a bloodthirsty cry of: 'No Quarter to bilge rats!'";
                    you_msg = " you";
                    
                    if(strlen(attacker->query_prop(PIRATE_ALT_MSG)) && attacker->query_prop(PIRATE_ALT_MSG)=="off")
                    {
                        attack_message = ({
                            "You bring your bottle crashing down on "+QTPNAME(target)+
                                " head, devastating "+HIM(target)+" with the blow.\n",
                                QCTNAME(attacker)+" brings "+HIS(attacker)+" bottle crashing "+
                                "down on your head, devastating you with the blow.\n",
                                QCTNAME(attacker)+ " brings "+HIS(attacker)+" bottle crashing "+
                                "down on "+QTPNAME(target)+" head, devastating "+HIM(target)+
                                " with the blow.\n"
                                });
                        break;
                    } 
                    else if(strlen(attacker->query_prop(PIRATE_ALT_MSG)))
                    {
                        default_msg = attacker->query_prop(PIRATE_ALT_MSG);
                    }
                    attack_message = ({
                        default_msg+you_msg+" "+
                            "bring your bottle crashing down on "+QTPNAME(target)+
                            " head, devastating "+HIM(target)+" with the blow.\n",
                            default_msg+" "+
                            QTNAME(attacker)+" brings "+HIS(attacker)+" bottle crashing "+
                            "down on your head, devastating you with the blow.\n",
                            default_msg+" "+
                            QTNAME(attacker)+ " brings "+HIS(attacker)+" bottle crashing "+
                            "down on "+QTPNAME(target)+" head, devastating "+HIM(target)+
                            " with the blow.\n"
                            });
                    break;
                    
                default:
                    attack_message = ({
                        "Grabbing your bottle, you hit "+QTNAME(target)+" hard over "+
                            "the head.\n",
                            "Grabbing "+HIS(attacker)+" bottle, "+QTNAME(attacker)+" hits you "+
                            "hard over the head.\n",
                            "Grabbing "+HIS(attacker)+" bottle, "+QTNAME(attacker)+" hits "+
                            QTNAME(target)+" hard over the head.\n"
                            });
                    break;
            }
        }

        /* message to the attacker */
        attacker->catch_msg(attack_message[0]);

        /* message to the target */
        target->catch_msg(attack_message[1]);

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
       "Raising your bottle, you charge straight at "+QTNAME(target)+
       ", but still bleary from last night's debauchery, you miss "+HIM(target)+" by a mile.\n",
       QCTNAME(attacker)+" raises "+HIS(attacker)+" bottle as "+HE(attacker)+
       " charges straight at you. Luckily, in "+HIS(attacker)+" drunken haste "+
       HE(attacker)+" misses you by a mile.\n",
       QCTNAME(attacker)+" raises "+HIS(attacker)+" bottle as "+HE(attacker)+
       " charges straight at "+QTNAME(target)+". But in "+HIS(attacker)+
       " drunken haste "+HE(attacker)+" misses "+QTNAME(target)+" by a mile.\n"
    });
    
    /* message to attacker */
    attacker->catch_tell(attack_message[0]);

    /* message to target */
    target->catch_tell(attack_message[1]);
 
    /* message to onlookers */
    attacker->tell_watcher(attack_message[2], target);
}

mixed
cannot_attack_with_pbash(object who, object target, string attack)
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
        return "Attacking yourself? You are not THAT drunk!\n";
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
         return "You feel more like finding the nearest bar than to attack "+
                 target->query_the_name(who) + ".\n";
         }
    }
    return 0;
}

void set_pbash_msg(string str)
{
  this_player()->add_prop(PIRATE_ALT_MSG, str);
}
