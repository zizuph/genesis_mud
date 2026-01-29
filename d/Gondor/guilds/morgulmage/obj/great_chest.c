/*
 * Modification History:
 *     October 2010 - Added saving rack functionality (Gorboth)
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
    set_short("great chest");
    set_name("chest");
    set_adj("great");
    set_long("This great chest lies in the center of the chamber. Grey bands " +
        "of an unknown metal tightly bind strips of pine together. Black " +
        "tar has been applied to the joints of the strips ensuring an " +
        "airtight seal. ");

    add_prop(OBJ_M_NO_GET, "The chest is fixed to the floor, you cannot take it.\n");
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
    
    set_enable_logging(0);
    set_enable_recovery(1);
    
    init_database();    
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
