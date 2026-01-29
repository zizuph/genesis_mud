/*
 *  /d/Gondor/guilds/rangers/shop_base.c
 *
 *
 * The base shop of the Rangers of Ithilien.
 * - From the Hobbiton Shop, 1991, by Elessar.
 *
 * Modifications:
 * - Modified by Randor 1992
 * - Modified to use Olorin's standard-Gondor-shop, July 1994.
 * - 12-Oct-1998, Gnadnar: tidy up, add items
 * - 15-July-01, Alto: modified to fit revised rangers theme.
 * - 24 May 04, Gwyneth: Tidied up
 * - March 2019, Finwe: Added Noldor as favored race, cleaned up list output
 */
inherit "/d/Gondor/common/lib/shop.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "rangers.h"
#include "shop_items.h"

/* Prototypes */
public void    create_shop();
public string  exa_poster();
public void    set_standard_equip(mixed x);
public int     not_welcome();
public int     discriminate();
public varargs object *clone_and_buy_it(string s1, string s2, string s3, int i);
public object  clone_it(string str);
public int     do_buy(string args);
public int     do_value(string args);
public int     do_sell(string args);
public int     do_list(string args);
public mixed   shop_hook_filter_sell(object x);
public void    shop_hook_stolen_item(object pl, object ob);
public void    enter_inv(object ob, object from);
public int     do_show(string str);
public void    do_report();
public void    create_ranger_shop();
public string  look_notebook();

/* Global Variables */
static string *Standard_Equip;
string *Sold_List = ({});

public void
create_shop()
{
    create_ranger_shop();
    set_hated_race(({"goblin"}));
    set_favoured_race(({"human","elf"}));
    set_money_greed_sell(&discriminate());
    set_money_greed_buy(&discriminate());
    set_money_greed_change(&discriminate());
    add_item("notebook", &look_notebook());
    add_item("poster", &exa_poster());
}

public void
create_ranger_shop()
{
    set_store_room(RANGERS_HQ_DIR + "hq_store");
    set_short("the Central Headquarters Equipment Store");
    set_long("You are in the Central Headquarters Equipment Store. " +
      "There are lots of strange items lying around, probably brought " +
      "here from distant lands. There is a poster on the wall, and " +
      "the exit from the store leads back south.\n");
    set_shop_name("The Central Headquarters Equipment Store");
    set_keeper_file(RANGERS_NPC + "fredegar");
    add_item(({"door"}), "The door is probably leading into the " +
        "storeroom of the shop. The door is standing open, but the shop " +
        "keeper probably would not be amused if you tried to go there.\n");
    add_exit(RANGERS_HQ_DIR + "dcorridor2", "south", 0, 0);

    set_standard_equip(GONDOR_EQUIP);
}

public string
look_notebook()
{
    if(!check_keeper())
    {
        return "You find no notebook.\n";
    }
    else
    {
        write("The shopkeeper pulls his notebook away from " +
            "your prying eyes, mumbling something about curiosity " +
            "and a dead cat.\n");
        say("The shopkeeper pulls his notebook away from " +
            QTPNAME(TP) + " prying eyes, mumbling something about " +
            "curiosity and a dead cat.\n");
        return "";
    }
}

public string
exa_poster()
{
  return "\nWelcome to the Rangers Equipment Store!\n" +
         "You can try these instructions: \n" +
         "    buy sword for gold and get copper back\n" +
         "    buy sword for gold coins\n" +
         "    sell sword for copper coins\n" +
         "    sell all  - will let you sell all items except for\n" +
         "                items you wield or wear.\n" +
         "    sell all! - will let you sell ALL items you have, well\n" +
         "                at least the droppable, and no coins.\n" +
         "    sell sword, sell second sword, sell sword 2, sell two swords\n" +
         "                also works. You might want to change the verb to\n" +
         "                'value' or 'buy' too. Beware, you will never buy\n"+
         "                more than one item at a time. So if you really\n" +
         "                want those three expensive swords, you have to \n" +
         "                repeat yourself three times.\n" +
         "    If you want a list of the special equipment available, do:\n"+
         "     'list equipment'.\n"+
         "    If you want a list of all swords available in the store, the\n" +
         "    correct syntax is: list swords\n" +
         "                'list weapons', 'list armours' also works.\n\n";
}

public void
set_standard_equip(mixed x)
{
    if (stringp(x))
        Standard_Equip = ({ x });
    else if (pointerp(x))
        Standard_Equip = x;
    else
        Standard_Equip = ITH_EQUIP;
}

public int
not_welcome()
{
    NF("The shopkeeper says: Forget it! I do not trade with the Enemy! " +
        "How did you even get in here? Guards! Arrest this person!\n");
    return 0;
}

public int
discriminate()
{
    object tp = TP;
    string race = tp->query_race();
    int bargain = tp->query_skill(SS_TRADING);

    if (bargain > 30) 
        bargain = 30;

    bargain = 115 - bargain;

    if (member_array(race, hated_race) > -1)
        bargain = (bargain * 120) / 100;
    else if (member_array(race, suspected_race) > -1)
        bargain = (bargain * 110) / 100;
    else if (IS_DUNADAN(tp) || IS_SINDAR(tp) || IS_NOLDOR(tp) || IS_MILITIA(tp))
        bargain = (bargain * 90) / 100;
    else if (member_array(race, favoured_race) > -1)
        bargain = (bargain * 95) / 100;
    return bargain;
}

object
clone_it(string str)
{
    int n, s;
    object ob;
    string *s_arr, *adjs;

    seteuid(getuid());

    s_arr = explode(str, " ");
    if ((s = sizeof(s_arr)) > 1)
        str = s_arr[s - 1];
    s_arr -= ({ str });
    --s;
    n = -1;
    while (++n < sizeof(Standard_Equip) && !objectp(ob))
    {
        if (Standard_Equip[n]->id(str))
        {
            adjs = Standard_Equip[n]->query_adjs();
            if (!s || (s == sizeof(adjs & s_arr)))
                ob = clone_object(Standard_Equip[n]);
        }
    }

    return ob;
}

public varargs object
clone_and_buy_it(string str1, string str2, string str3, int item_num = 1)
{
    int price, i, j, k, n, num = sizeof(query_money_types()),
        *value_arr = allocate(2 * num), *arr, error, err;
    object ob;

    if (!strlen(str1))
        return 0;

    ob = clone_it(str1);
    if (!objectp(ob))
        return 0;

    price = query_buy_price(ob);
    price *= item_num;
  
    for (i = 0; i < item_num; i++)
    {
        if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
        {
            shop_hook_buy_cant_pay(ob, arr);
            ob->remove_object();
            return 0;
        }
  
        if (error = arr[sizeof(arr) - 1])
        {
            if (error < -1)
            {
                /* Couldn't take the money from player, the coins were stuck */
                shop_hook_buy_magic_money(ob);
                ob->remove_object();
                return 0;
            }
            /* We don't want the money so no move error to us, if there was one
               it was because the player couldn't hold all coins, and if so the
               drop text is already written, but the deal is still on :) */
        }

        if (err = ob->move(this_player()))
        {
            shop_hook_buy_cant_carry(ob, err);
            /* Drop it on the ground. */
            ob->move(this_object());
        }
  
        if (i < item_num - 1)
            ob = clone_object(MASTER_OB(ob));
    }
  
    for (k = 0; k < 2 * num; k++)
        value_arr[k] += arr[k];
  
    if (objectp(ob))
        shop_hook_buy_pay_money(
            text(arr[0 .. num - 1]), text(arr[num .. 2 * num - 1]));
  
    return ob;
}

public int
do_buy(string args)
{
    int res, item_num;
    object shop_item;
    string str, str2, str3, item_name;
  
    if (!check_keeper())
        return 0;

    if (query_friend_or_foe(TP) < 0)
        return not_welcome();
    else if (!args || args == "")
    {
        NF("The shopkeeper says: Buy what?\n");
        return 0;
    }

    if (sscanf(args,"%s for %s and get %s", str, str2, str3) != 3)
    {
        str3 = "";
        if (sscanf(args,"%s for %s", str, str2) != 2)
        {
            str2 = "";
            str = args;
        }
    }

   if (sscanf(str, "%d %s", item_num, str) != 2)
      item_num = 1;

    /* No more than 10, no less than 1. */
    item_num = min(10, item_num);
    item_num = max(1, item_num);

    if (item_num > 1)
        str = LANG_SWORD(str);

    shop_item = clone_and_buy_it(str,str2,str3, item_num);
    if (objectp(shop_item))
    {
        if (!item_num)
            write("You didn't buy anything!\n");

        if (item_num > 1)
            item_name = LANG_WNUM(item_num) + " " + 
                LANG_PWORD(shop_item->short());
        else
            item_name = LANG_ADDART(shop_item->short());

        write("You bought " + item_name + ".\n");
        say(QCTNAME(this_player()) + " bought " + item_name + ".\n");
        res = 1;
    }
    else
        res = 0;

    if (!res)
        res = ::do_buy(args);

    return res;
}

public int
do_value(string args)
{
    if (check_keeper()) 
    {
        if (query_friend_or_foe(TP) < 0)
            return not_welcome();
        else
            return ::do_value(args);
    }
    return 0;
}

public int
do_sell(string args)
{
    if (check_keeper()) 
    {
        if (query_friend_or_foe(TP) < 0)
            return not_welcome();
        else
        {
            if(IS_RANGER(TP) &&
               member_array(TP->query_name(), Sold_List) == -1)
            {
                Sold_List += ({TP->query_name()});

                tell_room(TO, "The shopkeeper jots something down " +
                    "in a little notebook, then hides it away in his " +
                    "pocket.\n");
            }

            return ::do_sell(args);
        }
    }
    return 0;
}

public int
do_list(string args)
{
    string list_txt;
    int n, s;
    if (check_keeper()) 
    {
        if (query_friend_or_foe(TP) < 0)
            return not_welcome();
        else
        {
            if (args != "equipment" && args)
                return ::do_list(args);
            else if (!args || args == "")
            {
                ::do_list(args);
                write(" --- Standard equipment available by " +
                    "'list equipment'.\n");
                return 1;
            }
            write(" Standard Ranger equipment in stock: " +
                  "----------------------\n");
                s = sizeof(Standard_Equip);
                while (n < s)
                {
                    call_other(Standard_Equip[n], "load_me");
                    shop_hook_list_object(find_object(Standard_Equip[n]),
                        query_buy_price(find_object(Standard_Equip[n])));
                    n++;
                }
                write(" ----------------------------------------------" +
                    "------------\n");
                return 1;
        }
    }
    return 0;
}

public mixed
shop_hook_filter_sell(object x)
{
    return 0;
}

public void
shop_hook_stolen_item(object pl, object ob)
{
    keeper->command("eyebrow");
    keeper->command("say Where did you get this " + ob->short() + "?");
    if (ob->query_prop(GONDOR_M_RANGERS_NO_SELL))
    {
        keeper->command("say This is official Ranger equipment.");
        keeper->command("say You are not supposed to be carrying this,");
        keeper->command("say you must have stolen it .... or even....!");
        keeper->command("say Get out! Out of my sight!");
    }
    else if (ob->query_prop(GONDOR_M_ROHIRRIM_NO_SELL))
    {
        keeper->command("say This was crafted by our allies, the Rohirrim!");
        keeper->command("say You must have stolen it....or even worse!");
        keeper->command("say Get out, before I call the guards on you!");
    }
    else if (ob->query_prop(GONDOR_M_TIRITH_NO_SELL))
    {
        keeper->command("say This is official Gondorian equipment!");
        keeper->command("say You are not supposed to be carrying this,");
        keeper->command("say you must have stolen it...or even worse!");
        keeper->command("say Leave! Or I call the guards!");
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(from) || !objectp(ob) || !interactive(ob))
        return;

    if (!check_keeper())
        return;

    /* One in 5 chance of going to the inn, but not during Armageddon. */
    if (!random(5) && !ARMAGEDDON->shutdown_active())
        keeper->visit_inn();
}

/*
 * Function name: do_show
 * Description  : Allow the player to appraise one of the objects in stock.
 * Returns      : int - 1/0 - true if success.
 * Arguments    : string str - the name of the objects to search for.
 */
public int
do_show(string str)
{
    object ob;

    if (!check_keeper())
        return 0;

    if (query_friend_or_foe(TP)<0)
        return not_welcome();
    else if (!str || str == "")
    {
        NF("The shopkeeper says: Show what?\n");
        return 0;
    }

    if (::do_show(str))
        return 1;

    if (!objectp(ob = clone_it(str)))
        return 0;

    shop_hook_appraise_object(ob);
    ob->appraise_object();
    ob->remove_object();
    return 1;
}

int
do_report()
{
    if (!check_keeper())
    {
        notify_fail("There is no shopkeeper to receive a report from!\n");
        return 0;
    }

    if((IS_RANGER(TP) && TP->query_is_officer()) || TP->query_wiz_level())
    {
        if(sizeof(Sold_List) < 1)
        {
            write("You look at the shopkeeper's report and " +
                "find that business is very slow. No Ranger has sold " +
                "anything yet.\n");
            tell_room(TO, QCTNAME(TP) + " looks at the shopkeeper's " +
                "report.\n", TP);
            return 1;
        }
        else
        {
            write("You look at the shopkeeper's report and " +
                "see that the following Rangers have sold items in " +
                "this shop recently:\n" + implode(Sold_List, ", ") + "\n");
            tell_room(TO, QCTNAME(TP) + " looks at the shopkeeper's " +
                "report.\n", TP);
            return 1;
        }
    }
    else
    {
        write("You find the customer lists unavailable to " +
            "you, being marked for officers only.\n");
        tell_room(TO, QCTNAME(TP) + " tries to look at the shopkeeper's " +
            "report, but is not allowed.\n", TP);
        return 1;
    }
}

public void
init()
{
    ::init();

    add_action(do_report, "report");
}

