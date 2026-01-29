/*
 * shop_list.c
 *
 * Written by Quetzl, 9/10/95 for the improvment of the shop 'list' command
 *
 * 2005/07/09 Last update
 * 2011/07/21 Lavellan - Fixed to display qty and desc/price for single item
 */

inherit "/lib/shop";
#include <wa_types.h>
#include <filter_funs.h>
 
static mixed *store_oblist;
static string
    f_categ,
    endlin = "+-----------------------------------------------------------+\n",
    blklin = "|     |                                |                    |\n",
    catlin = "| Qty |           Gem Name             |     P   G  S  C    |\n",
    reglin = "|%4d | %-30s | %6d %2d %2d %2d    |\n",
    *filarr;
 
static int n_refig = 1;
 
 
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
 * Function name: print_item
 * Description:   Format a listing of *ob
 * Arguments:     *ob - an array of identical objects
 * Returns:       A string describing the objects, for use in listing
 */
 
public string
print_item(object *ob)
{
    string ret = "";
//    string categ;
    int qty, price;
    ob -= ({ 0 });
    if (!sizeof(ob))
        return "";
    else
        qty = sizeof(ob);
    price = query_buy_price(ob[0]) / ob[0]->num_heap();
    ret += sprintf(reglin, ob[0]->num_heap(),
        extract(ob[0]->singular_short(), 0, 40),
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
    ret += blklin;
//    prev_categ = "";
    for (j = 0; j < i; j++)
        ret += print_item(list[j]);
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
