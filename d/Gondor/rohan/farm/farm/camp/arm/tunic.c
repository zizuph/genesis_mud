/* Clothing item for the chests in the Dunlending Camp
 *
 * Raymundo, April 2020
 */

#pragma strict_types

inherit "/std/armour";
#include "/d/Gondor/defs.h"
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

#define NAME    "tunic"
#define ADJ1    "green"
#define ADJ2    "linen"
void create_armour() 
{
    set_name(NAME);
    add_adj(ADJ1);
    add_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + NAME);
    add_name("clothes");
     add_name("_dunlending_object");
    add_name("shirt");
    set_long("This " + query_short() + " looks simple and plain. "
        + "Because it's made of " + ADJ2 + " it wrinkles easily and "
        + "never looks prestine. However, it's also quite comfortable "
        + "on a hot day.\n");
    set_default_armour(0, A_BODY);
    
    
    
   

}

