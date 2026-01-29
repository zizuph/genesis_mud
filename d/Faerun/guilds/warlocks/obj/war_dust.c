/*
* /d/Faerun/guilds/warlocks/obj/war_dust.c
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
    
    set_name("_war_dust");
    add_name("dust");
    add_name("_spell_ingredient");
    add_name("ingredient");
    add_name("vampire dust");
    set_pname("dusts");
    add_name("pinch");
    add_name("pinches");
    add_prop(HEAP_S_UNIQUE_ID, "_war_dust");
    
    set_adj("pinch");
    
    set_short("pinch of vampire dust");
    set_pshort("pinches of vampire dust");
    set_long("This is a tiny pinch of dust from a decayed "
    +"vampire.\n");
    
/* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 5);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 1400);
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
