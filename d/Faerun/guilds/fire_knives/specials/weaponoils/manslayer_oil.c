/*
*
* Weapon oil for Fire Knives.
*
* Nerull 2017
*/

inherit "/std/heap";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "../../guild.h"


void
create_heap()
{
    set_heap_size(1);
    
    set_name("manslayer");
    set_pname("manslayers");
    add_name("oil");
    add_name("weapon oil");
    add_name("vial");
    add_name("manslayer oil");
    add_pname("oils");
    add_pname("manslayer oils");
    add_pname("weapon oils");
    add_pname("vials");
    add_name("manslayer_weaponoil");
    add_name("_weaponoil_manslayer");
    add_prop(HEAP_S_UNIQUE_ID, "_weaponoil_manslayer");
    
    set_adj("tiny");
    add_adj("green");
    
    set_short("tiny green vial");
    set_pshort("tiny green vials");
    set_long("This is tiny clear vial. Within you see some "
    +"green oily opaque substance that is slightly reacting "
    +"to the trapped air within.\n");

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 1);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 1);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 400);
}


/*
 * Function name: query_auto_load
 * Description  : Charms are autoloading. 
 * Returns      : string - the auto-load string.
 */
public string
query_auto_load()
{
    /* Don't auto load if we are about to destroy. */
    if (query_prop(TEMP_OBJ_ABOUT_TO_DESTRUCT))
        return 0;
    
    return (MASTER + ":" + num_heap());
}


/* 
 * Function name: init_arg
 * Description  : Called when autoloading. It will set the type of shard
 * Arguments    : string arg - the auto-load argument.
 */
void
init_arg(string arg)
{
    int size;
    
    if (sscanf(arg, "%d", size) == 1)
    {
        set_heap_size(max(1, size));
    }
}