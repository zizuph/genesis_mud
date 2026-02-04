/*
 * Shan Jin's Tunic
 * Goldberry May, 2000
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("tunic");
    set_pname("tunics");
    set_pshort("dark leather tunics");
    set_short("dark leather tunic");
    set_long("A dark leather tunic.\n");
    set_adj(({"dark","leather"}));

    set_default_armour(35, A_BODY, 0, 0);
    set_am(({ -2, 0, 2}));
}
