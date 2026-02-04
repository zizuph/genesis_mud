/*
 * black velvet cloak
 * Goldberry February, 2000
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("cloak");
    set_pname("cloaks");

    set_short("black velvet cloak");
    set_pshort("black velvet cloaks");
    set_long("A black cloak made from plush velvet.\n");
    set_adj(({"black","velvet"}));

    set_armour_size(SMALL);
    set_default_armour(30, A_ROBE, 0, 0);
    add_prop(OBJ_I_WEIGHT,          650);
    add_prop(OBJ_I_VOLUME,          400);
    set_am(({ -2, 0, 2}));
}
