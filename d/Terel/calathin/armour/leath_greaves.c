/*
 * Leather greaves for the guards of Calathin
 * Coded by Shinto 10-10-98
 */


#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("greaves");
    set_short("pair of leather greaves");
    set_adj(({ "leather"}));
    set_long("A pair of leather greaves, light weight and providing a small "+
             "amount of protection.\n");

    set_default_armour(12, A_LEGS, 0, 0);
    
    add_prop(OBJ_I_VALUE,            100);
    add_prop(OBJ_I_WEIGHT,          350);
}
