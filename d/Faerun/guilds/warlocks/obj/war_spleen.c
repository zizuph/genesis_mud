/*
* /d/Faerun/guilds/warlocks/obj/war_spleen.c
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
    
    set_name("_war_spleen");
    set_pname("spleens");
    add_name("_spell_ingredient");
    add_name("ingredient");
    add_name("spleen");
    add_name("bat spleen");
    add_name("_war_spleen");
    add_prop(HEAP_S_UNIQUE_ID, "_war_spleen");
    
    set_adj("tiny");
    set_adj("bat");
    
    set_short("tiny bat spleen");
    set_long("This tiny lump of organic material is a "
    +"spleen from a dissected bat.\n");
    

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 5);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 1170);
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
