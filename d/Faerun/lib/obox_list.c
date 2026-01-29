/*
 * shop_list.c
 *
 * Written by Quetzl, 9/10/95 for the improvement of the shop 'list' command
 *
 * Modified by Finwe to remove item values. This is used in packs,
 * bags, etc.
 *
 * Copied from Shire by Finwe, May 2006
 *
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
    endlin = "+---------------------------------------------------------------+\n",
    blklin = "|                                                               |\n",
    catlin = "|  Body Part                                                    |\n" + 
             "+---------------------------------------------------------------+\n",
    reglin = "| %-=30s %-=30s |\n",
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
    if (b[0]->query_organ())
        if (a[0]->query_organ())
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->query_race() < b[0]->query_race()) return -1;
            return 1;
        }
        else
            return 1;

    if (a[0]->query_race() < b[0]->query_race()) return -1;
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
    setuid();
    seteuid(getuid());
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
        return "Leftover";
    }
}

/*
 * Function name: print_item
 * Description:   Format a listing of *ob
 * Arguments:     *ob - an array of identical objects
 * Returns:       A string describing the objects, for use in listing
 */

public string
print_item(object *ob, object *ob2)
{
    string ret = "";
    string categ;
    string categ2;
    string seperator = "";
    string *item = ({ "" , ""});
    int qty, price, categLen;
    int numOfItems = 1;

    //    ob -= ({ 0 });
    // ob2 -= ({ 0 });
    if (!sizeof(ob))
        return "";

//        qty = sizeof(ob);
    
    item[0] = extract(ob[0]->short(), 0, 40);
    if(ob2)
    {
	item[1] = extract(ob2[0]->short(), 0, 40);
    }

    if(item[1] != "")
    {
	numOfItems = 2;
    }
    
    categ = figure_category(ob[0]);
    price = query_buy_price(ob[0]);

    if (categ != prev_categ)
    {
	ret += blklin;
	ret += "| " + categ;

	categLen = strlen(categ);
	for(int x = 0; x < 60 - 3 - categLen; x++)
	{
	    ret += " ";
	}
	ret += "     |\n";
	ret += "| ";

	for(int i = 0; i < categLen; i++)
	{
	    ret += sprintf("-");
	}
	for(int x = 0; x < 60 - 3 - categLen; x++)
	{
	    ret += " ";
	}
	ret += "     |\n";
    }
    prev_categ = categ;

    if(numOfItems == 2)
    {
	categ2 = figure_category(ob2[0]);
	price = query_buy_price(ob2[0]);
	
	if (categ2 != prev_categ)
	{
	    if(categ != categ2)
	    {

	    }
	    ret += blklin;
	    ret += "| " + categ2;
	    categLen = strlen(categ2);
	    for(int x = 0; x< 60 - 3 - categLen; x++)
	    {
		ret += " ";
	    }
	    ret += "|\n";
	    ret += "| ";
	    for(int i = 0; i < categLen; i++)
	    {
		ret += sprintf("-");
	    }
	    for(int x = 0; x < 60 - 3 - categLen; x++)
	    {
		ret += " ";
	    }
	    ret += "|\n";
	}
	prev_categ = categ2;
	ret += sprintf(reglin, item[0], item[1]);
    }
    else
    {
	ret += sprintf(reglin, item[0], "");
    }
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
    for (j = 0; j < i/2; j = j + 2)
    {
	if(figure_category(list[j][0]) == figure_category(list[j+1][0]))
	{
	    ret += print_item(list[j], list[j+1]);
	}
	else
	{
	    ret += print_item(list[j], 0);
	    j = j -1;
	}
    }

    if(j+1 < i)
    {
	ret += print_item(list[j+1], 0);
    }
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


