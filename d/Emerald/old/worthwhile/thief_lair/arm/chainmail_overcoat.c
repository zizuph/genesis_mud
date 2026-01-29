/* A fine piece of armour worn by Televanar (../thief_lair/npc/televanar.c)
   Code (c) Damian Horton (BKA Casimir) 1999.
*/

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/std/armour";

void
create_armour()
{
    set_name("overcoat");
    add_name("armour");
    set_short("elven chainmail overcoat");
    set_long("Light and nearly untarnishable, this magnificent piece of "+
	     "armour was almost certainly the product of a master elven "+
	     "smith. The overcoat covers the entirety of one's upper "+
	     "torso and the better part of ones arms. Due to the unusually "+
	     "flexible nature of its construction, it can simply be "+
	     "pulled over one's head like a tunic.\n");

    set_adj("elven");
    add_adj("chainmail");
       
    set_ac(32);   

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({  -2,   3,  -1}));
    set_at(A_BODY | A_R_ARM | A_L_ARM);
    
    add_prop(OBJ_I_WEIGHT, 6900);
    add_prop(OBJ_I_VOLUME, 4500);
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(32) + 200 + random(300)));
}

