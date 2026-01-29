/*
 * shop_list.c
 *
 * Written by Quetzl, 9/10/95 for the improvement of the shop 'list' command
 *
 * Modified by Finwe to remove item values. This is used in packs,
 * bags, etc and the smiths drop box.
 *
 * Palmer - 05-March-2004 Removed 20 spaces per line that someone added
 *          and didn't mention here in the ChangeLog. *poke*
 */

inherit "/lib/shop";
#include <wa_types.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <composite.h>
#include <config.h>
#include <files.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>


public string figure_category(object ob);

static mixed *store_oblist;
static string
    f_categ,
    endlin  = "+--------------------------------------------+\n",
    blklin  = "|                                            |\n",
    catlin  = "| Qty. |  Body Part                          |\n",
//    reglin  = "| %4d | %-=33s|\n ",
    heaplinl = "| %4d | %-=35s |\n",
    heaplinr = "| %4d | %-=35s |\n",
heaplin = "%4d %-=40s",
    prev_categ,
    *filarr;
int prev_qty;
string prev_hname;

static int n_refig = 1;
/* keeps track of which column to print 0 = left, 1 = right */
int left_or_right = 0;


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
// Body Parts and Leftovers
    if(IS_LEFTOVER_OBJECT(b[0]))
        if(IS_LEFTOVER_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_LEFTOVER_OBJECT(a[0]))
             return -1;
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
    string short_descr;

    if (ob->query_organ())
    {
        switch(ob->query_organ())
        {
            case "ear": return "Ears";
            case "eye": return "Eyes";
            case "heart": return "Hearts";
            case "horn": return "Horns";
            case "intestine": return "Intestines";
            case "kidney": return "Kidneys";
            case "kneecap": return "Kneecaps";
            case "nail": return "Nails";
            case "nose": return "Noses";
            case "rib": return "Ribs";
            case "scalp": return "Scalps";
            case "skull": return "Skulls";
            case "thighbone": return "Thighbones";
            case "tooth": return "Teeth";
            default: return "Misc";
        }
    }
    return "Leftover";
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
    string hqty, htype, hname, hitem;
    string ha, hhuge, hheap, hof;
    int qty, price;

// for coins
    string name,scoin_qty, scoin_type, scoin, sqty;
    object coinz;


    ob -= ({ 0 });
    if (!sizeof(ob))
        return "";
//    else if((IS_HEAP_OBJECT(ob[0])))
//    {
    qty = ob[0]->num_heap();
    hname = ob[0]->short();
    categ = figure_category(ob[0]);
//
        if (categ != prev_categ)
        {            
            left_or_right = 1;
            ret += blklin;
            ret +=sprintf(heaplinl, qty, hname);

        }
        else
        {
            if(left_or_right == 0)
            {
                ret += sprintf(heaplinl, qty, hname);
                left_or_right = 1;
            }
            else if(left_or_right == 1)
            {
                ret += sprintf(heaplinr, qty, hname);
                left_or_right = 0;
            }
        }

//            ret += sprintf(heaplin, qty, hname, categ);
//            ret += sprintf(heaplin, extract(ob[0]->short(), 0, 50), categ, hqty);
//        }
//    else
//    {
//        qty = sizeof(ob);
//        categ = figure_category(ob[0]);
//
//        if (categ != prev_categ)
//        {
//            left_or_right = 0;
//            ret += blklin;
//        }
//        else
//        {
//            if(left_or_right == 0)
//            {
//                ret += sprintf(reglinl, qty, extract(ob[0]->short(), 0, 50), categ);
//                left_or_right = 1;
//            }
//            else
//            {
//                ret += sprintf(reglinr, qty, extract(ob[0]->short(), 0, 50), categ);
//                left_or_right = 0;
//            }
//        }
//
//    }

    prev_categ = categ;
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
// print header and first line
    ret = endlin + catlin;
//    ret += print_item(list[0]);
//    left_or_right = 1;
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
//
//    if (query_verb() == "mlist")
//    {
//        setuid();
//        seteuid(getuid());
//        clone_object("/std/board/board_more")->more(print_shop_list(oblist));
//        return 1;
//    }
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
}
