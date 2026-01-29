/*
 * /doc/examples/obj/crystal.c
 * 
 * A simple heap object.
 */

inherit "/std/heap";

#include <stdproperties.h>
#include <macros.h>

string
crystal_long()
{
    return "The small clear crystal" + 
        ((num_heap() == 1) ? " is " : "s are ") + "completely " +
        "transparent and slightly luminescent.\n";
}

void
create_heap()
{
    set_heap_size(1);

    set_name("crystal");
    set_adj(({ "small", "clear" }));

    /* Give a proper long description for one crystal or for multiple
     * crystals.
     */
    set_long(crystal_long);

    add_prop(OBJ_M_NO_SELL, 1);

    /* This prop should uniquely identify the heap.  All other heaps
     * with the same id will merge with this one.
     */
    add_prop(HEAP_S_UNIQUE_ID, "kot_ri_crystal");

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 3);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 20);
}    

/* The following are necessary for an autoloading heap.  If you
 * don't need an autoloading heap, you don't need to include these
 * at all.
 */

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
