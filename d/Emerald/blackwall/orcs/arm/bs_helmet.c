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
    set_short("black steel helmet");
    set_adj(({"steel", "black", "blackened"}));
    set_long("A helmet made of a blackened steel. It is of solid "+
	     "construction and would provide good protection for your "+
	     "head during battle.\n");
       
    set_ac(34);   
    /* Set impale, slash, bludgeon, modifiers.  */
    set_am(({2, 0,- 2}));
    set_at(A_HEAD);
    
    set_likely_cond(8);
    set_likely_break(8);
    set_condition(1 + random(4)); // need not be prime

    add_prop(OBJ_I_WEIGHT, 3200);
    add_prop(OBJ_I_VOLUME, 2900);
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(34) - 50 - random(100)));
}

