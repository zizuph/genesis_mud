/*
 * Leather armour for the guards in Calathin.
 * Coded by Shinto 10-10-98
 *
 */


#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("armour");
    set_short("leather armour");
    set_adj(({"leather"}));
    set_long("A shirt of leather which is light and provides a small "+
             "amount of protection.\n");

    set_default_armour(20, A_BODY, 0, 0);
    
    add_prop(OBJ_I_VALUE,            150);
    add_prop(OBJ_I_WEIGHT,          800);
}
