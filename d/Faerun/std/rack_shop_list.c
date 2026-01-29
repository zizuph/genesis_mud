/*
 * shop_list.c
 *
 * Modified shop to provide a different listing format.
 *
 * Coded by Lucius based on code from Quetzl.
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

#ifndef __AVENIR_SHOP_DEFS__
#define __AVENIR_SHOP_DEFS__

#define SHOP_S_CATEGORY "__shop_s_category"

#endif  __AVENIR_SHOP_DEFS__


public int force_new_list(void);

public static mixed *sorted_arr;
private static string sort_str, sort_cat;
public static int blank_lines = 1, show_price = 1,
       maxlist = 35, inv_size;


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
    string res = ob->query_prop(SHOP_S_CATEGORY);

    if (res)
	return res;

    if (res = category(ob))
    {
	ob->add_prop(SHOP_S_CATEGORY, res);
	return res;
    }

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
	else if (val & A_HANDS)	      res = "Gloves";
	else if (val & A_FINGERS)     res = "Ring";
	else if (ob->check_armour())  res = "Armour";
	else                          res = "Clothing";
    }
    else
	res = "General";

    ob->add_prop(SHOP_S_CATEGORY, res);
    return res;
}
 
public void
update_category(object obj)
{
    obj->remove_prop(SHOP_S_CATEGORY);
    categorize(obj);
}

/* This sorting places weapons first, then armours, then general items.
 * Each main category is sorted alphabetically by sub-category name then
 * sorted alphabetically by the items in those sub-categories.
 */
public int
sort_inventory(object *one, object *two)
{
    /* Sort Weapons. */
    if (two[0]->check_weapon())
    {
        if (one[0]->check_weapon())
        {
	    string cat_one = categorize(one[0]),
		   cat_two = categorize(two[0]);

            if (cat_one < cat_two)
		return -1;

            if (cat_one > cat_two)
		return 1;

            if (one[0]->short() < two[0]->short())
		return -1;

            if (one[0]->short() == two[0]->short())
		return 0;
        }

	return 1;
    }

    if (one[0]->check_weapon())
	return -1;

#if 1
    /* Sort Armours. */
    if (two[0]->check_armour())
    {
	if (one[0]->check_armour())
        {
	    string cat_one = categorize(one[0]),
		   cat_two = categorize(two[0]);

            if (cat_one < cat_two)
		return -1;

            if (cat_one > cat_two)
		return 1;

            if (one[0]->short() < two[0]->short())
		return -1;

            if (one[0]->short() == two[0]->short())
		return 0;
        }

	return 1;
    }

    if (one[0]->check_armour())
	return -1;
#endif

    /* Sort clothing. */
    if (two[0]->query_slots_setting())
    {
	if (one[0]->query_slots_setting())
        {
	    string cat_one = categorize(one[0]),
		   cat_two = categorize(two[0]);

            if (cat_one < cat_two)
		return -1;

            if (cat_one > cat_two)
		return 1;

            if (one[0]->short() < two[0]->short())
		return -1;

            if (one[0]->short() == two[0]->short())
		return 0;
        }

	return 1;
    }

    if (one[0]->query_slots_setting())
	return -1;

    /* Now sort by category. */
    string cat_one = categorize(one[0]),
	   cat_two = categorize(two[0]);

#if 1
    if ((cat_one == "General") && (cat_two != "General"))
	return 1;

    if ((cat_one != "General") && (cat_two == "General"))
	return -1;
#endif

    if (cat_one < cat_two)
	return -1;

    if (cat_one > cat_two)
	return 1;

#if 1
    /* General alpha sort now, heaps by singular short. */
    if (one[0]->num_heap())
	cat_one = one[0]->singular_short();
    else
	cat_one = one[0]->short();

    if (two[0]->num_heap())
	cat_two = two[0]->singular_short();
    else
	cat_two = two[0]->short();
#else
    cat_one = one[0]->short();
    cat_two = two[0]->short();
#endif

    if (cat_one < cat_two)
	return -1;

    if (cat_one > cat_two)
	return 1;

    return 0;
}
 
public int
armour_filter(object *ob)
{
    return ob[0]->check_armour();
}

public int
weapon_filter(object *ob)
{
    return ob[0]->check_weapon();
}

public int
general_filter(object *ob)
{
    if (sizeof(FIND_STR_IN_ARR(sort_str, ob)))
	return 1;

    if (sort_str == lower_case(categorize(ob[0])))
	return 1;

    return 0;
}
 
/*
 * Provide the short / singular short of an object / heap.
 * Split out to allow for further customized strings by
 * inheriting objects.
 */
public string
query_object_short(object obj)
{
    if (obj->num_heap())
	return obj->singular_short();
    else
	return obj->short();
}

public string
shop_hook_list_object(object ob, int amount = 1)
{
    string cat, res, str;

    str = query_object_short(ob);

    if (ob->num_heap())
	amount = ob->num_heap();

    res = "";
    cat = categorize(ob);

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
    mixed *item_arr;
    object store_object;
    int i, max, size;

    if (!objectp(store_object = get_store_object()))
    {
        write("Error: no store object - please make a bug report.\n");
        return 1;
    }

    item_arr = all_inventory(store_object);

    /* Should not be needed with /d/Avenir/inherit/storage.c
     * being used -- which it should be (or emulated).
     *
    if (inv_size != (inv_size = sizeof(item_arr)))
	sorted_arr = 0;
     */

    if (!sizeof(sorted_arr))
    {
	sorted_arr = sort_array(
	    unique_array(item_arr, "short"), sort_inventory);

	if (!sizeof(sorted_arr))
	{
	    shop_hook_list_empty_store(str);
	    return 0;
	}
    }

    if (!strlen(str))
	str = "all";

    switch(str)
    {
    case "armors":
    case "armours":
	item_arr = filter(sorted_arr, armour_filter);
	break;
    case "weapons":
	item_arr = filter(sorted_arr, weapon_filter);
	break;
    default:
	sort_str = str;
	item_arr = filter(sorted_arr, general_filter);
	break;
    }

    if (!(size = sizeof(item_arr)))
	return shop_hook_list_no_match(str);

    /* This is the header block. */
    if (show_price)
    {
	/* Strlen == 77 */
	str = sprintf("+%'-'75s\n|%|4s|%|44s|%|10s|%|13s|\n+%'-'75s\n",
	    "+", "##", "Item Name", "Type", " P  G  S  C", "+");
    }
    else
    {
	/* Strlen == 63 */
	str = sprintf("+%'-'62s\n|%|4s|%|45s|%|10s|\n+%'-'62s\n",
	    "+", "##", "Item Name", "Type", "+");
    }

    if (blank_lines)
	sort_cat = categorize(item_arr[0][0]);

    max = min(maxlist, size);

    /* Individual items. */
    for (i = 0; i < max; i++)
	str += shop_hook_list_object(item_arr[i][0], sizeof(item_arr[i]));

    /* Handle truncation. */
    if (max < size)
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
    sorted_arr = 0;
    return 1;
}

public void
init_shop(void)
{
    ::init_shop();
    add_action(do_list, "mlist");
}

