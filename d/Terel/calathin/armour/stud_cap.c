/*
 * Leather cap for the guards of Calathin
 * Coded by Shinto 10-10-98
 */


#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("cap");
    set_short("studded leather cap");
    set_adj(({"studded", "leather"}));
    set_long("A studded leather cap to protect the head, not very good "+
             "protection.\n");

    set_default_armour(14, A_HEAD, 0, 0);
    
    add_prop(OBJ_I_VALUE,            100);
    add_prop(OBJ_I_WEIGHT,          350);
}
