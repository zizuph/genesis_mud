#include "local.h"
#include <wa_types.h>

inherit CLOTHING;

public void
create_clothing()
{
    set_name("robe");

    set_slots(A_ROBE);

    set_long("This is a robe, @@query_colour@@ of the colour and made " +
    "out of @@query_fabric@@.\n");
}


