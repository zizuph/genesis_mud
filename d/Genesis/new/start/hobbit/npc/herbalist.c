/*
 * File         : /d/Genesis/start/hobbit/npc/herbalist.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/27/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        Zagarn will be found as a cackling herbalist He will sell and buy
 *        herbs and related equipment in his role as a vandering merchant.
 *        No shop. He will give mean suggestions targeting different
 *        inhabitants. He will also give hints for newbie stuff like
 *        mention 'delivery tours' in the shipping office and 'herb
 *        picking' and searching in different places. Sometimes he gets
 *        depressed and will reward the newbie that comforts him with a
 *        small gift (a herb pouch) and a tip (buy gauntlets in the shop)
 *        This wandering herbalist has not yet become a herbalist but an
 *        ordinary merchant. The code for the shop functionality is taken
 *        from an example made by Mercade: /doc/examples/trade/merchant.c,
 *        and modified. Later code for herbalism and training skills will
 *        be added, when the apropriate code examples are made public.
 * 
 * TODO         :
 * - Add herbalist features
 * - Add chat
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
#include <filter_funs.h>
#include "../hobbit.h"

/* inherits */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/lib/shop";
inherit EX_LIB + "grid";
inherit "/d/Genesis/lib/intro";
/* defines */
// NPC states (bit values)
#define SELLING   1
// shop storage
#define STORE (EX_OBJ + "herbalist_sack")
/* prototypes */
void create_monster();
void herbalist_actions();
void equip_me();
string herbalist_default_answer();
/* global variables */
int     Status; // Status bits for herbalist 


/*
 * Function name: create_monster
 * Description  : set up the humanoid
 */
void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("zagarn");
    set_race_name("hobbit");
    
    set_gender(G_MALE);
    set_long(
      "The herbalist was once a great war hero but at the end of the " +
      "great war he was kept prisoned and has not completelly returned " +
      "to his former personality. Instead he started learning about " +
      "herbs and reading books about magics. Now adays he wanders about " +
      "in the village selling herbs and teaching herbalism to those who " +
      "dare to come near him.\n");
    add_prop(CONT_I_HEIGHT, 115);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/27/99.\n");
    
    set_stats(({30, 40, 40, 70, 40, 20}));
    set_hp(query_max_hp());
    add_name(({"herbalist"}));
    add_adj(({"pale", "wandering"}));
    
    // Set up actions
    set_act_time(10);
    add_act("@@herbalist_actions@@");
    
    // Set up answers
    set_default_answer(herbalist_default_answer);
    add_ask(({"sun", "weather", "wind"}),
        "say It's my destiny to face it, good or bad.", 1);
    
    // Set up trading
    config_default_trade();
    set_money_give_max(1000);
    
    // Set up walking
    grid_set_size(4, 10);  // How big is the grided are?
    grid_set_pos(3, 4);    // Where are we in it?
    
    // Get clothes
    equip_me();
    
    
}
/*
 * set up the herbalist features
 */
void
init_living()
{
    ::init_living();
    
    // Init the shop
    init_shop();
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
    command("giggle insane");
    command("introduce me");
    command("say I've been waiting for you, " + 
        who->query_name() + ".");
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
    command("peer grav at " + OB_NAME(who));
    command("say Some might call me insane, but I got a good memory.");
}

/*
 * Function name: herbalist_actions()
 * Description  :  Handles NPC actions
 */
string
herbalist_actions()
{
    int i;
    i = random(7);
    switch(i)
    {
        case 0:
        {
            command("moan slight");
            break;
        }
        case 1:
        {
            command("cackle");
            break;
        }
        case 2:
        {
            command("emote backs away slightly.");
            break;
        }
        case 3:
        {
            command("whistle silent");
            break;
        }
        case 4..6:
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
 * Function name: merchant_default_answer()
 * Description  : Handles the default answer for unknown questions.
 */
string
herbalist_default_answer()
{
    command("say I'm sure you find out somehow.");
    command("chuckle grim");
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
    
    // Make the storage sack
    clone = clone_object(STORE);
    clone->move(this_object(), 1);
    set_store_room(STORE);
    
    // Put it on!
    command("wear all");
}

/*
 * Since the normal shop assumes a store-room, we have to adjust some
 * of the hooks in order to give a better message.
 */

/*
* Function name: shop_hook_sold_items
* Description:   Hook that is called when player sold something
* Arguments:     item - The item array player sold
* Returns:       1
*/
int
shop_hook_sold_items(object *item)
{
    write("You sold " + COMPOSITE_DEAD(item) + ".\n");
    say(QCTNAME(this_player()) + " sold " + QCOMPDEAD + ".\n");
    /* lets tell everyone we put the stuff in our sack. */
    tell_room(environment(), QCTNAME(this_object()) + 
                             " puts the herbs in his sack.\n");
    return 1;
}

/*
 * Function name: shop_hook_bought_items
 * Description:   Called when player has bought something
 * Arguments:     arr - The array of objects
 * Returns:       1
 */
int
shop_hook_bought_items(object *arr)
{
    /* lets tell everyone we took the stuff out of our sack. */
    tell_room(environment(), QCTNAME(this_object()) + " takes " +
        (sizeof(arr) <= 1 ? "something" : "some things") +
        " out of his sack.\n");
    write("You bought " + COMPOSITE_DEAD(arr) + ".\n");
    say(QCTNAME(this_player()) + " bought " + QCOMPDEAD + ".\n");
    return 1;
}

/*
 * Function name: shop_hook_value_no_match
 * Description:   Called if there were no match with what the player asked
 *                about
 * Arguments:     str - The string player asked about
 * Returns:       0
 */
int
shop_hook_value_no_match(string str)
{
    /* we have a sack and not a store-room. */
    notify_fail("I have no '" + str + "' in my sack.\n");
}

/*
 * Function name: shop_hook_list_empty_store
 * Description:   If the storeroom is empty when the player wants a list
 *                of its items
 * Arguments:     str - If player specified string
 */
void
shop_hook_list_empty_store(string str)
{
    /* we do not have a store-room. */
    notify_fail("I have nothing to sell currently.\n");
}

/*
 * Function name: shop_hook_list_no_match
 * Description:   Called if player specified the list and no matching
 *                objects where found
 * Arguments:         str - The string he asked for
 * Returns:       0
 */
int
shop_hook_list_no_match(string str)
{
    /* we have a sack and no store-room */
    notify_fail("I have no '" + str + "' in my sack.\n");
}


/*
* Function name: shop_hook_allow_buy
* Description:   A hook to use if you want to test the object further if you
*                allow it to be bought
* Arguments:     ob - The object player wants to buy.
* Returns:       1 if we allow it to be bought (default)
*/
int
shop_hook_allow_buy(object ob)
{
    // command("say well, it's cloned from " + file_name(MASTER(ob)) + ".");
    command("say ok, take it!");
    return 1;
}

/*
 * This function is called from add_action(.., "read"), but since we
 * are not in a shop, we do not have a sign with instructions either.
 * This blocks that function.
 */
int
do_read(string str)
{
    return 0;
}


