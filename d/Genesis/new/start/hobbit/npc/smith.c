/*
 * File         : /d/Genesis/start/hobbit/npc/smith.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/24/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The blacksmith is a well built middle aged female warrior hobbit
 *        with speciality to remake armour and weapon into agricultural
 *        tools like rake, plough and spit. She will also make some newbie
 *        weapons for a nice price like 100? cc (sword) + 150? cc (Helmet
 *        + Shield) which will give any newbie enough force to kill
 *        underearthlings around the village. Her name is Sheena Rabbit
 * 
 * TODO         :
 *      - Add forging features
 *      - Add more triggers
 *      - Add weapon/armour trade
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
// Smith states (bit values)
#define FORGING   1

/* prototypes */
void create_monster();
void smith_actions();
void equip_me();
string smith_default_answer();

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
    set_name("sheena");
    set_race_name("hobbit");
    
    set_gender(G_FEMALE);
    set_long(
      "The blacksmith is a middle aged female hobbit. Her muscular body " +
      "has been built from hard work in the heat from the forge. She " +
      "has brown eyes and waist length black hair tied into a horsetail.\n");
    add_prop(CONT_I_HEIGHT, 120);
    add_prop(CONT_I_WEIGHT, 35000);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/24/99.\n");
    
    set_stats(({150, 110, 130, 30, 30, 90}));
    set_hp(query_max_hp());
    add_name(({"smith", "smitty", "amazon", "blacksmith"}));
    add_adj(({"attractive", "brown-eyed", "forging", "warrior", "athletic"}));
    set_act_time(5);
    add_act("@@smith_actions@@");
    set_default_answer(smith_default_answer);
    add_ask(({"hot", "fire", "coal", "body"}),
        "say The heat and some hard work keeps my body in shape.", 1);
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
    command("smile softly at " + who->query_name());
    command("introduce me to " + who->query_name());
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
    command("peer thought " + who->query_name());
    command("say I know, we have met.");
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
 * Function name: smith_actions()
 * Description  :  Handles NPC actions
 */
string
smith_actions()
{
    int i;
    if (Visitor && present(Visitor, environment(this_object())))
    {
        i = random(5);
        switch(i)
        {
            case 0: // Smile gent & wave
            {
                command("smile gent");
                command("wave brief at " + Visitor->query_name());
                break;
            }
            case 1..4: // Nothing
            {
                break;
            }
            default:
            {
                command("smile confused");
                break;
            }
        }
    }
    i = random(3);
    switch(i)
    {
        case 0:
        {
            command("emote examines the forge carefully.");
            break;
        }
        case 1:
        {
            command("emote pats the anvil.");
            break;
        }
        case 2:
        {
            command("emote smiles grimly.");
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
 * Function name: smith_default_answer()
 * Description  : Handles the default answer for unknown questions.
 */
string
smith_default_answer()
{
    command("smile innocently");
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
    
    // make and wear some basic clothes
    clone = clone_object(EX_OBJ + "linnen_pants");
    clone->move(TO);
    
    // Make some working clothes
    clone = clone_object(EX_ARM + "leather_apron");
    clone->move(TO);
    
    clone = clone_object(EX_ARM + "leather_boots");
    clone->move(TO);
    
    // Make some nice stuff
    clone = clone_object(EX_OBJ + "bronze_bracelet");
    clone->move(TO);
    clone = clone_object(EX_OBJ + "bronze_bracelet");
    clone->move(TO);
    
    // Put it on!
    command("wear pants"); // Must come before the apron
    command("wear all");
}

