/*
 * File         : /d/Genesis/start/hobbit/npc/baker.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1999, Joakim Larsson
 * Date         : 3/25/1999
 * Related Files: 
 * Purpose      : 
 *     The baker is a very fat young female hobbit. She met her husband
 *    in the camp on the other continent where she learned all she knew
 *    about cooking and baking. She is merrily unknowing about most of
 *    the war which her husband has kept from her. Her name is Minna
 *    Foxter
 * Todo         : 
 *      *      - Add chat
 *      *      - Add triggers
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
// Smith states (bit values)
#define BAKING   1

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
    set_name("minna");
    set_adj(({ "fat", "smiling", "blue-eyed", "red-haired", "curly-haired"}));
    set_race_name("hobbit");
    set_gender(G_FEMALE);
    set_long(
        "The baker is a very fat female hobbit. She has blue eyes and " +
        "light red curly hair and is constantly chewing on a piece of " +
        "candy.\n");
    add_prop(CONT_I_HEIGHT, 95);
    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(NPC_I_NO_LOOKS, 1);
    
    set_default_answer(npc_default_answer);
    add_ask(({"candies", "candy", "sweet", "bon-bon"}), ({"say Yes", " we got all kinds of that in 25 different shapes and colors."}), 1);
    
    set_stats(({60, 50, 50, 30, 30, 90}));
    set_alignment(50);
    set_hp(query_max_hp());
    add_act("@@npc_actions@@");
    set_act_time(6);
    equip_me();
    
    add_name("baker");
    
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
    command("emote chuckles happily with a broad smile in her face.");
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
    command("shout " + who->query_name() + "!");
    command("say So you are here again, how nice!");
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
    if (Visitor && present(Visitor, environment(this_object())))
    {
        i = random(3);
        switch(i)
        {
            case 0: // Smile & point
            {
                command("smile");
                command("point at " + Visitor->query_name());
                break;
            }
            case 1: // Smile merr
            {
                command("smile merr at " + Visitor->query_name());
                break;
            }
            case 2: // Wave merr
            {
                command("wave merr at " + Visitor->query_name());
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
            command("smile cheer");
            break;
        }
        case 1:
        {
            command("emote claps her floury hands together.");
            break;
        }
        case 2..4:
        {
            command("emote puts a couple of candies in her mouth.");
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
    command("shrug thought");
    command("say I don't think I know anything about that.");
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
    clone = clone_object(EX_OBJ + "linnen_apron");
    clone->move(TO);
    clone = clone_object(EX_OBJ + "linnen_pants");
    clone->move(TO);
    clone = clone_object(EX_OBJ + "linnen_shirt");
    clone->move(TO);
    
    // Make some armour featured clothes
    clone = clone_object(EX_ARM + "leather_shoes");
    clone->move(TO);
    
    // Put it on!
    command("wear all");
}

/* EOF */
