/*
 * File         : /d/Genesis/start/hobbit/npc/informer.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 3/7/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *         * - Add chat * - Add triggers
 * 
 * TODO         :
 
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
#define SLEEPING   1

/* prototypes */
void create_monster();
void informer_actions();
void informer_default_answer();
void equip_me();
string give_map();

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
    set_name("fiona");
    set_race_name("hobbit");
    
    set_gender(G_FEMALE);
    set_long(
      "The informer is hired to help the increasing number of visitors " +
      "to find their way around. She hand out maps and will try to " +
      "answer any questions about the surroundings.\n");
    add_prop(CONT_I_HEIGHT, 100);
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 3/7/99.\n");
    
    set_stats(({40, 70, 70, 50, 70, 90}));
    set_hp(query_max_hp());
    add_name("informer");
    add_adj(({"young", "smiling", "happy" }));
    set_act_time(5);
    add_act("@@informer_actions@@");
    set_default_answer(informer_default_answer);
    add_ask(({"seagull", "seagulls", "bird", "birds", "guano"}),
        "say The birds are a part of the special harbour atmosphere around here.", 1);
    add_ask(({"map", "palmphlet", "maps", "palmphelts"}),
        give_map, 1);
    equip_me();
    
    
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
    command("smile nicely");
    command("introduce me to " + OB_NAME(who));
    command("say How may I help you?");
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
    command("smile cheer at " + OB_NAME(who));
    command("say How may I help you further?");
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
 * Function name: informer_actions()
 * Description  :  Handles NPC actions
 */
string
informer_actions()
{
    int i;
    if (Visitor && present(Visitor, environment(this_object())))
    {
        i = random(3);
        switch(i)
        {
            case 0..1: // Smile happ
            {
                command("smile at " + OB_NAME(Visitor));
                break;
            }
            case 2: // Wave slightly at
            {
                command("wave at " + OB_NAME(Visitor));
                command("smile at " + OB_NAME(Visitor));
                break;
            }
            default:
            {
                command("sob deep");
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
            command("emote studies a pamphlet.");
            break;
        }
        case 1:
        {
            command("giggle .");
            break;
        }
        case 2:
        {
            command("say May I help you with something?");
            break;
        }
        case 3:
        {
            command("say I know most people in the village.");
            break;
        }
        case 4:
        {
            command("smile cheer");
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
 * Function name: informer_default_answer()
 * Description  : Handles the default answer for unknown questions.
 */
string
informer_default_answer()
{
    command("say I am sure something can be arranged to let you find out.");
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
    clone = clone_object(EX_OBJ + "linnen_dress");
    clone->move(TO);
    clone = clone_object(EX_OBJ + "linnen_hood");
    clone->move(TO);
    
    // Make some armour featured clothes
    clone = clone_object(EX_ARM + "leather_vest");
    clone->move(TO);
    clone = clone_object(EX_ARM + "leather_shoes");
    clone->move(TO);
    
    // Put it on!
    command("wear all");
}
/*
 * Function name: give_map()
 * Description  : create a map and give it to the visitor.
 */
string
give_map()
{
    command("say I'm glad you asked. \nPlease have a copy " +
        "of our newly delivered village map. \n It has been " +
        "hand copied by some monks in the mountains.");
    clone_object(EX_OBJ + "guano_blob")->move(TO);
    command("give all to " + OB_NAME(TP));
    command("It is free of charge, please enjoy your stay here.");
    return "";
}

