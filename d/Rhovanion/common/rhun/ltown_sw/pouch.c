/*
 * Rhosgobel quest item-- pouch.
 * Found in /d/Rhovanion/common/rhun/ltown_sw/pouch.c
 * Sold in the shop in Large Town SW in Rhun.
 *
 * Adapted from the bag by Nick/Mercade, found in
 * /doc/examples/obj/bag.c
 * 
 * -- Farlong, 11 April 1994
 */

inherit "/std/receptacle";

#include <stdproperties.h>

void
create_container()
{
	set_name("pouch");
    set_adj("small");
	add_adj("leather");
	add_name("_rhosgobel_quest_pouch");
	set_long(break_string("This small leather pouch seems"
		+" to have some strange qualities to it.\n",75));

    add_prop(CONT_I_WEIGHT, 250); 	/* It weights 250 grams */
    add_prop(CONT_I_MAX_WEIGHT, 2250); 	/* It can hold 2000 grams of weight. */
    add_prop(CONT_I_VOLUME, 30); 	/* Only 30 ml volume (very small) */
    add_prop(CONT_I_MAX_VOLUME, 2030); 	/* 2 litres of volume */

    add_prop(OBJ_I_VALUE, 40); 		/* Worth 40 cc */

	add_prop(CONT_M_NO_INS,1); /* Don't put anything in it! */
}
