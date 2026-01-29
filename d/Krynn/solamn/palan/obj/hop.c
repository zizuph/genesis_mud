/* created by Aridor  09/07/93 */

inherit "/std/food";
#include "/sys/stdproperties.h"

create_food()
{
    set_name("leaf");
    add_name("hop");
    set_pname("leaves");
    set_adj("hop");
    set_short("bunch of hop leaves");
    set_long("These are some hop leaves.\n");
    add_prop(OBJ_I_WEIGHT, 3);
    add_prop(OBJ_I_VOLUME, 10);
    set_amount(10);
}
