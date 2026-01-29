/*
 * shop_list.c
 *
 * Modified shop to provide a different listing format.
 *
 * Coded by Lucius based on ideas from Quetzl.
 *
 */
#pragma strict_types

inherit "/lib/shop";

#include <files.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

public int force_new_list(void);

public static int blank_lines = 1, show_price = 1,
		  maxlist = 40, inv_size;

private static string sort_cat;
private static mapping minv = ([ ]);
private static object *sorted = ({ });


public void
set_maxlist(int i)      { maxlist = i; }

public int
query_maxlist(void)     { return maxlist; }

public void
set_show_price(int i)   { show_price = i; }

public int
query_show_price(void)  { return show_price; }

public void
set_blank_lines(int i)  { blank_lines = i; }

public int
query_blank_lines(void) { return blank_lines; }

#if 0
/*
 * Any of these items will cause
 * the inventory to be resorted.
 */
public void
shop_hook_buy_no_buy(object ob, string str)
{
    force_new_list();
    ::shop_hook_buy_no_buy(ob, str);
}

public int
do_sell(string str)
{
    int result = ::do_sell(str);

    if (result)
	force_new_list();

    return result;
}

public int
do_buy(string str)
{
    int result = ::do_buy(str);

    if (result)
	force_new_list();

    return result;
}
#endif

/* Copy of query_buy_price() except heaps are displayed
 * with a singular price. Cannot modify query_buy_price
 * as that will let you buy any size heap for the cost
 * of a single heap item, not good.
 */
public int
query_list_price(object ob)
{
    int seed, value;

    if (ob->num_heap())
	value = ob->query_prop(HEAP_I_UNIT_VALUE);
    else
	value = ob->query_prop(OBJ_I_VALUE);

    sscanf(OB_NUM(ob), "%d", seed);
    return 2 * value * (query_money_greed_buy() +
	15 - this_player()->query_skill(SS_TRADING) / 4 +
	random(15, seed)) / 100;
}

/* Mask inside shops to customize the categorical listings. */
public string
category(object ob)	{ return 0; }

/* Max returned strlen == 8 */
public string
categorize(object ob)
{
    int val;
    string res = category(ob);

    if (strlen(res))
	return res;

    if (ob->check_weapon())
    {
	switch(ob->query_wt())
	{
	case W_AXE:	res = "Axe";	  break;
	case W_CLUB:	res = "Club";	  break;
	case W_KNIFE:	res = "Knife";	  break;
	case W_SWORD:	res = "Sword";	  break;
	case W_POLEARM:	res = "Polearm";  break;
	case W_MISSILE:	res = "Missile";  break;
	case W_JAVELIN:	res = "Javelin";  break;
	default:	res = "Weapon";	  break;
	}
    }
    else if (val = ob->query_slots_setting())
    {
	if (val == A_SHIELD)	      res = "Shield";
	/* Try to sort by likely-found order. */
	else if (val & A_BODY)	      res = "Body";
	else if (val & A_ROBE)	      res = "Robe";
	else if (val & A_ARMS)	      res = "Arms";
	else if (val & A_LEGS)	      res = "Legs";
	else if (val & A_HEAD)	      res = "Helmet";
	else if (val & A_FEET)	      res = "Boots";
	else if (val & A_NECK)	      res = "Necklace";
	else if (val & A_WAIST)	      res = "Belt";
	else if (val & A_HANDS)	      res = "Gloves";
	else if (val & A_FINGERS)     res = "Ring";
	else if (val & A_L_ANKLE)     res = "Anklet";
	else if (val & A_R_ANKLE)     res = "Anklet";
	else if (ob->check_armour())  res = "Armour";
	else                          res = "Clothing";
    }

    return (res ?: "General");
}
 
public int
sort_by_cat(object one, object two)
{
    string cat_one = minv[one][1],
	   cat_two = minv[two][1];

    string str_one = minv[one][0],
	   str_two = minv[two][0];

    if (cat_one < cat_two)
	return -1;

    if (cat_one > cat_two)
	return 1;

    if (str_one < str_two)
	return -1;

    if (str_one > str_two)
	return 1;

    return 0;
}
 
public varargs string
query_object_desc(object obj, int phase)
{
    if (phase)
	return minv[obj][0];

    if (obj->num_heap())
	return obj->singular_short();
    else
	return obj->short();
}

public int
sort_inventory(object store)
{
    object *weapons = ({}), *armours = ({}),
	   *clothing = ({}), *general = ({});

    foreach(object item : all_inventory(store))
    {
	string desc = query_object_desc(item);
	minv[item] = ({ desc, categorize(item) });

	if (!minv[desc])
	{
	    minv[desc] = 0;
	    if (item->check_weapon())
		weapons += ({ item });
	    else if (item->check_armour())
		armours += ({ item });
	    else if (item->query_slots_setting())
		clothing += ({ item });
	    else
		general += ({ item });
	}

	minv[desc] += (item->num_heap() ?: 1);
    }

    if (sizeof(weapons)) {
	sort_array(weapons, sort_by_cat);
	sorted += weapons;
    }
    if (sizeof(armours)) {
	sort_array(armours, sort_by_cat);
	sorted += armours;
    }
    if (sizeof(clothing)) {
	sort_array(clothing, sort_by_cat);
	sorted += clothing;
    }
    if (sizeof(general)) {
	sort_array(general, sort_by_cat);
	sorted += general;
    }

    return sizeof(sorted);
}

public int
armour_filter(object ob)
{
    return ob->check_armour();
}

public int
weapon_filter(object ob)
{
    return ob->check_weapon();
}

public int
general_filter(object ob, string sort_str)
{
    return (sort_str == lower_case(minv[ob][1]));
}
 
public string
shop_hook_list_object(object ob, int amount = 1)
{
    string res = "";
    string cat = minv[ob][1];
    string str = query_object_desc(ob, 1);

    if (blank_lines)
    {
	/* Blank line to seperate categories. */
	if (cat != sort_cat)
	{
	    if (show_price)
		res = sprintf("|%4s|%44s|%10s|%13s|\n", "", "", "", "");
	    else
		res = sprintf("|%4s|%45s|%10s|\n", "", "", "");
	}

	sort_cat = cat;
    }

    /* The fields are fixed width so that overflowing values won't
     * completely destroy the layout.  We'll doublecheck them anwyays
     * and round to the highest possible value for that field.
     *
     * People can always do 'value <object>' to get the proper amount.
     */
    if (amount > 999)
	amount = 999;

    if (show_price)
    {
	int *arr = split_values(query_list_price(ob));

	if (arr[3] > 99)  arr[3] = 99;
	if (arr[2] > 99)  arr[2] = 99;
	if (arr[1] > 99)  arr[1] = 99;
	if (arr[0] > 99)  arr[0] = 99;

	return res + sprintf("|%3.3d | %-42.42s | %|8.8s | " +
	    "%2.2d %2.2d %2.2d %2.2d |\n",
	    amount, str, cat, arr[3], arr[2], arr[1], arr[0]);
    }
    else
    {
	return res + sprintf("|%3.3d | %-43.43s | %|8.8s |\n",
	    amount, str, cat); 
    }
}

public int
do_list(string str)
{
    int count;
    object store;
    object *item_arr;

    if (!objectp(store = get_store_object()))
    {
        write("Error: no store object - please make a bug report.\n");
        return 1;
    }

    if (!sizeof(sorted) && !sort_inventory(store))
    {
	shop_hook_list_empty_store(str);
	return 0;
    }

    if (!strlen(str))
	str = "all";

    switch(str)
    {
    case "armors":
    case "armours":
	item_arr = filter(sorted, armour_filter);
	break;
    case "weapons":
	item_arr = filter(sorted, weapon_filter);
	break;
    case "all":
    case "items":
    case "objects":
	item_arr = sorted;
	break;
    default:
	/* Try to match a category name first, then test against str */
	if (!sizeof(item_arr = filter(sorted, &general_filter(,str))))
	    item_arr = FIND_STR_IN_ARR(str, sorted);

	break;
    }

    if (!sizeof(item_arr))
	return shop_hook_list_no_match(str);

    /* This is the header block. */
    if (show_price)
    {
	/* Strlen == 76 */
	str = sprintf("+%'-'75s\n|%|4s|%|44s|%|10s|%|13s|\n+%'-'75s\n",
	    "+", "##", "Item Name", "Type", " P  G  S  C", "+");
    }
    else
    {
	/* Strlen == 63 */
	str = sprintf("+%'-'62s\n|%|4s|%|45s|%|10s|\n+%'-'62s\n",
	    "+", "##", "Item Name", "Type", "+");
    }

    if (blank_lines && sizeof(item_arr))
	sort_cat = minv[item_arr[0]][1];

    foreach(object item : item_arr)
    {
	int amount = minv[minv[item][0]];
	str += shop_hook_list_object(item, amount);

	if (++count > maxlist) {
	    count = -1;
	    break;
	}
    }

    /* Handle truncation. */
    if (count < 0)
    {
	if (show_price)
	    str += sprintf("%'*'-75s|\n", "|****** TRUNCATED ");
	else
	    str += sprintf("%'*'-62s|\n", "|****** TRUNCATED ");
    }

    /* This is the footer. */
    if (show_price)
	str += sprintf("+%'-'75s\n", "+");
    else
	str += sprintf("+%'-'62s\n", "+");

    if (query_verb() == "mlist")
	this_player()->more(str, 0);
    else
	write(str);

    return 1;
}

public int
force_new_list(void)
{
    minv = ([]);
    sorted = ({});
    return 1;
}

public void
init_shop(void)
{
    ::init_shop();
    add_action(do_list, "mlist");
}

