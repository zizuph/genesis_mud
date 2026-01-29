/*
* /d/Faerun/guilds/warlocks/obj/war_heart_piece.c
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
    
    set_name("_war_heart_piece");
    add_name("piece");
    set_pname("pieces");
    add_name("_spell_ingredient");
    add_name("ingredient");
    add_prop(HEAP_S_UNIQUE_ID, "_war_heart_piece");
    
    set_adj("dried");
    add_adj("heart");
    
    set_short("dried heart piece");
    set_pshort("dried heart pieces");
    set_long("This is a sliced and petrified fragment from "
    +"some heart. It measures about two inches in length and width.\n");

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
