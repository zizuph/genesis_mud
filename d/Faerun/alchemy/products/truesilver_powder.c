/*
* /d/Faerun/alchemy/products/truesilver_powder.c
*
* Alchemy product/ingredient.
*
* Nerull 2021
*/

inherit "/std/heap";
#include <stdproperties.h>
#include <macros.h>
#include "../defs.h";

void
create_heap()
{
    set_heap_size(1);
    
    set_name("_truesilver_powder");
    set_pname("powders");
    add_name("powder");
    add_name("silvery powder");
    add_name("silver powder");
    add_name("pinch");
    add_name("pinches");
    add_prop(HEAP_S_UNIQUE_ID, "_truesilver_powder");
    
    set_adj("silvery");
    
    set_short("pinch of silvery powder");
    set_pshort("pinches of silvery powder");
    set_long("This is a pinch of fine grinded silvery "
    +"powder. You believe this is truesilver judging by its "
    +"purity.\n");
    

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 5);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 1640);
}


/* 
 * This is called when an autoloading object is reloaded.  We use
 * it to restore the heap to it's correct size.
 */
void
init_arg(string arg)
{
    set_heap_size(atoi(arg));
}


/*
 * This is called when the player is logging out.  We use it to
 * store the size of the heap so that we can restore it to the right
 * amount when the player logs back in.
 */
string
query_auto_load()
{
    return MASTER + ":" + num_heap();
}
