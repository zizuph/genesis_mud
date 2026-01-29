/* An Elven chainmail - Tulix III, recoded 13/07/95 */
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
    set_short("elven chainmail");
    set_pshort("elven chainmails");
    set_long("It's a steel chainmail. On closer inspection, "  
        + "you realise that it is probably Elven in origin. " 
        + "It looks better than normal chainmail.\n");

    set_adj("elven");
    add_adj("elf");
    add_adj("steel");  
    
    set_ac(28);  /* 25 +3 for elf made & steel */

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({  -2,   3,  -1}));
    set_at(A_BODY);
    
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 2000);

}
