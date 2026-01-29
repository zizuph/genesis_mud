inherit "/d/Gondor/std/guild_rack";

#include <filter_funs.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <files.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

int rack_type;

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
    add_prop(CONT_I_MAX_VOLUME, 2000000);
    add_prop(CONT_I_MAX_WEIGHT, 5000000);
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
 * Function name: is_ithil
 * Description  : Is this an ithil object
 * Arguments    : ob - the object to check
 * Returns      : 0 if not, 1 if it is
 */
int is_ithil(object ob)
{
    if(ob->id("_ithil_armour")) return 1;
    if(ob->id("_ithil_weapon")) return 1;
    if(ob->query_prop(GONDOR_M_MORGUL_NO_SELL)) return 1;

    return 0;
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
        // Non saving items without the mark
        case 1:
        {
            rack_obs = filter(rack_obs, not @ is_recoverable);
            rack_obs = filter(rack_obs, not @ is_ithil);
            break;
        }
        // Non saving items with the mark
        case 2:
        {
            rack_obs = filter(rack_obs, not @ is_recoverable);
            rack_obs = filter(rack_obs, is_ithil);
            break;
        }
    }
    
    return rack_obs;
}