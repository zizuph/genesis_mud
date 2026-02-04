/*
   A blue cloak, suitable for a prince. Mortricia 920722
 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include <wa_types.h>

create_terel_armour()
{
    set_name("cloak");
    set_short("blue cloak");
    set_long("It's a blue cloak with silver linings.\n");
    set_adj(({"blue"}));

    set_default_armour(20, A_ROBE, 0, 0);
    set_am(({ -2, 0, 2}));
}
