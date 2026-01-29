/*
* /d/Faerun/guilds/black_flame/obj/fire_water.c
*
* Spell component for the Black flame guild.
*
* Nerull 2022
*/

inherit "/std/heap";
#include <stdproperties.h>
#include <macros.h>

void
create_heap()
{

    set_heap_size(1);

    set_name("_bf_fire_water");
    add_name("water");
	add_name("jar");
    add_name("_spell_ingredient");
    add_name("ingredient");
    add_name("fire water");
	add_name("jar of fire water");
    set_pname("jars of fire water");
    
    add_prop(HEAP_S_UNIQUE_ID, "_bf_fire_water");
    
    set_adj("fire");
    
    set_short("jar of fire water");
	set_pshort("jars of fire water");
    set_long("This is a jar containing fire water. It contains "
	+"about 80 centiliters.\n");


    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 100);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 80);
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
