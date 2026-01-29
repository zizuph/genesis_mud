/*
 * coin bag for Drow
 * -- Finwe, April 2002
 * -- Fixed, Finwe, May 2006
 */

inherit "/d/Faerun/obj/backpack";
inherit "/d/Faerun/lib/box_list";
inherit "/lib/shop";
inherit "/lib/keep";

#include "/d/Faerun/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <wa_types.h>

#define PURSE_I_WEAR    "_purse_i_wear"
#define PACK_ID   "_drow_money_bag_"

public void show_list(object for_obj, object *obarr);
static string
    f_categ,
    endlin = "+=================================+\n",
    blklin = "|                                 |\n",
    catlin = "| Coins                           |\n",
    devlin = "|---------------------------------|\n",
    reglin = "|  %4i %-=25s |\n",
    prev_categ,
    *filarr;
 
static int n_refig = 1;
int total_qty, cc_qty;
int purse_worn = 0;   /* 0 = not worn, 1 = worn */

static string coin_type;


void
create_container()
{
    setuid();
    seteuid(getuid());

    set_name("bag");
    add_name(PACK_ID);
    set_adj("silk");
    set_short("large silk bag");
    set_long("@@long_func@@");
    set_slots(A_L_SHOULDER);

    add_prop(OBJ_I_VALUE, 100+random(150));
    add_prop(CONT_I_WEIGHT, 7000);
    add_prop(CONT_I_VOLUME, 7000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(CONT_I_CLOSED,     0);


}

/*


/* Function name: short_func
 * Description  : Returns a string for the short description depending
 *                on whether or not there are herbs in the pouch.
 * Returns      : string description
 */
string
short_func()
{
//    if (sizeof(all_inventory(TO)))
//        return "leather purse containing some coins";

    return short();
}

/* Function name: long_func
 * Description  : Returns a string for the long description depending
 *                on whether or not the pouch is tied to your belt.
 * Returns      : string description
 */
public string
long_func()
{
    string long_desc = "This is a " + short() + " to hold coins. It is " +
        "made from silk threads and is very soft. It is a gift from the " +
        "deities of the Drow and very valuable. ";

    if (query_prop(OBJ_M_NO_SELL))
        long_desc += " At present, the purse is protected from being sold. " +
        "You may remove this protection by doing <unkeep purse>.";
    else
        long_desc += " You may protect this from being sold by doing " +
        "<keep purse>. This does not protect it from being stolen. You " +
        "will have to wear the " + short() + " to protect it from thieves " +
        "and cutthroats.";
    return (long_desc + "\n");
}

/* Function name: prevent_enter
 * Description  : Checks that it is an herb.
 * Arguments    : object obj - the object entering
 * Returns      : 1 if it is not an herb, 0 if it is
 */
public int
prevent_enter(object obj)
{

    if (!IS_COINS_OBJECT(obj) && !obj->id("_sybarun_token"))
    {
        write("You can only put coins in the " + query_name() + ".\n");
        return 1;
    }

    return 0;

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
    string name,scoin_qty, scoin_type,categ;
    object coinz;
    int qty, price;

    ob -= ({ 0 });
    if (!sizeof(ob))
        return "";
    else
        qty = ob[0]->num_heap();

    coinz = ob [0];

    sscanf(coinz->short(), "%s %s",scoin_qty, scoin_type);
/*
    if(qty == 1)
        name = scoin_type + " coin";
    else
        name = scoin_type + " coins";
*/

    ret += sprintf(reglin, qty, scoin_type);

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
    ret = endlin + catlin + devlin;
    prev_categ = "";
    for (j = 0; j < i; j++)
        ret += print_item(list[j]);
    ret += blklin + 
            "| Total Value of Coins:           |\n" + 
    sprintf("|  %,4i platinum                  |\n" +
            "|    %2i gold                      |\n" +
            "|    %2i silver                    |\n" +
            "|    %2i copper                    |\n",  
        TOTAL_MONEY(TO) / 1728, 
       (TOTAL_MONEY(TO) % 1728) / 144, 
       (TOTAL_MONEY(TO) % 144) / 12, 
        TOTAL_MONEY(TO) % 12);

    ret += endlin;
    return ret;
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
//for_obj->catch_tell ("[describe contents]\n");

    for_obj->catch_tell(show_sublocs(for_obj));

    if (this_object()->query_prop(CONT_I_ATTACH))
    {
        if (sizeof(obarr) > 0)
        {
            for_obj->catch_tell(capitalize(COMPOSITE_DEAD(obarr)) + 
                (sizeof(obarr) > 1 ? " are" : " is") + " on the " +
                this_object()->short() + ".\n");
        }
        else
        {
            for_obj->catch_tell("There is nothing on the " + 
                this_object()->short() + ".\n");
        }
    }
    else if (sizeof(obarr) > 0)
    {
        show_list(for_obj, obarr);
    }
    else
    {
        for_obj->catch_tell("  " + "The " + this_object()->short() +
            " is empty.\n");
    }
}

public void
show_list(object for_obj, object *obarr)
{
//for_obj->catch_tell ("[show list]\n");

    int i, price;

//for_obj->catch_tell ("[show list] filter dead\n");
    obarr = FILTER_DEAD(obarr);
//for_obj->catch_tell ("[show list] unique array\n");
    obarr = unique_array(obarr, "short", 0);
//for_obj->catch_tell ("[show list] sort array\n");
    obarr = sort_array(obarr, "sort_objects_to_list", this_object());
    // obarr = filter(obarr, query_id_herb);
//for_obj->catch_tell ("[show list] print shop list\n");
    for_obj->catch_tell(print_shop_list(obarr));
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

enter_env(object dest,object old)
{
  remove_name(PACK_ID);
  if(present(PACK_ID,E(TO)))
    {
      return;
    }

  add_name(PACK_ID);
  if(living(E(TO)))
    dest->add_subloc(PACK_ID, this_object());
}

public void
leave_env(object from, object to)
{
    ::leave_env();
}


init()
{
    ::init();
}

mixed
check_sell()
{
    if (sizeof(all_inventory(TO)))
        return "There are still some coins in the " + short() + "!\n";
    else
        return 0;
}

