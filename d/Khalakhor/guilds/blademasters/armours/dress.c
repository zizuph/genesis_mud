/*
 * dress.c
 * 
 * Black dress for female (hopefully) Blademasters to wear.
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
    set_name("dress");
    add_pname("clothing");
    add_pname("clothes");
    set_adj("heavy");
    add_adj("black");
    set_short("black heavy dress");
    set_long("The "+short()+" is made of wool, and almost " +
      "uncomfortably warm. It's a fairly simple design, yet " +
      "not unflattering with tight-fitting sleeves and " +
      "top, but the ankle-length of the dress is split up " +
      "either side to mid-thigh to allow for a greater freedom " +
      "of movement. The hem of the dress is embroidered with " +
      "intricate thistles in blue thread.\n");

    set_slots(A_LEGS | A_WAIST | A_TORSO);
    set_layers(1);
    set_looseness(2);

    add_prop(OBJ_I_VALUE, 120);
    add_prop(OBJ_I_WEIGHT, 4000);
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
