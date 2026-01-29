/*
 * glovess.c
 * 
 * Black gloves for Blademasters to wear.
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
    set_name("gloves");
    add_name("clothing");
    add_name("pair of gloves");
    set_pname("pairs of gloves");
    add_pname("pairs of black leather gloves");
    add_pname("pairs of leather gloves");
    add_pname("clothes");
    add_pname("pairs of black leather gloves");
    set_adj("black");
    add_adj("leather");
    set_short("pair of black leather gloves");
    set_pshort("pairs of black leather glovess");
    set_long("The black leather gloves are well-crafted " +
        "with strong stitching and reinforced palms. The " +
        "inner portion of the fingers of the gloves look " +
        "like a sturdy lace, which provides protection, " +
        "while allowing a good sense of touch.\n");

    config_wearable_item(A_HANDS, 3, 5, this_object());

    add_prop(OBJ_I_VALUE, 65);
    add_prop(OBJ_I_WEIGHT, 250);
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
