/* 
 * Autosave Rack Master
 *  
 * This master object keeps track of all the saving racks in the game.
 * During Armageddon, it will be called by the domain_link to update
 * all the saving racks go into "Armageddon" mode. This mode will
 * ensure that non-glowing/non-saving items last beyond Armageddon.
 *
 * Created by Petros, October 2010
 */
#pragma strict_types
#pragma save_binary

#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <filepath.h>
#include <files.h>

inherit "/d/Genesis/specials/lib/database_lib";

/*
 * Function:    query_database_file
 * Description: Mask this function to specify where the data should
 *              be stored.
 */
public string
query_database_file()
{
    return MASTER_OB(this_object()) + "_data";
}

public void
create()
{
    setuid();
    seteuid(getuid());
    
    ::init_database();
        
    add_column("instance"); // actual object in rack
}

/*
 * Function:    is_valid_saving_rack
 * Description: A function used to determine whether the item being
 *              entered is a valid saving rack.
 */
public int
is_valid_saving_rack(object obj)
{
    if (!objectp(obj))
    {
        return 0;
    }
   
    if (!IN_ARRAY("/d/Genesis/specials/lib/item_recovery_lib.c",
                  inherit_list(obj)))
    {
        return 0;
    }
        
    return 1;
}

/*
 * Function:    add_saving_rack_entry
 * Description: This adds the entry for the object into the database
 */
public int
add_saving_rack_entry(object obj)
{
    if (!is_valid_saving_rack(obj))
    {
        // Can't add an invalid object
        return 0;
    }    
        
    string file = MASTER_OB(obj);
    
    send_debug_message("autosave_rack_master", 
        "Adding entry for " + file);
    return add_or_update_row( ([ 
                "instance"      : obj,
                ]) );    
}

/*
 * Function:    notify_all_saving_racks
 * Description: This gets called during Armageddon by the domain_link
 *              so that all the saving racks in the realm will get
 *              notified to update their racks accordingly.
 */
public void
notify_all_saving_racks()
{
    mixed * valid_rows = ({ });
    foreach (mixed row : m_rows)
    {
        if (!objectp(row["instance"]))
        {
            continue;
        }
        valid_rows += ({ row });
        object current_rack = row["instance"];
        current_rack->check_for_armageddon();
    }
    
    // We save only the valid rows back to the database. It's the
    // way that we clean up old data from racks that no longer
    // exist in the game.
    m_rows = valid_rows;
    save_data();
}

/*
 * Function:    refresh_all_saving_racks
 * Description: This gets called during Armageddon by the domain_link
 *              so that all the saving racks in the realm will get
 *              notified to refresh the contents. This helps to remove
 *              any bad accounting of objects during the course of
 *              the uptime.
 */
public void
refresh_all_saving_racks()
{
    mixed * valid_rows = ({ });
    foreach (mixed row : m_rows)
    {
        if (!objectp(row["instance"]))
        {
            continue;
        }
        valid_rows += ({ row });
        object current_rack = row["instance"];
        current_rack->refresh_database();
    }
    
    // We save only the valid rows back to the database. It's the
    // way that we clean up old data from racks that no longer
    // exist in the game.
    m_rows = valid_rows;
    save_data();
}

public void
remove_object()
{
    save_data();
    // We call destruct here on purpose. 
    // Because it calls destruct() directly, all normal things done
    // through remove_object() will be ignored.
    // Since this isn't a real object, it shouldn't matter.
    destruct();
}
