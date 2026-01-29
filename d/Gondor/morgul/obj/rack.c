/*
 * Modification history:
 *   - Added rack-saving functionality (Gorboth, October 2010)
 */

inherit "/std/container";
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_container()
{
    set_short("weapon rack");
    set_name("rack");
    set_adj("weapon");
    set_long(BSN("The weapon rack contains weapons and armours. "
      + "It looks very massive and can probably hold the equipment "
      + "for several soldiers."));

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "It is too heavy, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 200000);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME,  5000);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

    enable_reset(200);

    if (!IS_CLONE)
    {
        return;
    }
    
    set_enable_logging(0);
    set_enable_recovery(1);
    
    FIX_EUID
    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());

    set_alarm(2.0, 0.0, reset_container);
}

void
reset_container()
{

    FIX_EUID
    if (!present("hatchet", TO))
        clone_object(WEP_DIR + "hatchet")->move(TO, 1);
    if (!present("robe", TO))
        clone_object(MORGUL_DIR + "obj/blackcloak")->move(TO, 1);
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
