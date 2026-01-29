/* Leg armour worn by orcs. (~blackwall/orcs/npc)
   Code (c) 2000 to Damian Horton, BKA Casimir.
*/

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/std/armour";

void
create_armour()
{
    set_name("greaves");
    set_short("chainmail greaves");
    set_adj(({"chainmail"}));
    set_long("Steel chainmail greaves, with a tarnished and "+
	     "ill-maintained appearance.\n");       
    set_ac(25);   

    /* Set impale, slash, bludgeon, modifiers.  */
    set_am(({ -2, 3, -1}));
    set_at(A_LEGS);
    
    set_likely_cond(15);
    set_likely_break(10);
    set_condition(2 + random(4)); // need not be prime

    add_prop(OBJ_I_WEIGHT, 4100);
    add_prop(OBJ_I_VOLUME, 7900);
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(25) - 50 -  random(100)));
}

