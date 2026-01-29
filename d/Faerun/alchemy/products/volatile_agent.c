/*
* /d/Faerun/alchemy/products/volatile_agent.c
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
    
    set_name("_volatile_agent");
    set_pname("agent");
    add_name("volatile agent");
    add_name("fiery volatile agent");
    add_prop(HEAP_S_UNIQUE_ID, "_volatile_agent");
    
    set_adj("fiery");
    set_adj("volatile");
    
    set_short("fiery volatile agent");
    set_pshort("fiery volatile agent");
    set_long("This is a transparent gelatinous substance containing "
    +"a spark of contained and solified dragonfire. It is highly "
    +"volatile and can explode violently at any moment with tremendeous "
    +"force. This is an alchemical ingredient.\n");
    

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 8000);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 3000);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 5000);
    
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
