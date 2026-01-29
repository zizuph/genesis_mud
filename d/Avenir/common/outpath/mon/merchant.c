#pragma strict_types
// -*-C++-*-
// file name:    ~Avenir/common/outpath/mon/merchant.c
// creator(s):    Boriska, 
// /d/Genesis/doc/examples/trade/merchant.c (C) January 7th 1994 by Mercade
// purpose:       mobile shop for Avenir tunnels
// note:          Merchant's storeroom has a convinence function for wizards to
//                determine where he is.
/*
 * Revision:
 *     Cirion, May 1996: Updated for use in the Outpath area
 *     Lilith, Feb 2014: Minor updates to restrict_path, etc
 *     Lucius, Jul 2017: Code cleanups
 *
 */
inherit "/std/monster";
inherit "/lib/shop";

#include "../outpath.h"
#include <money.h>

#define STORE		(OUTPATH + "store")
#define BEARER		(MON + "bearer")
#define MERCHANT	(MON + "merchant")
#define MAX_STORE	30
#define SELL_PERIOD	1500.0
#define BEARER_ABSENCE	60.0

public static object bearer, store;

void
create_monster() 
{
    if (!IS_CLONE)
	return;

    setuid();
    seteuid(getuid());

    set_name("potso");
    add_name(({"gnome","merchant"}));
    set_race_name("gnome merchant");
    set_adj("stout");
    set_long("This stout little fellow seems to be a merchant of sorts.\n");

    set_gender(G_MALE);

    set_stats(({ 50,50,50,50,50,50 }));

    set_skill(SS_DEFENCE,      180);
    set_skill(SS_AWARENESS,    100);
    set_skill(SS_UNARM_COMBAT, 100);

    add_prop(LIVE_I_SEE_DARK, 1);

    set_random_move(120, 1);
    set_monster_home(OUTPATH +"n1");
    set_restrain_path(({ OUTPATH,
	"/d/Avenir/common/port", "/d/Avenir/common/ledge" }));

    set_act_time(30);
    add_act("say GoblinsSureMakeGoodCarriers.");
    add_act("say BoyAreGoblinsEverDumb.NiceThough.ButDumb.");
    add_act("@@storechat@@");

    config_default_trade();
    set_money_give_max(5000);

    set_store_room(STORE);
    STORE->set_merchant(this_object());
    store = get_store_object();

    set_alarm(2.0, 0.0, "make_bearer");
}

string
storechat()
{
    string name;
    object *stuff, thing;

    if (!objectp(store) || !sizeof(stuff = all_inventory(store)))
	return "";

    thing = one_of_list(stuff);
    name = thing->query_short();
    name = capitalize(implode(explode(name, " "), ""));

    return "say IHaveAVeryNice"+name+"ForSaleWhouldYouLikeToBuyIt?";
}

private void
make_bearer()
{
    bearer = clone_object(BEARER);
    bearer->move_living("away", environment());
    bearer->set_merchant(TO);
    command("pat lucky");
    team_join(bearer); 
}

void
init_living()
{
    ::init_living();
    init_shop();
}

/*
 * Function name: shop_hook_sold_items
 * Description:   Hook that is called when player sold something
 * Arguments:	  item - The item array player sold
 * Returns:	  1
 */
int
shop_hook_sold_items(object *item)
{
    write(break_string("You sold " + COMPOSITE_DEAD(item) + ".\n", 75));
    say(QCTNAME(this_player()) + " sold " + QCOMPDEAD + ".\n");
    bearer->command("emote grunts sadly.");
    command("comfort lucky");
    return 1;
}

/*
 * Function name: shop_hook_bought_items
 * Description:   Called when player has bought something
 * Arguments:	  arr - The array of objects
 * Returns: 	  1
 */
int
shop_hook_bought_items(object *arr)
{
    tell_room(environment(), QCTNAME(this_object()) +
      " unloads " +
      (sizeof(arr) <= 1 ? "something" : "some things")+
      " from "+QTNAME(bearer)+".\n");
    write("You bought " + COMPOSITE_DEAD(arr) + ".\n");
    say(QCTNAME(this_player()) + " bought " + QCOMPDEAD + ".\n");
    bearer->command("smile stupid");
    return 1;
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
    bearer->command("shrug");
    notify_fail("Sorry, I have no '" + str + "' you are talking about.\n");
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
    tell_room (environment(), QCTNAME(TO)+" checks his packs but comes up with " +
      "empty hands.\n");
    bearer->command ("shrug");
    notify_fail("");
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
    tell_room (environment(), QCTNAME(TO)+" checks his packs looking for " + str +
      " but comes up with empty hands.\n");
    bearer->command("shrug");
    notify_fail(""); // just say nothing.
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

/*
 * Function name: shop_hook_allow_sell
 * Description:	  If you want to do more testing on objects the player intend
 *		  to sell.
 * Argument:	  ob - The object player wants to sell
 * Returns:	  1 if we allow player to sell the object (default)
 */
int
shop_hook_allow_sell(object ob)
{
    if (bearer->query_no_show() || !present(bearer, environment()))
    {
	notify_fail ("My bearer is gone, I cannot buy anything.\n");
	return 0;
    }

    if (!objectp(store) || sizeof(all_inventory(store)) >= MAX_STORE)
    {
	notify_fail ("Sorry, my bearer cannot carry more. Come back later.\n");
	return 0;
    }

    return 1;
}

void
do_die(object killer)
{
    bearer->run_away();
    store->set_merchant(0);
    // remember the fact of merchant's death so
    // it will be cloned when his start room resets.
    ::do_die(killer);
}

private void
gone()
{
    store->set_merchant(0);

    command("frown");
    command("say My bearer is gone, there is nothing for me to do here.");
    command("say Go and find another fool to trade with you.");

    run_away();
    remove_object();
}

// called from do_die() in bearer.
void
bearer_died()
{
    set_alarm(6.0, 0.0, gone);
}

