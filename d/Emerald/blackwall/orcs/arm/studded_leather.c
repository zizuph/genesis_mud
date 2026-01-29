/* Armour worn by orcs. (~blackwall/orcs/npc)
   Code (c) 2000 to Damian Horton, BKA Casimir.
*/

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/std/armour";

void
create_armour()
{
    set_short("studded leather armour");
    set_adj(({"studded", "leather"}));
    set_long("Body armour composed of hardened leather fitted with iron "+
	     "rivets. It is smelly and ill-kept.\n");       
    set_ac(15);   

    /* Set impale, slash, bludgeon, modifiers.  */
    set_am(({0, 1, -1}));
    set_at(A_BODY);

    set_likely_cond(12);
    set_likely_break(10);
    set_condition(0); // need not be prime
    
    add_prop(OBJ_I_WEIGHT, 4200);
    add_prop(OBJ_I_VOLUME, 7500);
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(15) + random(75)));
}



