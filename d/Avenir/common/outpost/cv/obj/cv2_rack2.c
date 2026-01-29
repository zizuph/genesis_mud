/*
 * /d/Faerun/guilds/vampires/obj/cv2_rack.c
 *
 * Nerull 2021
 * Lilith, Mar 2022 -- secondary rack. Originally the second rack
 *   was just a  second instance of the first one, but that problem
 *   with that is that one rack was over-writing the other and
 *   the players were losing their gear :(
 *
 */
inherit "/d/Faerun/guilds/vampires/obj/guild_rack";

#include <filter_funs.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <files.h>
#include <wa_types.h>
#include "/d/Faerun/guilds/vampires/guild.h";


int rack_type;

public void
create_rack()
{  
    set_name("rack");
    set_adj("wooden");
    add_adj("wall-wide");
    
    set_short("wooden wall-wide rack");
    set_long("The wooden wall-wide rack spans across the length "
    +"of the entire wall, along which are various slots and "
    +"hooks onto which you can hang the various items required for "
    +"your manifold tasks. Judging by the height of each hook it is "
    +"easy to see each piece as a whole.\n");

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