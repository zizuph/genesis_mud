/*
 * dwarf_plate.c
 * Dwarven Platemail for the Body guard
 * Coded by Shinto 11-12-98
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <wa_types.h>

public void
create_terel_armour()
{
    set_name("platemail");
    set_short("dwarven platemail");
    set_adj("dwarven");
    set_long("Dwarven platemail, finely crafted from tempered "+
                   "steel. Thick plates to protected the body strapped "+
                   "with steel links.\n");
    set_armour_size(SMALL);

    set_default_armour(40, A_BODY, 0, 0);
    
    add_prop(OBJ_I_VALUE,            1000);
    add_prop(OBJ_I_WEIGHT,          10000);
}
