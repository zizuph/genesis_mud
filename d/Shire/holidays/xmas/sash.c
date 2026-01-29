/* Holiday belt of holly worn about the waist
 * -- Finwe, November 2001
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
    set_name("sash");
    add_adj(({"festive" ,"holiday"}));
    add_name("_shire_holly_sash_");
    set_short("festive holiday sash");
    set_long("This is a bright colored sash from spun cotton meant " +
        "to be worn around the waist. Fine holly leaves are " +
        "delicatly embroidered onto the sash. Red berries " +
        "accent the holly and leaves.\n");

    add_item(({"holy", "holly leaves"}),
        "The holly leaves are expertly embroidered onto the sash. " +
        "They look very real and are a deep green color. It is " +
        "considered magical and full of good luck.\n");
    add_item(({"berries", "holly berries"}),
        "The holly berries are ruby red and are expertly embroidered " +
        "between the holly leaves.\n");
    

    /* The sash can be worn about the waist only*/
    set_slots(A_WAIST);

    /* We won't make the sash take up any space around the waist.
     */
    set_layers(0);

    /* We allow layers to be worn under the head */
    set_looseness(2);

    set_keep(1); 

    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 150);

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

