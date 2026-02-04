/*
    A pair of blue boots. Mortricia 920722
 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name(({"boots", "pair of boots"}));
    set_pname("pairs of boots");
    set_short("pair of blue boots");
    set_pshort("pairs of blue boots");
    set_long("It's a pair of blue boots. They look almost new.\n");
    set_adj(({"blue"}));

    set_default_armour(15, A_FEET, 0, 0);
}
