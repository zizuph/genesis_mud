inherit "/d/Krynn/guilds/knights/obj/guild_rack";

#include <filter_funs.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <files.h>
#include <wa_types.h>

#define GLOW_RACK_LOG   ("/d/Krynn/guilds/knights/log/glow_rack_log")

//#include "/d/Gondor/defs.h"

int rack_type;


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


public void
create_rack()
{
    set_short("equipment rack");
    set_name("rack");
    set_adj("equipment");
    set_long("This massive equipment rack is set deeply into the north wall. " +
        "It stretches nearly the entire length of the chamber and from the " +
        "floor to the ceiling. Countless hooks, chains and straps line its " +
        "interior for effective ordering and storage of various equipment " +
        "types.\n");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "It is too heavy, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 4000000);
    add_prop(CONT_I_MAX_WEIGHT, 6000000);
    add_prop(CONT_I_VOLUME,  5000);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

    rack_type = 0;
}

/* 
 * Function name: set_rack_type
 * Description  : Set the type of rack
 * Arguments    : type - the type of the rack (0 - saving items, 1 - non
 *              :   saving items without mark, 2 - non saving with mark)
 */
void set_rack_type(int type)
{
    rack_type = type;
}



/*
 * Function name: is_recoverable
 * Description  : See if we can recover this item
 * Arguments    : ob - the item to check
 * Returns      : 0 when unrecoverable, 1 when it is
 */
int is_recoverable(object ob)
{
    if(ob->query_recover() && !ob->may_not_recover())
        return 1;

    return 0;
}

object *filter_rackable_objects(object *obs) {
    object *rack_obs = ::filter_rackable_objects(obs);
    
    switch(rack_type)
    {
        // Saving items
        case 0:
        {
            rack_obs = filter(rack_obs, is_recoverable);
            break;
        }
    }
    
    return rack_obs;
}
