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
    set_name("helmet");
    add_name("helm");
    set_short("great horned helmet");
    set_adj(({"steel", "great", "black", "horned", "blackened"}));
    set_long("A great helmet made of a blackened steel. Two six inch long "+
	     "ivory horns have been affixed into its sides. Additional "+
	     "plates of steel hand down the side to protect the wearers "+
	     "cheeks, though the face is otherwise open, allowing "+
	     "excellently visibility considering the protection this "+
	     "helmet would offer.\n");       
    set_ac(39);   

    add_item(({"horns", "ivory horns"}),
	     "The horns affixed to the helmet are over half a foot in "+
	     "length and perhaps an inch in diamater at their base. They "+
	     "are made of ivory providing a ghastly contrast with the "+
	     "blackened steel of which the helm is fabricated. You can "+
	     "only guess what manner of beast might have once been "+
	     "possessed if those horns.\n");

    /* Set impale, slash, bludgeon, modifiers.  */
    set_am(({-3,  3,  0}));
    set_at(A_HEAD);
    
    add_prop(OBJ_I_WEIGHT, 3750);
    add_prop(OBJ_I_VOLUME, 3150);
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(39) + random(100)));
}

