/*
 * pumps.c
 *
 * Pumps to be sold in Dol Amroth
 *
 * By Skippern 20(c)01
 */
inherit "/std/object";
inherit "/lib/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

private nomask void
create_object()
{
    set_name("pumps");
    add_name("shoes");
    add_adj("red");
    set_short("pair of red pumps");
    set_pshort("pairs of red pumps");
    set_long("This is a pair of pumps. They are made out of red velvet.\n");

    set_slots(A_FEET);

    set_layers(1);
    set_looseness(0);

    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, 175);
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
