/* A steel shield - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
                               
void
create_armour()
{
    set_name("shield");
    set_short("steel shield");
    add_pname("armours");
    set_long("It's a medium sized steel shield. Its very heavy "  
        + "though, as it is very thick.\n");

    add_adj("steel");
    
    set_ac(27); /* +2 steel. */

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({   0,   0,    0}));
    set_at(A_SHIELD);
    
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 1000);
}
