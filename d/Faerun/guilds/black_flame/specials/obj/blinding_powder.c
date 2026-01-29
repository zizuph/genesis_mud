/*
*
* Blinding powder for Fire Knives.
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
    
    set_name("blinding_powder");
    set_pname("powders");
    add_name("blinding powder");
    add_pname("blinding powders");
    
    add_name("stingy powder");
    add_name("red stingy powder");
    
    add_name("powder");
    
    add_pname("pinch of powder");
    add_pname("pinch of red powder");
    add_pname("pinch of stingy powder");
    add_pname("pinch of red stingy powder");
    
    add_pname("stingy powders");
    add_pname("red stingy powders");
    add_pname("pinches of powder");
    add_pname("pinches of red powder");
    add_pname("pinches of stingy powder");
    add_pname("pinches of red stingy powder");
    
    
    
    add_name("_blinding_powder");
    add_prop(HEAP_S_UNIQUE_ID, "_blinding_powder");
    
    set_adj("red");
    add_adj("stingy");
    
    set_short("pinch of red stingy powder");
    set_pshort("pinches of red stingy powder");
    set_long("Enhanced by alchemy, this powder of red "
    +"pepper will sting the eyes of most living creatures.\n");

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 20);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 30);
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