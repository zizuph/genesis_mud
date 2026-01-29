/*
 * winter coat
 *
 * wool
 */

#include "local.h"
#include <wa_types.h>

inherit CLOTHING;

public void
create_clothing()
{
    set_name("coat");
    set_adj("winter");
    add_adj("fur-lined");

    set_slots(A_TORSO | A_WAIST | A_ARMS);

    set_layers(4);
    set_looseness(3);

    set_short("@@query_colour@@ fur-lined @@query_fabric@@ winter coat");

    set_long("This is a warm winter coat of @@query_fabric@@, dyed " +
    "@@query_colour@@ and lined with fur. The coat looks as if it " +
    "will keep out the fiercest of winter storms.\n");
}


