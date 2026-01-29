/*
 * clerical robe
 *
 * linen, silk or velvet
 */

#include "local.h"
#include <wa_types.h>

inherit CLOTHING;

public void
create_clothing()
{
    set_name(({"cowled robe","robe"}));
    set_adj("cowled");

    set_slots(A_ROBE);

    set_layers(4);
    set_looseness(56);

    set_long("This is a heavy robe of @@query_colour@@ @@query_fabric@@. " +
    "A cowl covers the head of the wearer. The robe is of high quality.\n");
}


