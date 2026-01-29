/*
 * Added recoverablility so players don't have to find these everytime
 * since it is a spell component.
 * -- Finwe November 2004
 *
 * Changed it to heap
 * -- Finwe January 2005
 */

inherit "/lib/keep";
inherit "/std/heap";

#include "/sys/stdproperties.h"
#include <macros.h>

string
iron_long()
{
    return "The " + 
        ((num_heap() == 1) ? "shred" : "shreds") + " of iron probably came " +
        "from a tool a blacksmith was forging. It probably isn't worth very " + "much.\n";
}

create_heap()
{
    set_heap_size(1);

    set_name(({"_cast_iron", "iron" }));
    add_name("shred");
    set_short("shred of cast iron");
    set_pshort("shreds of cast iron");
    set_adj("cast");

    /* Give a proper long description for one crystal or for multiple
     * crystals.
     */
    set_long(iron_long);

    /* This prop should uniquely identify the heap.  All other heaps
     * with the same id will merge with this one.
     */
    add_prop(HEAP_S_UNIQUE_ID, "cast_iron_shred");

    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VALUE, 2);
//    set_keep();
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
