/*
* /d/Faerun/alchemy/products/hellfire.c
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
    
    set_name("_hellfire_flask");
    set_pname("hellfires");
    add_name("hellfire");
    add_name("rust-red flask");
    
    add_name("hellfire flask");
    add_name("flask");
    add_name("flasks");
    add_name("large flask");
    add_name("large flasks");
    add_prop(HEAP_S_UNIQUE_ID, "_hellfire_flask");
    
    set_adj("rust-red");
    set_adj("large");
    
    set_short("large rust-red flask");
    set_pshort("large rust-red flasks");
    
    set_long("This is a large glass flast containing "
    +"a lot of fine rust-red powder and other chemical "
    +"ingredients. It looks both very dangerous and unstable.\n");
    

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 30000);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 5000);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 1640);
    
    set_may_not_recover();
    
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
