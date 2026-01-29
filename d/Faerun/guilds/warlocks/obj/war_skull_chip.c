/*
* /d/Faerun/guilds/warlocks/obj/war_skull_chip.c
*
* Spell component for the warlock guild.
*
* Nerull 2017
*/

inherit "/std/heap";
#include <stdproperties.h>
#include <macros.h>

void
create_heap()
{
    set_heap_size(1);
    
    set_name("_war_skull_chip");
    add_name("chip");
    add_name("_spell_ingredient");
    add_name("ingredient");
    set_pname("chips");
    add_prop(HEAP_S_UNIQUE_ID, "_war_skull_chip");
    
    set_adj("curved");
    add_adj("bone");
    
    set_short("curved bone chip");
    set_pshort("curved bone chips");
    set_long("This fragment of bone is roughly circular in appearance and "
    +"slightly curved. It measures about two inches in diameter.\n");

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 5);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 1);
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
