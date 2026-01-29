/*
 * File         : /d/Genesis/start/hobbit/npc/guard.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/24/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The village is guarded by old Mungar and his three sons. Mungar
 *        were leading a small elite force during the war and now he has
 *        taught his sons about his professional skills. Now they earn
 *        their living from keeping the trouble out from the village.
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
#include <composite.h>
#include "../hobbit.h"

/* inherits */
inherit "/std/monster";
inherit "/std/act/action";
inherit EX_LIB + "grid";
/* defines */
// NPC states (bit values)
#define POLISHING   1

/* prototypes */
void create_monster();
void guard_actions();
void equip_me();
string guard_default_answer();

/* global variables */
int     Status; // Status bits for the NPC


/*
 * Function name: create_monster
 * Description  : set up the humanoid
 */
void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("guard");
    set_race_name("hobbit");
    
    set_gender(G_MALE);
    set_long(
      "This is an elite guard of this village. It is his job to keep " +
      "this village a peaceful place.\n");
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/24/99.\n");
    
    
    set_hp(query_max_hp());
    add_name(({"guard"}));
    add_adj(({"proud", "vigilant"}));
    set_short("vigilant guard");
    
    // Set up actions
    set_act_time(10);
    add_act("@@guard_actions@@");
    
    // Set up answers
    set_default_answer(guard_default_answer);
    add_ask(({"sun", "weather", "wind"}),
        "say No matter the weather, we guard this village.", 1);
    
    // Set up walking
    grid_set_size(1, 1);  // These values will be overloaded by calls 
    grid_set_pos(1, 1);   // from each start room for the guards
    
    // Get dressed
    equip_me();
    
    
}
/*
 * Function name: add_introduced
 * Description  : Whenever someone is introduced to me (CC), this function
 *                is called in me to tell me that 'name' (BB) is being
 *                introduced to me. The living that does the introduction
 *                (AA) is available though this_player().
 * Arguments    : string name - the [lower case] name of the living that
 *                              is being introduced to me. (BB)
 */
public void
add_introduced(string name)
{
    command("peer at " + name);
    command("say Nice meeting you, " + capitalize(name) + ".");
    command("smile grim");
}

/*
 * Function name: guard_actions()
 * Description  :  Handles NPC actions
 */
string
guard_actions()
{
    int i;
    i = random(5);
    switch(i)
    {
        case 0:
        {
            command("yawn");
            break;
        }
        case 1:
        {
            command("peer quickly");
            break;
        }
        case 2:
        {
            if (!environment()->query_prop(ROOM_I_INSIDE))
            {
                command("emote examines the sky.");
            }
            break;
        }
        case 3:
        {
            command("whistle confidently");
            break;
        }
        case 4:
        {
            grid_move_it(); // Take a walk
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
 * Function name: guard_default_answer()
 * Description  : Handles the default answer for unknown questions.
 */
string
guard_default_answer()
{
    command("say I am very sorry, but I don't know.");
    command("scratch");
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
    clone = clone_object(EX_ARM + "leather_boots");
    clone->move(TO);
    
    // Make a shield and a weapon
    
    // Put it on!
    command("wear all");
    command("wield all");
}
/*
 * Function name: configure_me(int size)
 * Description  : Set the guard personality.
 */
void
configure_me(int size)
{
    add_prop(CONT_I_HEIGHT, (120 * size) / 100);
    add_prop(CONT_I_WEIGHT, (55000 * size) / 100);
    set_stats(({30, (80 * size) / 100, (80 * size) / 100,
                70,  40,               (80 * size) / 100}));
    set_hp(query_max_hp());
}

