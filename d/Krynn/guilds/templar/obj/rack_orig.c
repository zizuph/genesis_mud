inherit "/std/container";
// Step 1. Inherit the Recovery Library
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <cmdparse.h>
#include "../local.h"


void
create_rack()
{
}

void
create_container()
{
    set_name("rack");
    set_adj("large");
    add_adj("wooden");
    set_long("This is a large rack for holding various items.\n");
    add_prop(OBJ_I_VALUE,   0);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID,  0);
    add_prop(OBJ_M_NO_GET,  1);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 7500);
    add_prop(CONT_I_MAX_WEIGHT, 900000);
    add_prop(CONT_I_MAX_VOLUME, 900000);

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
prevent_enter(object ob)
{
    if (living(ob))
    return 1;
    return 0;
}

public int
sort_recover(string str)
{
    int i;
    object *ob, *ob2 = ({});

    if (!(ARMAGEDDON->shutdown_active()))
    {
    NF("Sorting is alloved only during Armageddon.\n");
    return 0;
    }

    if (!strlen(str) ||
      !parse_command(str, E(TP), "[the] %i", ob) ||
      !sizeof(ob = NORMAL_ACCESS(ob, 0, 0)))
    {
    NF(C(query_verb()) + " what?\n");
    return 0;
    }
    if (sizeof(ob) > 1)
    {
    NF(C(query_verb()) + " what?  Be more specific.\n");
    return 0;
    }
    if(ob[0] != TO)
    {
    NF(C(query_verb()) + " what?\n");
    return 0;
    }

    ob = all_inventory(TO);
    if (!sizeof(ob))
    {
    NF("There is nothing to sort in "+short()+".\n");
    return 0;
    }

    for (i=0; i<sizeof(ob); i++)
    {
    if (!ob[i]->check_recoverable())
        ob2 += ({ ob[i] });
    }
    if (!sizeof(ob2))
    {
    write("Everything in "+short()+" glows.\n");
    return 1;
    }
    ob = ({});

    for (i=0; i<sizeof(ob2); i++)
    {
    if (!ob2[i]->move(E(TO)))
        ob += ({ ob2[i] });
    }
    if (!sizeof(ob))
    {
    write("You did not sort anything out of "+short()+".\n");
    return 1;
    }
    str = COMPOSITE_DEAD(ob);
    write("You sorted "+str+" out of "+short()+".\n");
    tell_room(E(TP), QCTNAME(TP)+" sorted "+str+" out of "+short()+".\n", TP);
    return 1;
}

public void
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
