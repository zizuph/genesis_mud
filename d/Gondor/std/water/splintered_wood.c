/*
 * /d/Gondor/std/water/splintered_wood.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * just a piece of wood that might once have been part of a boat
 */

#pragma strict_types

inherit "/std/heap";
#include <stdproperties.h>

public void	create_heap();

/*
 * Function name:	create_heap
 * Description	:	set up the splinters
 */
public void
create_heap()
{
    set_name( ({ "wood", "splinter", "piece" }) );
    set_adj( ({ "piece of", "splintered" }) );
    set_short("piece of splintered wood");
    set_pshort("pieces of splintered wood");
    set_long("The wood is too badly splintered to be of use.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 454);	/* 1 lb */
    add_prop(OBJ_I_VOLUME, 4719);	/* 36 inches x 8 inches x 1 inch */
    add_prop(HEAP_S_UNIQUE_ID, "_boat_kindling_");
    set_heap_size(1);
} /* create_heap */
