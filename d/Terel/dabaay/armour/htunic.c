/*
 * black velvet tunic 
 * Goldberry February, 2000
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("tunic");
    set_pname("tunics");
    set_short("black velvet tunic");
    set_adj(({"black","velvet"}));
    set_pshort("black velvet tunics");
    set_long("A tunic made of plush black velvet.\n");

    set_armour_size(SMALL);
    set_default_armour(32, A_BODY, 0, 0);
    set_am(({ -2, 0, 2}));
    add_prop(OBJ_I_WEIGHT,          550);
    add_prop(OBJ_I_VOLUME,          300);
    add_prop(OBJ_I_VALUE,          1300);
}
