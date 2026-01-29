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
    set_name("shield");
    set_short("reinforced kite shield");
    set_adj(({"kite", "reinforced"}));
    set_long("A wooden kite shield, made of sturdy oak and reinforced "+
	     "with bands of iron.\n");       
    set_ac(27);   

    /* Set impale, slash, bludgeon, modifiers.  */
    set_am(({ 2, 0, -2}));
    set_at(A_SHIELD);

    set_likely_cond(12);
    set_likely_break(12);
    set_condition(random(6)); // need not be prime
    
    add_prop(OBJ_I_WEIGHT, 4400);
    add_prop(OBJ_I_VOLUME, 9200);
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(27) - random(50)));
}








