/*
 * boots.c
 * 
 * Black boots for Blademasters to wear.
 *
 * Khail - Mar 4/97
 */
#pragma strict_types

#include "defs.h"
#include <macros.h>

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

public int
is_blademaster_equipment()
{
    return 1;
}

public void
create_object()
{
    set_name("boots");
    add_name("clothing");
    add_name("pair of boots");
    set_pname("pairs of boots");
    add_pname("pairs of black boots");
    add_pname("pairs of leather boots");
    add_pname("pairs of black leather boots");
    add_pname("clothes");
    set_adj("black");
    add_adj("leather");
    set_short("pair of black leather boots");
    set_pshort("pairs of black leather boots");
    set_long("The black leather boots are very well made, " +
        "with stiches so fine they can barely be seen. " +
        "They've been polished well enough they shine " +
        "almost midnight blue, and the long shaft of " +
        "them have laces up the sides to fit snugly " +
        "to your lower leg.\n");

    config_wearable_item(A_FEET, 5, 5, TO);

    add_prop(OBJ_I_VALUE, 95);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_BLADEMASTER_ARM, 1);
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

/* Function name: appraise_object (MASK)
 * Description  : Appraise the object.
 * Arguments    : int num - The appraise number, randomized.
 * Returns      : n/a
 */

public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}
