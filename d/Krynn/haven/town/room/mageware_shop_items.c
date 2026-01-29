
// Commented out to avoid runtimes due to changes made by Faerun wizards
// inherit "/d/Faerun/lib/shop_list";

inherit "/d/Krynn/haven/town/room/shop_list";

#include <language.h>
 
public void set_standard_equip(mixed x);
public object *clone_and_buy_it(string str1, string str2, string str3);
public object clone_it(string str);
public int do_buy(string args);
public int do_list(string args);
public int do_show(string str);
static string *standard_equip;
string *sold_list = ({});

#define HERB_GLOVES     "/d/Shire/frogmorton/obj/herb_gloves"
#define HERB_JAR        "/d/Gondor/guilds/rangers/obj/herbjar"
#define HERB_POUCH      "/d/Gondor/common/obj/herbpouch"

#define MAGE_EQUIP  ({ HERB_GLOVES, HERB_JAR, HERB_POUCH })

/*
 * Function name: shop_hook_list_object
 * Description:   List an object 
 * Arguments:	  ob - The object
 */
void
shop_hook_list_object(object ob, int price)
{
    string str, mess, categ;
    str = sprintf("%-41s", capitalize(LANG_ASHORT(ob)));
    categ = figure_category(ob);
    if (mess = text(split_values(price)))
    {
        mess = sprintf(" %-8s | %2d %2d %2d %2d", categ, price / 1728, (price % 1728) / 144, (price
% 144) / 12, price % 12);
        write("| " +str + "|" + mess + " |\n");
    }
    else
    {
	write(str + "That item wouldn't cost you much.\n");
    }
} 
public void
set_standard_equip(mixed x)
{
    if (stringp(x))
        standard_equip = ({ x });
    else if (pointerp(x))
        standard_equip = x;
    else
        standard_equip = MAGE_EQUIP;
}
object
clone_it(string str)
{
    int n, s;
    object ob;
    string *s_arr,
        *adjs; 
    seteuid(getuid());
    s_arr = explode(str, " ");
    if ((s = sizeof(s_arr)) > 1)
        str = s_arr[s - 1];
    s_arr -= ({ str });
    --s;
    n = -1;
    while (++n < sizeof(standard_equip) && !objectp(ob))
    {
        if (standard_equip[n]->id(str))
        {
            adjs = standard_equip[n]->query_adjs();
            if (!s || (s == sizeof(adjs & s_arr)))
                ob = clone_object(standard_equip[n]);
        }
    }
    return ob;
} 
object *
clone_and_buy_it(string str1, string str2, string str3)
{
    int price, i, j, k, n,
        num = sizeof(query_money_types()),
        *value_arr = allocate(2 * num),
        *arr, error, err;
    object ob;
    if (!strlen(str1))
	return 0;
    ob = clone_it(str1);
    if (!objectp(ob))
    {
	return 0;
    }
    price = query_buy_price(ob);
  
    if (err = ob->move(this_player()))
    {
        shop_hook_buy_cant_carry(ob, err);
        ob->remove_object();
        return 0;
    }
  
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
        }
        /* We don't want the money so no move error to us, if there was one
           it was because the player couldn't hold all coins, and if so the
           drop text is already written, but the deal is still on :) */
    }
  
    for (k = 0; k < 2 * num; k++)
        value_arr[k] += arr[k];
  
    if (objectp(ob))
        shop_hook_buy_pay_money(
            text(arr[0 .. num - 1]), text(arr[num .. 2 * num - 1]));
  
    return ({ ob });
}
public int
do_buy(string args) 
{
    int     res;
    object *item;
    string  str,
        str2,
        str3;
  
    if (!args || args == "")
    {
        notify_fail("The shopkeeper says: Buy what?\n");
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
    if (res = ::do_buy(args))
        return res;
    else
    {
	item = clone_and_buy_it(str,str2,str3);
	if (sizeof(item))
            return shop_hook_bought_items(item);
        else
            return 0;
    }
    return 0;
}
public int
do_list(string args)
{
    string list_txt; 
    int n, s;
    object *oblist;
    if (args != "equipment" && args )
        return ::do_list(args);
    else if (!args || args == "")
    {
        ::do_list(args);
        write(" --- Standard mageware equipment available by 'list equipment'\n"+
              " --- Herbs in store available by 'list herbs'\n");
        return 1;
    }
    write("This is the standard mageware equipment in stock at this shop:\n\n" +
    "+-------------------------------------------------------------------+\n"+
    "|                 Name                     | Category |  P  G  S  C |\n"+
    "+-------------------------------------------------------------------+\n");
     s = sizeof(standard_equip);
    while (n < s) 
    {
        call_other(standard_equip[n], "load_me");
        shop_hook_list_object(find_object(standard_equip[n]),
        query_buy_price(find_object(standard_equip[n])));
        n++;
    }
    write("+-------------------------------------------------------------------+\n");
    return 1;
}
public mixed
shop_hook_filter_sell(object x)
{
    return 0;
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
    if (!str || str == "")
    {
        notify_fail("The shopkeeper says: Show what?\n");
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
