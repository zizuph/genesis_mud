/*
   A blue cloak, suitable for a prince. Mortricia 920722
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("tunic");
    set_short("black tunic");
    set_long("It's a black tunic with grey linings.\n");
    set_adj(({"black"}));

    set_default_armour(20, A_BODY, 0, 0);
    set_am(({ -2, 0, 2}));
}
