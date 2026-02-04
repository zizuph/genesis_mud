/* 
 *  A pair of boots for Calathin citizens.
 *  By Shinto 11-2-98
 *  Modified for use with the Farms  -- Tomas Nov. 1999
 */
#include "/d/Terel/include/Terel.h"
inherit STDWEARABLE;

#include <wa_types.h>
#include <stdproperties.h>

public void
create_terel_wearable_item()
{
    set_name("boots");
    set_short("pair of worn muddy grey boots");
    set_pshort("pairs of grey boots");
    set_adj("grey");
    set_adj("worn");
    set_adj("muddy");
    set_long("A "+short()+" mostly worn by the working class.\n");

 
    set_slots(A_FEET);
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
