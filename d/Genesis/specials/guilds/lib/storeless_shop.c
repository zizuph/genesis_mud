/*
 * Generic Storeless Shop
 *
 * This storeless shop will automatically handle things like generating and tracking
 * the contents of the store from a stored map. Keeping track of thousands of 
 * objects in memory is wasteful.
 * Instead, this storeless shop will allow one to filter the list, and when
 * purchasing objects, will actually clone the object from a map and give it to the
 * player.
 *
 * Created by Petros, May 2010
 */
#pragma strict_types;

#include <filter_funs.h>
#include <macros.h>
#include <language.h>
#include <files.h>

// inherit "/w/petros/shop";
inherit "/lib/shop";
inherit "/d/Genesis/specials/guilds/lib/storeless_shop_support";

/*
 * Function:    do_list
 * Description: Lists requested objects in the store
 */
public int
do_list(string arg)
{
    object * matching_objects = ({ });
    if (!strlen(arg) || arg == "all")
    {
        // That means we want all objects
        foreach (string filename, mixed data : object_list)
        {
            object current_object;
            if (objectp(current_object = safely_load_master_file(filename)))
            {
                matching_objects += ({ current_object });
            }
        }
    }
    else
    {
        // Try to match the objects based on the input
        matching_objects = find_objects_using_name(arg);
    }

    if (!sizeof(matching_objects))
    {
        shop_hook_list_empty_store("");
        return 0;
    }

    object * herb_objects = FILTER_HERB_OBJECTS(matching_objects);
    object * other_objects = matching_objects - herb_objects;
    this_player()->more(
        print_herb_list(herb_objects)
      + print_object_list(other_objects));    
    return 1; 
}

/*
 * Function:    hook_buy_only_herbs
 * Description: Use notify_fail to send a message telling the player
 *              that this shop only allows herbs to be sold.
 * Argument:    ob - the object that the player tried to sell.
 */
public void
hook_buy_only_herbs(object ob)
{
    notify_fail("This is an herb shop that only buys herbs.\n");
}

/*
 * Function name: shop_hook_allow_sell
 * Description:   If you want to do more testing on objects the player intend
 *                to sell.
 * Argument:      ob - The object player wants to sell
 * Returns:       1 if we allow player to sell the object (default)
 */
public int
shop_hook_allow_sell(object ob)
{
    if (!objectp(ob) || !IS_HERB_OBJECT(ob))
    {
        hook_buy_only_herbs(ob);
        return 0;
    }
    return 1;
}

/*
 * Function:    query_store_room
 * Desrciption: Returns the store room for storeless shops, which is just the
 *              VOID_OBJECT (/obj/void)
 */
public string
query_store_room()
{
    return VOID_OBJECT;
}

/*
 * Function name: query_object_value
 * Desrciption:   What the object is worth. Allows shops to mask and
 *                value objects differently. Specifically useful for
 *                allowing herb shops, since herbs can normally not
 *                be sold in regular shops.
 */
int
query_object_value(object ob)
{
    if (IS_HERB_OBJECT(ob))
    {
        return ob->query_herb_value() * ob->num_heap();
    }
    return ::query_object_value(ob);
}

/*
 * Function:    query_max_buy
 * Description: Returns how many objects can be bought in one
 *              transaction.
 */
public int 
query_max_buy()  
{ 
    return 20;
}

/*
 * Function:    query_max_sell
 * Description: Returns how many objects can be sold in one
 *              transaction
 */
public int 
query_max_sell() 
{ 
    return 20; 
}

/*
 * Function name: find_str_in_object
 * Description:   Maskable function that by default calls the macro
 *                FIND_STR_IN_OBJECT. Allows a shop to define its own
 *                mechanism for how to get objects from the storeroom.
 */
public object *
find_str_in_object(string str, object obj)
{
    if (MASTER_OB(obj) != query_store_room())
    {
        return ::find_str_in_object(str, obj);
    }

    return clone_object_quantity_from_store(str);
}

/*
 * Function name: buy_it
 * Description:   Try to let the player buy the item array
 * Arguments:     ob - the object array
 *                str2 - string describing how the money should be paid
 *                str3 - what coin types to get chainge back in
 * Returns:       1 on sucess
 */
object *
buy_it(object *ob, string str2, string str3) 
{
    object * purchased_items = ::buy_it(ob, str2, str3);
    object * unpurchased_items = ob - purchased_items;
    unpurchased_items->remove_object(); // remove the unpurchased objects
    foreach (object purchased_item : purchased_items)
    {
        string master_filename = MASTER_OB(purchased_item);
        int stock_quantity = query_object_quantity(purchased_item);
        if (IS_HEAP_OBJECT(purchased_item))
        {
            update_object_entry(master_filename, stock_quantity - purchased_item->num_heap());
        }
        else
        {
            update_object_entry(master_filename, stock_quantity - 1);        
        }
    }
    
    return purchased_items;    
}

/*
 * Function:    remove_sold_objects
 * Description: Calls remove_object on all the objects in the argument. This is
 *              called in an alarm inside of sell_it to get rid of objects that
 *              have been sold.
 */
public void
remove_sold_objects(object * objects_sold)
{
    if (sizeof(objects_sold))
    {
        objects_sold->remove_object();
    }
}

/*
 * Function name: sell_it
 * Description:   Try to let the player sell the item array
 * Arguments:     ob - the object array
 *                check - wheather check for worn or wielded stuff
 *                str - string describing how the money should be paid
 * Returns:	  An array with the objects sold
 */
public object *
sell_it(object *ob, string str, int check) 
{
    object * objects_sold = ::sell_it(ob, str, check);
        
    // Update the entries in the object list
    foreach (object object_sold : objects_sold)
    {
        string master_filename = MASTER_OB(object_sold);
        int stock_quantity = query_object_quantity(object_sold);
        if (IS_HEAP_OBJECT(object_sold))
        {
            update_object_entry(master_filename, stock_quantity + object_sold->num_heap());
        }
        else
        {
            update_object_entry(master_filename, stock_quantity + 1);
        }
    }
    
    set_alarm(0.0, 0.0, &remove_sold_objects(objects_sold));
    
    return objects_sold;
}

/*
 * Function name: shop_hook_value_store
 * Description:   Player values object in store
 * Arguments:     ob   - The object 
 *		  text - The value in text form
 */
void
shop_hook_value_store(object ob, string text)
{
    ::shop_hook_value_store(ob, text);

    // We need to remove the object after it's been valued because these
    // are "virtual" objects that get cloned for specific purposes.    
    ob->remove_object();
}

/*
 * Function name: init_shop
 * Description  : This function is called for each living that enters the
 *                room. It adds the necessary commands to the players.
 *                You should call this from the init() function in your
 *                room.
 */
public void
init_shop()
{
    ::init_shop();
    load_object_data();
}
