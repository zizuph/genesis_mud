#pragma strict_types

inherit "/std/heap.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_heap()
{
    set_name("nail");
    set_long(BSN("This is an iron nail like it is used for building "
        + "wooden houses. It is quite thick and about 8 inches "
        + "long."));
    set_short("iron nail");
    set_pshort("iron nails");

    set_adj( ({ "iron", "long", "thick", }) );

    add_prop(HEAP_S_UNIQUE_ID,   "thick iron nail");
    add_prop(HEAP_I_UNIT_VALUE,    12);
    add_prop(HEAP_I_UNIT_WEIGHT,  120);
    add_prop(HEAP_I_UNIT_VOLUME,   20);

    set_heap_size(1);
}
