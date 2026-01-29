/* created by Aridor  09/07/93 */

inherit "/std/food";
#include "/sys/stdproperties.h"

create_food()
{
    set_name("grains");
    set_pname("grains");
    set_adj("malt");
    set_short("handful of malt grains");
    set_pshort("handful of malt grains");
    add_name("malt");
    set_long("It's a handful of malt grains.\n");
    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VOLUME, 1);
    set_amount(10);
}
