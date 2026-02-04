/*
 *
 * blackened steel greaves 
 * Goldberry February 2000
 *
 */


#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name(({"greaves","pair of greaves"}));
    set_pname("pairs of greaves");
    set_short("pair of blackened steel greaves");
    set_pshort("pairs of blackened steel greaves");
    set_adj(({"blackened", "steel"}));
    set_long("A pair of steel greaves, light weight and providing a good "+
             "amount of protection.\n");
    set_armour_size(ANY_SIZE);
    set_default_armour(40, A_LEGS, 0, 0);
    
    add_prop(OBJ_I_VALUE,            700);
    add_prop(OBJ_I_WEIGHT,          350);
}

