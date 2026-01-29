/*
 * File         : /d/Genesis/start/hobbit/npc/informer.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1999, Joakim Larsson
 * Date         : 3/25/1999
 * Related Files: 
 * Purpose      : 
 * Todo         : 
 *      
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
// NPC states (bit values)
#define SLEEPING   1

/* prototypes */
void npc_actions();
void npc_default_answer();
void equip_me();
string give_map();
string bakery();
string bank();
string blacksmith();
string guild();
string port();
string pub();
string shop();


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
    set_name("fiona");
    set_adj(({ "young", "smiling", "happy"}));
    set_race_name("hobbit");
    set_gender(G_FEMALE);
    set_long(
        "The informer is hired by the Reed village council to help the " +
        "increasing number of visitors to find their way around. She also " +
        "hands out maps and will try to answer any questions about the " +
        "village.\n");
    add_prop(CONT_I_HEIGHT, 100);
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(NPC_I_NO_LOOKS, 1);
    
    set_default_answer(npc_default_answer);
    add_ask(({"bakery", "candy"}), bakery, 1);
    add_ask(({"bank", "money"}), bank, 1);
    add_ask(({"blacksmith", "smithy", "armour", "weapon"}), blacksmith, 1);
    add_ask(({"guild", "training", "adventurers guild"}), guild, 1);
    add_ask(({"map", "palmphlet", "maps", "palmphlets"}), give_map, 1);
    add_ask(({"port", "ship", "ships"}), port, 1);
    add_ask(({"pub", "beer", "food"}), pub, 1);
    add_ask(({"seagull", "seagulls", "guano", "guanos"}), "say The birds are a part of the special harbour atmosphere around here.", 1);
    add_ask(({"shop", " sell", " buy"}), shop, 1);
    
    set_stats(({40, 70, 70, 50, 70, 90}));
    set_alignment(50);
    set_hp(query_max_hp());
    add_act("@@npc_actions@@");
    set_act_time(6);
    equip_me();
    
    add_name("informer");
    
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
 * Function name: npc_default_answer()
 * Description  : Handles the default answer for unknown questions.
 */
string
npc_default_answer()
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
    command("say I'm glad you asked!");
    command("say Please have a copy of our newly published village map.");
    command("say It is hand made by some monks in the mountains.");
    clone_object(EX_OBJ + "village_map")->move(TO);
    command("give map to " + OB_NAME(TP));
    command("It is free of charge, please enjoy your stay here.");
    return "";
}

/*
 * Function name: blacksmith()
 * Description  : give direction to the blacksmith.
 */
string
blacksmith()
{
    command("say You'll find the blacksmith just on the other " +
        "side of the bridge here.");
    command("point west");
    command("say Give Sheena my regards.");
    command("smile gently");
    return "";
}

/*
 * Function name: shop()
 * Description  : give direction to the shop.
 */
string
shop()
{
    command("say You'll find a shop on the other side " +
        "of the bridge and south.");
    command("point southwest");
    command("whisper to " + OB_NAME(TP) + " Be aware that the owner " +
        "is a bit greedy.");
    command("smile gently");
    return "";
}

/*
 * Function name: post()
 * Description  : give direction to the post office.
 */
string
post()
{
    command("say You'll find the post office just outside of here " +
        "and it is fully equiped with the latest gnomish gizmo.");
    command("point south");
    command("smile gently");
    return "";
}

/*
 * Function name: pub()
 * Description  : give direction to the pub, the "Iron Peace".
 */
string
pub()
{
    command("say At the Iron Inn you can have a small meal and " +
        "a beer at quite comfortable prices.");
    command("say you will find it just southeast of here.");
    command("point southeast");
    command("whisper to " + OB_NAME(TP) + " Be aware that Tan, the publican, " +
        "can be a little harch some times, but he is a good man by heart.");
    command("say He might even ask you for some help.");
    command("smile gently");
    return "";
}

/*
 * Function name: guild()
 * Description  : give direction to the Adventurers guild.
 */
string
guild()
{
    command("say To get in shape you can visit the Adventurer's guild.");
    command("say you will find it just outside of here.");
    command("point east");
    command("say Say hello to Solar from me, she is really a nice lady " +
        "you know.");
    command("smile gently");
    return "";
}

/*
 * Function name: bank()
 * Description  : give direction to the bank.
 */
string
bank()
{
    command("say During hot days the bank is a nice place to visit.");
    command("say Go east and up the road northwards, and you will see it.");
    command("point northeast");
    command("say You will probably have to wake up Obi, he is a tired man.");
    command("smile gently");
    return "";
}

/*
 * Function name: bakery()
 * Description  : give direction to the bakery.
 */
string
bakery()
{
    command("say One visit to Minna at the bakery and you will need " +
        "to spend the rest of the week with Solar.");
    command("chuckle cheer");
    command("say Just go over the bridge and turn right and you'll smell it.");
    command("point northwest");
    command("say Her candy is delicious, I am serious. It's a threat " +
        "to mankind!");
    command("smile cheer");
    return "";
}

/*
 * Function name: port()
 * Description  : give direction to the port.
 */
string
port()
{
    command("say The port is found if you follow the portroad just west " +
        "of here, southwards. On the east pier you find the shipping office " +
        "where you can get more info on the ship lines and such.");
    command("point south");
    command("whisper to " + OB_NAME(TP) + " Maybe you could give Bon my " +
        "dearest regards also. He's so nice!");
    command("blush slight");
    command("giggle");
    return "";
}

/* EOF */
