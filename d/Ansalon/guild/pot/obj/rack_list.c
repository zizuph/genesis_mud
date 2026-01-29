/*
 * shop_list.c
 *
 * Modified shop to provide a different listing format.
 *
 * Coded by Lucius based on ideas from Quetzl.
 *
 */
#pragma strict_types

#include <files.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

public int force_new_list(void);

public static int blank_lines = 1, show_price = 1,
		  maxlist = 400, inv_size;

private static string sort_cat = "";
private static mapping minv = ([ ]);
private static object *sorted = ({ });


public void
set_maxlist(int i)      { maxlist = i; }

public int
query_maxlist(void)     { return maxlist; }

public void
set_blank_lines(int i)  { blank_lines = i; }

public int
query_blank_lines(void) { return blank_lines; }

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
	else if (val & A_ARMS)	      res = "Arms";
	else if (val & A_LEGS)	      res = "Legs";
	else if (val & A_HEAD)	      res = "Helmet";
	else if (val & A_FEET)	      res = "Boots";
	else if (val & A_HANDS)	      res = "Gloves";
	else if (val & A_ROBE)	      res = "Robe";
	else if (ob->check_armour())  res = "Armour";
	else                          res = "Clothing";
    }
    else if (IS_LEFTOVER_OBJECT(ob))
	res = "Leftover";
    else if (IS_FOOD_OBJECT(ob))
	res = "Food";
    else if (IS_DRINK_OBJECT(ob))
	res = "Drink";

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

public string
list_one_object(object ob, int amount = 1)
{
    string res = "";
    string cat = minv[ob][1];
    string str = query_object_desc(ob, 1);

    if (blank_lines)
    {
	/* Blank line to seperate categories. */
	if (cat != sort_cat)
	    res = sprintf("|%4s|%45s|%10s|\n", "", "", "");

	sort_cat = cat;
    }

    /* The fields are fixed width so that overflowing values won't
     * completely destroy the layout.  We'll doublecheck them anwyays
     * and round to the highest possible value for that field.
     */
    if (amount > 999)
	amount = 999;

    return res + sprintf("|%3.3d | %-43.43s | %|8.8s |\n",
	amount, str, cat); 
}

public void
show_visible_contents(object for_obj)
{
    int count;
    string str;

    force_new_list();

    if (!sizeof(sorted) && !sort_inventory(this_object()))
	return;

    /* Strlen == 63 */
    str = sprintf("+%'-'62s\n|%|4s|%|45s|%|10s|\n+%'-'62s\n",
	"+", "##", "Item Name", "Type", "+");

    if (blank_lines && sizeof(sorted))
	sort_cat = minv[sorted[0]][1];

    foreach(object item : sorted)
    {
	int amount = minv[minv[item][0]];
	str += list_one_object(item, amount);

	if (++count > maxlist) {
	    count = -1;
	    break;
	}
    }

    /* Handle truncation. */
    if (count < 0)
	str += sprintf("%'*'-62s|\n", "|****** TRUNCATED ");

    /* This is the footer. */
    str += sprintf("+%'-'62s\n", "+");
    for_obj->catch_tell(str);
}

public void
force_new_list(void)
{
    minv = ([]);
    sorted = ({});
}
