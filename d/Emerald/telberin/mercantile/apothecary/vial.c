#include "apothecary.h"

inherit "/std/heap";
inherit APOTHECARY_MEDICATION;

#include <stdproperties.h>

public void
create_vial()
{
}

public void
add_default_desc()
{
    set_short("vial of " + query_medication_desc());
    set_pshort("vials of " + query_medication_desc());
    set_name("vial");
    set_pname("vials");
}

nomask public void
create_heap()
{
    add_prop(HEAP_I_UNIT_WEIGHT, 10);
    add_prop(HEAP_I_UNIT_VOLUME, 10);

    set_heap_size(1);

    create_vial();

    add_prop(HEAP_S_UNIQUE_ID, "_telberin_apothecary_vial_" +
        query_medication_id());
}
