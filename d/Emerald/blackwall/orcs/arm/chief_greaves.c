/* A fine piece of armour worn by Morognor. (~blackwall/orcs/npc)
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
    set_short("blackened steel greaves");
    set_adj(({"steel", "blackened", "black"}));
    set_long("Greaves consisting of plates of blackened steel covering "+
	     "dirty links of chainmail. They appear to be of a high "+
	     "quality.\n");       
    set_ac(36);   

    /* Set impale, slash, bludgeon, modifiers.  */
    set_am(({ 1, 0, -1}));
    set_at(A_LEGS);
    
    add_prop(OBJ_I_WEIGHT, 5100);
    add_prop(OBJ_I_VOLUME, 7800);
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(36) + random(100)));
}

