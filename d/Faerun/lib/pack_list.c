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
    endlin  = "+-------------------------------------------------------------+\n",
    blklin  = "|      |                                          |           |\n",
    catlin  = "| Qty. |  Name                                    | Category  |\n",
    reglin  = "| %4d | %-=40s | %-9s |\n",
    heaplin = "| %4d | %-=40s | %-9s |\n",
    coinlin = "| %4i | %-=40s | %-9s |\n",
    cointlin= "| %-=4s | %-=40s | %-9s |\n",
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
// Weapons
    if(IS_WEAPON_OBJECT(b[0]))
        if(IS_WEAPON_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_WEAPON_OBJECT(a[0]))
             return -1;
// Armours
    if(IS_ARMOUR_OBJECT(b[0]))
        if(IS_ARMOUR_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_ARMOUR_OBJECT(a[0]))
             return -1;
// Arrows
    if(IS_ARROW_OBJECT(b[0]))
        if(IS_ARROW_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_ARROW_OBJECT(a[0]))
             return -1;
// Books
    if(IS_BOOK_OBJECT(b[0]))
        if(IS_BOOK_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_BOOK_OBJECT(a[0]))
             return -1;
// Coins
    if(IS_COINS_OBJECT(b[0]))
        if(IS_COINS_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_COINS_OBJECT(a[0]))
             return -1;
// Containers
    if(IS_CONTAINER_OBJECT(b[0]))
        if(IS_CONTAINER_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_CONTAINER_OBJECT(a[0]))
             return -1;
// Drinks
    if(IS_DRINK_OBJECT(b[0]))
        if(IS_DRINK_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_DRINK_OBJECT(a[0]))
             return -1;
// Foods
    if(IS_FOOD_OBJECT(b[0]))
        if(IS_FOOD_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_FOOD_OBJECT(a[0]))
             return -1;
// Gems
    if(b[0]->query_gem())
        if(a[0]->query_gem())
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(a[0]->query_gem())
             return -1;
// Herbs
    if(IS_HERB_OBJECT(b[0]))
        if(IS_HERB_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_HERB_OBJECT(a[0]))
             return -1;
//Keys
    if(IS_KEY_OBJECT(b[0]))
        if(IS_KEY_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_KEY_OBJECT(a[0]))
             return -1;
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
//Potions
    if(IS_POTION_OBJECT(b[0]))
        if(IS_POTION_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_POTION_OBJECT(a[0]))
             return -1;
// Projectiles
    if(IS_PROJECTILE_OBJECT(b[0]))
        if(IS_PROJECTILE_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_PROJECTILE_OBJECT(a[0]))
             return -1;
// Ropes
    if(IS_ROPE_OBJECT(b[0]))
        if(IS_ROPE_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_ROPE_OBJECT(a[0]))
             return -1;
// Scrolls
    if(IS_SCROLL_OBJECT(b[0]))
        if(IS_SCROLL_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_SCROLL_OBJECT(a[0]))
             return -1;
// Torches and Lights
    if(IS_TORCH_OBJECT(b[0]))
        if(IS_TORCH_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_TORCH_OBJECT(a[0]))
             return -1;
// Wearable Items
    if(IS_WEARABLE_OBJECT(b[0]))
        if(IS_WEARABLE_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_WEARABLE_OBJECT(a[0]))
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
    string short_descr;

    if (IS_WEAPON_OBJECT(ob))
        switch(ob->query_wt())
        {
            case W_SWORD: return "Sword";
            case W_AXE: return "Axe";
            case W_KNIFE: return "Knife";
            case W_CLUB: return "Club";
            case W_POLEARM: return "Polearm";
            case W_MISSILE: return "Missile";
            case W_JAVELIN: return "Javelin";
            default: return "Weapon";
        }
        if(ob->function_exists("create_arrow", ob))
            return "Arrow";

    if (IS_ARMOUR_OBJECT(ob))
    {
        switch(ob->query_at())
        {
            case A_ARMS: return "Arms";
            case A_L_ARM: return "Arms";
            case A_R_ARM: return "Arms";
            case W_LEFT: return "Arms";
            case W_RIGHT: return "Arms";
            case A_BACK: return "Back";
            case A_BODY: return "Torso";
            case A_TORSO: return "Torso";
            case A_FEET: return "Feet";
            case A_L_FOOT: return "Feet";
            case A_R_FOOT: return "Feet";
            case A_EARS: return "Ears";
            case A_L_EAR: return "Ears";
            case A_R_EAR: return "Ears";
            case A_FINGERS: return "Ring";
            case A_ANY_FINGER: return "Ring";
            case A_L_FINGER: return "Ring";
            case A_R_FINGER: return "Ring";
            case A_HANDS: return "Hands";
            case A_L_HAND: return "Hands";
            case A_R_HAND: return "Hands";
            case A_HEAD: return "Helmet";
            case A_LEGS: return "Legs";
            case A_NECK: return "Neck";
            case A_ROBE: return "Robe";
            case A_SHIELD: return "Shield";
            case A_SHOULDERS: "Shoulders";
            case A_L_SHOULDER: "Shoulders";
            case A_R_SHOULDER: "Shoulders";
            case A_WRISTS: return "Wrists";
            case A_L_WRIST: return "Wrists";
            case A_R_WRIST: return "Wrists";
            case A_WAIST: return "Waist";
            case A_L_HIP: return "Hips";
            case A_L_HIP: return "Hips";
            case A_L_ANKLE: return "Ankles";
            case A_R_ANKLE: return "Ankles";

        }
        return "Armour";
    }
    if(IS_LEFTOVER_OBJECT(ob))
        return "Body Part";
    if(IS_HERB_OBJECT(ob))
        return "Herb";
    if(IS_DRINK_OBJECT(ob))
        return "Drink";
    if(IS_FOOD_OBJECT(ob))
        return "Food";
    if(IS_COINS_OBJECT(ob))
        return "Money";
    if (ob->query_gem())
        return "Gem";
    if(ob->id("vial"))
        return "Vial";
    if(IS_POTION_OBJECT(ob))
        return "Potion";

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
    string hqty, htype, hname, hitem;
    string ha, hhuge, hheap, hof;
    int qty, price;

// for coins
    string name,scoin_qty, scoin_type, scoin, sqty;
    object coinz;

    ob -= ({ 0 });
    if (!sizeof(ob))
        return "";
    else if(IS_COINS_OBJECT(ob[0]))
    {
        categ = "Money";
        if (!sizeof(ob))
            return "";
        else
            qty = ob[0]->num_heap();

        coinz = ob [0];
        sscanf(coinz->short(), "%s %s %s",scoin_qty, scoin_type, scoin);
        scoin_type = ob[0]->query_coin_type();

        if(qty == 1)
            scoin_type = scoin_type + " coin";
        else
            scoin_type = scoin_type + " coins";

//        categ = figure_category(ob[0]);
            if (categ != prev_categ)
                ret += blklin;
                ret += sprintf(coinlin, qty, scoin_type, categ);
                prev_categ = categ;
// check qty and print appropriate display
/*        switch(qty)
        {
            case 1..99:
                ret += sprintf(coinlin, qty, scoin_type, categ);
                prev_categ = categ;
                break;
            case 100..299:
                ret += sprintf(cointlin, "some", scoin_type, categ);
                prev_categ = categ;
                break;
            case 300..499:
                ret += sprintf(cointlin, "many", scoin_type, categ);
                prev_categ = categ;
                break;
            case 500..799:
                ret += sprintf(cointlin, "lots", scoin_type, categ);
                prev_categ = categ;
                break;
            case 800..999:
                ret += sprintf(cointlin, "pile", scoin_type, categ);
                prev_categ = categ;
                break;
            case 1000..9999999:
                ret += sprintf(cointlin, "huge", scoin_type, categ);
                prev_categ = categ;
                break;
            default:
                ret += sprintf(cointlin, "****", scoin_type, categ);
                prev_categ = categ;
        }
*/    
        return ret;

    }
    else if((IS_HEAP_OBJECT(ob[0])))
    {
        qty = ob[0]->num_heap();
        hname = ob[0]->singular_short();
        categ = figure_category(ob[0]);

        if (categ != prev_categ)
            ret += blklin;
        ret += sprintf(heaplin, qty, hname, categ);
    }
    else
    {
        qty = sizeof(ob);
        categ = figure_category(ob[0]);
        price = query_buy_price(ob[0]);

        if (categ != prev_categ)
            ret += blklin;
        ret += sprintf(reglin, qty, extract(ob[0]->short(), 0, 50), categ);
    }

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
