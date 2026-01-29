/*
* /d/Faerun/guilds/warlocks/obj/war_sulphur.c
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
    
    set_name("_war_sulphur");
    add_name("sulphur");
    add_name("_spell_ingredient");
    add_name("ingredient");
    add_name("lump");
    add_name("lump of sulphur");
    set_pname("sulphurs");
    add_name("_war_sulphur");
    add_prop(HEAP_S_UNIQUE_ID, "_war_sulphur");
    
    set_adj("yellow");
    add_adj("lump");
    
    set_short("yellow lump of sulphur");
    set_pshort("yellow lump of sulphurs");
    set_long("This small yellow lump of pure sulphur is "
    +"the size and shape similar to a regular gold coin. It gives away "
    +"an odor resembling rotten eggs.\n");
    

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 5);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 1010);
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
