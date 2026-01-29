/* -*- Mode: C -*-
 * skirt.c
 * 
 * A skirt to be sold on Dol Amroth.
 *
 * By Skippern 20(c)01
 */
inherit "/std/object";
inherit "/lib/wearable_items";

#include <stdproperties.h>
#include <wa_types.h>

private nomask void
create_object()
{
    set_name("skirt");
    add_adj("long");
    set_short("long skirt");
    set_pshort("long skirts");
    set_long("This is a long skirts. They folds nicely down, and " +
	"are made out of heavy wool.\n");

    set_slots(A_LEGS);
    set_layers(1);
    set_looseness(0);

    add_prop(OBJ_I_WEIGHT, 550);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_VALUE,  350);
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

