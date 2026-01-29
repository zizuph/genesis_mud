/*
 *  /d/Sparkle/area/tutorial/lib/shop.c
 *
 *  The standard shop module for Silverdell stores.
 *
 *  This file is copied from /d/Gondor/common/lib/shop which
 *  was created by Olorin in 1994. 
 * 
 *  Features that differ from /d/Genesis/lib/shop:
 *  - Shopkeeper
 *  - Check for special items that are not bought
 *  - greed is set using VBFC discriminate()
 *
 *  Gorboth, July 2003
 *
 *  Removed room inheritance so that shops can inherit other room code,
 *  or possibly be a room at all. This necessitated the removal of a few
 *  room-specific pseudo-items and reworking of the shopkeeper routines,
 *  but the functionality lost is minimal. -Shiva, Oct 17 2003
 */
#pragma save_binary
#pragma strict_types
#include "../defs.h"

inherit "/d/Genesis/lib/shop";

#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <cmdparse.h>

#define MAXLIST 30
#define MONEY_TYPE ({ "cc", "sc", "gc", "pc" })
#define SHOP_TMP_WANT_NO_BUSINESS "_want_no_business"

/*
 *      Prototypes
 */
public string  figure_category(object ob);
public void    remove_tmp_want_no_business(object pl);
public void    shop_hook_no_business(object pl);

/*
 *      Global variables
 */
static object  keeper;
static int has_keeper = 0;
static string *enemies = ({}),
              *hated_race,
              *suspected_race,
              *favoured_race,
               keeper_file,
              *no_sell_prop,
               shop_name;

static mixed  *store_oblist;
static string
    f_categ,
    endlin = "+----------------------------------------------------------"
           + "-----------------+\n",
    blklin = "|                              |          |      |        "
           + "                  |\n",
    catlin = "|            Item              |   Item   | Item |     "
           + "** Item Cost **      |\n"
           + "|            Name              |   Type   | Qty. | Plat."
           + " Gold Silver Copper |\n"
           + "+----------------------------------------------------------"
           + "-----------------+\n",
    reglin = "| %-28s | %-8s | %4d | %4d %5d %6d %6d |\n",
    prev_categ,
    *filarr;
 
static int n_refig = 1;

public void
set_has_keeper(int i)
{
    has_keeper = i;
}


public void
set_keeper(object k)
{
    keeper = k;
    if (keeper != 0)
    {
        set_has_keeper(1);
    }
}


public object
query_keeper()
{
    return keeper;
}


public void
set_no_sell_prop(mixed str)
{
    if (stringp(str))
        no_sell_prop = ({ str });
    else if (pointerp(str))
        no_sell_prop = str;
}


void set_shop_name(string str) { shop_name = str; }
void set_hated_race(string *arr) { hated_race = arr; }
void set_suspected_race(string *arr) { suspected_race = arr; }
void set_favoured_race(string *arr) { favoured_race = arr; }


/*
 * Function name:   setup_shop
 * Description:     Initialize the shop room
 */
public void
setup_shop()
{
    set_store_room(LIB_DIR + "store");
    set_shop_name("Silverdell's Standard Shop");

    set_no_sell_prop("_Silverdell_no_sell");

    set_money_give_max(1000);
    set_money_give_out(   ({ 10000,   700,  40,    1 }));
    set_money_give_reduce(({     0,     4,   3,    9 }));
    set_money_greed_sell("@@discriminate");
    set_money_greed_buy("@@discriminate");
    set_money_greed_change("@@discriminate");

    config_default_trade();  /* Set up the trading system */
}


public mixed
check_keeper()
{
    object  *enemies;

    if (has_keeper)
    {
        if (keeper)
        {
            if (present(keeper, environment(this_player())))
            {
                if (sizeof(enemies = keeper->query_enemy(-1)) > 0)
                {
                    if (member_array(this_player(), enemies) != -1)
                    {
                        notify_fail("The shopkeeper is fighting you, so you"
                          + " cannot do that.\n");
                    }
                    else
                    {
                        notify_fail("The shopkeeper is busy fighting, so you"
                          + " cannot do that.\n");
                    }
        
                    return 0;
                }
                else if (member_array(keeper, this_player()->query_enemy(-1)) != -1)
                {
                    notify_fail("You are fighting the shopkeeper, so you cannot"
                      + " do that.\n");
                    return 0;
                }
            }
            else
            {
                notify_fail("The shopkeeper seems to be gone. You can"
                  + " <ring bell> to try and get some service.\n");
                return 0;
            }
        }
        else
        {
            notify_fail("The shopkeeper seems to be gone. You can"
              + " <ring bell> to try and get some service.\n");
            return 0;
        }

    }

    return 1;
}


int
query_shop_no_business(mixed pl)
{
    return 0;
}


/* Don't conflict with the sign in the room. */
public int
do_read(string str)
{
    if (str == "instructions")
    {
	return ::do_read("sign");
    }
    return 0;
}


public int
do_value(string arg)
{
    if (check_keeper())
    {
        if (query_shop_no_business(this_player()))
        {
            shop_hook_no_business(this_player());
            return 0;
        }
        return ::do_value(arg);
    }
    return 0;
}


public int
shop_hook_sell_no_match(string str)
{
    notify_fail("The shopkeeper says: You don't have any " + str + ".\n");
    return 0;
}


public int
shop_hook_sold_nothing()
{
    if (!this_player()->query_prop(SHOP_TMP_WANT_NO_BUSINESS))
        notify_fail("The shopkeeper says: You didn't have much to sell.\n");
    return 0;
}


public void
shop_hook_sell_no_value(object ob)
{
    notify_fail("The shopkeeper says: " + capitalize(LANG_THESHORT(ob))
      + " is worthless.\n");
}


public void
shop_hook_sell_no_sell(object ob, string str)
{
    if (stringp(str))
        notify_fail(str);
    else
        notify_fail("The shopkeeper says: I don't buy such items.\n");
}


public void
shop_hook_sell_object_stuck(object ob, int err)
{
    notify_fail("The shopkeeper says: It seems you are stuck with that.\n");
}


public void
shop_hook_sell_get_money(string str)
{
    write("The shopkeeper gives you " + str + ".\n");
}


public void
shop_hook_buy_no_match(string str)
{
    notify_fail("The shopkeeper says: I have no " + str + " to sell.\n");
}


public void
shop_hook_cant_carry(object ob, int err)
{
    notify_fail("You drop " + LANG_THESHORT(ob) + " on the floor.\n" +
       "The shopkeeper says: You can't carry more, I'm afraid.\n");
}


public void
shop_hook_buy_magic_money(object ob)
{
    keeper->command("say You are carrying magic money my friend, " +
        "no deal!\n");
}


public void
shop_hook_buy_pay_money(string str, string change)
{
    write("You give " + str + " to the shopkeeper.\n");
    if (change)
        write("The shopkeeper gives you " + change + " back.\n");
}


public void
shop_hook_value_not_interesting(object ob)
{
    if (!this_player()->query_prop(SHOP_TMP_WANT_NO_BUSINESS))
        notify_fail("The shopkeeper says: That item doesn't interest me.\n");
    else
        notify_fail("");
}


public void
shop_hook_value_held(object ob, string text)
{
    keeper->command("say I could offer about " + text +
        " for your " + ob->short() + ".");
}


public void
shop_hook_value_store(object ob, string text)
{
    keeper->command("say I value " + LANG_THESHORT(ob) +
        " to " + text + ".");
}


public void
shop_hook_value_asking(string str)
{
    say(QCTNAME(this_player())+" asks "+QTNAME(keeper) +
        " about the value of the "+str+".\n");
}


public int
shop_hook_value_no_match(string str)
{
    notify_fail("The shopkeeper says: We hold no '" + str + "' in stock.\n");
}


public void
shop_hook_list_empty_store(string str)
{
    notify_fail("The shopkeeper says: We are currently sold out.\n");
}


public int
shop_hook_list_no_match(string str)
{
    notify_fail("The shopkeeper says: We have no '" + str + "' in stock.\n");
}


public void
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
public mixed
shop_hook_filter_sell(object x)
{
    if (weapon_filter(x))
    {
        return "The shopkeeper says: You'll have to take that " 
          + x->short() + " to the Weapon Smith. I only trade in"
          + " general supplies.\n";
    }

    if (armour_filter(x))
    {
        return "The shopkeeper says: You'll have to take that "
          + x->short() + " to the Armourer. I only trade in"
          + " general supplies.\n";
    }

    return 0;
}


public void
shop_hook_stolen_item(object pl, object ob)
{
    keeper->command("say Where did you get this " +
        ob->short() + "?");
    keeper->command("glare " + pl->query_real_name());
    keeper->command("say I can't imagine you came by such things honorably.");
    keeper->command("say Leave before I call the guards!");
}


public void
shop_hook_no_business(object pl)
{
    keeper->command("say I do not want your business, " +
        (pl->query_gender() ? "Lady" : "Mister") + "!");
    keeper->command("say Please leave my shop!");
}


/*
 * Function name: shop_hook_allow_sell
 * Description:   If you want to do more testing on objects 
 *                the player intend to sell.
 * Argument:      ob - The object player wants to sell
 * Returns:       1 if we allow player to sell the object (default)
 */
public int
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
            notify_fail("The shopkeeper says: I do not want your " + ob->short() + ".\n");
        return 0;
    }

    notify_fail("");
    if (member_array(name, enemies) > -1)
    {
        if (pl->query_prop(SHOP_TMP_WANT_NO_BUSINESS))
            return 0;
        this_object()->shop_hook_no_business(pl);
        pl->add_prop(SHOP_TMP_WANT_NO_BUSINESS, 1);
        set_alarm(0.0, 0.0, &remove_tmp_want_no_business(pl));
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
    else if (intp(prop) && query_verb() != "value")
        this_object()->shop_hook_stolen_item(pl, ob);
    else
        return 1;

    pl->add_prop(SHOP_TMP_WANT_NO_BUSINESS, 1);
    set_alarm(0.0, 0.0, &remove_tmp_want_no_business(pl));

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
public int
shop_hook_allow_buy(object ob)
{
    object  pl = this_player();
    string  name = pl->query_name();

    notify_fail("");
    if (member_array(name, enemies) > -1)
    {
        if (pl->query_prop(SHOP_TMP_WANT_NO_BUSINESS))
            return 0;
        this_object()->shop_hook_no_business(pl);
        pl->add_prop(SHOP_TMP_WANT_NO_BUSINESS, 1);
        set_alarm(0.0, 0.0, &remove_tmp_want_no_business(pl));
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
public int 
wiz_check()
{
    seteuid(geteuid(this_object()));
    if (this_player()->query_wiz_level())
        return 0;
    if(check_keeper())
    {
        write("The owner of the store keeps you from going there.\n");
        say("The owner of the store blocks " + QTNAME(this_player()) + ".\n");
    }
    else
    {
        write("Some magic force keeps you from going there.\n");
        say(QCTNAME(this_player()) + " tries to enter the storeroom but"
          + " fails.\n");
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
public int
discriminate()
{
    object  tp = this_player();
    string  race = tp->query_race();
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
public object *
sell_it(object *ob, string str, int check) 
{
    int     price, 
            i, j, k,
            s, 
           *tmp_arr, 
           *null, 
           *value_arr, 
           *null_arr, 
            err;
    mixed   tmp;
    object *sold;

    call_other(store_room, "load_me"); /* Make sure store room is loaded */

    value_arr = allocate(sizeof(query_money_types()));
    null_arr = value_arr + ({});
    sold = allocate(sizeof(ob));

    for (i = 0, s = sizeof(ob); i < s; i++)
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
 

/*
 * Function name: query_store_oblist
 * Description:   Get a list of the current sorted list
 * Returns:       The current list (type mixed *)
 */
 
public mixed
query_store_oblist()
{
    return store_oblist;
}
 
/*
 * Function name: sort_objects_to_list
 * Description:   Sort the list of objects through sort_array
 * Arguments:     a, b - arrays of identical objects
 * Returns:       1 if a after b, else -1
 */
 
public int
sort_objects_to_list(object *a, object *b)
{
    if (b[0]->check_weapon())
        if (a[0]->check_weapon())
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if (a[0]->check_weapon())
            return -1;
    if (b[0]->check_armour())
        if (a[0]->check_armour())
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if (a[0]->check_armour())
            return -1;
    if (a[0]->short() < b[0]->short()) return -1;
    return 1;
}
 
/*
 * Function name: sort_and_stack_inventory
 * Description:   Group the inventory of store_room by short, then sort it
 *                by category, and alphabetically
 * N.B.           DO NOT call this function directly! A lot of cpu can be
 *                saved by calling the function force_new_list() instead
 */
 
static void
sort_and_stack_inventory()
{
    object *oblist;
    setuid(); seteuid(getuid());
    store_room->load_me();
    oblist = FILTER_DEAD(all_inventory(find_object(query_store_room())));
    oblist = unique_array(oblist, "short", 0);
    oblist = sort_array(oblist, "sort_objects_to_list", this_object());
    store_oblist = oblist;
    n_refig = 0;
}
 
/*
 * Function name: figure_category
 * Description:   Figure out which category ob belongs to
 * Arguments:     ob - the object to describe
 * Returns:       The category - weapon type, armour type or "General"
 */
 
public string
figure_category(object ob)
{
    int val;
    if (ob->check_weapon())
        switch(ob->query_wt())
        {
            case W_SWORD: return "Sword";
             case W_SWORD: return "Sword";
            case W_AXE: return "Axe";
            case W_KNIFE: return "Knife";
            case W_CLUB: return "Club";
            case W_POLEARM: return "Polearm";
            case W_MISSILE: return "Missile";
            case W_JAVELIN: return "Javelin";
            default: return "Weapon";
        }
    if (ob->check_armour())
    {
        val = ob->query_at();
        if (val == A_SHIELD) return "Shield";
        if (val & A_HANDS) return "Gloves";
        if (val == A_HEAD) return "Helmet";
        if (val & A_FINGERS) return "Ring";
        if (val & A_FEET) return "Boots";
        if (val & A_LEGS) return "Legs";
        if (val & A_ARMS) return "Arms";
        return "Armour";
    }
    return "General";
}
 
/*
 * Function name: print_item
 * Description:   Format a listing of *ob
 * Arguments:     *ob - an array of identical objects
 * Returns:       A string describing the objects, for use in listing
 */
 
public string
print_item(object *ob)
{
    string ret = "";
    string categ;
    int qty, price;
    ob -= ({ 0 });
    if (!sizeof(ob))
        return "";
    else
        qty = sizeof(ob);
    categ = figure_category(ob[0]);
    price = query_buy_price(ob[0]);
    if (categ != prev_categ)
        ret += blklin;
    prev_categ = categ;
    ret += sprintf(reglin, extract(ob[0]->short(), 0, 40), categ, qty,
        price / 1728, (price % 1728) / 144, (price % 144) / 12, price % 12);
    return ret;
}
 
/*
 * Function name: print_shop_list
 * Description:   Print out the list of items we wanted
 * Arguments:     *list - an array of arrays of identical objects, sorted
 * Returns:       A string showing all objects on list
 */
 
public string
print_shop_list(mixed *list)
{
    string ret;
    int i, j;
    i = sizeof(list);
    if (!i)
    {
        return "";
    }
    ret = endlin + catlin;
    prev_categ = "";
    for (j = 0; j < i; j++)
        ret += print_item(list[j]);
    ret += endlin;
    return ret;
}
 
 
/*
 * Function name: filter_wants_to_view
 * Description:   Filter out only what we said we wanted
 * Arguments:     *ob - an array of identical objects
 * Returns:       1 if we want the item, otherwise 0
 */
 
public int
filter_wants_to_view(mixed *ob)
{
    int i;
    if (!pointerp(filarr)) filarr = allocate(0);
    i = sizeof(filarr);
    if (member_array(lower_case(figure_category(ob[0])), filarr) != -1)
        return 1;
    while(i--)
        if(ob[0]->id(filarr[i])) return 1;
    return 0;
}
 
public int
do_list(string arg)
{
    object *oblist;
    if (!strlen(arg))
        arg = "all";
    filarr = explode(arg, ", ");
    if (n_refig)
        sort_and_stack_inventory();
    oblist = store_oblist;
    if (arg == "weapons")
        oblist = filter(oblist, "filter_w", this_object());
    else if (arg == "armours")
        oblist = filter(oblist, "filter_a", this_object());
    else if (arg != "all")
        oblist = filter(oblist, "filter_wants_to_view", this_object());
    if (!sizeof(oblist))
    {
        // The player did not list any categories. We will look into
        // the inventory using FIND_STR_IN_OBJECT
        oblist = FIND_STR_IN_OBJECT(arg, store_room->get_this_object());
        if (!sizeof(oblist))
        {
            if (arg != "all")
                return shop_hook_list_no_match(arg);
            shop_hook_list_empty_store("");
            return 0;
        }     
        // Input to print_shop_list takes array of an array
        oblist = ({ oblist });
    }
     
    if (query_verb() == "mlist")
    {
        setuid();
        seteuid(getuid());
        clone_object("/std/board/board_more")->more(print_shop_list(oblist));
        return 1;
    }
    write(print_shop_list(oblist));
    return 1;
}
 
public int
filter_w(object *ob)
{
    return ob[0]->check_weapon();
}
 
public int
filter_a(object *ob)
{
    return ob[0]->check_armour();
}
 
/*
 * Function name: force_new_list
 * Description:   Force a new list to be generated when next wanted
 * N.B.           This function saves time by only resorting the list when
 *                it is called for, use this instead of resorting directly.
 */
 
public void
force_new_list()
{
    n_refig = 1;
}
 
 
public void
init_shop()
{
    ::init_shop();
    add_action(do_list, "mlist");
}


public int
do_sell(string arg)
{
    if (::do_sell(arg))
    {
        n_refig = 1;
        return 1;
    }
    return 0;
}
 
public int
do_buy(string arg)
{
    if (::do_buy(arg))
    {
        n_refig = 1;
        return 1;
    }
    return 0;
}
