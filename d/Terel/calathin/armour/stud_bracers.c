/*
 * Leather bracers for the guards of Calathin
 * Coded by Shinto 10-10-98
 */


#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("bracers");
    set_short("pair of studded leather bracers");
    set_adj(({"studded", "leather"}));
    set_long("A pair of studded leather bracers, light weight and providing a small "+
             "amount of protection.\n");

    set_default_armour(15, A_ARMS, 0, 0);
    
    add_prop(OBJ_I_VALUE,            125);
    add_prop(OBJ_I_WEIGHT,          400);
}
