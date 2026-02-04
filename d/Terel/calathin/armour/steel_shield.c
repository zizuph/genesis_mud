/*
 * A shield for the arena of Calathin.
 * Coded by Shinto 7-20-99
 *
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("shield");
    set_short("steel shield");
    set_adj(({"steel", "plate"}));
    set_long("A pair of steel shield. Light armour providing "+
                  "some protection.\n");

    set_default_armour(30, A_SHIELD, 0, 0);
    
    add_prop(OBJ_I_VALUE,            200);
    add_prop(OBJ_I_WEIGHT,          800);
}
