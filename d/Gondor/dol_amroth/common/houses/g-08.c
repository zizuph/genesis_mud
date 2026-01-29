/*
 * common/houses/g-08.c
 *
 * By Skippern 20(c)02
 *
 */
#include "../../defs.h"

inherit DOL_STD + "inside";

create_inside()
{
    set_short("a small kitchen");
    set_long("This small kitchen seems to be the center of " +
	     "this home. In a corner a large stowe stands " +
	     "heating the room aswell as being where the food " +
	     "is prepared. Along a wall is cupboard stands " +
	     "holding several plates and cups.\n");

    add_item("cupboard", "A cupboard stand by a wall holding " +
	     "several plates and cups.\n");
    add_item( ({"cup", "cups" }), "");
    add_item( ({"plate", "plates" }), "");
    add_item( ({"stowe", "owen" }), "");
    //    add_item( ({"", "" }), "");

    clone_object(DOL_OBJ + "doors/g-08-door")->move(this_object());
}
