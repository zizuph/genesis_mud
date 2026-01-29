/* An iron helmet - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
                               
void
create_armour()
{
    set_name("helmet");
    set_short("iron plate helmet");
    add_pname("armours");
    set_long("It's a helmet made of plate iron, with "  
        + "no visor or nose guard. It's quite heavy for a helmet.\n");

    set_adj("plate");
    add_adj("iron");
    
    set_ac(20); /* iron plate, no mod. */

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({   0,   0,    0}));
    set_at(A_HEAD);
    
    add_prop(OBJ_I_WEIGHT, 2400);
    add_prop(OBJ_I_VOLUME, 600);
}
