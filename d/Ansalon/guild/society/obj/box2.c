/*
 * /d/Ansalon/guild/society/obj/box2.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Box to keep miscellaneous things in.
 *
 * Gwyneth, 1999
 */
inherit "/std/container";
// Step 1. Inherit the Recovery Library
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <stdproperties.h>
#include <macros.h>

object gWho;

void
create_container()
{
    set_name("box");
    set_adj("magic");
    set_short("magic box");
    set_long("A soft white glow emits from the box, and it hums " + 
        "with pleasure every time someone drops something in.\n");

    add_prop(CONT_I_MAX_WEIGHT, 900000);
    add_prop(CONT_I_MAX_VOLUME, 900000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The magic box turns red and hums " +
        "warningly when you try to pick it up.\n");
        
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

void
reset_hum()
{
    gWho = this_object();
}

void
add_box_log(object ob, string str)
{
    if (file_size("/d/Ansalon/guild/society/obj/boxlog") > 100000)
        rename("/d/Ansalon/guild/society/obj/boxlog",
               "/d/Ansalon/guild/society/obj/boxlog.old");
    
    write_file("/d/Ansalon/guild/society/obj/boxlog", ctime(time()) +
    " " + ob->short() + " " + str + ". " +
    (ob->query_nullstone_type() ? ob->query_nullstone_type() : "") +
    "\n");
}

public void
enter_inv(object ob, object from)
{
    int *alarms = query_alarms();

    ::enter_inv(ob, from);

    if (gWho == from)
    {
        return;
    }

    // Step 4. Add add_rack_entry to enter_inv
    add_rack_entry(ob);
    
    if (objectp(from) && living(from))
    {
        if (function_exists("create_container", ob))
        {
            foreach(object item: all_inventory(ob))
            {
                add_box_log(item, "added");
            }
        }
        add_box_log(ob, "added");
    }
    
    tell_room(environment(this_object()), "The magic box glows white and " +
        "hums with pleasure as it is filled.\n");

    if (!sizeof(alarms))
    {
        gWho = from;
        set_alarm(1.0, 0.0, &reset_hum());
        return;
    }
    
    gWho = from;
    return;
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
    
    if (objectp(to) && living(to))
    {
        if (function_exists("create_container", ob))
        {
            foreach(object item: all_inventory(ob))
            {
                add_box_log(item, "removed");
            }
        }
        add_box_log(ob, "removed");
    }
    
    // Step 5. Add remove_rack_entry to leave_inv
    remove_rack_entry(ob);
}
