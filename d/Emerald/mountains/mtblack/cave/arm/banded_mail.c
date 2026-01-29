/* Banded torso armour - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
                               
void
create_armour()
{
    set_name("mail");
    set_pname("mails");
    add_pname("armours");
    set_short("banded torso mail");
    set_pshort("banded torso mails");
    set_long("It's a set of steel plates that overlap to "  
        + "provide good protection for the wearer. It looks quite heavy, " 
        + "but looks like very good armour.\n");

    set_adj("torso");
    add_adj("banded");
    add_adj("steel");
    
    set_ac(39); /* +2 for being steel. */

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({   0,   0,   0}));
    set_at(A_BODY);
    
    add_prop(OBJ_I_WEIGHT, 12000);
    add_prop(OBJ_I_VOLUME, 4000);
}
