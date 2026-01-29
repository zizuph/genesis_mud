/* leather-bracelet.c
 * 
 * A non-armour bracelet worn by warriors in the camp
 */
inherit "/std/armour";
//inherit "/lib/wearable_item";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("bracelet");
    set_adj("leather");
    set_short("leather bracelet");
    set_long("The bracelet is made from a wide band of dark brown leather, covered " +
             "with steel rivets and a shiny buckle to adjust it around the wrist.\n");
    
    set_slots(A_ANY_WRIST); /* Worn on any wrist */
    set_layers(0);
    set_looseness(0);
    set_ac(10);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE,  100);
}


