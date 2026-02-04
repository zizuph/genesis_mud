/* A pair of sandals. Mortricia 920722 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name(({"sandals", "pair of sandals"}));
    set_pname("pairs of sandals");
    set_short("pair of plain sandals");
    set_pshort("pairs of plain sandals");
    set_long("It's a pair of plain sandals. They look used.\n");
    set_adj(({"plain"}));

    set_default_armour(3, A_FEET, 0, 0);
}
