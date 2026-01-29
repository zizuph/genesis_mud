/*
 * File         : /d/Genesis/start/hobbit/npc/spider.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 11/12/1998
 * Purpose      : 
 * Related Files: 
 *      - hobbit/doc/mosquito.c, the original combat code by Mercade
 *      - /doc/examples/poison/spider.c, the original poison code
 * Comments     :
 *        This spider is ment to crawl around in a warehouse with barrels
 *        from southern continents. It will crawl around and do some
 *        emotes and possibly spin a net. If someone tries to catch it it
 *        will bite with a quite harmless poison to teach newbies what
 *        that is. If attacked it will die imediatelly upon the first hit,
 *        however if it is missed i may as well bite back. NOTE: The
 *        combat code is based on Mercade's Gondor mosquito and modified
 *        to fit its new purpose. The poison part has been taken from the
 *        poison example files.
 * 
 * TODO         :
 *      - add bite when taken without gloves or try to take cobweb
 *      - add picable cobweb object when finnished
 *      - add some emotes when spider misses its bites
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

/* directives */
#pragma strict_types

/* inherits */
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";


/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <filter_funs.h>
#include <poison_types.h>
#include <ss_types.h>
#include "../hobbit.h"

/* defines */
// Combat values
#define BASE_DEX           (5)
#define DEX_LIMIT          (5)
#define LEFT_RIGHT   ({ "left", "right" })
#define DOUBLE_PARTS ({ "biceps", "hand", "cheek",  "ear", "leg", "thigh", \
                        "fore-arm", "upper arm", "calf" })
#define SINGLE_PARTS ({ "nose", "belly", "breast", "chin", "forehead" })
#define SPIDER_POISON    ("/std/poison_effect")
// Spider states (bit values)
#define IN_HIDEOUT 1
#define START_WEB  2
#define DONE_WEB   4
#define DINNER     8



/* prototypes */
void create_creature();
void spider_actions();


/* globals */
int     Status;
string  HideOut = "from under a barrel";
string  HideIn  = "under a barrel";
string *double_parts = DOUBLE_PARTS;
string *single_parts = SINGLE_PARTS;
int    *damage;
string  poison_file  = SPIDER_POISON;

string  SpiderAction5t6 = "starts building on a cobweb.";
string  SpiderAction7   = "inspects the cobweb carefully and fixes some " +
                          "minor faults.";
string  SpiderAction8t9 = "hides in a corner of the cobweb awaiting dinner.";

// access functions for globals
void set_hideout(string I, string O) { HideIn = I; HideOut = O;}


/*
 * Function name:       create_creature
 * Description  :       set up the non-humanoid
 */
void
create_creature()
{
    set_name("spider");
    set_short("red legged spider");
    set_long(
      "With a spheric black body and eight red legs this spider can " +
      "easily be detected. Its jaws are quite big compared to the body.\n");
    add_prop(CONT_I_HEIGHT, 1);
    add_prop(CONT_I_VOLUME, 1);
    add_prop(CONT_I_WEIGHT, 2);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    
    set_act_time(2);
    add_act("@@spider_actions@@");
    set_gender(G_NEUTER);
    set_stats(({ 0, 0, 0, 0, 0, 0 }));
    remove_prop(OBJ_M_NO_GET);
    set_race_name("spider");
    set_pname("spiders");
    set_adj("red legged");
    set_short(query_adj() + " spider");
    set_pshort(query_adj() + " spiders");
    
    
}

/*
 * Function name: spider_actions()
 * Description  :  Keep track of spider status and movements
 */
void
spider_actions()
{
    int i;
    i = random(10);
    if ((IN_HIDEOUT & Status) != 0)
    {
        if (i < 2)
        {
            set_invis(0);
            command("emote crawls out " + HideOut + ".");
            Status &=  ~IN_HIDEOUT;
            Status &=  ~DINNER;
        }
    }
    else
    {
        switch(i)
        {
            case 0..1: // If under the hideout - get out (taken care of above)
            {
                break;
            }
            case 2..4: // Hide under object set by set_hideout()
            {
                if ((IN_HIDEOUT & Status) == 0)
                {
                    command("emote crawls in " + HideIn + ".");
                    set_invis(99);
                    Status |= IN_HIDEOUT;
                }
                break;
            }
            case 5..6: // If no web initiated - start build a web
            {
                if (((START_WEB & Status) == 0))
                {
                    command("emote " + SpiderAction5t6);
                    Status |=  START_WEB;
                }
                break;
            }
            case 7:  // if web not finished - check out creation
            {
                if (((START_WEB & Status) != 0) && ((DONE_WEB & Status) == 0))
                {
                    command("emote " + SpiderAction7);
                    Status |=  DONE_WEB;
                }
                break;
            }
            case 8..9: // if web finished - wait for dinner
            {
                if (((DONE_WEB & Status) != 0) && ((DINNER & Status) == 0))
                {
                    command("emote " + SpiderAction8t9);
                    Status |=  DINNER;
                }
                break;
            }
            default:
            {
                command("emote does something totally unexpected.");
            }
        }
    }
}

/*
 * Function name: try_bite()
 * Description  :  Try to hurt the attacker with a poisonous bite
 *        50% hardcoded chance to make it.
 */
void
try_bite(object victim)
{
    object bite;
    int    part;
    string body_part;
    
    if (random(2))
    {
        return;
    }
    part = random(2 * sizeof(double_parts) + sizeof(single_parts));
    body_part = ((part < sizeof(single_parts)) ? single_parts[part] :
      LEFT_RIGHT[(part - sizeof(single_parts)) % 2] + " " +
      double_parts[(part - sizeof(single_parts)) / 2]);
    tell_object(victim, "A fast tickeling feeling comes up your leg and you " +
      "feel an itch in your " + body_part + " and you think you have been " +
      "biten by " + query_art_name(victim) + ".\n");
    say(victim->query_name() + " grabs at " + POSSESSIVE(victim) +
      " " + body_part + " and you suspect that " + PRONOUN(victim) +
      " has just been biten there by something.\n",  victim);
    seteuid(getuid());
    bite = clone_object(poison_file);
    if (bite)
    {
        bite->move(victim, 1);
        bite->set_time(1000);
        bite->set_interval(100);
        bite->set_strength(40);
        bite->set_damage(({POISON_FATIGUE, 100, POISON_STAT, SS_CON }));
        bite->start_poison();
    }
    
}

/*
 * Function name: attacked_by
 * Description  : This function is called when the spider is attacked.
 *        The spell-attack property is set to re-direct combat to this object. 
 *        We do not want the normal attacking on particular hit locations.
 * Arguments    : object attacker - whoever had the nerve to come after us.
 */
void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    try_bite(attacker);
    attacker->add_prop(LIVE_O_SPELL_ATTACK, TO);
}

/*
 * Function name: spell_attack
 * Description  : Each combat round the attacker tries to stomp it. 
 *                There is no such things as arm-wrestling with spiders.
 * Arguments    : object attacker - who tries to stomp on us.
 *                object target - the target should be me.
 */
void
spell_attack(object attacker, object target)
{
    int dark_attack = 100;
    int dex;
    
    // Skip it if target is someone else or you can' t see the attacker
    if ((target != TO) || (!CAN_SEE(attacker, target)))
    {
        return;
    }
    
    // Hit is partially based on dexterity and 50 percent on chance.
    if (((IN_HIDEOUT & Status) == 0) &&
      (random(dex) < DEX_LIMIT) && (random(2)))
    {
        attacker->tell_watcher(QCTNAME(attacker) + " manages to stomp " +
          QTNAME(TO) + " to a pulp.\n", TO);
        tell_object(attacker, BSN("You manage to stomp the spider " +
          query_the_name(attacker) + " to a pulp!"));
        
        /* We need to calculate the current HP since we want to reset the
         *  delay value since that is queried in the do_die() function.
         */
        calculate_hp();
        set_hp(0);
        do_die(attacker);
        return;
    }
    attacker->tell_watcher(QCTNAME(attacker) + " tries to stomp " + QNAME(TO) + 
      ", but fails to hit it.\n", TO);
    tell_object(attacker, BSN("You try to stomp " + query_the_name(attacker) + 
      ", but fail to hit it!"));
    
    /* We need to re-add property directly after the heartbeat has 
     *  called this function
     */
    set_alarm(0.1, 0.0, &attacker->add_prop(LIVE_O_SPELL_ATTACK, TO));
}

