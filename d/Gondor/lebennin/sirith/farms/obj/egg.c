/*
 * /d/Gondor/lebennin/sirith/farms/obj/egg.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>	/* for OBJ_I_*		*/

public void	create_food();

/*
 * Function name:	create_food
 * Description	:	set up the egg
 */
public void
create_food()
{
    set_name("egg");
    add_adj( ({ "brown", "speckled" }) );
    set_short("speckled brown egg");
    set_long("The speckled brown egg is not very large.\n");
    set_amount(50); /* 50 grams of food. */
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 75);
    add_prop(OBJ_I_VALUE, 5);
} /* create_food */

