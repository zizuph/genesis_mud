/*
* /d/Faerun/alchemy/products/truefire.c
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
    
    set_name("_truefire_flask");
    set_pname("truefires");
    add_name("truefire");
    add_name("yellow flask");
    
    add_name("truefire flask");
    add_name("flask");
    add_name("flasks");
    add_name("large flask");
    add_name("large flasks");
    add_prop(HEAP_S_UNIQUE_ID, "_truefire_flask");
    
    set_adj("yellow");
    set_adj("large");
    
    set_short("large yellow flask");
    set_pshort("large yellow flasks");
    
    set_long("This is a large glass flast containing "
    +"a lot of fine yellowpowder and other chemical "
    +"ingredients. It looks both dangerous and unstable.\n");
    

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
