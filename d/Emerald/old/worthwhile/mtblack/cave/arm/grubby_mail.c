/* A Grubby Chainmail - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("chainmail");
    set_pname("chainmails");
    add_pname("armours");
    set_short("grubby chainmail");
    set_pshort("grubby chainmails"); 
    set_long("It's chainmail, which can be worn as armour."  
	+ "It's rather grubby, and it smells a little bit.  " 
	+ "It looks like it could stop you getting hurt.\n");

    set_adj("grubby");

    set_ac(15);

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({ 1, 1, -2}));
    set_at(A_BODY);
    
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 500);
    
}
