/*
 * A chainmail for the arena of Calathin.
 * Coded by Shinto 7-20-99
 *
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("chainmail");
    set_short("steel chainmail");
    set_adj(({"steel", "shirt"}));
    set_long("A shirt of steel chainmail. Light armour providing "+
                  "some protection.\n");

    set_default_armour(30, A_BODY, 0, 0);
    
    add_prop(OBJ_I_VALUE,            200);
    add_prop(OBJ_I_WEIGHT,          1250);
}
