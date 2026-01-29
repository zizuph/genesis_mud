#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include <files.h>
#include <cmdparse.h>
#include <language.h>

inherit "/std/room";
inherit "/d/Genesis/specials/lib/item_recovery_lib";

#include "../guild.h"
#include "../rack_defs.h"


/* Prototypes */
public int filter_allow_rack(object ob);

public varargs mixed *
query_due_list(mixed player, object item);
public varargs int
resolve_due_list(mixed player, object item, int average = 0);

public int      query_rack_points(mixed player);
public int      remove_rack_points(int value, mixed player);
public int      add_rack_points(int value, mixed player);

public int      set_filter_list(mixed player, string *list);
public mapping  query_filter_list(mixed player);

public string  *query_value_strings();
public string  *query_imbue_stones();
public string   query_equipment_value(object item, object player);
public object  *query_equipment_filter(object player, object *items);

public int      calculate_rack_points(object item, object player);
public int      query_rack_average(object player);


/* Variables */
int gNum;

/*
 * Function name: create_room
 * Description  : Creates a store room
 */
void
create_room()
{
    set_short("The Armory");
    set_long("This area is not reachable by mortals.\n");
    
    set_enable_logging(0);
    set_enable_recovery(1);

    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());
    
    safely_load_master_file(RACK_MANAGER);
}

/*
 * Function:    post_process_recovered_object
 * Description: Allows someone to override this and post process the object
 *              once it's been created (autoload and/or recover)
 * Arguments:   obj - the object that was recovered/loaded
 *              row - the entire row that contains all the data
 */
public void
post_process_recovered_object(object obj, mixed * row)
{
    obj->add_prop(ADDED_TO_ARCHERS_ARMORY, 1);
}

public mixed
query_prop(string prop)
{
    if (member_array(prop, ({CONT_I_REDUCE_WEIGHT,
                             CONT_I_REDUCE_VOLUME})) > -1)
        return 100;
    
    return ::query_prop(prop);
}

public int
query_herbs_limit(mixed player)
{
    player = get_player_name(player);
    return RACK_MANAGER->query_option("herbs_limit", player);
}

public mapping
query_herb_list(mixed player)
{
    player = get_player_name(player);
    return RACK_MANAGER->query_option("herb_list", get_player_name(player));
}

/*
 * Function name: cleanup_loot
 * Description  : This function will clean all loot in the room that was
 *                dropped here. It will only function if no interactive
 *                players are in the room.
 */
void
cleanup_loot()
{
    /* Prevent it from cleaning up loot */
}

/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container to
 *                see if we will allow it in.
 * Arguments:     object ob - the object that is trying to enter.
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int
prevent_enter(object ob)
{
    if (living(ob) && !ob->query_wiz_level())
        return 1;
    
    return 0;
}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (from == this_object())
        return;
    
    string *list, stone;

    if (stone = ob->query_nullstone_type())
    {
        list = RACK_MANAGER->query_option("imbue_stones", "storage_list");
        
        if (!pointerp(list))
            list = ({});
        
        if (member_array(stone, list) < 0)
            list += ({ stone });
    
        RACK_MANAGER->set_option("imbue_stones", "storage_list", list);
    }
    // Step 4. Add add_rack_entry to enter_inv
    add_rack_entry(ob);
}


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    // Not actually leaving this container, just return
    if (to == this_object() || !objectp(to))
        return;
    
    // Step 5. Add remove_rack_entry to leave_inv
    remove_rack_entry(ob);
}

public varargs mixed
query_due_list(mixed player, object item)
{
    mapping list;

    player  = get_player_name(player);
    list    = RACK_MANAGER->query_option("due_list", player);
    
    if (objectp(item) && sizeof(list[master_ob(item)]))
        return list[master_ob(item)];
    
    return list;
}

public varargs int
resolve_due_list(mixed player, object item, int collect = 0)
{
    mapping list;
    mixed  *array;
    
    player  = get_player_name(player);
    list    = RACK_MANAGER->query_option("due_list", player);
    
    if (!mappingp(list))
        list = ([]);
    
    if (m_sizeof(list))
    {
        foreach(string name, mixed *arr: list)
        {
            if (!sizeof(arr) || time() - arr[2] > T_LIMIT)
                m_delkey(list, name);
        }
    }
    
    if (!pointerp(array = list[master_ob(item)]))
        array = ({});
    
    if (!collect)
    {
        if (sizeof(array) && --array[1] < 1)
            m_delkey(list, master_ob(item));
        else
            list[master_ob(item)] = array;
    }
    else
    {
        collect = calculate_rack_points(item, player);
        
        if (sizeof(array) && ++array[1] > 0)
            array[2] = time();
        else
            array = ({ master_ob(item), 1, time(), collect });
        
        list[master_ob(item)] = array;
    }
    
    return RACK_MANAGER->set_option("due_list", player, list);
}

/* Storing Items */

public varargs int
store_herbs(object item, mixed player, int amount = 0)
{
    mapping list;
    string  name;
    int     success, num;
    
    if (!(name = item->query_herb_name()))
        return -4;
    
    if (stringp(player))
        player = find_player(player);
    
    if (!objectp(player))
        return -3;
    
    list = query_herb_list(player);
    
    if (!mappingp(list))
        list = ([]);
        
    if (member_array(name, m_indexes(list)) < 0)
        list[name] = ({ 0, master_ob(item) });
    
    if (!pointerp(list[name]))
        return -2;
    
    if (!(num = query_herbs_limit(player) - list[name][0]) || num < 0)
        return -1;
    
    if (!amount)
        amount = item->heap_size();
        
    num = min(item->heap_size(), (amount > num) ? num : amount);
    
    if (!RACK_MANAGER->set_option("herb_list", player, list))
        return 0;
    
    item->reduce_heap_size(num);
    return num;
}

/*
 *     -3: Reached the allowed herb limit
 *     -2: Not allowed
 *     -1: Failed adding rack points
 *      0: Success.
 */
public varargs int
store_item(object item, mixed player, int amount, int dn = 0)
{
    if ((!objectp(this_player()) || !objectp(player)) &&
        objectp(find_player(player)))
        set_this_player(find_player(player));
        
    /* If the item is a herb, it is removed and added to the manager */
    switch(store_herbs(item, player, amount))
    {
        case -4:
        // Not a herb
            break;
        case -3:
        // DEBUG, No player
            return -2;
        case -2:
        // DEBUG, Database not an array
            return -2;
        case -1:
        // Herb storage is full.
        if (objectp(player) || objectp(this_player()))
        {
            if (query_herbs_limit(player))
                this_player()->catch_msg("There is no more space in your " +
                "herb storage.");
            else
                this_player()->catch_msg("You have not been granted access " +
                "to a personal herbs storage.\n");
        }
            return -3;
        case 0:
        // DEBUG, Failed to add to manager
            return -2;
        default:
        this_player()->catch_msg("You access your personal herb storage.\n");
            return 0;
    }
    
    switch(filter_allow_rack(item))
    {
        case -5:
        // DEBUG, Cannot be dropped or given
            return -2;
        case -4:
        // DEBUG, Cannot be inserted
            return -2;
        case -3:
        // DEBUG, Broken item
            return -2;
        case -2:
        // DEBUG, Worn or wielded
            return -2;
        case -1:
        // DEBUG, Autoloading
            return -2;
        case 0:
        // DEBUG, Kept item
            return -2;
        default:
            break;
    }
    
    if (!dn && add_rack_points(calculate_rack_points(item, player), player))
        return -1;
    
    item->add_prop(ADDED_TO_ARCHERS_ARMORY, 1);
    
    resolve_due_list(player, item);
    
    return item->move(this_object(), 1);
}

/* Collect Items */


/*
public varargs int
handle_herbs(mixed item, mixed player, int store)
{
    mapping list;
    string  name;
    int     num, success;
    
    if (stringp(item) && (store > -1 || !name = item))
        return 1;
    
    if (stringp(player))
        player = find_player(player);
    
    if (!objectp(player))
        return -1;
    
    list = RACK_MANAGER->query_option("herb_list", get_player_name(player));
        
    if (!mappingp(list))
        list = ([]);
        
    if (!list[name])
        list[name] = ({0,""});
    
    if (objectp(item))
        list[name][1] = master_ob(item);
        
    if (!num = query_herbs_limit() - list[name][0] || num < 0)
        return -2;
    
    if (store > -1)
        num = (item->heap_size() > num) ? num : item->heap_size();
    else
        num = list[name][0];
    
    list[name][0] += (num * store);
        
    if (success = RACK_MANAGER->set_option("herb_list", player, list))
    {
        if (objectp(item))
        {
            item->reduce_heap_size(num);
        }
        else
        {
            item = clone_object(list[name][1]);
            item->move(player, 1);
            item->set_heap_size(num);
        }
    }
    return success;
}*/

/*     -2: No herb in storage
 *     -1: Failed removing rack points
 *      0: Success.
 *      1: To heavy for destination.
 *      2: Can't be dropped.
 *      3: Can't take it out of it's container.
 *      4: The object can't be inserted into bags etc.
 *      5: The destination doesn't allow insertions of objects.
 *      6: The object can't be picked up.
 *      7: Other (Error message printed inside move() func)
 *      8: Too big volume for destination
 *      9: The container is closed, can't remove
 *     10: The container is closed, can't put object there 
 */
public int
collect_item(object item, object player)
{
    //if (collect_herbs()
    /* Check rack_points && Add calculations */
    if (remove_rack_points(calculate_rack_points(item, player), player))
        return -1;
    
    resolve_due_list(player, item, 1);
    
    return item->move(player);
}

/*
 * Function name: filter_allow_rack
 * Description  : Filter out any items that cannot be dropped, given etc
 * Arguments    : ob - the object to check
 * Returns      :   -5: Failed: Cannot be dropped or given
 *                  -4: Failed: Cannot be inserted
 *                  -3: Failed: Broken item
 *                  -2: Failed: Worn or wielded
 *                  -1: Failed: Autoloading
 *                   0: Failed: Kept item
 *                   1: Success
 */
public int
filter_allow_rack(object ob)
{
    // Check for the various properties
    if (ob->query_prop(OBJ_M_NO_DROP) ||
        ob->query_prop(OBJ_M_NO_GIVE))
        return -5;
        
    if (ob->query_prop(OBJ_M_NO_INS))
        return -4;
    
    if (ob->query_prop(OBJ_I_BROKEN))
        return -3;
    
    if (ob->query_worn() || ob->query_wielded())
        return -2;
    
    if (ob->query_auto_load())
        return -1;
    
    if (ob->query_keep())
        return 0;

    return 1;
}

/* Listing Items */

public int
set_filter_list(mixed player, mapping list)
{
    player = get_player_name(player);
    return RACK_MANAGER->set_option("filter_list", player, list);
}

public mapping
query_filter_list(mixed player)
{
    mapping list;
    player = get_player_name(player);
    
    if (list = RACK_MANAGER->query_option("filter_list", player))
        return list;
    
    return ([]);
}

public object *
query_equipment_filter(object player, object *items)
{
    object *item_list = ({});
    mapping filters;
    /* Add function that checks for allowed layman member */
   // if (player->query_guild_name_occ() != GUILD_NAME)
   //     return items;
    
    filters = query_filter_list(player);
    /* Remove filtered items */
    foreach(object item: items)
    {
        if (member_array(master_ob(item), filters["prime_filter"]) > -1)
        {
            item_list += ({ item });
            continue;
        }
        
        if (member_array(query_equipment_value(item, player),
            filters["price_filter"]) < 0)
        {
            item_list += ({ item });
        }
        
        if (member_array(master_ob(item), filters["scrap_filter"]) > -1 &&
            member_array(item, item_list) > -1)
        {
            item_list -= ({ item });
        }
        
        if (stringp(item->query_nullstone_type()) &&
            member_array(item->query_nullstone_type(),
            RACK_MANAGER->query_option("imbue_stones", "storage_list")) > -1 &&
            member_array(item->query_nullstone_type(),
            filters["imbue_filters"]) < 0)
        {
            item_list += ({ item });
        }
    }
    
    return item_list;
}

public string *
query_imbue_stones()
{
    return RACK_MANAGER->query_option("imbue_stones", "storage_list");
}

public string *
query_value_strings()
{
    return ({   "free", "cheap", "low",
                "medium", "high", "steep",
                "stiff", "absurd"   });
}

public string
query_equipment_value(object item, object player)
{
    string value, *values;
    
    values = query_value_strings();
    
    switch(calculate_rack_points(item, player))
    {
        case 0:
        value = values[0];
            break;
        case 1..1000:
        value = values[1];
            break;
        case 1001..3000:
        value = values[2];
            break;
        case 3001..5000:
        value = values[3];
            break;
        case 5001..6000:
        value = values[4];
            break;
        case 6001..8000:
        value = values[5];
            break;
        case 8001..10000:
        value = values[6];
            break;
        default:
        value = values[7];
            break;
    }
    
    return value;
}

/* Value System */
public int
add_rack_points(int value, mixed player)
{
    if (!strlen(player = get_player_name(player)))
        return -3;
    
    if (value < 0)
        return -2;
    
    if (RACK_MANAGER->query_option("rack_points", player))
        value += RACK_MANAGER->query_option("rack_points", player);
    
    if (!RACK_MANAGER->set_option("rack_points", player, value))
        return -1;
    
    return 0;
}

public int
remove_rack_points(int value, mixed player)
{
    if (!strlen(player = get_player_name(player)))
        return -3;
    
    if (value < 0)
        return -2;
    
    if (RACK_MANAGER->query_option("rack_points", player))
        value = RACK_MANAGER->query_option("rack_points", player) - value;
    
    if (value < 0)
        return -1;
    
    if (!RACK_MANAGER->set_option("rack_points", player, value))
        return 1;
    
    return 0;
}

public int
query_rack_points(mixed player)
{
    if (!strlen(player = get_player_name(player)))
        return 0;
    
    return RACK_MANAGER->query_option("rack_points", player);
}

public int
query_rack_condition(object item)
{
    int dull, corr, condition;
    
    if (is_armour(item))
    {
        dull = item->query_condition();
        corr = item->query_repair();
        
        condition = dull - corr;
    }
    
    if (is_weapon(item))
    {
        dull = item->query_dull() - item->query_repair_dull();
        corr = item->query_corroded() - item->query_repair_corr();
        
        condition = dull + corr / 2;
    }
    
    return condition;
}

public int
calculate_rack_points(object item, object player)
{
    int     value, rack_avg, cost, points;
    object *inside;
    mixed  *due_list;
    
    if (is_weapon(item))
        value = item->query_hit() * item->query_pen();
    else if (is_armour(item))
        value = item->query_ac() * item->query_ac();
    
    /* Need to add an imbue modifier */
    
    /* If it has no value yet, its a free item */
    if (!value)
        return 0;
    
    /* Get the players rack average, minimum 10 */
    rack_avg = max(10, query_rack_average(player));
    /* Get the number of same items in the store */
    inside   = filter(deep_inventory(this_object()),
               &operator(==)(,master_ob(item)) @ &master_ob());
    
    points = (100 * value) / rack_avg;
    
    /* Cost modifier */
    if (calling_function(-1) == "store_item")
    {
        /* Save original points value */
        cost    = points;
        /* Reduce the reward of donating an item based on avg */
        points  = (points * 100) / ((70 - rack_avg) + 100);
        /* Reduce the reward based on number of same items */
        points -= (points * (sizeof(inside) / 5));
        
        /* Check for restoring the original cost of a withdrawn item */
        if (pointerp(due_list = query_due_list(player, item)) && due_list[3])
            points = min(cost, due_list[3]);
    }
    
    /* Modify based on the items condition */
    points -= ((points / 7) * min(7, (query_rack_condition(item))));
    
    /* Return the value, pointlessly maxed */
    return max(0, points);
}

public int
query_rack_average(mixed player)
{
    player = get_player_name(player);
    /* Either defined elsewhere or here.. not yet decided */
    return RACK_MANAGER->query_option("rack_avg", player);
}