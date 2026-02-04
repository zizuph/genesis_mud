/* 
 *  A breeches for Calathin citizens.
 *  By Shinto 11-2-98
 *  modified by Tomas for use with the Farms
 */
#include "/d/Terel/include/Terel.h"
inherit STDWEARABLE;

#include <wa_types.h>
#include <stdproperties.h>

public void
create_terel_wearable_item()
{
    set_name("breeches");
    set_short("pair of dirty grey breeches");
    set_pshort("pairs of dirty grey breeches");
    set_adj("grey");
    set_adj("dirty");
    set_long("A "+short()+" mostly worn by the working class.\n");

    /* The hat is worn on the head */
    set_slots(A_LEGS);
    set_terel_wearable_item_size(MEDIUM);

    set_layers(1);
    set_looseness(1);

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_VALUE,   50);
}

/*
 * We need to override leave_env() so that we can be sure to
 * remove the hat if it gets moved from the wearer while it
 * is still worn.
 */
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}
