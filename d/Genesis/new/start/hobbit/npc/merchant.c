/*
 * File         : /d/Genesis/start/hobbit/npc/merchant.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/24/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The shop is owned by a small and greedy hobbit and will allow
 *        selling new equipment like spades, sacks and gauntlets as well
 *        as buying and selling loot.
 * 
 * TODO         :
 *      - Add chat
 *      - Add triggers
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

/* directives */
#pragma strict_types

/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <ss_types.h> 
#include <filter_funs.h>

#include "../hobbit.h"

/* inherits */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/d/Genesis/lib/intro";
/* defines */
// NPC states (bit values)
#define CLEANING   1

/* prototypes */
void create_monster();
void merchant_actions();
void equip_me();
string merchant_default_answer();

/* global variables */
int     Status;
object  Visitor;

/*
 * Function name: create_monster
 * Description  : set up the humanoid
 */
void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("soltan");
    set_race_name("hobbit");
    
    set_gender(G_MALE);
    set_long(
      "The merchant is a small old hobbit with a greedy look in his " +
      "face. He was one of the first merchants in the village trading " +
      "farming tools for war treasures.\n");
    add_prop(CONT_I_HEIGHT, 115);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/24/99.\n");
    
    set_stats(({30, 40, 40, 70, 40, 20}));
    set_hp(query_max_hp());
    add_name(({"merchant", "shop-owner", "owner"}));
    add_adj(({"small", "greedy"}));
    set_act_time(5);
    add_act("@@merchant_actions@@");
    set_default_answer(merchant_default_answer);
    add_ask(({"sun", "weather", "wind"}),
        "say well, I don't see much of it spending most of my time here in the shop.", 1);
    equip_me();
    
    
}
/*
 * Function name: introduce
 * Description  : A player that introduces himself to the NPC for the 
 *                first time will get a respons defined by this function
 * Arguments    : object who - The introduced player object
 */
void
introduce(object who)
{
    command("smile ingrat at " + who->query_name());
    command("introduce me");
    command("say What can I do for you, " + who->query_name() + "?");
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
    command("smile ingrat at  " + who->query_name());
    command("say Hello again, " + 
        (who->query_gender() ? "my Lady!" : "Sir!"));
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
 * Function name: merchant_actions()
 * Description  :  Handles NPC actions
 */
string
merchant_actions()
{
    int i;
    if (Visitor && present(Visitor, environment(this_object())))
    {
        i = random(2);
        switch(i)
        {
            case 0: // Smile eager & wave invitingly
            {
                command("smile eager");
                command("wave invit at " + Visitor->query_name());
                break;
            }
            case 1: // peer greed
            {
                command("peer greed at " + Visitor->query_name());
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
    i = random(5);
    switch(i)
    {
        case 0:
        {
            command("peer greed");
            break;
        }
        case 1:
        {
            command("count coins");
            break;
        }
        case 2:
        {
            command("emote gazes through the door for more customers.");
            break;
        }
        case 3:
        {
            command("whistle cheer");
            break;
        }
        case 4:
        {
            command("emote whipes off the counter carefully.");
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
 * Function name: merchant_default_answer()
 * Description  : Handles the default answer for unknown questions.
 */
string
merchant_default_answer()
{
    command("say I've met a lot of people but never heard about that.");
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
    
    // Put it on!
    command("wear all");
}

