/*
 * Special Items Master for the Gladiators Guild
 *
 * This master object keeps track of the special items that the Guild
 * wants to keep track of. Whenever this item is borrowed or put in,
 * an entry is placed in the log for Overseers to see.
 *
 * Created by Petros, March 2009
 */

#pragma strict_types

#include "../defs.h"
#include <filter_funs.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public string *     special_items = ({ });
public string *     invalid_items = ({ });

// Defines
#define DATA        (GLAD_OBJ + "racks/special_items")
#define MAX_ITEMS   25

// Prototypes

                    
// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
void
create()
{
    setuid();
    seteuid(getuid());
    
    if (file_size(DATA + ".o"))
    {
        restore_object(DATA);
        
        // We also do a cleanup of the data for invalid files in case
        // some wizard changes the files around
        foreach (string file : special_items)
        {
            if (!objectp(find_object(file)))
            {
                if (LOAD_ERR(file)
                    || !objectp(find_object(file)))
                {
                    invalid_items += ({ file });
                }
            }
        }
        special_items -= invalid_items;
        save_object(DATA);        
    }
}

public void
add_special_item(object item)
{
    string master_file;
    
    if (!objectp(item)
        || (!IS_WEAPON_OBJECT(item) && !IS_ARMOUR_OBJECT(item)))
    {
        // We only allow to add weapons and armours.
        return;
    }
    
    master_file = MASTER_OB(item);
    if (!IN_ARRAY(master_file, special_items)
        && sizeof(special_items) < MAX_ITEMS)
    {
        special_items += ({ master_file });
        save_object(DATA);
    }
}

public void
remove_special_item(mixed item)
{
    string master_file;
    
    if (objectp(item))
    {
        master_file = MASTER_OB(item);
    }
    else if (stringp(item))
    {
        master_file = item;
    }
    else
    {
        return;
    }
    
    special_items -= ({ master_file });
    save_object(DATA);
}

/*
 * Function:    remove_special_item_by_short
 * Description: When a player needs to remove an item, all they
 *              have is the short description. We need to allow them
 *              to remove it by just specifying the short desc. This
 *              function loops through all the items to find the entry
 *              with the short desc.
 */
public int
remove_special_item_by_short(string shortdesc)
{
    object item;
    int removed;
    
    setuid();
    seteuid(getuid());    
    removed = 0;
    foreach (string file : special_items)
    {
        if (objectp(item = find_object(file))
            || (!LOAD_ERR(file) && objectp(item = find_object(file))))
        {
            // Successfully loaded the item. Now check to see if it
            // matches the short_desc
            if (lower_case(item->short()) == lower_case(shortdesc))
            {
                special_items -= ({ file });
                save_object(DATA);
                return 1;
            }
        }
    }    
    
    return 0;
}

public string *
query_special_items()
{
    return special_items + ({ });
}

public int
query_is_special_item(object item)
{
    if (!objectp(item))
    {
        return 0;
    }
    
    if (IN_ARRAY(MASTER_OB(item), special_items))
    {
        return 1;
    }
    
    return 0;
}

public int
query_specials_full()
{
    if (sizeof(special_items) >= MAX_ITEMS)
    {
        return 1;
    }
    
    return 0;
}

