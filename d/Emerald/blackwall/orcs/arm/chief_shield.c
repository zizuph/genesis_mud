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
    set_name("shield");
    set_short("heavy black shield");
    set_adj(({"steel", "black", "blackened", "heavy"}));
    set_long("A large and heavy shield forged out of black steel. It is "+
	     "square at the top, and rounded at the base of its close to "+
	     "one metre extent. Its solid steel form is gently curved to "+
	     "deflect blows rather than absorb the entirety of their "+
	     "impact. It looks capable of turning aside any blow ... in "+
	     "sufficiently strong and skilled hands.\n");       
    set_ac(40);   

    /* Set impale, slash, bludgeon, modifiers.  */
    set_am(({ 0, 0, 0}));
    set_at(A_SHIELD);
    
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 8200);
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(40) + random(100)));
}








