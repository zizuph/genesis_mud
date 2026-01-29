/*
 * /d/Gondor/lebennin/sirith/farms/obj/plum.c
 * 
 * Copyright (C) 1997 Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>	/* for OBJ_I_*		*/

public void	create_food();

/*
 * Function name:	create_food
 * Description	:	set up the plum
 */
public void
create_food()
{
    set_name("plum");
    set_adj("purple");
    set_adj("glossy");
    set_short("glossy purple plum");
    set_long("The plum's skin is purple with blue highlights.\n");
    set_amount(50);
    add_prop(OBJ_I_WEIGHT, 170);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 5);
} /* create_food */
