/*
 * Bag to hold gems
 * Finwe, May 2006
 *
 * Cotillion, 2018-12-29
 * - Fixed weight issues
 */

inherit "/d/Faerun/obj/backpack";
inherit "/d/Faerun/lib/box_list";
inherit "/lib/shop";
inherit "/lib/keep";

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <wa_types.h>

#define CARRY_I_WEAR    "_carry_i_wear"
#define PACK_ID   "_faerun_gem_bag_"

public void show_list(object for_obj, object *obarr);
static string
    f_categ,
    endlin = "+=================================================+\n",
    blklin = "|                                                 |\n",
    catlin = "| Gems                                            |\n",
    devlin = "|-------------------------------------------------|\n",
    reglin = "|  %5,i %-=40s |\n",
    prev_categ,
    *filarr;
 
static int n_refig = 1;
int total_qty, cc_qty, ttl_gems;
int purse_worn = 0;   /* 0 = not worn, 1 = worn */

static string coin_type;


void
create_container()
{
    setuid();
    seteuid(getuid());

    set_name("bag");
    add_name(PACK_ID);
    set_adj("black");
    set_adj("leather");
    set_short("black leather bag");
    set_long("@@long_func@@");
    set_slots(A_R_SHOULDER);

    add_prop(OBJ_I_VALUE, 100+random(150));
    add_prop(CONT_I_WEIGHT, 1500);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_MAX_WEIGHT, 19000);
    add_prop(CONT_I_MAX_VOLUME, 19000);

    add_prop(CONT_I_REDUCE_VOLUME, 125);


    add_prop(CONT_I_CLOSED, 1);

//    add_prop(OBJ_M_NO_DROP,1);
//    add_prop(OBJ_I_NO_GIVE,1);
//    add_prop(OBJ_I_NO_STEAL,1);

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
    string long_desc = "This is a " + short() + ". It is made of soft black leather and can be worn on the shoulder. The " + short() + " is large and designed to hold gems.";

    if (query_prop(OBJ_M_NO_SELL))
        long_desc += " Currently, the " + short() + " is protected and cannot be sold. " +
        "This protection may be removed with <unkeep bag>.";
    else
        long_desc += " You may protect this from being sold by doing " +
        "<keep bag>. This does not protect it from being stolen. You " +
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

//    if (!obj->id("_gem_ingredient") || !function_exists("create_gems",obj))

    if (!function_exists("create_gems",obj))
    {
        write("You can only put gems in the " + query_name() + ".\n");
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
    string name,scoin_qty, scoin_type, scoin_temp1, scoin_temp2, scoin_temp3, categ;
    object coinz;
    int qty, price;

    ob -= ({ 0 });
    if (!sizeof(ob))
        return "";
    else
        qty = ob[0]->num_heap();

    coinz = ob [0];

// if num of gems is 1000 or more, strip words 'huge heap of'
    if(qty >= 1000)
        sscanf(coinz->short(), "%s %s %s %s %s",scoin_qty, scoin_temp1, 
            scoin_temp2, scoin_temp3, scoin_type);
    else        
        sscanf(coinz->short(), "%s %s",scoin_qty, scoin_type);

    ret += sprintf(reglin, qty, scoin_type);
    ttl_gems += qty;
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

    ttl_gems = 0;
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
    sprintf("|  Total Gems: %,6i                             |\n",  
        ttl_gems);

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

    int i, price;

    obarr = FILTER_DEAD(obarr);
    obarr = unique_array(obarr, "short", 0);
    obarr = sort_array(obarr, "sort_objects_to_list", this_object());

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


enter_env(object env,object from)
{
    ::enter_env(env, from);                                                
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    this_player()->remove_subloc(PACK_ID);
}

mixed
check_sell()
{
    if (sizeof(all_inventory(TO)))
        return "There are still some gems in the " + short() + "!\n";
    else
        return 0;
}

/*
 * Function name: wear
 * Description  : Called from the armour when worn
 * Arguments    : what - The object worn.
 * Returns      : True if it went ok, a string or -1 otherwise
 */
public mixed
wear(object what)
{

    write("You wear the " + short() + " over your shoulder.\n");
    say(QCTNAME(TP) + " wears " + LANG_ADDART(short()) + "over " + 
        HIS_HER(TP) + " shoulder.\n");
    return 1;
}


/*
 * Function name: remove
 * Description  : Called when the purse is removed
 * Arguments    : what - The object being removed
 * Returns      : False or -1.
 */
public mixed
remove(object what)
{
    if (what != TO)
        return -1;

    return 0;
}
