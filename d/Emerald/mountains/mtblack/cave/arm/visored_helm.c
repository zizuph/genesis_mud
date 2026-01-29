/* A visored helmet - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
                               
void
create_armour()
{
    set_name("helmet");
    set_short("visored helmet");
    add_pname("armours");
    set_long("It's a helmet made of tempered iron, with "  
        + "a large visor. It does seem very heavy for a helmet.\n");

    set_adj("visored");
    add_adj("iron");
    
    set_ac(26); /* +1 for tempered iron. */

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({   0,   0,    0}));
    set_at(A_HEAD);
    
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VOLUME, 1000);
}
