/*
  This merchant will act like a shop; selling stuff in his inventory.
  There should be *good* buyer-seller interfaces.

  Usage :
  Inherit this file as a normal /std/monster, set up the normal
  living parameters in create_merchant().

  For defining the merchant, you define functions rather than set
  variables;

  status accept_object(object ob) ; Return true if the merchant buys it.
  object query_storage()          ; Return object to keep stuff in.
                                  ; Default is the inventory of the merchant.

  The merchant keeps his money on his person. He can pay no more for an
  item than he owns. This function decides the max. value he keeps.

  int    maximum_wealth()         ; Return maximum wealth in CC. Def: 10000.

*/

#include "macros.h"
#include "stdproperties.h"
#include "language.h"
#include "composite.h"
#include "money.h"

#include "../gnome.h"

#pragma save_binary

inherit  LIB;
inherit  TRANSACT;
inherit  "/std/monster";

#include "citizen.c"

int     wealth,
        tot_price;
mapping deal_stuff,
        last_list;

/*
  Mudlib functions.
*/

void create_merchant() { ::create_monster(); set_name("merchant"); }
void reset_merchant()  { ::reset_monster(); }

nomask void
create_monster() {
    deal_stuff = ([ ]);
    last_list  = ([ ]);
    create_merchant();
}

nomask void reset_monster()  { reset_merchant();  }

init_living() {
    add_action("show", "show");
    add_action("list", "list");
    add_action("buy", "buy");
    add_action("sell", "sell");
    add_action("confirm", "confirm");
    add_action("value", "value");
}

/*
  These two remove items in the mappings.
*/

void
remove_deal_stuff(string name) {
    m_delete(deal_stuff, name);
}

void
remove_last_list(string name) {
    m_delete(last_list, name);
}

/*
  fish_out() extracts the proper array of objects from a mixed array
  returned by parse_command()
*/

object *
fish_out(mixed *parse_arr) {
    if (parse_arr[0] < 0) {
	if (-parse_arr[0] < sizeof(parse_arr)) {
	    parse_arr = ({ parse_arr[-parse_arr[0]] });
	} else {
	    parse_arr = ({ });
	}
    } else if (parse_arr[0] > 0) {
	parse_arr = parse_arr[1 .. parse_arr[0]];
    } else {
	parse_arr = parse_arr[1 .. 1000];
    }
    return parse_arr;
}

/*
  Code for merchant-queries.
*/

status
accept_object(object ob) { return 1; }

string
is_sellable(object ob) {
    return
      (ob->short() &&
       !function_exists("create_heap", ob) &&
       ob->query_prop(OBJ_I_VALUE) &&
       !ob->query_prop(OBJ_I_NO_GET));
}

int
query_wealth() {
    return merge_values(what_coins(this_object()));
}

object
query_storage() {
    return this_object();
}

int
maximum_wealth() {
    return 10000;
}

/*
  The code for LIST.
*/

void
do_list(object *things) {
    filter(things, "show_it", this_object());
}

varargs status
list(string str) {
    mixed *inv;
    string foo, bar, extra;
    string name;

    if (!str || str == "") {
	str = "all";
    }
    if (sscanf(str, "%sexpensive %s", foo, bar)) {
	str = foo + bar;
	extra = "e";
    }
    if (sscanf(str, "%scheap %s", foo, bar)) {
	str = foo + bar;
	extra = "c";
    }
    if (!str || str == "") {
	str = "all";
    }

    if (parse_command(str, deep_inventory(query_storage()), "%i", inv)) {

	inv = fish_out(inv);

	/*
	 * Remove silly things.
	 */

	inv = filter(inv, "is_sellable", this_object());
    }
    if (!inv || !sizeof(inv)) {
	M_Tell("I don't think I know what you want to see.\n");
	return 1;
    }

    if (extra == "e" || extra == "c") {
	object *tmp;
	int     mean_value;
	/*
	 * This slightly obnoxious code is to ensure that 'second'
	 * etc access the correct object.
	 */
	tmp = sort_array(inv, "sort_condition", this_object());
	mean_value = (int)tmp[sizeof(tmp)/2]->query_prop(OBJ_I_VALUE);
	if (extra == "e") {
	    tmp = filter(tmp, "high_value", this_object(), mean_value); 
	    inv = inv[0 .. sizeof(tmp)/2];
	} else {
	    tmp = filter(tmp, "low_value", this_object(), mean_value); 
	    inv = inv[0 .. sizeof(tmp)/2];
	}
    }
    /*
     * The player has been shown a list - this is saved, because
     * a buy must be relative to the last list seen!
     * Once again *hug marvin* for those mappings.
     */

    name = (string)this_player()->query_real_name();
    last_list[name] = inv;
    call_out("remove_last_list", 600, name);

    M_Tell("This may interest you :\n");
    say(QCTNAME(this_player()) + " looks for something to buy.\n");
    do_list(inv);
    if (sizeof(inv) > 20) {
	M_Tell("That was a lot of stuff. If you want to see a smaller "+
	       "portion of it, try asking me for more specific things, "+
	       "or use 'cheap'/'expensive'.\n");
    }
    return 1;
}

status
high_value(object ob, int value) {
    return (int)ob->query_prop(OBJ_I_VALUE) >= value;
}

status
low_value(object ob, int value) {
    return (int)ob->query_prop(OBJ_I_VALUE) <= value;
}

status
sort_condition(object ob1, object ob2) {
    return ( (int)ob1->query_prop(OBJ_I_VALUE) <
	     (int)ob2->query_prop(OBJ_I_VALUE) );
}

/*
  The code for SHOW.
*/

void
show_it(object ob) {
    write (sprintf("%20s : %6d cc.\n",
		   capitalize(LANG_ADDART((string)ob->short())),
		   ob->query_prop(OBJ_I_VALUE)));
}

status
show(string what) {
    object  show_ob;
    mixed  *ob_list, *tmp;
    int i, price, *result;
    string change;

    if (!what) {
	return list();
    }

    if (parse_command(what, deep_inventory(query_storage()), "%i", ob_list)) {

	if (tmp = last_list[(string)this_player()->query_real_name()]) {
	    ob_list = ({ ob_list[0] }) + (ob_list - (ob_list - tmp));
	}
	ob_list = fish_out(ob_list);
	if (sizeof(ob_list)) {
	    show_ob = ob_list[0];
	}
    }
    if (!show_ob) {
	M_Tell("I have no such thing to show you.\n");
	return 1;
    }

    price = (int)show_ob->query_prop(OBJ_I_VALUE);

    result = transact(price, this_player(), this_object(), -1, 1);

    M_Emote("shows you the " + show_ob->short() + " :\n");
    write(BS(show_ob->long() + "\n"));

    M_Tell("It is valued at " + price + " cc.\n");

    if (sizeof(result) == 1) {
	if (result[0] == 1) {
	    M_Tell("You wouldn't afford it!\n");
	} else if (result[0] == 2) {
	    M_Tell("I can't sell it, I have no change.\n");
	}
	return 1;
    }
    M_Tell("I want " + text(result[0 .. 3]) + "for it.\n");
    if (change = text(result[4 .. 7])) {
	M_Tell("I'd give you back " + change + " in change.\n");
    }
    return 1;
}

/*
  The code for BUY.
*/

status
buy(string what) {
    object  buy_ob;
    mixed  *ob_list, *tmp;
    string  change;
    int    *result;
    int     price, m_res;

    if (!what) {
	M_Tell("Buy what?\n");
	return 1;
    }

    /*
     * Okay, we are about to buy something. We have a list, ob_list,
     * which is the normal arr[0] identifier as well as all matching
     * objects but we may want to replace this with the last list
     * seen by the player - IF there is one.
     * OOOPS, no, it is not that easy... We must make a cut through
     * the last things listed and the things identified with the buy.
     */

    if (parse_command(what, deep_inventory(query_storage()), "%i", ob_list)) {

	if (tmp = last_list[(string)this_player()->query_real_name()]) {
	    ob_list = ({ ob_list[0] }) + (ob_list - (ob_list - tmp));
	    /*
	     * HELP! This is not happening.
	     */
	    m_delete(last_list, (string)this_player()->query_real_name());
	}

	/*
	 * Err, am I really writing this code?
	 */
	ob_list = fish_out(ob_list);
	if (sizeof(ob_list)) {
	    buy_ob = ob_list[0];
	}
    }
    if (!buy_ob) {
	M_Tell("I have no such thing to sell to you.\n");
	return 1;
    }

    price = (int)buy_ob->query_prop(OBJ_I_VALUE);

    m_res = (int)buy_ob->move(this_player());
    if (m_res) {
	M_Tell("You can't carry it!\n");
	return 1;
    }

    result = transact(price, this_player(), this_object(), -1);

    if (sizeof(result) == 1) {
	if (result[0] == 1) {
	    M_Tell("You cannot afford it!\n");
	} else if (result[0] == 2) {
	    M_Tell("I cannot pay back change on your coins.\n");
	}
	buy_ob->move(query_storage());
	return 1;
    }
    M_Tell("It's a deal!\n");
    write ("You give " + M_Keeper + " " + text(result[0 .. 3]) + ".\n");
    say(QCTNAME(this_player()) + " buys " +
	LANG_ADDART((string)buy_ob->short()) + ".\n");
    change = text(result[4 .. 7]);
    M_Emote("gives you the " + buy_ob->short() + ".\n");
    if (change) {
	M_Emote("gives you your change, " + change + ".\n");
    }
    wealth = query_wealth();
    if (wealth > maximum_wealth()) {
	int *res;
	/*
	 * Call a transact function to remove wealth.
	 * Dir < 0 because we want to keep change.
	 */
	tell_room(environment(this_object()),
		  BS(M_Keeper + " puts some of his money on the ground " +
		     "and snaps his fingers. They disappear in a flash " +
		     "and a cloud of sulphur smoke.\n"));

	res = transact(wealth - (maximum_wealth() / 2), this_object(), 0, -1);
	if (sizeof(res) == 1) {
	    write ("Error : ({ " + res[0] + " })\n");
	}
    }
    return 1;
}

/*
  The code for SELL.
*/

status
sell(string what) {
    object  ob;
    mixed  *stuff, *will_buy;
    string  name, change;
    int    *result;
    int     i;

    if (!what) {
	M_Tell("Sell what?\n");
	return 1;
    }
    if (!parse_command(what, deep_inventory(this_player()), "%i", stuff)) {
	M_Tell("You have no such things to sell.\n");
	return 1;
    }

    stuff = fish_out(stuff);

    /*
     * stuff must be rid of the fundamentally unsellable things.
     */

    stuff = filter(stuff, "is_sellable", this_object());

    if (!sizeof(stuff)) {
	M_Tell("What are you trying to sell?\n");
	return 1;
    }

    /*
     * stuff is the array of what the player wants to sell.
     * This must be filtered through accept_object() because
     * merchants may decide what they want to buy.
     */

    will_buy = filter(stuff, "accept_object", this_object());

    if (!sizeof(will_buy)) {
	M_Tell("I won't buy that.\n");
	return 1;
    }

    tot_price = 0;
    wealth = query_wealth();

    will_buy = filter(will_buy, "calc_sell", this_object());

    if (sizeof(will_buy) == sizeof(stuff)) {
	M_Tell("You wish to sell " + COMPOSITE_DEAD(stuff) + " - OK.\n");
    } else if (sizeof(will_buy)) {
	M_Tell("I will buy " + COMPOSITE_DEAD(will_buy) + " but not " +
	     COMPOSITE_DEAD(stuff - will_buy) + ".\n");
    } else {
	if (sizeof(stuff) == 1) {
	    M_Tell("I am afraid I can't afford it.\n");
	} else {
	    M_Tell("I am afraid I can't afford any of it.\n");
	}
	return 1;
    }

    result = transact(tot_price, this_object(), this_player(), 1, 1);

    if (sizeof(result) == 1) {
	if (result[0] == 1) {
	    M_Tell("I can't afford that.\n"); /* SHould not happen!! */
	} else if (result[0] == 2) {
	    M_Tell("I don't have the change.\n");
	}
	return 1;
    }

    M_Tell("I will pay you " + text(result[0 .. 3]) + ".\n");
    if (change = text(result[4 .. 7])) {
	M_Tell("You will give me change, " + change + ".\n");
    }

    M_Tell("Use 'confirm' to settle the deal.\n");
    say(QCTNAME(this_player()) + " strikes a deal.\n");
    name = (string)this_player()->query_real_name();
    deal_stuff[name] = will_buy;
    call_out("remove_deal_stuff", 600, name);
    return 1;
}

status
calc_sell(object ob) {
    int price;
    if (!ob->id("coin")) {
	price = (int)ob->query_prop(OBJ_I_VALUE);
	if (price + tot_price > wealth) {
	    return 0;
	} else {
	    tot_price += price;
	    return 1;
	}
    }
    return 0;
}

/*
  The code for CONFIRM.
*/

status
confirm() {
    object *stuff, *sold;
    int    *result;
    string name, sold_stuff, change;

    name = (string) this_player()->query_real_name();
    stuff = deal_stuff[name];
    if (!stuff) {
	M_Emote("frowns at you.\n");
	M_Tell("If we've made a deal, I have forgotten it.\n");
	return 1;
    }

    remove_deal_stuff(name);

    tot_price = 0;
    wealth = query_wealth();

    sold = filter(stuff, "do_sell", this_object());

    if (!sizeof(sold)) {
	M_Tell("I can't go through with this deal.\n");
	return 1;
    }

    result = transact(tot_price, this_object(), this_player(), -1);

    if (sizeof(result) == 1) {
	if (result[0] == 1) {
	    M_Tell("I can't afford that.\n"); /* Should not happen!! */
	} else if (result[0] == 2) {
	    M_Tell("I don't have the change for your coins.\n");
	}
	/*
	 * The transact failed - move the stuff back.
	 * The relay() function is like filter() but calls every object
	 * in the array, thus we achieve the desired effect.
	 */
	relay(sold, "move", this_object(), this_player());
	return 1;
    }

    sold_stuff = COMPOSITE_DEAD(sold);
    if (sizeof(stuff) == sizeof(sold)) {
	say(QCTNAME(this_player()) + " sells " + sold_stuff + ".\n");
	write (BS("You sell " + sold_stuff + ".\n"));
    } else {
	say(QCTNAME(this_player()) + " sells " + sold_stuff + ".\n");
	write (BS("You sell " + sold_stuff + ", but " + M_Keeper +
		  " won't buy " + COMPOSITE_DEAD(stuff - sold) + ".\n"));
    }

    M_Emote("gives you " + text(result[0 .. 3]) + ".\n");
    if (change = text(result[4 .. 7])) {
	write(BS("You return " + change + " to " +
		 query_objective() + ".\n"));
    }
    return 1;
}

status
do_sell(object ob) {
    int result, price;
    if (!ob || living_environment(ob) != this_player()) {
	return 0;
    }
    result = ob->move(query_storage());
    if (!result) {
	price = (int)ob->query_prop(OBJ_I_VALUE);
	if (price + tot_price <= wealth) {
	    tot_price += price;
	    return 1;
	}
    }
    return 0;
}