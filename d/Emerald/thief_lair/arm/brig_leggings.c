/* A pair of Brigandine Leggings - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("leggings");
    set_pname("pairs of leggings");
    add_pname("armours");
    set_short("pair of brigandine leggings");
    set_pshort("pairs of brigandine leggings");
    set_long("It's a pair of brigandine leggings that are "  
        + "made from metal scales which have been backed by leather.\n");

    set_adj("brigandine");
    add_adj("pair of");
    
    set_ac(23); /* standard brigandine leggings, no mod. */

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({   1,   1,   -2}));
    set_at(A_LEGS);
    
    add_prop(OBJ_I_WEIGHT, 7100);
    add_prop(OBJ_I_VOLUME, 2000);
}
