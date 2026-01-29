/* An Iron Ringmail - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("ringmail");
    set_pname("ringmails");  
    add_pname("armours");
    set_short("iron ringmail");
    set_pshort("iron ringmails"); 
    set_long("It's a set of iron ringmail, which can be worn "  
        + "over your shoulders. " 
        + "It looks like ordinary ringmail.\n");

    set_adj("iron");

    set_ac(17); /* Standard iron ringmail. */

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({  -1,   2,  -1}));
    set_at(A_BODY);
    
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 1000);
    
}
