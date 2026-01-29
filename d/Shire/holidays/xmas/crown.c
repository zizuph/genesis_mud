/* Holiday crown of ivy worn on the head
 * June 1999 by Finwe
 */

#pragma save_binary

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";


#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <wa_types.h>
#include "/d/Shire/sys/defs.h"

// Global Vars

void
create_object()
{
    set_name("crown");
    add_adj(({"delicate" ,"festive"}));
    add_name("_shire_ivy_crown_");
    set_short("delicate festive crown");
    set_long("This is crown made up many ivy " +
        "sprigs, delicately woven together. It forms a crown that " +
        "can be worn on the head. Some believe ivy to be symbolic " +
        "of merriment and drinking, hence its holiday popularity.\n");

    add_item(({"ivy", "sprigs of ivy", "ivy sprigs"}),
        "The ivy sprigs are long and flexible. They are woven " +
        "together to form a crown that can be worn on the head. " +
        "The ivy is fresh and green.\n");

    /* The crown can be worn on the head only*/
    set_slots(A_BROW);

    /* We won't make the crown take up any space on the head.
     */
    set_layers(0);

    /* We allow layers to be worn under the head */
    set_looseness(2);

    set_keep(1); 

    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,  50);
    add_prop(OBJ_I_VALUE,   25);

}


/*
 * We need to override leave_env() so that we can be sure to remove
 * the anklet if it gets moved from the wearer while it is still worn.
 */
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    wearable_item_leave_env(env, to);
}

/*
 * We need to override appraise_object() so that we can be sure that the
 * player can appraise it properly.
 */
void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}


void
enter_env(object inv,object from)
{
    ::enter_inv(inv,from);

    if (!interactive(inv))
	return;
}

