/*
 *  /d/Gondor/guilds/morgulmage/obj/alcove.c 
 * 
 *  This is a storage option for the Morgul Mages on the 4th level of their
 *  Tower.
 *
 *  Created at player request by Gorboth, October 2010
 */

#pragma strict_types

inherit "/std/receptacle.c";
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_receptacle()
{
    set_short("deep alcove");
    set_name("alcove");
    add_name( ({ "wall" }) );
    set_adj( ({ "deep", "west", "western" }) );
    set_long("A deep alcove has been hollowed in the wall here, allowing"
      + " the dutiful stewards of the Tower to use the many layers of"
      + " shelves that the alcove contains to store the various and"
      + " sundry items they would choose. A roll-case door makes it possible"
      + " to close the alcove and hide its contents from view.\n");

    add_prop(OBJ_M_NO_GET, "Surely, you jest.\n");
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_MAX_WEIGHT, 750000);
    add_prop(CONT_I_VOLUME,  4500);
    add_prop(CONT_I_WEIGHT,  5000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);

    setuid();
    seteuid(getuid());
    
    if (!IS_CLONE)
    {
        return;
    }
    
    set_enable_logging(0);
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
