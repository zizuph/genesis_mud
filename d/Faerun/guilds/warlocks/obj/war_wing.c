/*
* /d/Faerun/guilds/warlocks/obj/war_wing.c
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

    set_name("_war_wing");
    add_name("wing");
    add_name("_spell_ingredient");
    add_name("ingredient");
    add_name("fairy wing");
    set_pname("fairy wings");
    
    add_prop(HEAP_S_UNIQUE_ID, "_war_wing");
    
    set_adj("bloody");
    
    set_short("bloody fairy wing");
    set_long("This is a fresh bloody wing from "
    +"a fairy. Judging by the looks, the wing has "
    +"been brutally ripped off the body of the "
    +"fairy.\n");


    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 5);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 1333);
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
