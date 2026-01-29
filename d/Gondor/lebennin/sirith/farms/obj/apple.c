/*
 * /d/Gondor/lebennin/sirith/farms/obj/apple.c
 * 
 * Copyright (C) 1997 Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>	/* for OBJ_I_*	*/

public void	create_food();

/*
 * Function name:	create_food
 * Description	:	set up the apple
 */
public void
create_food()
{
    set_name("apple");
    set_adj("red");
    set_adj("shiny");
    set_short("shiny red apple");
    set_long("The apple is red with tiny yellow speckles.\n");
    set_amount(50);
    add_prop(OBJ_I_WEIGHT, 170);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 5);
} /* create_food */
