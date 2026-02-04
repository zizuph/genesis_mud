/* A pair of leggingss. Mortricia 920722 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name(({"leggings", "pair of leggings"}));
    set_pname("pairs of leggings");
    set_short("pair of plain leather leggings");
    set_pshort("pairs of plain leather leggings");
    set_long("It's a pair of plain leather leggings. They look used.\n");
    set_adj(({"plain", "leather"}));

    set_default_armour(5, A_LEGS, 0, 0);
}
