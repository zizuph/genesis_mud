/*
 * /d/Ansalon/guild/society/obj/neq_rack.c
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
 * non-Saving Equipment Rack
 * Gwyneth, May 2000  
 *
 * Modified 2021-06-03 by Carnak:
 *  - Made broken items free to remove from the racks.
 */
inherit "/std/container";
// Step 1. Inherit the Recovery Library
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include "../guild.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>

object  gGlowRack;

int check_glow_rack();

void
create_container()
{
    set_name("rack");
    add_name("non_glowing_rack");
    set_adj("pecan");
    add_adj("wood");
    set_short("pecan wood rack");
    set_long("This is a rack where members can place their equipment for " +
        "use by other members. The word 'Sort' has been carved into the " +
        "side.\nIt glows with a faint silver aura.\n");

    add_prop(CONT_I_MAX_WEIGHT, 9000000);
    add_prop(CONT_I_MAX_VOLUME, 9000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The pecan wood rack is bolted to the floor.\n");

    set_alarm(0.1, 0.0, &check_glow_rack());

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
check_glow_rack()
{
    if (!objectp(gGlowRack))
        gGlowRack = present("glowing_rack", environment(this_object()));

    if (!objectp(gGlowRack))
        return 0;
    else
        return 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (from == this_object())
    {
        return;
    }

    // Step 4. Add add_rack_entry to enter_inv
    add_rack_entry(ob);

    if (!interactive(from))
        return;

    if (query_verb() == "return")
        return;

    if (!check_glow_rack())
    {
        from->catch_tell("Something went wrong! Please bug report.\n");
        return;
    }

    gGlowRack->enter_racks(ob, from->query_real_name());
    return;
}

void
leave_inv(object ob, object to)
{
    int new_value;
    string name, equip;

    ::leave_inv(ob, to);

    if (to == this_object() || !objectp(to))
    {
        // Not actually leaving this container, just return
        return;
    }
    
    // Step 5. Add remove_rack_entry to leave_inv
    remove_rack_entry(ob);
    
    if (!interactive(to) || ob->query_prop(OBJ_I_BROKEN))
        return;

    if (!check_glow_rack())
    {
        to->catch_tell("Something went wrong! Please bug report.\n");
        return;
    }

    gGlowRack->leave_racks(ob, to);
    return;
}
