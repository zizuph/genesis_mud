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
    set_name("gauntlets");
    add_name("guards");
    set_short("blackened steel gauntlets");
    set_adj(({"steel", "blackened", "black", "arm", "plate"}));
    set_long("Arm guards consisting of plates of blackened steel "+
	     "overlapping with links of heavy chainmail. They appear "+
	     "to have been well made.\n");       
    set_ac(37);   

    /* Set impale, slash, bludgeon, modifiers.  */
    set_am(({ 1, 0, -1}));
    set_at(A_ARMS);
    
    add_prop(OBJ_I_WEIGHT, 3900);
    add_prop(OBJ_I_VOLUME, 3900);
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(37) + random(100)));
}

