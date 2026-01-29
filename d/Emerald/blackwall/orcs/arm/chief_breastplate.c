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
    set_name("breastplate");
    set_short("rippled black breastplate");
    set_adj(({"steel", "rippled", "black"}));
    set_long("A large breatplate forged from some kind of blackened steel. "+
	     "The breastplate has been carefully crafted so that it "+
	     "appears that it is rippled with muscles. Use reveals that "+
	     "these same ripples are advantageous in deflecting glancing "+
	     "blows.\n");       
    set_ac(38);   

    /* Set impale, slash, bludgeon, modifiers.  */
    set_am(({ -1, 2, -1}));
    set_at(A_BODY);
    
    add_prop(OBJ_I_WEIGHT, 7200);
    add_prop(OBJ_I_VOLUME, 6400);
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(38) + 100 + random(200)));
}

