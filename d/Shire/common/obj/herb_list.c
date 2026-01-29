/*
 * shop_list.c
 *
 * Written by Quetzl, 9/10/95 for the improvement of the shop 'list' command
 * 
 * Modified by Finwe to remove item values. This is used in packs, 
 * bags, etc and the smiths drop box. 
 *
 * List used excluisvely for herb sacks
 * Expanded columns to accomodate for large herb descrs
 * Adds total number of herbs at end of list
 * -- Finwe, July 2004
 */

inherit "/lib/shop";
#include <filter_funs.h>
#include <herb.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Shire/sys/defs.h"

 
public string figure_category(object ob);
 
static mixed *store_oblist;
int ttl_non_recov = 0; // Number of non-glowing herbs

static string
    f_categ,
    endlin = "+=====================================================================+\n",
    blklin = "|                                                              |      |\n",
    catlin = "| Herbs                                                        | Qty. |\n",
    devlin = "|---------------------------------------------------------------------|\n",
//    reglin = "| %-20s | %4d |\n",
    reglin = "| %-=60s | %4d |\n",
    prev_categ,
    *filarr;
 
static int n_refig = 1;
int total_qty;  // total herbs 

public void
shop_hook_buy_no_buy(object ob, string str)
{
    ::shop_hook_buy_no_buy(ob, str);
    n_refig = 1;
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
string aname = a[0]->query_short ();
string bname = b[0]->query_short ();

//  string aname = a[0]->query_herb_name ();
//  string bname = b[0]->query_herb_name ();
  if (aname < bname) return (-1);
  if (aname > bname) return (1);
  return (0);
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
    if (ob->query_herb_name())
        return ob->query_herb_name();
    else
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
//write ("[print item] " + file_name (ob[0]) + "\n");

    string ret = "";
    string name;
    object herb;
    int qty, price;
    ob -= ({ 0 });
    if (!sizeof(ob))
        return "";
    else
        qty = sizeof(ob);

    // Relies on this_player being set reasonably. Hopefully
    // this is the case when somebody is examining a container.
    herb = ob [0];

    name = (herb->short ());
//    herb_name = herb->query_herb_name ();
//    write (last_name + " " + herb_name + "\n");
//    if (herb_name !=last_name)
//    {

        if (herb->query_herb_name ())
        {
            // name += " (" + (herb->query_herb_name ()) + ")";
            ret += sprintf(reglin, name, qty);
            total_qty = total_qty + qty;
            return ret;
        }
        else
        {
            ret += sprintf(reglin, "* " +name, qty);
        }
//        last_name = herb_name;
//    }


    return ret;
}


/*
 * Function name: reject_herb
 * Description  : Move item to environment
 * Returns      : 1 = success  0 = fail
 */
int
reject_herb(object ob, object env)
{
    if (ob->move(env) == 0) 
    {  
	ttl_non_recov += 1; 
        return 1; 
    } 
    return 0; 
}


/*
 * Function name: check_herb
 * Description  : check to see if herb is recoverable or autoloading
 */
void
check_herb(object ob, object env)
{
    if (ob->check_recoverable()) 
        return;
    if (ob->query_auto_load())
        return;
    else
//        reject_herb(ob, env);
    ttl_non_recov += 1;
}

/*
 * Function name: do_sort
 * Description  : runs inventory through check_lasting.
 */
void count_herbs()
{
    ttl_non_recov = 0;
    map(all_inventory(this_object()), 
        &check_herb(,environment(this_object()))); 
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
    total_qty = 0,
    i = sizeof(list);
    if (!i)
    {
        return "";
    }
    ret = endlin + catlin + devlin;
    prev_categ = "";
    for (j = 0; j < i; j++)
        ret += print_item(list[j]);
// counts recoverable herbs and prints totals
    count_herbs();
    ret += blklin + sprintf( reglin, "Total Herbs", total_qty);

    ret += endlin;
    return ret;
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
        if (arg != "all")
            return shop_hook_list_no_match(arg);
        shop_hook_list_empty_store("");
        return 0;
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
 
/*
 * Function name: do_read
 * Description:   If a player wants to know what instuctions can be
 *                used
 * Arguments:     str - string, hopefully "sign"
 * Returns:       1/0
 */
 
int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (str != "sign")
        return 0;
 
    write(
"You can try these instructions: \n" +
"    buy sword for gold coins    (default: the smallest denomination)\n" +
"    buy sword for gold and get copper back\n" +
"    sell sword for copper coins (default: the largest denomination)\n" +
"    sell all  - will let you sell all items except for items you wield\n" +
"                or wear. Beware that if you have many items to sell,\n" +
"                check whether you have sold all or repeat the command.\n" +
"    sell all! - will let you sell ALL items you have, well at least the\n" +
"                droppable ones, and no coins. (see warning at 'sell all')\n" +
"    sell sword, sell second sword, sell sword 2, sell two swords also\n" +
"                works. Beware, you will never buy more than one item at\n"+
"                a time. So if you really those three expensive swords, you\n" +
"                have to repeat yourself three times.\n" +
"    value     - will value an item you carry before you decide to sell it.\n" +
"    show      - appraise one of the items in stock before you buy it.\n" +
"    list      - will list the items in stock, 'list armour' and 'list\n" +
"                weapon' are valid commands, or e.g. 'list sword'.\n" + 
"                multiple types can be listed as well, e.g. 'list axe,\n" +
"                helmet, general'.\n" + 
"    mlist     - the same as 'list', but using 'more'.\n");
    return 1;
}
 
public void
init_shop()
{
    ::init_shop();
    add_action(do_list, "mlist");
}
