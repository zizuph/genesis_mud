#include "../apothecary.h"

inherit APOTHECARY_VIAL;

#include <stdproperties.h>

public void
create_vial()
{
    set_medication_name("placebo");
    set_medication_id("placebo");
    set_medication_desc("white powder");
    add_default_desc();

    add_prop(HEAP_I_UNIT_VALUE, 100);
}
