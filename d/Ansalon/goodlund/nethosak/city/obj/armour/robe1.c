/*
 * Cowled robe
 *
 * wool or linen
 */

#include "/d/Ansalon/taman_busuk/neraka/obj/clothes/local.h"
#include <wa_types.h>

inherit CLOTHING;

public void
create_clothing()
{
    set_name("robe");
    set_adj("cowled");

    set_slots(A_ROBE);

    set_layers(4);
    set_looseness(6);

    set_short("@@query_colour@@ cowled @@query_fabric@@ robe");

    set_long("This is a heavy robe of @@query_colour@@ @@query_fabric@@. " +
    "A cowl covers the head of the wearer. The robe is of high quality.\n");
}


