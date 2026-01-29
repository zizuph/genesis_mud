/* created by Aridor  09/07/93 */

inherit "/std/food";
#include "/sys/stdproperties.h"

create_food()
{
    set_name("earthworm");
    set_pname("earthworm");
    set_adj("little");
    set_short("little earthworm");
    set_long("It's a yucky little worm. You wonder what you can do with it?\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 10);
    set_amount(1);
}
