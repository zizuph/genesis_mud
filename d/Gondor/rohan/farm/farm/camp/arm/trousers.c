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

#define NAME    "trousers"
#define ADJ1    "brown"
#define ADJ2    "doeskin"
void create_armour() 
{
    set_name(NAME);
    add_adj(ADJ1);
    add_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + NAME);
    add_name("clothes");
     add_name("_dunlending_object");
    add_name("pants");
    set_long("These " + query_short() + " look simple and plain. "
        + "Because they're made of " + ADJ2 + ", they're quite "
        + "durable, and suited to the gritty life of a farmer. You "
        + "notice some cuts on the legs of the trousers.\n");
    set_default_armour(0, A_LEGS);
    
    add_item( ({"cut", "cuts"}), "The cuts appear to be made from "
        + "swords! These trousers were likely taken off a dead body.\n");
    
   

}

