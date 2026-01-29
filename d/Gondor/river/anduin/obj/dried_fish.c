/*
 * /d/Gondor/river/anduin/obj/dried_fish.c
 *
 * A dried fish for the fishcamp.
 */

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* prototypes */
public void	create_food();


/*
 * Function name:	create_food
 * Description	:	set up the fish
 */
public void
create_food()
{
    set_name("fish");
    set_adj("dried");
    set_long(BSN("The fish has a leathery texture, and a strong "+
	"smell. It is perhaps a foot long."));

    set_amount(150);
    add_prop(OBJ_I_VALUE, 0);   /* food cannot be sold */
    add_prop(OBJ_I_VOLUME, 590);	/* 12 x 3 x 1 inch */
    add_prop(OBJ_I_WEIGHT, 454);	/* 1 lb */


    add_cmd_item( ({ "dried fish", "fish", }),
	"smell",
	BSN("The drying process seems to have intensified the "+
	    "aroma of the fish."));
} /* create_food */
