/* A pair of boots. Mortricia 920722 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name(({"boots", "pair of boots"}));
    set_pname("pairs of boots");
    set_short("pair of plain boots");
    set_pshort("pairs of plain boots");
    set_long("It's a pair of plain boots. They look used.\n");
    set_adj(({"plain"}));

    set_default_armour(3, A_FEET, 0, 0);
}
