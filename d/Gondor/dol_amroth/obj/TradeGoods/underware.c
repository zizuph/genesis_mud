/* -*- Mode: C -*-
 *
 * underware.c
 *
 * Some underware to be sold in Dol Amroth
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
    set_name("underwear");
    add_adj("warm");
    add_adj("woolen");
    add_adj("piece of");
    add_adj("piece");
    add_adj("red");
    set_short("piece of warm underwear");
    set_pshort("pieces of warm underwear");
    set_long("This is a piece of warm underwear. It is made out of wool, " +
	     "and dyed red.\n");

    set_slots(A_LEGS|A_BODY|A_ARMS);
    set_layers(0);
    set_looseness(0);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME,   50);
    add_prop(OBJ_I_VALUE,  45);

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
