/*
 * Recoverable Auction Rack
 *
 * This rack is used to store the auction items from the auction house
 * Using the recovery library should allow the items to be re-created
 *
 * Created by Britanica, January 2016
 */

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"

inherit "/std/container";
// Step 1. Inherit the Recovery Library
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

private object last_item_added;

public void
create_container()
{
    set_name("rack");
    set_short("auction rack");
    set_long("A large rack used to store items currently under auction.\n");
    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);    
    add_prop(OBJ_M_NO_GET, "The " + short() + " is simply too heavy to "
        + "be taken.\n");    
    
    setuid();
    seteuid(getuid());
    
    if (!IS_CLONE)
    {
        return;
    }
    
    // Step 2. Set the options of whether you want to enable logging or recovery
    set_enable_logging(1);
    set_enable_recovery(1);
    
    // Step 3. Initialize the Database and call recover_objects_from_database
    //         using an alarm.
    init_database();    
    add_column("auction_id");
    set_alarm(0.0, 0.0, &recover_objects_from_database());
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
    {
        return;
    }
    
    last_item_added = ob;
    string auction_id = ob->query_prop("auction_id");
    if (strlen(auction_id))
    {
        // Step 4. Add add_rack_entry to enter_inv
        add_rack_entry(ob);
    }
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
    
    if (to == this_object() || !objectp(to))
    {
        // Not actually leaving this container, just return
        return;
    }
    
    // Step 5. Add remove_rack_entry to leave_inv
    remove_rack_entry(ob);
}

public void
populate_row_entry(object obj, mapping entry)
{
    ::populate_row_entry(obj, entry);
    string auction_id = obj->query_prop("auction_id");
    if (strlen(auction_id))
    {
        entry += (["auction_id" : auction_id]);
    }
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
    write("Post processing.\n");
    if (mappingp(row))
    {
        string auction_id = row["auction_id"];
        write("Row Map auction id " + auction_id + ".\n");
        if (!objectp(obj))
        {
            obj = last_item_added;
        }

        /* The imbuement recoverer recovers an object which will replace itself */
        if (obj->query_prop("_recovered_obj")) {
            obj = obj->query_prop("_recovered_obj");
        }

        int imbuement_missing = obj->query_prop("_imbuement_missing");
        if (strlen(auction_id))
        {
            if (imbuement_missing)
            {
                write("Imbuement missing.\n");
                send_debug_message("item_recovery_lib", "Imbuement missing " + 
                    " cancelling auction " + auction_id + ".", query_log_file());
                    
                AUCTION_HOUSE->cancel_auction(atoi(auction_id));
            }
            else
            {
                write("Master Obj is " + MASTER_OB(obj) + ".\n");
                obj->add_prop("auction_id", auction_id);
                add_rack_entry(obj);
                save_data();
            }
        }
    }
}

public object get_auction_item(string auction_id)
{
    object result = 0;
    foreach(object obj: all_inventory(this_object()))
    {
        if (obj->query_prop("auction_id") == auction_id)
        {
            result = obj;
            break;
        }
    }
    return result;
}

public void add_auction_item(string auction_id, object obj)
{
    obj->add_prop("auction_id", auction_id);
    obj->move(this_object(), 1);
}

/*
 * Function:    query_database_file
 * Description: Mask this function to specify where the data should
 *              be stored.
 */
public string
query_database_file()
{
    return DATA_DIR + "auction_rack_data";
}
