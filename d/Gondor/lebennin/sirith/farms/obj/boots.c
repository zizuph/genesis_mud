/*
 * /d/Gondor/lebennin/sirith/farms/obj/boots
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 */

#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>			/* for A_FEET 		*/
#include <stdproperties.h>		/* for OBJ_I_*		*/
#include <formulas.h>			/* for F_VALUE_ARMOUR	*/

public void	create_armour();

/*
 * Function name:	create_armour
 * Description	:	set up the boots
 */
public void
create_armour()
{
    set_name( ({ "pair of boots", "boots", "armour" }) );
    set_adj( ({ "farm", "leather", "sturdy", "muddy" }) );
    set_short("pair of sturdy boots");
    set_pshort("pairs of sturdy boots");
    set_long("The pair of sturdy farm boots is very muddy.\n");
    set_default_armour(5, A_FEET | A_ANKLES, (({ -1, 1, 0})), 0);
    add_prop(OBJ_I_WEIGHT, 360);   /* 260 gram */
    add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5)+random(20));
} /* create_armour */
