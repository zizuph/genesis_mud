/*
 * shirt.c
 * 
 * Black shirt for Blademasters to wear.
 *
 * Khail - Mar 4/97
 */
#pragma strict_types

#include "defs.h"

inherit "/lib/keep";
inherit "/lib/wearable_item";
inherit "/d/Khalakhor/std/object";

public int
is_blademaster_equipment()
{
    return 1;
}

public void
create_khalakhor_object()
{
    set_name("shirt");
    add_pname("clothing");
    add_pname("clothes");
    set_adj("thick");
    add_adj("black");
    set_short("thick black shirt");
    set_long("The thick black shirt is well made, and thick "+
      "enough to be warm without a coat in most climates. " +
      "The shirt's collar bears no lapels, but laces high " +
      "covering the throat.\n");

    set_slots(A_BODY | A_ARMS);
    set_looseness(2);
    set_layers(1);

    add_prop(OBJ_I_VALUE, 120);
    add_prop(OBJ_I_WEIGHT, 1050);
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
