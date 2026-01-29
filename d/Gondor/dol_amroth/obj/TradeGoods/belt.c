/* -*- Mode: C -*-
 *
 * belt.c
 *
 * A belt to be sold in Dol Amroth.
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
    set_name("belt");
    add_adj("leather");
    set_short("leather belt");
    set_pshort("leather belts");
    set_long("This is a leather belt with a cast iron buckle picting a " +
	     "white tree with seven stars above it.\n");

    set_slots(A_WAIST);
    set_layers(0);
    set_looseness(10);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME,   50);
    add_prop(OBJ_I_VALUE,  50);
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

