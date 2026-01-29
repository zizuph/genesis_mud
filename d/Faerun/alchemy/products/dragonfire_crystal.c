/*
* /d/Faerun/alchemy/products/dragonfire_crystal.c
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
    
    set_name("_dragonfire_crystal");
    set_pname("crystals");
    add_name("crystal");
    add_name("dragonfire crystal");
    add_pname("dragonfire crystals");
    add_prop(HEAP_S_UNIQUE_ID, "_dragonfire_crystal");
    
    set_adj("dragonfire");
    
    set_short("dragonfire crystal");
    set_pshort("dragonfire crystals");
    set_long("This is a transparent crystal about the size of "
    +"your fist. Within, as if frozen in time, you see a spark "
    +"of solidified fire of a dragon.\n");
    

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 5000);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 2000);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 4000);
    
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
