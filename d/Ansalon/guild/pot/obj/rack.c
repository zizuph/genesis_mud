/* Stralle @ Genesis 010624
 *
 * A standard rack, based on the racks for the dragonarmies by Milan(?).
 *
 * Revisions:
 *   Lucius, Aug 2016: Auto-set keep flag on all entering items.
 */
#pragma strict_types

inherit "/std/container";
// Step 1. Inherit the Recovery Library
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 
// Rack listing
inherit "/d/Ansalon/guild/pot/obj/rack_list";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "/d/Ansalon/common/defs.h"

void
create_rack()
{
}

void
create_container()
{
    set_name("rack");
    set_long("It is rack meant to keep various items.\n");

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_WEIGHT, 15000);
    add_prop(CONT_I_VOLUME, 15000);
    add_prop(CONT_I_MAX_WEIGHT, 9000000);
    add_prop(CONT_I_MAX_VOLUME, 9000000);
    
    create_rack();

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

public int
sort_recover(string str)
{
    object ob, *arr, *arr2, *arr3;
    int i, size;
    string text;

    if (!ARMAGEDDON->shutdown_active())
        return 0;
    
    if (!str || !parse_command(str, environment(TP), "[the] %o", ob))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    if (ob != TO)
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    arr = all_inventory(TO);
    if (!sizeof(arr))
    {
        write("There is nothing to " + query_verb() +
            " in " + short() + ".\n");
        return 1;
    }
    
    for (i = 0, size = sizeof(arr), arr2 = ({ }) ; i < size ; i++)
    {
        if (!arr[i]->check_recoverable())
        {
            arr2 += ({ arr[i] });
            if (arr[i]->move(environment(TO)))
            {
                arr3 += ({ arr[i] });
                arr2 -= ({ arr[i] });
            }
        }
    }

    if (!sizeof(arr2))
    {
        write("Everything in " + short() + " glows.\n");
        return 1;
    }
    
    text = COMPOSITE_DEAD(arr2);
    if (sizeof(arr3))
        text += " however, " + COMPOSITE_DEAD(arr3) + " became stuck";
    
    write("You sort out " + text + " in " + short() + ".\n");
    say(QCTNAME(TP) + " sorts out " + text + " in " + short() + ".\n");
    
    return 1;
}

void
init()
{
    ::init();
    
    add_action(sort_recover, "sort");
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

    // Auto-set keep flag on objects.
    ob->set_keep(1);
    
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
