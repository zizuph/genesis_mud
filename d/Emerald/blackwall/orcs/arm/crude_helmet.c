/* Helmet worn by orcs. (~blackwall/orcs/npc)
   Code (c) 2000 to Damian Horton, BKA Casimir.
*/

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/std/armour";

void
create_armour()
{
    set_name("helmet");
    add_name("helm");
    set_short("crude iron helmet");
    set_adj(({"crude", "iron"}));
    set_long("A crudely manufactured helmet made of unrefined iron. It "+
	     "doesn't look pretty, but it would provide adequate "+
	     "protection for your noggin nontheless.\n");
       
    set_ac(28);   
    /* Set impale, slash, bludgeon, modifiers.  */
    set_am(({2, 1, -3}));
    set_at(A_HEAD);

    set_likely_cond(20);
    set_likely_break(15);
    set_condition(random(6)); // need not be prime

    add_prop(OBJ_I_WEIGHT, 2900);
    add_prop(OBJ_I_VOLUME, 2900);
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(26) - 100 - random(100)));
}



