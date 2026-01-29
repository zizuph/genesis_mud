/*
* /d/Faerun/guilds/warlocks/obj/war_blood.c
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
    
    set_name("_war_blood");
    add_name("blood");
    add_name("_spell_ingredient");
    add_name("ingredient");
    set_pname("bloods");
    add_name("vial");
    add_name("vials");
    add_name("tiny vial");
    add_name("tiny vials");
    add_name("virgin blood");
    add_name("virgins blood");
    add_name("virgin's blood");
    
    set_adj("tiny");
    set_adj("vial");
    
    set_short("tiny vial of virgin's blood");
    set_pshort("tiny vials of virgin's blood");
    set_long("Containing just a few drops of blood from "
    +"a virgin, the vial is about the size of a human thumb.\n");
    
    set_heap_size(1);
    
    add_prop(HEAP_S_UNIQUE_ID, "_war_blood_vial");

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 5);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 1200);
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
