/*
 * Made coin purse recoverable and keepable
 * -- Finwe, April 2005
 *
 * Modification log:
 *   Lavellan (2011/07/11) - changed value (endless money bug otherwise)
 */
inherit "/d/Gondor/common/guild/obj/backpack";
inherit "/d/Shire/lib/box_list";
inherit "/lib/keep";
inherit "/lib/shop";

#include "/d/Shire/sys/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

string 
    endline = "+-----------------------------------+\n",
    blkline = "|      |                            |\n",
    catline = "| Qty. | Coins                      |\n",
//    reglin = "| %-=50s | %-8s | %4d |\n",
regline = "| %-4d | %-=25s  |\n";


void
create_container()
{
    set_name("purse");
    set_adj("leather");
    set_pshort("leather purse");
    set_short("@@short_func@@");
    set_long("@@long_func@@");

    set_keep(1);

    //add_prop(OBJ_I_VALUE,         250);
    add_prop(OBJ_I_VALUE,         50);
    add_prop(CONT_I_VOLUME,       300);
    add_prop(CONT_I_WEIGHT,       300);
    add_prop(CONT_I_MAX_VOLUME, 20000);
    add_prop(CONT_I_MAX_WEIGHT, 20000);
    add_prop(CONT_I_RIGID,          0);
    add_prop(CONT_I_CLOSED,         0);
}


/* Function name: short_func
 * Description  : Returns a string for the short description depending
 *                on whether or not there are herbs in the pouch.
 * Returns      : string description
 */
string
short_func()
{
    if (sizeof(all_inventory(TO)))
        return "leather purse with some coins";

    return "leather purse";
}

/* Function name: long_func
 * Description  : Returns a string for the long description depending
 *                on whether or not the pouch is tied to your belt.
 * Returns      : string description
 */
public string
long_func()
{
    string long_desc = "This is a leather purse. It is square shaped " +
        "and made of cowhide. The purse is well worn and softened from " +
        "constant use. ";

    if (query_prop(OBJ_M_NO_SELL))
        long_desc += "You may <keep purse> to protect it from being sold.";
    else
        long_desc += "You may <keep purse> to the " + short() + 
            " from being accidentally sold.";
    return (long_desc + "\n");
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

	
    if (!obj->query_coin_type())
    {
        obj->add_name(obj->query_coin_type());
    }
}
    
/* 
 * item_filter, used to filter out certain objects when shifting stuff 
 * in or out of pack, like non-sellables, non-droppables, 
 * containers etc. 
 */
 
int
item_filter(object ob)
{
    return IS_COINS_OBJECT(ob);
}

 
public int
prevent_enter(object obj)
{
    if (!IS_COINS_OBJECT(obj))
    {
        write("You may only put coins in the " + short() + ".\n");
        return 1;
    }

    return 0;
}

public void
show_list(object for_obj, object *obarr)
{
    int i, price;

    obarr = FILTER_DEAD(obarr);
    obarr = unique_array(obarr, "short", 0);
    obarr = sort_array(obarr, "sort_objects_to_list", TO);

    for_obj->catch_tell(print_shop_list(obarr));
}

/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));

    if (TO->query_prop(CONT_I_ATTACH))
    {
        if (sizeof(obarr) > 0)
        {
            for_obj->catch_tell(capitalize(COMPOSITE_DEAD(obarr)) + 
                (sizeof(obarr) > 1 ? " are" : " is") + " on the " +
                TO->short() + ".\n");
        }
        else
        {
            for_obj->catch_tell("There is nothing in the " + 
                TO->short() + ".\n");
        }
    }
    else if (sizeof(obarr) > 0)
    {
        show_list(for_obj, obarr);
    }
    else
    {
        for_obj->catch_tell(" The " + TO->short() +
            " is empty.\n");
    }
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
    ret = endline + catline;
    prev_categ = "";
    for (j = 0; j < i; j++)
        ret += print_item(list[j]);
    ret += endline;
    return ret;
}


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
        qty = ob[0]->num_heap();

    categ = figure_category(ob[0]);
    price = query_buy_price(ob[0]);
    if (categ != prev_categ)
        ret += blkline;
    prev_categ = categ;
    ret += sprintf(regline, qty, extract(ob[0]->short(), 0, 25));
    return ret;
}
