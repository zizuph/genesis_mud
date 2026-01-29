/*
 * shop_list.c
 *
 * Written by Quetzl, 9/10/95 for the improvment of the shop 'list' command
 *
 * Modified for use in Palanthas with permission by Gorboth.
 *
 * Mortis 06.2006
 *
 */

inherit "/lib/shop";
#include <wa_types.h>
#include <filter_funs.h>
 
public string figure_category(object ob);
 
static mixed *store_oblist;
static string
    f_categ,
    endlin = "+-----------------------------------------------------------------------------+\n",
    blklin = "|                                             |         |     |               |\n",
    catlin = "|                    Item                     |   Item  |     | Cost in Coins |\n"
           + "|                    Name                     |   Type  | Qty |   P  G  S  C  |\n"
           + "+-----------------------------------------------------------------------------+\n",
    reglin = "| %-42s  | %-7s | %3d | %3d %2d %2d %2d  |\n",
    prev_categ,

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
 * Function name: sort_objects_to_list
 * Description:   Sort the list of objects through sort_array
 * Arguments:     a, b - arrays of identical objects
 * Returns:       1 if a after b, else -1
 */
 
public int
sort_objects_to_list(object *a, object *b)
{
    if (b[0]->check_weapon())
        if (a[0]->check_weapon())
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if (a[0]->check_weapon())
            return -1;
    if (b[0]->check_armour())
        if (a[0]->check_armour())
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if (a[0]->check_armour())
            return -1;
    if (a[0]->short() < b[0]->short()) return -1;
    return 1;
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
    if (ob->check_weapon())
        switch(ob->query_wt())
        {
            case W_SWORD: return "Sword";
             case W_SWORD: return "Sword";
            case W_AXE: return "Axe";
            case W_KNIFE: return "Knife";
            case W_CLUB: return "Club";
            case W_POLEARM: return "Polearm";
            case W_MISSILE: return "Missile";
            case W_JAVELIN: return "Javelin";
            default: return "Weapon";
        }
    if (ob->check_armour())
    {
        val = ob->query_at();
        if (val == A_SHIELD) return "Shield";
        if (val & A_HANDS) return "Gloves";
        if (val == A_HEAD) return "Helmet";
        if (val & A_FINGERS) return "Ring";
        if (val & A_FEET) return "Boots";
        if (val & A_LEGS) return "Legs";
        if (val & A_ARMS) return "Arms";
        return "Armour";
    }
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
    string ret = "";
    string categ;
    int qty, price;
    ob -= ({ 0 });
    if (!sizeof(ob))
        return "";
    else
        qty = sizeof(ob);
    categ = figure_category(ob[0]);
    price = query_buy_price(ob[0]);
    if (categ != prev_categ)
        ret += blklin;
    prev_categ = categ;
    ret += sprintf(reglin, extract(ob[0]->short(), 0, 41), categ, qty,
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
    prev_categ = "";
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
 
public void
init_shop()
{
    ::init_shop();
    add_action(do_list, "mlist");
}
