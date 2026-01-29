/* A studded helmet - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
                               
void
create_armour()
{
    set_name("helmet");
    set_pname("helmets");
    add_pname("armours");
    set_short("studded helmet");
    set_pshort("studded helmets");
    set_long("It's a helmet made of hardened leather, with "  
        + "large metal studds set into it. It does not seem very heavy.\n");

    set_adj("studded");
    add_adj("leather");
    
    set_ac(9);

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({   0,   1,   -1}));
    set_at(A_HEAD);
    
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 200);
    
}
