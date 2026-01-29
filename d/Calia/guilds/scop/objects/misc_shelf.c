
/* 
 *  Miscellaneous rack for the Spirit Circle of Psuchae
 *  July 29th, 2003
 *
 *  Modified on October 20, 2010 - Added auto-save functionality
 */


inherit "/std/container";
// Step 1. Inherit the Recovery Library
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

#include "defs.h"

void
create_container()
{
    set_name("shelf");
    set_adj("large");
    add_adj("wooden");
    set_short("large wooden shelf");
    set_long("This wooden shelf sits along the west wall and has "+
        "alot of space for you to place things that do not really fit "+
        "into either the weapons rack or the armour rack. You " +
        "can clean it out, which will remove all of the items that "+
        "will not save. <clean shelf>\n"); 

    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The large wooden shelf is attached to the wall.\n");

    setuid();
    seteuid(getuid());
    
    if (!IS_CLONE)
    {
        return;
    }
    
    // Step 2. Set the options of whether you want to enable logging or recovery
    set_enable_logging(0);
    set_enable_recovery(1);
    
    // Step 3. Initialize the Database and call recover_objects_from_database
    //         using an alarm.
    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());    
}

int
do_clean(string str)
{
    int i;
    object *obj;

    if (str != "shelf")
    {
        NF("Clean what? The shelf? <clean shelf>\n");
        return 0;
    }
   
    obj = filter(all_inventory(),&operator(!=)(1) @ &->check_recoverable());

    for (i = 0 ; i < sizeof(obj) ; i++)
    {
        obj[i]->move(environment());
    }

    if (!sizeof(obj))
        write("There was nothing on the shelves that needed to be "+
            "cleaned out.\n");
    
    else
    {        
        write("You clean " + COMPOSITE_ALL_DEAD(obj) + " off of the shelf.\n");
        tell_room(TO, QCTNAME(TP) + " cleans " + COMPOSITE_ALL_DEAD(obj) + 
        " off of the shelf.", TP);
    }

    return 1;
}

public int
prevent_enter(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
    {
        write("Why would you want to put broken things on the shelf?\n");
        return 1;
    }

    if (obj->query_wt())
    {
        write("The " + obj->short() + " would fit better in the weapon "+
            "rack.\n");
        return 1;
    }

    else
    if (obj->query_at())
    {
        write("The " + obj->short() + " would fit better in the armour "+
            "rack.\n");
        return 1;
    }

    ::prevent_enter(obj);
}

void
init()
{
    add_action(do_clean, "clean");
    ::init();
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
    
    if (to == this_object() || !objectp(to))
    {
        // Not actually leaving this container, just return
        return;
    }
    
    // Step 5. Add remove_rack_entry to leave_inv
    remove_rack_entry(ob);
}
