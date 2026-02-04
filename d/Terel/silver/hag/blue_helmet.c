/*
    A blue helmet, suitable for a prince. Mortricia 920722
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("helmet");
    set_short("blue helmet");
    set_long("A blue helmet of good quality.\n");
    set_adj(({"blue"}));

    set_default_armour(25, A_HEAD, 0, 0);
    set_am(({ 4, 2, -6}));
}
