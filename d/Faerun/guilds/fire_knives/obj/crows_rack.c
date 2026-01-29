/*
 * /d/Faerun/guilds/fire_knives/obj/crows_rack.c
 *
 * Nerull 2020
 */

#include <filter_funs.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <files.h>
#include <wa_types.h>
#include "../guild.h"

inherit FIREKNIVES_OBJ_DIR + "guild_rack";

int rack_type;

public void
create_rack()
{  
    set_name("rack");
    set_adj("wooden");
    add_adj("wall-wide");
    
    set_short("wooden wall-wide rack");
    set_long("The wooden wall-wide armour rack spans across the length "
    +"of the entire western wall, along which are various slots and "
    +"hooks onto which you can hang the various armours required for "
    +"your manifold tasks. Judging by the height of each hook it is "
    +"easy to see each piece of armour as a whole, their separate "
    +"aimed body parts placed at your corresponding size.\n");

    //set_no_show_composite(1);

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


object *filter_rackable_objects(object *obs) 
{
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