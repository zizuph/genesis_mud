/* An iron buckler - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
                               
void
create_armour()
{
    set_name("buckler");
    set_pname("bucklers");
    add_pname("armours");
    set_short("iron buckler");
    set_pshort("iron bucklers");
    set_long("It's an iron buckler that is useful as a small shield.\n");

    add_adj("iron");
    
    set_ac(15); /* iron , -5 buckler mod. */

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({   0,   0,    0}));
    set_at(A_SHIELD);
    
    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 600);
}
