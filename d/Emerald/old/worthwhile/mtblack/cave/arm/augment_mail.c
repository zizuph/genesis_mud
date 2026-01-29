/* An Augmented Mail - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("mail");
    add_name("armour");
    add_pname("armours");
    set_short("augmented mail");
    set_long("It's a set of bronze augmented mail, which "  
        + "consists of chainmail with metal strips woven through the links, " 
        + "to make it more effective.\n");

    set_adj("augmented");
    add_adj("bronze");

    set_ac(33); /* -1 for being bronze. */

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({  -1,   1,   0}));
    set_at(A_BODY);
    
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 3000);
}
