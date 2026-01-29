// /d/Avenir/common/lib/shop/std_shop
// revisions: Lilith 17Feb97
/*
 *  The standard shop of the domain Gondor
 *
 *  Features that differ from /d/Genesis/lib/shop:
 *  - Shopkeeper
 *  - Check for special items that are not bought
 *  - greed is set using VBFC discriminate()
 *
 *  Olorin, July 1994
 *
 *  Modification log: Adopted and Modified as standard Avenir shop
 *                         by Ilyian, May 1995 (by permission from Olorin
 *                         and Elessar.
 *                         Made reset call arm_me in the shopkeeper.
 *                         any armed shopkeeper should have an arm_me 
 *                         defined as arming routine. Glinda may-95.
 */
inherit "/std/room";
inherit "/d/Genesis/lib/shop";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Avenir/common/common.h"

#define MAXLIST 30
#define NUM 4
#define MONEY_TYPE ({ "cc", "sc", "gc", "pc" })
#define SHOP_TMP_WANT_NO_BUSINESS "_want_no_business"

/*
 * Prototypes
 */
void    reset_room();
string  exa_poster();

/*
 * Global variables
 */
object  keeper,
       *hated_race,
       *suspected_race,
       *favoured_race;
string *enemies = ({}),
        keeper_file,
       *no_sell_prop,
        shop_name;

void set_keeper_file(string str) { keeper_file = str; }
void set_shop_name(string str) { shop_name = str; }
void set_hated_race(object *ob) { hated_race = ob; }
void set_suspected_race(object *ob) { suspected_race = ob; }
void set_favoured_race(object *ob) { favoured_race = ob; }


void
set_no_sell_prop(mixed str)
{
    if (stringp(str))
        no_sell_prop = ({ str });
    else if (pointerp(str))
        no_sell_prop = str;
}

/*
 * Function name:   create_shop
 * Description:     Initialize the shop room
 */
void
create_shop()
{
    set_long("The standard shop of the domain Avenir.\n");
    set_short("A shop");
    set_store_room(COM + "lib/store");
    set_shop_name("Avenir's Standard Shop");
    set_keeper_file(COM + "bazaar/NPCS/shopkeeper.c");
    set_no_sell_prop("_Avenir_no_sell");
}

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
nomask void
create_room()
{
    config_default_trade();  /* Set up the trading system */

    set_money_give_max(1000);
    set_money_give_out(   ({ 10000,   700,  40,    1 }));
    set_money_give_reduce(({     0,     4,   3,    9 }));
    set_money_greed_sell("@@discriminate");
    set_money_greed_buy("@@discriminate");
    set_money_greed_change("@@discriminate");

    add_item(({"item","items"}), BSN(
        "There are far too much items lying around to pick one out of. You "
      + "should better take a look at the pricelist, to get an idea of what "
      + "usefull stuff you can buy here."));

    add_item(({"owner","store owner"}), BSN(
        "The owner of the store is watching you closely, so you do not get "
      + "the chance to steal anything. Besides that, he leaves you on your "
      + "own to check out the stuff that is lying around."));

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room
                       * Should probably put IN_IN in it too, but  
                       * we'll leave that to the individual shops */

    create_shop();

    add_item(({"sign", "poster","list","prices"}), exa_poster());
    add_cmd_item(({"sign", "poster","list","prices"}), "read", exa_poster());

    reset_room();
}

int
do_read(string str)
{
    return 0;
}

string
exa_poster()
{
    return "\n"
      + "Welcome to " + shop_name + "!\n"
      + "You can do the following here: \n"
      + "    buy <item>  for gold and get copper back\n"
      + "    buy <item>  for gold coins\n"
      + "    sell <item> for copper coins\n"
      + "    sell all  - will let you sell all items except for\n"
      + "                those worn, wielded, or made keepable.\n\n"
      + "    If you want a list of all of a certain item available\n"
      + "    in the store, the correct syntax is: 'list <item>'" 
      + "\n";
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    ::init();
    init_shop();
}

void
fix_keeper()
{
    keeper = clone_object(keeper_file);
    keeper->arm_me();
    keeper->move(TO);
}

void
reset_room()
{
    if(!objectp(keeper))
        fix_keeper();
}

mixed
check_keeper()
{
    object  enemy;
    if (keeper && present(keeper,TO))
    {
        if(enemy = keeper->query_attack())
        {
      if(enemy == TP)
     notify_fail("The shopkeeper is trying to kill you, so you cannot do that!\n");
          else
        NF("The shopkeeper is busy fighting, so you cannot do that!\n");
          return 0;
        }
        else
            return 1;
    }
    else
    {
        NF("There is no shopkeeper here, so you cannot do that!\n");
        return 0;
    }
}

int
do_buy(string args)
{
    if (check_keeper())
        return ::do_buy(args);
    return 0;
}

int
do_value(string args)
{
    if (check_keeper())
        return ::do_value(args);
    return 0;
}

int
do_sell(string args)
{
    if (check_keeper())
        return ::do_sell(args);
    return 0;
}

int
do_list(string args)
{
    if (check_keeper())
        return ::do_list(args);
    return 0;
}

int
shop_hook_sell_no_match(string str)
{
    NF("The shopkeeper says: You don't have any " + str + ".\n");
    return 0;
}

int
shop_hook_sold_nothing()
{
    if (!this_player()->query_prop(SHOP_TMP_WANT_NO_BUSINESS))
        NF("The shopkeeper says: You didn't have much to sell.\n");
    return 0;
}

void
shop_hook_sell_no_value(object ob)
{
    NF("The shopkeeper says: "+CAP(LANG_THESHORT(ob))+" is worthless "+
        "to me. Try somewhere else.\n");
}

void
shop_hook_sell_no_sell(object ob, string str)
{
    if (stringp(str))
        notify_fail(str);
    else
        NF("The shopkeeper says: I don't buy such items.\n");
}

void
shop_hook_sell_object_stuck(object ob, int err)
{
    NF("The shopkeeper says: It seems you are stuck with that.\n");
}

void
shop_hook_sell_get_money(string str)
{
    write("The shopkeeper gives you " + str + ".\n");
}

void
shop_hook_buy_no_match(string str)
{
    NF("The shopkeeper says: I have no " + str + " to sell.\n");
}

void
shop_hook_cant_carry(object ob, int err)
{
    NF("You drop the " + ob->short() + " on the floor.\n" +
       "The shopkeeper says: You can't carry more, I'm afraid.\n");
}

void
shop_hook_buy_magic_money(object ob)
{
    keeper->command("say You are carrying magic money my friend, " +
        "no deal!\n");
}

void
shop_hook_buy_pay_money(string str, string change)
{
    write("You give " + str + " to the shopkeeper.\n");
    if (change)
        write(CAP(PRONOUN(keeper)) + " gives you " + change + " back.\n");
}

void
shop_hook_value_not_interesting(object ob)
{
    if (!this_player()->query_prop(SHOP_TMP_WANT_NO_BUSINESS))
       notify_fail("The shopkeeper says: That item doesn't interest me.\n");
    else
     notify_fail("");
}

void
shop_hook_value_held(object ob, string text)
{
    keeper->command("say I could offer about " + text +
        " for your " + ob->short() + ".");
}

void
shop_hook_value_store(object ob, string text)
{
    keeper->command("say I value the " + ob->short() +
        " to " + text + ".");
}

void
shop_hook_value_asking(string str)
{
    say(QCTNAME(TP)+" asks "+QTNAME(keeper) +
        " about the value of the "+str+".\n");
}

int
shop_hook_value_no_match(string str)
{
    NF("The shopkeeper says: We hold no '" + str + "' in stock.\n");
}

void
shop_hook_list_empty_store(string str)
{
    NF("The shopkeeper says: We are currently sold out.\n");
}

int
shop_hook_list_no_match(string str)
{
    NF("The shopkeeper says: We have no '" + str + "' in stock.\n");
}

/* The idea for this routine is got from Padermud. --Randor
 */
mixed
neat_text(int *arr)
{
    int     i;
    string  temp;

    if (sizeof(arr) < NUM) /* invalid array */
        return;

    temp = "";
    for (i = NUM - 1; i >= 0; i--)
    {
        if (arr[i] > 0)
            temp += sprintf("%2d %2s ", arr[i], MONEY_TYPE[i]);
        else
            temp += "      ";
    }
    return temp;
}

void
shop_hook_list_object(object ob, int price)
{
    string  str,
            mess;
    mess = neat_text(split_values(price));
    if (!stringp(mess))
        mess = "That item wouldn't cost you much.\n";
    write(BSN(sprintf("%-35s %20s", capitalize(LANG_ASHORT(ob)), mess)));
}

void
remove_tmp_want_no_business(object pl)
{
    pl->remove_prop(SHOP_TMP_WANT_NO_BUSINESS);
}

/*
 * Function name:    shop_hook_filter_sell
 * Description:      Default filter function
 *                   Checks if player can sell item to shop
 *                   Default buys everything but weapons and armours
 * Argument:         object ob - the object to check
 * Returns:          The fail message or 1 if shop does not buy,
 *                   0 else
 */
mixed
shop_hook_filter_sell(object x)
{
    if (weapon_filter(x) || armour_filter(x))
        return "The shopkeeper says: I do not want your " + x->short() + "!\n" +
               "The shopkeeper says: I do not trade in weapons or armours!\n";
    else
        return 0;
}

void
shop_hook_stolen_item(object pl, object ob)
{
    keeper->command("say Where did you get this " +
        ob->short() + "?");
    keeper->command("glare " + pl->query_real_name());
    keeper->command("say You must have stolen it ... or worse!");
    keeper->command("say Leave before I call the guards!");
}

void
shop_hook_no_business(object pl)
{
    keeper->command("say I do not want your business, " +
        (pl->query_gender() ? "Lady" : "Mister") + "!");
    keeper->command("spit " + pl->query_real_name());
    keeper->command("say Leave before I call the guards!");
}

/*
 * Function name: shop_hook_allow_sell
 * Description:   If you want to do more testing on objects
 *                the player intend to sell.
 * Argument:      ob - The object player wants to sell
 * Returns:       1 if we allow player to sell the object (default)
 */
int
shop_hook_allow_sell(object ob)
{
    int     i;
    mixed   prop = 0,
            test,
            msg;
    object  pl = this_player();
    string  name = pl->query_name();


    if ((msg = shop_hook_filter_sell(ob)))
    {
        if (stringp(msg))
            notify_fail(msg);
        else
          notify_fail("The shopkeeper says: I do not want your " + ob->short() + "!\n");
        return 0;
    }

    NF("");
    if (member_array(name, enemies) > -1)
    {
        if (pl->query_prop(SHOP_TMP_WANT_NO_BUSINESS))
            return 0;
        TO->shop_hook_no_business(pl);
        pl->add_prop(SHOP_TMP_WANT_NO_BUSINESS, 1);
        set_alarm(0.0, 0.0, "remove_tmp_want_no_business", pl);
        return 0;
    }

    for (i = 0; i < sizeof(no_sell_prop); i++)
    {
        if ((test = ob->query_prop(no_sell_prop[i])))
            prop = test;
    }

    if (!prop)
        return 1;

    if (stringp(prop))
        write(prop);
    else if (intp(prop))
        TO->shop_hook_stolen_item(pl, ob);
    else
        return 1;

    pl->add_prop(SHOP_TMP_WANT_NO_BUSINESS, 1);
    set_alarm(0.0, 0.0, "remove_tmp_want_no_business", pl);

    enemies += ({ name });
    return 0;
}

/*
 * Function name: shop_hook_allow_buy
 * Description:   A hook to use if you want to test the object
 *                further if you allow it to be bought
 * Arguments:     ob - The object player wants to buy.
 * Returns:       1 if we allow it to be bought (default)
 */
int
shop_hook_allow_buy(object ob)
{
    object  pl = this_player();
    string  name = pl->query_name();

    NF("");
    if (member_array(name, enemies) > -1)
    {
        if (pl->query_prop(SHOP_TMP_WANT_NO_BUSINESS))
            return 0;
        TO->shop_hook_no_business(pl);
        pl->add_prop(SHOP_TMP_WANT_NO_BUSINESS, 1);
        set_alarm(0.0, 0.0, "remove_tmp_want_no_business", pl);
        return 0;
    }

    return 1;
}

/*
 * Function name:   wiz_check
 * Description:     Check if a player is a wizard
 * Returns:         0 if the player is a wizard
 *                  1 otherwise
 */
int wiz_check()
{
    seteuid(geteuid(TO));
    if (TP->query_wiz_level())
        return 0;
    if(check_keeper())
    {
        write("The owner of the store keeps you from going there.\n");
        say("The owner of the store blocks " + QCTNAME(TP) + ".\n");
    }
    else
    {
        write("Some magic force keeps you from going there.\n");
        say(QCTNAME(TP) + " tries to enter the storeroom but fails.\n");
    }
    return 1;
}

/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
int
discriminate()
{
    object  tp = TP;
    string  race = tp->query_race_name();
    int     bargain = tp->query_skill(SS_TRADING);

    if (bargain > 30)
        bargain = 30;
    bargain = 115 - bargain;

    if (member_array(race, hated_race) > -1)
        bargain = (bargain * 120) / 100;
    else if (member_array(race, suspected_race) > -1)
        bargain = (bargain * 110) / 100;
    else if (member_array(race, favoured_race) > -1)
        bargain = (bargain * 90) / 100;
    return bargain;
}

/*
 * Function name: sell_it
 * Description:   Try to let the player sell the item array
 * Arguments:     ob - the object array
 *                check - wheather check for worn or wielded stuff
 *                str - string describing how the money should be paid
 * Returns:       An array with the objects sold
 */
object *
sell_it(object *ob, string str, int check)
{
    int price, i, j, k, *tmp_arr, *null, *value_arr, *null_arr, err;
    object *sold;
    mixed tmp;

    call_other(store_room, "load_me"); /* Make sure store room is loaded */

    value_arr = allocate(sizeof(query_money_types()));
    null_arr = value_arr + ({});
    sold = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
        if (ob[i]->query_prop(OBJ_I_VALUE) == 0)
        {
            shop_hook_sell_no_value(ob[i]);
            continue;
        }

        if (check && (ob[i]->query_worn() ||
                      ob[i]->query_wielded()))
        {
            shop_hook_sell_worn_or_wielded(ob[i]);
            continue;
        }

        if (tmp = ob[i]->query_prop(OBJ_M_NO_SELL))
        {
            shop_hook_sell_no_sell(ob[i], tmp);
            continue;
        }

        if (!shop_hook_allow_sell(ob[i]))
            continue;

        /* Save price if ob destructed in move */
        price = query_sell_price(ob[i]);

        if (price <= 0)
        {
            shop_hook_sell_no_value(ob[i]);
            continue;
        }

        if (err = ob[i]->move(store_room))
        {
            shop_hook_sell_object_stuck(ob[i], err);
            continue;
        }

        if (price > 0)
        {
            tmp_arr = calc_change(price, null, str);
            for (k = 0; k < sizeof(value_arr); k++)
                value_arr[k] += tmp_arr[k];

            sold[j] = ob[i];
            j++;
            if (j >= 20)
                break;
    /*
     * Only let people sell 20 objects at once and hopefully we wont get
     * those too long evaluation problems.
     */
        }
    }

    sold = sold - ({ 0 });

    if (sizeof(sold) > 0)
    {
        change_money(null_arr + value_arr, this_player());
        shop_hook_sell_get_money(text(value_arr));
    }

    return sold;
}

