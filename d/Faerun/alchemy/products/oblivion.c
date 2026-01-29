/*
* /d/Faerun/alchemy/products/oblivion.c
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
    
    set_name("_oblivion_elixir");
    set_pname("elixirs");
    add_name("elixir");
    add_name("oblivion");
    add_name("jet-black elixir");
    add_name("oblivion elixir");
    add_name("vial");
    add_name("vials");
    add_name("tiny vial");
    add_name("tiny vials");
    add_prop(HEAP_S_UNIQUE_ID, "_oblivion_elixir");
    
    set_adj("jet-black");
    
    set_short("jet-black elixir");
    set_pshort("jet-black elixirs");
    set_long("This is a tiny glass vial containing some "
    +"jet-black fluid. It can be consumed.\n");
    

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
