/*
*
* Garotte wire for Fire Knives.
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
    
    set_name("garotte_wire");
    set_pname("wires");
    add_name("wire");
    add_name("garotte wire");
    add_pname("garotte wires");
    add_name("_garotte_wire");
    add_prop(HEAP_S_UNIQUE_ID, "_garotte_wire");
    
    set_adj("thin");
    add_adj("strong");
    
    set_short("thin strong wire");
    set_pshort("thin strong wires");
    set_long("This is a thin strong organic wire, probably made "
    +"of intestines. This wire is perfect to garotte unfortunate "
    +"victims.\n");

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 40);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 100);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 30);
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