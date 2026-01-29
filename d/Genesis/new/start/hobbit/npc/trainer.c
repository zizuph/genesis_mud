/*
 * File         : /d/Genesis/start/hobbit/npc/trainer.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/24/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The trainer is an old scarred female hobbit trainer that has not
 *        forgotten the time she spent as a professional killer. Now she
 *        teaches all and everybody how to defend themselves and stay out
 *        of trouble.
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
#include  <living_desc.h>
#include <filter_funs.h>
#include "../hobbit.h"

/* inherits */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/d/Genesis/lib/intro";
/* defines */
// NPC states (bit values)
#define MEDITATING   1

/* prototypes */
void create_monster();
void trainer_actions();
void equip_me();
string trainer_default_answer();

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
    set_name("solar");
    set_race_name("hobbit");
    
    set_gender(G_FEMALE);
    set_long(
      "The trainer is an old scarred female hobbit. Now she teaches all " +
      "and everybody how to defend themselves and stay out of trouble. " +
      "The collection of scars is prof that the she knows what she " +
      "talks about.\n");
    add_prop(CONT_I_HEIGHT, 100);
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/24/99.\n");
    
    set_stats(({70, 90, 90, 50, 90, 200}));
    set_hp(query_max_hp());
    add_name("trainer");
    add_adj(({"old", "athletic"}));
    set_act_time(5);
    add_act("@@trainer_actions@@");
    set_default_answer(trainer_default_answer);
    add_ask(({"training", "skills"}),
        "say If you pay the price in sweat and coins I'll teach you something.", 1);
    set_scar(SCAR_RIGHT_CHEEK | SCAR_FOREHEAD);
    
    
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
    command("smile stiff");
    command("introduce me");
    command("say to " + who->query_name() +
         " Welcome " + who->query_name() + ".");
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
    command("smile calm at  " + who->query_name());
    command("say to " + who->query_name() + " Relax " +
        (who->query_gender() ? "woman." : "man."));
    command("say We have aready been introduced, remember?");
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
 * Function name: trainer_actions()
 * Description  :  Handles NPC actions
 */
string
trainer_actions()
{
    int i;
    if (Visitor && present(Visitor, environment(this_object())))
    {
        i = random(2);
        switch(i)
        {
            case 0: // Smile invitingly
            {
                command("smile invit at " + Visitor->query_name());
                break;
            }
            case 1: // Nod in acknowledge
            {
                command("nod ackn at " + Visitor->query_name());
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
    if (MEDITATING & Status)
    {
        Status &=  ~MEDITATING;
        command("rise");
    }
    else
    {
        i = random(5);
        switch(i)
        {
            case 0:
            {
                command("blank");
                break;
            }
            case 1:
            {
                command("stretch");
                break;
            }
            case 2:
            {
                command("meditate");
                Status |= MEDITATING;
                break;
            }
            case 3:
            {
                command("smile .");
                break;
            }
            case 4:
            {
                command("emote mumbles secretively");
                break;
            }
            default:
            {
                command("emote does something totally unexpected.");
            }
        }
    }
    return "";
}

/*
 * Function name: trainer_default_answer()
 * Description  : Handles the default answer for unknown questions.
 */
string
trainer_default_answer()
{
    command("say My advice to you is for you to seek the answer " +
        "within yourself.");
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
    
    // Make and wear some basic clothes
    clone = clone_object(EX_OBJ + "linnen_pants");
    clone->move(TO);
    clone = clone_object(EX_ARM + "cotton_robe");
    clone->move(TO);
    
    // Put it on!
    command("wear all");
}

