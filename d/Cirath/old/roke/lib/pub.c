/*
 * Support for selling food, drinks and other articles
 */
#pragma strict_types

inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <language.h>
#include <composite.h>
#include <filter_funs.h>
#include <cmdparse.h>

static	mixed	drinks;	/* Array holding all drink data */
static	mixed	dr_id;	/* Array holding all names the drinks can be identified
			 * with when bought */
static	mixed	food;
static	mixed	fo_id;
static	mixed	articles;
static	mixed	art_id;
static  object  buyer;

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */
#define MAX_PURCHASED 20

/*  Prototypes  */
int order(string str);
int drinks_on_me(string str);

/*
 * Function name: config_pub
 * Description:   Configure the pub.
 *		  Call it from your create_xxx()
 */
void
config_pub()
{
    config_default_trade();  /* Set up the trading system */
}

/*
 * Function name: init_pub
 * Description:   This function adds the buy and order command to this_player()
 *		  call it from your init()
 */
void
init_pub()
{
    add_action(order, "buy");
    add_action(order, "order");
    add_action(drinks_on_me, "drinks");
}

/*
 * Function name: fix_drink
 * Description:   Set up a drink and return the object
 * Arguments:	  data - The drink data from the drinks array
 * Returns:	  The configured drink object
 */
object
fix_drink(mixed data)
{
    object ob;

    seteuid(getuid(this_object()));
    ob = clone_object("/std/drink");
    ob->set_name(data[0]);
    ob->set_adj(data[1]);
    ob->set_soft_amount(data[2]);
    ob->set_alco_amount(data[3]);
    ob->set_short(data[5]);
    ob->set_pshort(data[6]);
    ob->set_long(data[7]);
    ob->add_prop(HEAP_I_UNIT_VOLUME, data[2] + data[3]);
    ob->add_prop(HEAP_I_UNIT_WEIGHT, data[2] + data[3]);
    ob->add_prop(HEAP_I_UNIT_VALUE, data[4]);

    return ob;
}

/*
 * Function name: fix_food
 * Description:   Configure the food object and return it
 * Arguments:	  data - The data for the food
 * Returns:	  The food object
 */
object
fix_food(mixed data)
{
    object ob;

    seteuid(getuid(this_object()));
    ob = clone_object("/std/food");
    ob->set_name(data[0]);
    ob->set_adj(data[1]);
    ob->set_amount(data[2]);
    ob->set_short(data[4]);
    ob->set_pshort(data[5]);
    ob->set_long(data[6]);
    ob->add_prop(HEAP_I_UNIT_VOLUME, data[2]);
    ob->add_prop(HEAP_I_UNIT_WEIGHT, data[2]);
    ob->add_prop(HEAP_I_UNIT_VALUE, data[3]);

    return ob;
}

/*
 * Function name: fix_article
 * Description:   Clone the object and return it
 * Arguments:	  data - The data for the article
 * Returns:	  The object
 */
object
fix_article(mixed data)
{
    object ob;
    int t;

    seteuid(getuid(this_object()));
    catch(ob = clone_object(data[0])); //FIXA

    return ob;
}

/*
 * Function name: pub_std_usage_string
 * Description:   Get a string describing how to use the pub.
 *                This can be attached to a menu.
 * Returns:       The description string.
 */
string
pub_std_usage_string()
{
    return
        "Use 'buy <item>' or 'order <item>' to order something.\n" +
        "You can also do 'buy <num> <items>'. You can't buy more than " + 
        MAX_PURCHASED + " at a time.\n" +
        "Try 'buy <item> with <cointype>' if you want to specify what to " +
        "pay with, or 'buy <item> with <cointype> and get <cointype>' to " +
        "specify the kind of change you want.\n" +
        "You may order for other players as well as order for " +
        "multiple players.\n" +
        "Try using 'order <num> <item> for <players>' similar to how you " +
        "target players with an emotion.\n" +
        "You may also 'order <num> <item> for team' to buy things for " +
        "teammates.\n" +
        "Use 'drinks on me' to be generous, and 'drinks off me' to be " +
        "cheap.\n";
}

/*
 * Function name: pub_hook_cant_pay
 * Description:   A hook to redefine if you want own message when player can't 
 *		  pay the price.
 * Arguments:     price - The price he should have payed
 */
void
pub_hook_cant_pay(int price)
{
    write("You haven't got enough money to pay the price.\n");
}

/*
 * Function name: pub_hook_cant_carry
 * Description:   A hook to redefine if you want own message when player can't
 *		  carry what was ordered.
 * Arguments:     ob     - The object he couldn't carry
 *                player - The player who couldn't carry
 */
void
pub_hook_cant_carry(object ob, object player)
{
    player->catch_msg(capitalize(ob->short()) + 
        " is too heavy for you. You drop it to the ground.\n");
    tell_room(environment(player),
        capitalize(ob->short()) + " is too heavy for " + QTNAME(player) +
        " and falls to the ground.\n", ({player}));
}

/*
 * Function name: pub_hook_no_player
 * Description  : Tells the player that we can't fin who is buying for.
 * Arguments    : name : The player we were trying to buy for
 */
void
pub_hook_no_player(string name)
{
    write(capitalize(name)+" is not around for you to buy for.\n");
}

/*
 * Function name: pub_hook_player_buys
 * Description:   A hook to redefine if you want own message when player
 *                gets his/hers order.
 * Arguments:     ob - The object player ordered
 *                price - The price the player payed for the object
 *                players - The player(s) recieving the order
 *                buyer   - The player paying the bill
 *                pay     - The coins payed.
 *                change  - The coins got in change.
 */
void
pub_hook_player_buys(object ob, int price, object *players, object buyer, 
                     string pay, mixed change)
{
    string comp_names;
    object env, tmp;
    int yourself, payself;

    env = this_object();
    while (objectp(tmp = environment(env)) && !env->query_prop(ROOM_I_IS))
        env = tmp;

    if (!objectp(buyer))
        buyer = this_player();

    yourself = member_array(this_player(), players) != -1;
    payself = buyer == this_player();

    if (yourself && sizeof(players) == 1)
    {
        if (payself)
            write("You pay " + pay + " and order yourself " + 
                ob->short() + ".\n");
        else
            this_player()->catch_msg("You order yourself " + ob->short() +
                " that " + QCTNAME(buyer) + " pays for.\n");

        say(QCTNAME(this_player()) + " orders " +
            this_player()->query_objective() + "self " + ob->short() + ".\n");
        if (!payself)
            buyer->catch_msg("You pay " + pay + ".\n");
        if (stringp(change))
            buyer->catch_msg("You get " + change + " back.\n");
        return;
    }

    comp_names = COMPOSITE_LIVE(players - ({this_player()}));

    if (payself)
    {
        write("You pay " + pay + " and order " + ob->short() + " for " + 
            comp_names + (yourself ? " as well as for yourself" : "") + ".\n");
        (players - ({buyer}))->catch_msg(QTNAME(buyer) + " buys you " +
            ob->short() + ".\n");
        tell_room(env, QCTNAME(buyer) + " orders " + ob->short() +
            " for " + QCOMPLIVE +
            (yourself ?
                " as well as for " + buyer->query_objective() + "self" : "") +
            ".\n", players + ({buyer}));
    }
    else
    {
        write("You order " + ob->short() + " for " + comp_names + 
            (yourself ? " as well as for yourself" : "") + ".\n");

        (players - ({this_player()}))->catch_msg(QTNAME(this_player()) +
            " orders " + ob->short() + " for you.\n");
        tell_room(env, QCTNAME(this_player()) + " orders " +
            ob->short() + " for " + QCOMPLIVE +
            (yourself ? " as well as for " +
                this_player()->query_objective() + "self" : "") +
            ".\n", players + ({this_player()}));
        buyer->catch_msg("You pay " + pay + ".\n");
    }
    if (stringp(change))
        buyer->catch_msg("You get " + change + " back.\n");
}

/*
 * Function name: pub_hook_ordered_too_many
 * Description  : Tells the player that he ordered too many items.
 * Arguments    : int num - the amount the player ordered.
 * Returns      : int 0/1 - 0 for a notify_fail, 1 for a write.
 */
int
pub_hook_ordered_too_many(int num)
{
    notify_fail("You cannot buy more than " + MAX_PURCHASED +
        " meals or drinks at a time.\n");
    return 0;
}

/*
 * Function name: pub_hook_invalid_order
 * Description:   Notify the player that the ordered item is not in stock.
 * Arguments:     string str - the item the player tried to order
 * Returns:       1/0
 */
int
pub_hook_invalid_order(string str)
{
    notify_fail("No " + str + " in stock.\n");
    return 0;
}

/*
 * Function name: pub_hook_syntax_failure
 * Description:   Notify the player of invalid syntax.
 * Arguments:     string str - arguments to the command
 * Returns:       1/0
 */
int
pub_hook_syntax_failure(string str)
{
    notify_fail(capitalize(query_verb()) + " what?\n");
    return 0;
}

/*
 * Function name: pub_hook_drinks_on_me
 * Description  : The player pays for all drinks.
 */
void
pub_hook_drinks_on_me()
{
    write("You shout: Drinks are on me!\n");
    say(QCTNAME(this_player()) + " shouts: Drinks are on me!\n");
}

/*
 * Function name: pub_hook_drinks_off_me
 * Description  : The player don't want to pay for all drinks anymore.
 */
void
pub_hook_drinks_off_me()
{
    write("You shout: No more drinks on me!\n");
    say(QCTNAME(this_player()) + " shouts: No more drinks on me!\n");
}

/*
 * Function name: pub_hook_buyer_cant_pay
 * Description:   Notify that the generous buyer is out of money.
 * Arguments:     buyer - the one who can't pay
 */
void
pub_hook_buyer_cant_pay(object buyer)
{
    tell_room(environment(this_player()), QCTNAME(buyer) +
        " is out of money! No more drinks on " +
        buyer->query_objective() + "!\n");
}

/*
 * Function name: pub_hook_may_order
 * Description:   Check if the player may order.
 *                If not, set notify_fail.
 * Returns:       1/0
 */
int
pub_hook_may_order()
{
    return 1;
}

/*
 * Function name: get_order
 * Description:   gets the object the player ordered and returns it and
 *                the price of that object back to the order function.
 * Arguments:     order_name - what the player attempted to order.
 * Returns:       mixed array of 2 elements.
 *                [0]  order - The object the player ordered.
 *                [1]  price - What the object costs.
 */
mixed *
get_order(string order_name)
{
    object order;
    int price, i;

    for (i = 0; i < sizeof(dr_id); i++)
	if (member_array(order_name, dr_id[i]) >= 0)
	{
	    order = fix_drink(drinks[i]);
	    price = drinks[i][4];
            return ({order, price});
	}

    for (i = 0; i < sizeof(fo_id); i++)
        if (member_array(order_name, fo_id[i]) >= 0)
        {
            order = fix_food(food[i]);
            price = food[i][3];
            return ({order, price});
        }

    for (i = 0; i < sizeof(art_id); i++)
        if (member_array(order_name, art_id[i]) >= 0)
        {
            order = fix_article(articles[i]);
            price = articles[i][1];
            return ({order, price});
        }

    return ({0, 0});
}

/*
 * Function name: drinks_on_me
 * Description:   The player want to pay for all drinks.
 * Arguments:	  str - The order from the player
 * Returns:	  1 or 0
 */
int
drinks_on_me(string str)
{
    if (!str || (str != "on me" && str != "off me"))
    {
        notify_fail("Do you mean 'drinks on me' or 'drinks off me'?\n");
        return 0;
    }

    if (str == "off me")
    {
        if (buyer != this_player())
        {
            write("The drinks are not on you!\n");
            return 1;
        }
        buyer = 0;
        pub_hook_drinks_off_me();
        return 1;
    }
    
    if (objectp(buyer) && present(buyer, environment(this_player())))
    {
        if (buyer == this_player())
            write("You are already paying for the drinks!\n");
        else
            this_player()->catch_msg(QCTNAME(buyer) + " is already paying " +
                "for the drinks!\n");
        return 1;
    }

    buyer = this_player();
    pub_hook_drinks_on_me();
    return 1;
}

/*
 * Function name: order
 * Description:   The player has ordered something, let's see if we can satisfy
 *		  him.
 * Arguments:	  str - The order from the player
 * Returns:	  1 or 0
 */
int
order(string str)
{
    string player_name, item_name, coin_pay_text, coin_get_text;
    string *words, with, back, tmpstr;
    int num, tmp, i, price, *money_arr, payed;
    object order, *all, *players, env;
    mixed *temp;

    if (!str)
        return pub_hook_syntax_failure(str);
    
    if (!pub_hook_may_order())
        return 0;
    
    if (sscanf(str, "%s with %s for %s", item_name, with, player_name) == 3)
        ;
    else if (sscanf(str, "%s for %s with %s", item_name, player_name, with) ==
        3)
        ;
    else if (sscanf(str, "%s for %s", item_name, player_name) == 2)
        with = "";
    else if (sscanf(str, "%s with %s", item_name, with) == 2)
        player_name = this_player()->query_real_name();
    else
    {
        player_name = this_player()->query_real_name();
        item_name = str;
        with = "";
    }

    /* Detect any number before the item */
    words = explode(item_name, " ");
    num = 1;
    if (sizeof(words) > 1)
    {
	tmp = LANG_NUMW(words[0]);
	if (!tmp)
	    sscanf(words[0], "%d", tmp);
	if (tmp > 0)
	{
	    num = tmp;
	    item_name = implode(words[1 .. sizeof(words)], " ");
	}
    }

    if (num > MAX_PURCHASED)
    {
	return pub_hook_ordered_too_many(num);
    }

    /* Locate the surrounding room */
    env = this_object();
    while (objectp(order = environment(env)) && !env->query_prop(ROOM_I_IS))
        env = order;

    all = FIND_STR_IN_OBJECT(player_name, env);
    players = FILTER_PLAYERS(all);

    if (!sizeof(players))
    {
        /* Allow specifically named npc:s */
        if (sizeof(all) == 1 && all[0]->query_npc())
        {
            players = all;
        }
	else if (player_name == "team" || player_name == "teammates")
	{
	    players = this_player()->query_team_others() + ({this_player()});
	    players = FILTER_PRESENT_LIVE(players);
	}
	else
	{
	    pub_hook_no_player(player_name);
	    return 1;
	}
    }

    back = "";
    if (with != "")
    {
        if (sscanf(with, "%s and get %s", tmpstr, back) == 2)
            with = tmpstr;
    }

    temp = get_order(item_name);
    order = temp[0];
    price = temp[1];

    if (!order)
    {
        /* Try to detect plural. */
        if (num > 1 && extract(item_name, -1) == "s")
        {
            tmpstr = extract(item_name, 0, -2);
            temp = get_order(tmpstr);
            order = temp[0];
            if (!order)
                return pub_hook_invalid_order(item_name);
            price = temp[1];
            item_name = tmpstr;
        }
        else
            return pub_hook_invalid_order(item_name);
    }

    if (!order->query_prop(HEAP_I_IS) && num != 1)
    {
	write("You are only able to buy one of " + LANG_THESHORT(order)+
            " at a time.\n");
	/* Clean up the object we've cloned. */
	order->remove_object();
	return 1;
    }
    else
	order->set_heap_size(num);

    price = price * num * sizeof(players);

    /* Are there anyone else paying for drinks? */
    payed = 0;
    if (objectp(buyer) && buyer != this_player() &&
        function_exists("create_drink", order))
    {
        if (present(buyer, environment(this_player())))
        {
            money_arr = pay(price, buyer);
            if (sizeof(money_arr) == 1)
            {
                pub_hook_buyer_cant_pay(buyer);
                buyer = 0;
                order->remove_object();
                return 1;
            }
            payed = 1;
            coin_pay_text = text(exclude_array(money_arr, NUM, NUM * 2 - 1));
            coin_get_text = text(exclude_array(money_arr, 0, NUM - 1));     
            pub_hook_player_buys(order, price, players, buyer, 
                coin_pay_text, coin_get_text);
        }
        else
            buyer = 0;
    }

    if (!payed)
    {
        money_arr = pay(price, this_player(), with, 0, 0, back);
        if (sizeof(money_arr) == 1)
        {
            pub_hook_cant_pay(price);
            order->remove_object();
            return 1;
        }
        coin_pay_text = text(exclude_array(money_arr, NUM, NUM * 2 - 1));
        coin_get_text = text(exclude_array(money_arr, 0, NUM - 1));     
        pub_hook_player_buys(order, price, players, this_player(),
            coin_pay_text, coin_get_text);
    }

    if (order->move(players[0]))
    {
        pub_hook_cant_carry(order, players[0]);
        order->move(environment(players[0]));
    }
    for (i = 1; i < sizeof(players); i++)
    {
	order = get_order(item_name)[0];
	if (num > 1 && order->query_prop(HEAP_I_IS))
	    order->set_heap_size(num);
	if (order->move(players[i]))
	{
	    pub_hook_cant_carry(order, players[i]);
            order->move(environment(players[i]));
	}
    }
    return 1;   
}

/*
 * Function name: add_drink
 * Description:   Add a drink to the menu list
 * Arguments:	  id	    - An array with names to id the drink when buying
 *		  names     - The names of the drink
 *		  adj	    - The adjectives of the drink
 * 		  soft	    - The soft amount (integer)
 *		  alco	    - The alcoholic amount (integer)
 * 		  price	    - The price of the drink (cost to buy)
 *		  short	    - Short description of the drink (if special)
 *		  pshort    - A plural short description
 *		  long	    - Long description of the drink
 *                dummy     - Obsolete, kept for backward compability
 */
varargs void
add_drink(mixed id, mixed names, mixed adj, int soft, int alco, int price,
	  string short, string pshort, string long, mixed dummy)
{
    if (!pointerp(id))
	id = ({ id });
    if (!pointerp(names))
	names = ({ names });
    if (!pointerp(adj))
	adj = ({ adj });
    if (!drinks)
	drinks = ({ });
    if (!dr_id)
	dr_id = ({ });

    dr_id += ({ id });
    drinks += ({ ({ names, adj, soft, alco, price, short,
                    pshort, long }) });
}

/*
 * Function name: query_drinks
 * Description:   Query the drink array
 * Returns:	  The drink array
 */
mixed
query_drinks() { return drinks; }

/*
 * Function name: query_drink_id
 * Description:   Query the drink id:s
 * Returns:	  The array holding all drink id:s
 */
mixed
query_drink_id() { return dr_id; }

/*
 * Function name: remove_drink
 * Description:   Remove a special drink, identified with id
 * Arguments:	  id - A identifying string
 * Returns:	  1 if removed
 */
int
remove_drink(string id)
{
    int i;

    for (i = 0; i < sizeof(dr_id); i++)
	if (member_array(id, dr_id[i]) >= 0)
	{
	    dr_id = exclude_array(dr_id, i, i);
	    drinks = exclude_array(drinks, i, i);
	    return 1;
	}

    return 0;
}

/*
 * Function name: add_food
 * Description:   Add an item of food  to the menu list
 * Arguments:     id        - An array with names to id the food when buying
 *                names     - The names of the food
 *                adj       - The adjectives of the food
 *                amount    - The amount (integer)
 *                price     - The price of the food (cost to buy)
 *                short     - Short description of the food (if special)
 *		  pshort    - The plural short description (if special)
 *                long      - Long description of the food
 *                dummy     - Obsolete, kept for backward compability
 */
varargs void
add_food(mixed id, mixed names, mixed adj, int amount, int price,
         string short, string pshort, string long, mixed dummy)
{
    if (!pointerp(id))
        id = ({ id });
    if (!pointerp(names))
        names = ({ names });
    if (!pointerp(adj))
        adj = ({ adj });
    if (!food)
        food = ({ });
    if (!fo_id)
        fo_id = ({ });

    fo_id += ({ id });
    food += ({ ({ names, adj, amount, price, short, pshort, long }) });
}

/*
 * Function name: query_food
 * Description:   Query the food array
 * Returns:       The food array
 */
mixed
query_food() { return food; }

/*
 * Function name: query_food_id
 * Description:   Query the food id:s
 * Returns:       The array holding all food id:s
 */
mixed
query_food_id() { return fo_id; }

/*
 * Function name: remove_food
 * Description:   Remove a special food, identified with id
 * Arguments:     id - A identifying string
 * Returns:       1 if removed
 */
int
remove_food(string id)
{
    int i;

    for (i = 0; i < sizeof(fo_id); i++)
        if (member_array(id, fo_id[i]) >= 0)
        {
            fo_id = exclude_array(fo_id, i, i);
            food = exclude_array(food, i, i);
            return 1;
        }

    return 0;
}

/*
 * Function name: add_article
 * Description:   Add an item to the menu list
 * Arguments:     id        - An array with names to id the item when buying
 *                file      - The path to the object file
 *                price     - The price of the item (cost to buy)
 */
void
add_article(mixed id, string path, int price)
{
    if (!pointerp(id))
        id = ({ id });
    if (!articles)
        articles = ({ });
    if (!art_id)
        art_id = ({ });

    art_id += ({ id });
    articles += ({ ({ path, price }) });
}

/*
 * Function name: query_articles
 * Description:   Query the articles array
 * Returns:       The articles array
 */
mixed
query_articles() { return articles; }

/*
 * Function name: query_articles_id
 * Description:   Query the articles id:s
 * Returns:       The array holding all articles id:s
 */
mixed
query_articles_id() { return art_id; }

/*
 * Function name: remove_article
 * Description:   Remove an article, identified with id
 * Arguments:     id - A identifying string
 * Returns:       1 if removed
 */
int
remove_article(string id)
{
    int i;

    for (i = 0; i < sizeof(art_id); i++)
        if (member_array(id, art_id[i]) >= 0)
        {
            art_id = exclude_array(art_id, i, i);
            articles = exclude_array(articles, i, i);
            return 1;
        }
    return 0;
}
