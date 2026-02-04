/*
 */

#pragma strict_types

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>
#include <stdproperties.h>

void
create_terel_armour()
{
    set_name("boots");
    set_short("pair of black boots");
    set_pshort("pairs of black boots");
    set_long("It's a black boots with grey linings.\n");
    set_adj(({"black"}));
    add_prop(OBJ_I_WEIGHT, 500);
    set_armour_size(MEDIUM);

    set_default_armour(20, A_FEET, 0, this_object());
}

