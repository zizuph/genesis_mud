#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <composite.h>

inherit "/std/container";
inherit "/lib/wearable_item";

void
create_container()
{
	set_name("overcoat");
	add_name("coat");
	add_name("pocket");
	add_name("pockets");
	set_adj(({"threadbare","black"}));
	set_short("threadbare black overcoat");
	set_long("The glory days has passed this coat by. " +
	"There is much of the frayed collar and worn hems " +
	"about it. The fabric is torn in places, and the " +
	"once black colour is now a washed out grey.\n");

	add_prop(CONT_I_WEIGHT, 2000);
	add_prop(CONT_I_VOLUME, 3000);
	add_prop(CONT_I_MAX_WEIGHT, 3000);
	add_prop(CONT_I_MAX_VOLUME, 4000);
	add_prop(CONT_I_HOLDS_COMPONENTS, 1);

	set_slots(A_CHEST | A_ARMS | A_WAIST | A_NECK);

	set_layers(3);
	set_looseness(12);

	add_prop(OBJ_I_VALUE, 0);
}

void
leave_env(object from, object to)
{
	wearable_item_leave_env(from, to);
	::leave_env(from, to);
}

/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    if (sizeof(obarr) > 0)
    {
        for_obj->catch_tell("The pockets of the " + this_object()->short() +
            " contains " + COMPOSITE_DEAD(obarr) + ".\n");
    }
    else
    {
        for_obj->catch_tell("  " + "The pockets of the " + this_object()->short() +
            " are empty.\n");
    }
}
