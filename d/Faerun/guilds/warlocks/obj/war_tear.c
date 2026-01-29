/*
* /d/Faerun/guilds/warlocks/obj/war_tear.c
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
    
    set_name("_war_tear");
    add_name("tear");
    add_name("tear of the innocent");
    add_name("_spell_ingredient");
    add_name("ingredient");
    add_name("solified tear");
    set_pname("tears");
    
    add_prop(HEAP_S_UNIQUE_ID, "_war_tear");
    
    set_adj("solified");
    
    set_short("solified tear of the innocent");
    set_pshort("solified tears of the innocent");
    set_long("This is a collected and solified tear of a doomed "
    +"elven infant, which met its demise in the cauldron.\n");
    

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 5);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 1610);
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
