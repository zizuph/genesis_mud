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
    set_name("coat");
    add_name("chainmail");
    set_short("tarnished chainmail coat");
    set_adj(({"tarnished", "chainmail"}));
    set_long("A chainmail coat which protects both arms and torso. It has "+
	     "a dirty appearance and does not appear to have been well "+
	     "maintained.\n");       
    set_ac(25);   

    /* Set impale, slash, bludgeon, modifiers.  */
    set_am(({ -2, 3, -1}));
    set_at(A_BODY | A_ARMS);
    
    set_likely_cond(15);
    set_likely_break(10);
    set_condition(2 + random(4)); // need not be prime
    
    add_prop(OBJ_I_WEIGHT, 9200);
    add_prop(OBJ_I_VOLUME, 9800);
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(25) + 50 + random(100)));
}




