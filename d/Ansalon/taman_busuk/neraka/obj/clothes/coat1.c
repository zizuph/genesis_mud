/*
 * riding coat
 *
 * linen, silk or velvet
 */

#include "local.h"
#include <wa_types.h>

inherit CLOTHING;

public void
create_clothing()
{
    set_name("coat");
    set_adj("riding");

    set_slots(A_TORSO | A_WAIST | A_ARMS);

    set_layers(2);
    set_looseness(3);

    set_short("@@query_colour@@ @@query_fabric@@ riding coat");

    set_long("A stylish riding coat of @@query_fabric@@, " +
    "@@query_colour@@ of the colour. The coat is split in the back " +
    "to facilitate riding.\n");
}


