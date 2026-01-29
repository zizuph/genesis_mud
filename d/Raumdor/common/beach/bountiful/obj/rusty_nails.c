/*  /d/Raumdor/common/beach/bountiful/obj/srusty_nails.c
 *
 *  Crate supply item.
 *
 *  Nerull, 2021
 *
 */


inherit "/std/heap";
#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>


void
create_heap()
{
    set_heap_size(1);
    
    set_name("_pile_of_rusty_nails");
    add_name("nail");
    add_name("nails");
    add_name("rusty nails");
    add_name("huge pile");
    add_name("pile of rusty nails");
    add_name("pile of nails");
    set_adj("pile");
    add_adj("huge pile");
    add_prop(HEAP_S_UNIQUE_ID, "_pile_of_rusty_nails");
    
    set_short("huge pile of rusty nails");
    set_pshort("huge piles of rusty nails");
    
    set_long("This is a huge pile of old and very rusty nails of "
    +"iron.\n");
    
    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 29000);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 5000);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 500);
    
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
