/*
 * File         : /d/Genesis/start/hobbit/npc/clerk.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1999, Joakim Larsson
 * Date         : 3/25/1999
 * Related Files: 
 * Purpose      : 
 *     This hobbit clerk, running the little bank office, is a dreamer
 *    and sometimes he fells a sleep because hobbits don't care much
 *    about putting money in the bank. Still he thinks this a much
 *    nicer job than working in the fields. The His name is Obi Kaan
 * Todo         : 
 *      * - Prohibit bank transactions while asleep.
 *      * - Trigger code for 'pat' wich will wake up Obi.
 *      * - Snoring
 *      
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

/* directives */
#pragma strict_types
/* inherits */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/d/Genesis/lib/intro";
/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <ss_types.h> 
#include <filter_funs.h>
#include "../hobbit.h"
/* defines */
// Clerk states (bit values)
#define SLEEPING   1

/* prototypes */
void npc_actions();
void npc_default_answer();
void equip_me();

/* globals */
int     Status;
object  Visitor;

/*
 * Function name:       create_monster
 * Description  :       set up the npc
 */
void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("obi");
    set_adj(({ "pale", "sleepy", "yawning"}));
    set_race_name("hobbit");
    set_gender(G_MALE);
    set_long(
        "The clerk is quite pale and has a sleepy outlook.\n");
    add_prop(CONT_I_HEIGHT, 105);
    add_prop(CONT_I_WEIGHT, 32000);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_ATTACK, "You can't attack the clerk because he's behind the iron bars.\n");
    
    set_default_answer(npc_default_answer);
    add_ask(({"money", "cash", "coin", "coins"}), "say We got plenty of it passing by here every day.", 1);
    
    set_stats(({40, 50, 50, 50, 30, 90}));
    set_alignment(50);
    set_hp(query_max_hp());
    add_act("@@npc_actions@@");
    set_act_time(6);
    equip_me();
    
    add_name("clerk");
    
}
/*
 * Function name: introduce
 * Description  : A player that introduces himself to the nPC for the 
 *                first time will get a respons defined by this function
 * Arguments    : object who - The introduced player object
 */
void
introduce(object who)
{
    if (SLEEPING & Status)
    {
        Status &=  ~SLEEPING;
        command("emote wakes up.");
    }
    command("emote sets up a sleepy smile in his face.");
    command("introduce myself to " + OB_NAME(who));
}

/*
 * Function name: greet
 * Description  : A player that has already introduced himself to the NPC 
 *                will get a respons defined by this function.
 * Arguments    : object who - The introduced player object
 */
void
greet(object who)
{
    if (SLEEPING & Status)
    {
        Status &=  ~SLEEPING;
        command("emote wakes up.");
        command("yawn");
    }
    command("say I remember you, nice to meet you again " +
             who->query_name() + "!");
}

/*
 * Function name: set_visitor(who)
 * Description  : access method for the Visitor variable
 * Arguments    : object who - the player object visiting us.
 */
public void
set_visitor(object who)
{
    Visitor = who;
}

/*
 * Function name: npc_actions()
 * Description  :  Handles NPC actions
 */
string
npc_actions()
{
    int i;
    if (SLEEPING & Status)
    {
        Status &=  ~SLEEPING;
        command("emote wakes up.");
    }
    if (Visitor && present(Visitor, environment(this_object())))
    {
        i = random(3);
        switch(i)
        {
            case 0: // Respond depending on gender
            {
                if (Visitor->query_gender())
                {
                    command("eyebrow flirt at " + Visitor->query_name());
                }
                else
                {
                    command("eyebrow happ at " + Visitor->query_name());
                }
                break;
            }
            case 1: // Smile ackn
            {
                command("smile ackn at " + Visitor->query_name());
                break;
            }
            case 2: // Wave slight
            {
                command("wave slight at " + Visitor->query_name());
                break;
            }
            default:
            {
                command("smile confused");
                break;
            }
        }
    }
    Visitor = 0;
    i = random(10);
    switch(i)
    {
        case 0..1:
        {
            command("emote grins proudly.");
            break;
        }
        case 2..3:
        {
            command("yawn");
            break;
        }
        case 4:
        {
            command("emote falls asleep.");
            Status |= SLEEPING;
            break;
        }
        case 5..6:
        {
            command("emote stretches his tired body.");
            break;
        }
        case 7..9:
        {
            command("emote gazes dreamingly out through the window.");
            break;
        }
        default:
        {
            command("emote does something totally unexpected.");
        }
    }
    return "";
}

/*
 * Function name: npc_default_answer()
 * Description  : Handles the default answer for unknown questions.
 */
string
npc_default_answer()
{
    if (SLEEPING & Status)
    {
        Status &=  ~SLEEPING;
        command("emote wakes up.");
    }
    command("say I am not aware of that I'm afraid.");
    return "";
}

/*
 * Function name: equip_me()
 * Description  : create cloths and equipments and wear it.
 */
void
equip_me()
{
    object clone;
    
    seteuid(getuid(TO));
    
    // Make some basic clothes
    clone = clone_object(EX_OBJ + "linnen_pants");
    clone->move(TO);
    clone = clone_object(EX_OBJ + "linnen_shirt");
    clone->move(TO);
    
    // Make some armour featured clothes
    clone = clone_object(EX_ARM + "leather_vest");
    clone->move(TO);
    clone = clone_object(EX_ARM + "leather_shoes");
    clone->move(TO);
    
    // Make some nice objects
    clone = clone_object(EX_OBJ + "spectacles");
    clone->move(TO);
    
    // Put it on!
    command("wear all");
}

/* EOF */
