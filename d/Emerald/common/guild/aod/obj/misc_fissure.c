/*
 *  /d/Emerald/common/guild/aod/obj/misc_fissure.c
 * 
 *  This fissure is where miscellaneous items are stored in the Army of
 *  Darkness guild.
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
 */

#pragma strict_types

inherit "/std/container.c";
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_container()
{
    set_short("deep fissure");
    set_name("fissure");
    add_name( ({ "_aod_fissure" }) );
    set_adj( ({ "deep" }) );
    set_long("A deep fissure has opened in the ground just beside you here"
      + " at the base of the ravine. A bit of strange purple energy seems to"
      + " hover over it.\n");

    add_prop(OBJ_M_NO_GET, "Uhhhhhhh ......\n");
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_MAX_WEIGHT, 750000);
    add_prop(CONT_I_VOLUME,  4500);
    add_prop(CONT_I_WEIGHT,  5000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);

    if (!IS_CLONE)
    {
        return;
    }
    
    set_enable_logging(1);
    set_enable_recovery(1);
    
    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());

    set_no_show_composite(1);
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
        return;
    }

    remove_rack_entry(ob);
}
