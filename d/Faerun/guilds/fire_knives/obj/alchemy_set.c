/*
*
* Alchemy set for Fire Knives.
*
* Nerull 2019
*/

inherit "/std/heap";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "../guild.h"


void
create_heap()
{
    set_heap_size(1);
    
    set_name("alchemy_set");
    add_name("alchemy set");
    add_name("set");
    add_name("_alchemy_set");
    add_prop(HEAP_S_UNIQUE_ID, "_alchemy_set");
    
    set_adj("metal");
    
    set_short("alchemy set");
    set_pshort("alchemy sets");
    
    set_long("The alchemy set consists of a foldable tiny metal "
    +"base holding various small tubes and beakers which "
    +"contain various hazardious chemicals, metals and colours "
    +"for various uses such "
    +"as strengthening, conditioning, separating and creating different "
    +"reagents, poisons and other components and field tools. It is also "
    +"complete with a tiny burner, supply of tiny metal wires, a "
    +"tiny mortar and a small grinder.\n");

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 4000);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 4000);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 7000);
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