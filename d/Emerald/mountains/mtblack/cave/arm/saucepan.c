/* A Saucepan (helmet) - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
                               
void
create_armour()
{
    set_name("saucepan");
    set_short("iron saucepan");
    add_pname("armours");
    set_long("It's a large piece of cooking equipment with a " +
        "long handle. It would probably fit over your head.\n");
    
    set_adj("iron");
    
    set_ac(9);

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({   1,   0,   -1}));
    set_at(A_HEAD);
    
    
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 300);
}
