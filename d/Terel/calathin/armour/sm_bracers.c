/*
 * blackened steel bracers for Sliver
 * Coded by Shinto 011900
 */


#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name(({"bracers","pair of bracers"}));
    set_pname("pairs of bracers");
    set_short("pair of blackened steel bracers");
    set_pshort("pairs of blackened steel bracers");
    set_adj(({"blackened", "steel"}));
    set_long("A pair of steel bracers, light weight and providing a good "+
             "amount of protection.\n");
    set_armour_size(ANY_SIZE);
    set_default_armour(35, A_ARMS, 0, 0);
    
    add_prop(OBJ_I_VALUE,            700);
    add_prop(OBJ_I_WEIGHT,          350);
}
