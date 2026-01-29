/**
* Shoe merchant.
* Designed by Anahita.
* Louie  2005
*
* Navarre September 17th 2006, removed the act where he talks about Anahita.
* I dont like npcs talking about players by name.
*/

#pragma strict_types
 
#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define STOREROOM "/d/Krynn/solace/new_village/shoe/shoe_merchant_storeroom"

inherit M_FILE
inherit "/lib/shop";

/** prototypes **/
void return_intro(object ob);

void
create_krynn_monster()
{
    config_default_trade();

    set_name("ped");
    set_title("the Cobbler");
    add_name(({"shopkeeper","cobbler"}));
    set_race_name("elf");
    set_gender(0);
    set_adj("slender");
    add_adj("long-faced");
    set_short("slender long-faced elf");
    set_long("This slender elf looks well travelled.  He carries a pack "+
        "on his back, and is apparently a merchant of some sort.  " +
    "\n");

    set_store_room(STOREROOM);
    query_store_room()->load_me();

    set_act_time(5);
    add_act("emote rummages through his pack.");
    add_act("emote looks at your feet.");
    add_act("say You can tell a lot about a woman from her shoes!");
    add_act("say My fashions are all the rage in Palanthas.");

    set_all_hitloc_unarmed(50);

    set_stats(({70,70,70,70,70}));

    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_PARRY,50);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_WEP_POLEARM,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_KNIFE,50);
    add_prop(NPC_I_NO_RUN_AWAY,1);

    set_alignment(0);

}

void
add_introduced(string str)
{
    object ob = find_player(lower_case(str));
    if(ob && !ob->query_met(TO))
    {
	set_alarm(1.0, 0.0, &return_intro(ob));
    }
}

void
return_intro(object ob)
{
    string who;

    if(!present(ob, E(TO)))
    {
	return;
    }

    who = ob->query_real_name();

    command("say A pleasure to meet you, truly!");

    set_alarm(2.5, 0.0, &command("introduce me to "+who));
}

//From /lib/shop.c - we don't allow players to sell anything
int
shop_hook_allow_sell(object ob)
{
    TO->command("say I'm not in the purchasing business.");
    return 0;
}


/*
 * Function name: shop_hook_list_object
 * Description:   List an object
 * Arguments:	  ob - The object
 */
void
shop_hook_list_object(object ob, int price)
{
    string mess;

//   write("list_object OB: "+ob->query_name()+" Price: "+price+".\n");

    if (!strlen(mess = text(split_values(price))))
    {
        TO->command("say That wouldn't cost you much.");
    }
    
    switch (random(4))
    {
        case 0:
            TO->command("say I have "+LANG_ASHORT(ob)+" for "+mess+".");
            break;
        case 1:
            TO->command("say Let's see, how about "+LANG_ASHORT(ob)+" for "+mess+".");
            break;
        case 2:
            TO->command("say For "+mess+" I have "+LANG_ASHORT(ob)+".");
            break;
        case 3:
            TO->command("say Incredibly, I have "+LANG_ASHORT(ob)+" for "+mess+".");
            break;
        default:
            TO->command("say I have "+LANG_ASHORT(ob)+" for "+mess+".");
            break;
    }
}
/*
 * Function name: shop_hook_list_empty_store
 * Description:   If the storeroom is empty when the player wants a list
 *		  of its items
 * Arguments:	  str - If player specified string
 */
void
shop_hook_list_empty_store(string str)
{
    TO->command("say Sorry, I'm currently all out of merchandise.");
    NF("");

    //notify_fail("The store room is currently empty.\n");
}

/*
 * Function name: shop_hook_list_no_match
 * Description:   Called if player specified the list and no matching
 *		  objects where found
 * Arguments:	  str - The string he asked for
 * Returns:	  0
 */
int
shop_hook_list_no_match(string str)
{
    TO->command("say I don't have any '"+str+"' in stock.");
    NF("");
    //notify_fail("We have no '" + str + "' in stock.\n");
}
/*
 * Function name: shop_hook_buy_no_match
 * Description:   Called if player tried to buy something and no matching
 *		  objects where found
 * Arguments:	  str - The string he asked for
 * Returns:	  0
 */
int
shop_hook_buy_no_match(string str)
{
    TO->command("say I don't have any '"+str+"' in stock.");
    NF("");
    //notify_fail("We have no '" + str + "' in stock.\n");
}
/*
 * Function name: shop_hook_value_no_match
 * Description:   Called if there were no match with what the player asked
 *		  about
 * Arguments:     str - The string player asked about
 * Returns:	  0
 */
int
shop_hook_value_no_match(string str)
{
    TO->command("say I don't have any '"+str+"' in stock.");
    NF("");
    //notify_fail("We hold no '" + str + "' in stock.\n");
}

/*
 * Function name: shop_hook_buy_cant_pay
 * Description:   Called when player can't pay for what he wants to buy.
 *		  The /lib/trade.c sets some default error messages but
 *		  perhaps you are not happy with them?
 * Arguments:	  ob - The object
 *		  arr - The error code as it comes from trade.c
 */
void
shop_hook_buy_cant_pay(object ob, int *arr)
{
    TO->command("say Please!  You obviously can't even afford the "+ob->short()+".");

}

/*
 * Function name: do_buy
 * Description:   Try to let the player buy an item
 * Arguments:     string - describing how to pay and get change
 * Returns:       1 on sucess
 */
int
do_buy(string str)
{
    if (!str || str =="")
    {
	    TO->command("say What would you like to buy?  "+
            "Perhaps you want to see a 'list' of my wares?");
        NF("");
	    return 0;
    }

    return ::do_buy(str);
}

void
init_living()
{
    ::init_living();
    add_action(do_buy,   "buy");
    add_action(do_show,  "show");
    add_action(do_list,  "list");
    //add_action(do_read,  "read");
    add_action(do_store, "store");
}
